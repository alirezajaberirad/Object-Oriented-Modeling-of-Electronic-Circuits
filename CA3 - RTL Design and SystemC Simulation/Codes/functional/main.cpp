#include "testBench.h"
#include <string>

int sc_main(int argc, char** argv){
    testBench* TB1 = new testBench("testBench1");

    sc_trace_file* FILE;
    FILE = sc_create_vcd_trace_file("functionalModuleTest");
    sc_trace(FILE, TB1->clk, "clk");
    sc_trace(FILE, TB1->NewPageBus, "NewPage");
    sc_trace(FILE, TB1->completed, "completed");


    for(int i=0; i<16; i++)
        sc_trace(FILE, TB1->top1->mem[i], "Memory_"+ std::to_string(i) );

    sc_start(100, SC_NS);
    return 0;
}