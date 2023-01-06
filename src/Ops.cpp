#include "Ops.h"
#include "Machine.h"
#include "string"

void Exit::Execute(Machine& machine)
{
	// TODO
    machine.setFlag("exit", true);
}

void MovI::Execute(Machine& machine)
{
	// TODO
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (std::get<1>(mParameters) > 7 || std::get<1>(mParameters) < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), std::get<1>(mParameters));
    
}

void Add::Execute(Machine& machine)
{
    // TODO
    
    int sum = machine.getReg(std::get<1>(mParameters)) + machine.getReg(std::get<2>(mParameters));
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (sum > 7 || sum < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), sum);
    int64_t leftO = static_cast<int64_t>(machine.getReg(std::get<1>(mParameters)));
    int64_t rightO = static_cast<int64_t>(machine.getReg(std::get<2>(mParameters)));
    int64_t checkSum = leftO + rightO;
    if(checkSum > INT32_MAX){
        throw NonFatalException(12);
    }
    if(checkSum < INT32_MIN){
        throw NonFatalException(13);
    }
    
}

void Mov::Execute(Machine& machine)
{
    // TODO
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (machine.getReg(std::get<1>(mParameters)) > 7 || machine.getReg(std::get<1>(mParameters)) < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), machine.getReg(std::get<1>(mParameters)));
}

void Sub::Execute(Machine& machine)
{
    // TODO
    int sub = machine.getReg(std::get<1>(mParameters)) - machine.getReg(std::get<2>(mParameters));
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (sub > 7 || sub < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), sub);
    int64_t leftO = static_cast<int64_t>(machine.getReg(std::get<1>(mParameters)));
    int64_t rightO = static_cast<int64_t>(machine.getReg(std::get<2>(mParameters)));
    int64_t checkSub = leftO - rightO;
    if(checkSub > INT32_MAX ){
        throw NonFatalException(12);
    }
    if(checkSub < INT32_MIN){
        throw NonFatalException(13);
    }
    
}


void Mul::Execute(Machine& machine)
{
    // TODO
    int mul = machine.getReg(std::get<1>(mParameters)) * machine.getReg(std::get<2>(mParameters));
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (mul > 7 || mul < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), mul);
    int64_t leftO = static_cast<int64_t>(machine.getReg(std::get<1>(mParameters)));
    int64_t rightO = static_cast<int64_t>(machine.getReg(std::get<2>(mParameters)));
    int64_t checkMul = leftO * rightO;
    if(checkMul > INT32_MAX){
        throw NonFatalException(12);
    }
    if(checkMul < INT32_MIN){
        throw NonFatalException(13);
    }
   
}

void Div::Execute(Machine& machine)
{
    // TODO
    if(machine.getReg(std::get<2>(mParameters)) == 0){
        throw FatalException(102);
    }
    else{
        int div = machine.getReg(std::get<1>(mParameters)) / machine.getReg(std::get<2>(mParameters));
        if(std::get<0>(mParameters) == "sc"){
            throw NonFatalException(10);
        }
        if(std::get<0>(mParameters) == "r0"){
            throw NonFatalException(11);
        }
        if(std::get<0>(mParameters) == "tc" && (div > 7 || div < 0)){
            throw NonFatalException(14);
        }
        machine.setReg(std::get<0>(mParameters), div);
        int64_t leftO = static_cast<int64_t>(machine.getReg(std::get<1>(mParameters)));
        int64_t rightO = static_cast<int64_t>(machine.getReg(std::get<2>(mParameters)));
        int64_t checkDiv = leftO / rightO;
        if(checkDiv > INT32_MAX){
            throw NonFatalException(12);
        }
        if(checkDiv < INT32_MIN){
            throw NonFatalException(13);
        }
        
    }
    
}
void Inc::Execute(Machine& machine)
{
    // TODO
    int v = machine.getReg(std::get<0>(mParameters));
    ++v;
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (v > 7 || v < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), v);
    
    int64_t check = static_cast<int64_t>(v);
    if(++check > INT32_MAX){
        throw NonFatalException(12);
    }
    
    
}

void Dec::Execute(Machine& machine)
{
    // TODO
    int v = machine.getReg(std::get<0>(mParameters));
    --v;
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (v > 7 || v < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), v);
    
    int64_t check = static_cast<int64_t>(v);
    if(--check < INT32_MIN){
        throw NonFatalException(13);
    }
    
    
}

void Jmp::Execute(Machine& machine)
{
    // TODO
    machine.setReg("pc", machine.getReg(std::get<0>(mParameters)));
}

void Cmpeq::Execute(Machine& machine)
{
    // TODO
    if(machine.getReg(std::get<0>(mParameters)) == machine.getReg(std::get<1>(mParameters))){
        machine.setFlag("test", true);
    }
    else {
        machine.setFlag("test", false);
    }
    
}

void Cmplt::Execute(Machine& machine)
{
    // TODO
//    bool v = machine.getReg(std::get<0>(mParameters)) < machine.getReg(std::get<1>(mParameters));
//    machine.setFlag("test", v);
    if(machine.getReg(std::get<0>(mParameters)) < machine.getReg(std::get<1>(mParameters))){
        machine.setFlag("test", true);
    }
    else {
        machine.setFlag("test", false);
    }
}


void Jt::Execute(Machine& machine)
{
    // TODO
    if(machine.getFlag("test")){
        machine.setReg("pc", machine.getReg(std::get<0>(mParameters)));
    }
    
}

void Jnt::Execute(Machine& machine)
{
    // TODO
    if(!machine.getFlag("test")){
        machine.setReg("pc", machine.getReg(std::get<0>(mParameters)));
    }
}
//push reg1 Pushes reg1 onto stack, and increments the sc register
//pop reg1 Pops top of stack into reg1, and decrements the sc register
//load reg1,reg2 reg1 = stack[reg2]
//store reg1,reg2 stack[reg1] = reg2
//loadi reg1,int reg1 = stack[int]
//storei int,reg1 stack[int] = reg1
//loadsc reg1,reg2 reg1 = stack[sc – reg2 – 1]
//storesc reg1,reg2 stack[sc – reg1 – 1] = reg2

void Push::Execute(Machine& machine)
{
    // TODO
    machine.pushStack(machine.getReg(std::get<0>(mParameters)));
}

void Pop::Execute(Machine& machine)
{
    // TODO
    int v = machine.popStack();
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (v > 7 || v < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), v);
    
}

void Load::Execute(Machine& machine)
{
    // TODO
    int v = machine.getStack(machine.getReg(std::get<1>(mParameters)));
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (v > 7 || v < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), v);
}

void Store::Execute(Machine& machine)
{
    // TODO
    int v = machine.getReg(std::get<1>(mParameters));
    machine.setStack(machine.getReg(std::get<0>(mParameters)), v);
}

void LoadI::Execute(Machine& machine)
{
    // TODO
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && ( machine.getStack(std::get<1>(mParameters)) > 7 ||  machine.getStack(std::get<1>(mParameters)) < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), machine.getStack(std::get<1>(mParameters)));
}

void StoreI::Execute(Machine& machine)
{
    // TODO
    int v = machine.getReg(std::get<1>(mParameters));
    machine.setStack(std::get<0>(mParameters), v);
}

void LoadSc::Execute(Machine& machine)
{
    // TODO
    int index = machine.getReg("sc") - machine.getReg(std::get<1>(mParameters)) - 1;
    int v = machine.getStack(index);
    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException(10);
    }
    if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException(11);
    }
    if(std::get<0>(mParameters) == "tc" && (v > 7 || v < 0)){
        throw NonFatalException(14);
    }
    machine.setReg(std::get<0>(mParameters), v);
}

void StoreSc::Execute(Machine& machine)
{
    // TODO
    int index = machine.getReg("sc") - machine.getReg(std::get<0>(mParameters)) - 1;
    machine.setStack(index,  machine.getReg(std::get<1>(mParameters)));
}

void Pendown::Execute(Machine& machine)
{
    // TODO
    machine.setFlag("pen", true);
}

void Penup::Execute(Machine& machine)
{
    // TODO
    machine.setFlag("pen", false);
}

void Fwd::Execute(Machine& machine)
{
    // TODO
    machine.forward(std::get<0>(mParameters));
}

void Back::Execute(Machine& machine)
{
    // TODO
    machine.backward(std::get<0>(mParameters));
}

