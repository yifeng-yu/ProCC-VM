#include "Machine.h"
#include <map>
#include <fstream>
#include <iostream>

Machine::Machine()
:bi(320,240)
,imgd(bi)
{
	// TODO
    bi.set_all_channels (0,0,0);
    imgd.pen_width(1);
    imgd.pen_color(255, 255, 255);
    opMap.emplace("movi", &CreateOp<MovI>);
    opMap.emplace("add", &CreateOp<Add>);
    opMap.emplace("exit", &CreateOp<Exit>);
    opMap.emplace("mov", &CreateOp<Mov>);
    opMap.emplace("sub", &CreateOp<Sub>);
    opMap.emplace("mul", &CreateOp<Mul>);
    opMap.emplace("div", &CreateOp<Div>);
    opMap.emplace("inc", &CreateOp<Inc>);
    opMap.emplace("dec", &CreateOp<Dec>);
    opMap.emplace("jmp", &CreateOp<Jmp>);
    opMap.emplace("cmpeq", &CreateOp<Cmpeq>);
    opMap.emplace("cmplt", &CreateOp<Cmplt>);
    opMap.emplace("jt", &CreateOp<Jt>);
    opMap.emplace("jnt", &CreateOp<Jnt>);
    opMap.emplace("push", &CreateOp<Push>);
    opMap.emplace("pop", &CreateOp<Pop>);
    opMap.emplace("load", &CreateOp<Load>);
    opMap.emplace("store", &CreateOp<Store>);
    opMap.emplace("loadi", &CreateOp<LoadI>);
    opMap.emplace("storei", &CreateOp<StoreI>);
    opMap.emplace("loadsc", &CreateOp<LoadSc>);
    opMap.emplace("storesc", &CreateOp<StoreSc>);
    opMap.emplace("penup", &CreateOp<Penup>);
    opMap.emplace("pendown", &CreateOp<Pendown>);
    opMap.emplace("fwd", &CreateOp<Fwd>);
    opMap.emplace("back", &CreateOp<Back>);
    
    for(int i = 0; i < 8; i++){
        regMap.emplace("r" + std::to_string(i), 0);
    }
    regMap.emplace("pc", 0);
    regMap.emplace("sc", 0);
    regMap.emplace("ex", 0);
    regMap.emplace("tx", 0);
    regMap.emplace("ty", 0);
    regMap.emplace("tr", 0);
    regMap.emplace("tc", 0);

    flagMap.emplace("exit", false);
    flagMap.emplace("test", false);
    flagMap.emplace("pen", false);
    
    // open the file

}

void Machine::readFile(const std::string& filename){
    std::ifstream file(filename);
    std::string line;
    while(true){
        std::getline(file,line);
        if(file.fail()){
            break;
        }
        const char delim = ' ';
        std::vector<std::string> retVal;

        size_t start = 0;
        size_t delimLoc = line.find_first_of(delim, start);
        while (delimLoc != std::string::npos)
        {
            retVal.emplace_back(line.substr(start, delimLoc - start));

            start = delimLoc + 1;
            delimLoc = line.find_first_of(delim, start);
        }

        retVal.emplace_back(line.substr(start));
        std::string opName = retVal[0];
        std::shared_ptr<Op> ptr;
        ptr = opMap.at(opName)();
        mOps.emplace_back(ptr);
        if(retVal.size() > 1){
            std::string params = retVal[1];
            ptr -> Parse(params);
        }
        
        

    }
}

void Machine::Execute(){
    
    std::ofstream outputFile("log.txt");
    std::ofstream stackOutputFile("stack.txt");
    while(!getFlag("exit")){
        for(int i = 0; i < 20; i++){
            outputFile << "*";
        }
        outputFile << std::endl;
        for(int i = 0; i < 8; i++){
            outputFile << "r" + std::to_string(i) << "=" << getReg("r" + std::to_string(i)) << std::endl;
        }
        outputFile << "pc=" << getReg("pc") << std::endl;
        outputFile << "sc=" << getReg("sc") << std::endl;
        outputFile << "ex=" << getReg("ex") << std::endl;
        outputFile << "tx=" << getReg("tx") << std::endl;
        outputFile << "ty=" << getReg("ty") << std::endl;
        outputFile << "tr=" << getReg("tr") << std::endl;
        outputFile << "tc=" << getReg("tc") << std::endl;
        outputFile << "exit=" << getFlag("exit") << std::endl;
        outputFile << "test=" << getFlag("test") << std::endl;
        outputFile << "pen=" << getFlag("pen") << std::endl;
        
        
        int pcValue = getReg("pc");
        stackOutputFile << "pc: " << pcValue << " Stack: ";
        for(int i = 0; i < stackVector.size(); i++){
            stackOutputFile <<stackVector[i] << " ";
        }
        stackOutputFile << std::endl;
        std::shared_ptr<Op> ptr = mOps[pcValue];
        setReg("pc", ++pcValue);
        try {
            ptr -> Execute(*this);
        } catch (NonFatalException& ne) {
            setReg("ex", ne.code);
        } catch (FatalException& e){
            setReg("ex", e.code);
            setFlag("exit", true);
        }
        
        outputFile << "Executing: " << ptr->GetName() << std::endl;
        if(getFlag("exit")){
            for(int i = 0; i < 20; i++){
                outputFile << "*";
            }
            outputFile << std::endl;
            for(int i = 0; i < 8; i++){
                outputFile << "r" + std::to_string(i) << "=" << getReg("r" + std::to_string(i)) << std::endl;
            }
            outputFile << "pc=" << getReg("pc") << std::endl;
            outputFile << "sc=" << getReg("sc") << std::endl;
            outputFile << "ex=" << getReg("ex") << std::endl;
            outputFile << "tx=" << getReg("tx") << std::endl;
            outputFile << "ty=" << getReg("ty") << std::endl;
            outputFile << "tr=" << getReg("tr") << std::endl;
            outputFile << "tc=" << getReg("tc") << std::endl;
            outputFile << "exit=" << getFlag("exit") << std::endl;
            outputFile << "test=" << getFlag("test") << std::endl;
            outputFile << "pen=" << getFlag("pen") << std::endl;
            if(getFlag("exit")){
                int pcValue = getReg("pc");
                stackOutputFile << "pc: " << pcValue << " Stack: ";
                for(int i = 0; i < stackVector.size(); i++){
                    stackOutputFile <<stackVector[i] << " ";
                }
                stackOutputFile << std::endl;
                break;
            }
        }
        
    
    }
    bi.save_image("output.bmp");
}

int Machine::getReg(std::string r){
    return regMap.at(r);
}
void Machine::setReg(std::string r, int v){
    regMap.at(r) = v;
}
bool Machine::getFlag(std::string f){
    return flagMap.at(f);
}
void Machine::setFlag(std::string r, bool v){
    flagMap.at(r) = v;
}
int Machine::popStack(){
    int size = getReg("sc");
    if( size == 0){
        throw FatalException(103);
    }
    
    int p = stackVector.back();
    stackVector.pop_back();
    setReg("sc", --size);
    return p;
}
void Machine::pushStack(int i){
    int size = getReg("sc");
    if(size >= 256){
        throw FatalException(101);
    }
    stackVector.emplace_back(i);
    setReg("sc", ++size);
}

int Machine::getStack(int i){
    if(i < 0 || i >= getReg("sc")){
        throw FatalException(100);
    }
    else {
        return stackVector[i];
    }
    
}
void Machine::setStack(int index, int v){
    if(index < 0 || index >= getReg("sc")){
        throw FatalException(100);
    }
    else {
        stackVector[index] = v;
    }
    
}

void Machine::setPenColor()
{
    int color = getReg("tc");

    if(color == 0){
        imgd.pen_color(255, 255, 255);
    }
    else if (color == 1){
        imgd.pen_color(255, 255, 0);
    }
    else if (color == 2){
        imgd.pen_color(255, 0, 255);
    }
    else if (color == 3){
        imgd.pen_color(255, 0, 0);
    }
    else if (color == 4){
        imgd.pen_color(0, 255, 255);
    }
    else if (color == 5){
        imgd.pen_color(0, 255, 0);
    }
    else if (color == 6){
        imgd.pen_color(0, 0, 255);
    }
    else if (color == 7){
        imgd.pen_color(0, 0, 0);
    }
}
void Machine::forward(std::string reg1){
    int reg = getReg(reg1);

    int tx = getReg("tx");
    int ty = getReg("ty");
    float angle = getReg("tr") * 0.0174533f;
    int endx = tx + static_cast<int>(std::cos(angle)*reg);
    int endy = ty + static_cast<int>(std::sin(angle)*reg);
    setPenColor();
    if(getFlag("pen")){
        imgd.line_segment(tx,ty,endx,endy);
    }
    setReg("tx", endx);
    setReg("ty", endy);
    
}

void Machine::backward(std::string reg1){
    int reg =  getReg(reg1);
    
    int tx = getReg("tx");
    int ty = getReg("ty");
    float angle = getReg("tr") * 0.0174533f;
    int endx = tx - static_cast<int>(std::cos(angle)*reg);
    int endy = ty - static_cast<int>(std::sin(angle)*reg);
    setPenColor();
    if(getFlag("pen")){
        imgd.line_segment(tx,ty,endx,endy);
    }
    setReg("tx", endx);
    setReg("ty", endy);
    
}

