#pragma once
#include "Ops.h"
#include <memory>
#include <vector>
#include <map>
#include "../img/bitmap_image.hpp"
#include "Exceptions.h"

template <typename T>
std::shared_ptr<Op> CreateOp()
{
    return std::make_shared<T>();
}

class Machine
{
public:
	Machine();
    void readFile(const std::string& filename);
    int getReg(std::string r);
    void setReg(std::string r, int v) ;
    int getStack(int i);
    void setStack(int index, int v);
    void pushStack(int i);
    int popStack();
    bool getFlag(std::string f);
    void setFlag(std::string r, bool v);
    void Execute();
    void forward(std::string reg1);
    void backward(std::string reg1);
    void setPenColor();
    

private:
	std::vector<std::shared_ptr<Op>> mOps;
    std::map<std::string, std::function<std::shared_ptr<Op>()>> opMap;
    std::map<std::string, int> regMap;
    std::map<std::string, bool> flagMap;
    std::vector<int> stackVector;
    bitmap_image bi;
    image_drawer imgd;
    
};
