#include "SrcMain.h"
#include <iostream>
#include "Machine.h"

void ProcessCommandArgs(int argc, const char* argv[])
{
	// TODO
    Machine* m = new Machine();
    m -> readFile(argv[1]);
    m -> Execute();
    
}
