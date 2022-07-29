#include "topModule.h"

SC_MODULE(testBench){
    sc_signal <sc_logic > clk, completed;
    sc_signal <sc_lv<4> > NewPageBus;
    sc_signal <sc_logic > free;

    topModule* top1;

    SC_CTOR(testBench){
        top1 = new topModule("top_module_instance");
            top1->clk(clk);
            top1->completed(completed);
            top1->NewPageBus(NewPageBus);
            top1->free(free);
        
        SC_THREAD(newPageInsertion);
        SC_THREAD(start);
        SC_THREAD(clocking);
    }

    void newPageInsertion();
    void start();
    void clocking();
};

void testBench::newPageInsertion(){
    while(true){
        NewPageBus = sc_lv<4>("0100");
        wait(200, SC_NS);
        NewPageBus = sc_lv<4>("0101");
        wait();
    }
}

void testBench::start(){
    while(true){
        completed = sc_logic('0');
        wait(7, SC_NS);
        completed = sc_logic('1');
        wait(21, SC_NS);
        completed = sc_logic('0');
        wait(420, SC_NS);
        completed = sc_logic('1');
        wait(310, SC_NS);
        completed = sc_logic('0');
        wait();
    }
}

void testBench::clocking(){
    while(true){
        wait(5, SC_NS);
        clk = sc_logic('1');
        wait(5, SC_NS);
        clk = sc_logic('0');
    }
}