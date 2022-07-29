#include "TestBench.h"
#include <string>

int sc_main(int argc, char** argv){
    testBench* TB1 = new testBench("testBench1");

    sc_trace_file* FILE;
    FILE = sc_create_vcd_trace_file("TopModuleTest");
    sc_trace(FILE, TB1->clk, "clk");
    sc_trace(FILE, TB1->NewPageBus, "NewPage");
    sc_trace(FILE, TB1->completed, "completed");
    sc_trace(FILE, TB1->free, "free");
    sc_trace(FILE, TB1->top1->ctrl->read, "read");
    sc_trace(FILE, TB1->top1->ctrl->write, "write");
    sc_trace(FILE, TB1->top1->ctrl->AP_ld, "AP_ld");
    sc_trace(FILE, TB1->top1->ctrl->AB_sel, "AB_sel");
    sc_trace(FILE, TB1->top1->ctrl->APR_ld, "APR_ld");
    sc_trace(FILE, TB1->top1->ctrl->cnt_rst, "cnt_rst");
    sc_trace(FILE, TB1->top1->ctrl->cnt_inc, "cnt_inc");
    sc_trace(FILE, TB1->top1->ctrl->DWB_sel, "DWB_sel");


    for(int i=0; i<8; i++)
        sc_trace(FILE, TB1->top1->dp->mem->mem[i], "Memory_"+ std::to_string(i) );

    sc_start(1500, SC_NS);
    return 0;
}