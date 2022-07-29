#include "LRU_updater.h"

SC_MODULE(testBench){
    sc_signal <sc_logic > clk, completed;
    sc_signal <sc_lv<4> > NewPageBus;

    LRU_updater* top1;

    SC_CTOR(testBench){
        top1 = new LRU_updater("LRU_updater_instance");
            top1->clk(clk);
            top1->completed(completed);
            top1->NewPageBus(NewPageBus);
        
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
        wait(20, SC_NS);
        NewPageBus = sc_lv<4>("0101");
        wait(20, SC_NS);
        NewPageBus = sc_lv<4>("1110");
        wait();
    }
}

void testBench::start(){
    while(true){
        completed = sc_logic('0');
        wait(5, SC_NS);
        completed = sc_logic('1');
        wait(10, SC_NS);
        completed = sc_logic('0');
        wait(10, SC_NS);
        completed = sc_logic('1');
        wait(10, SC_NS);
        completed = sc_logic('0');
        wait(10, SC_NS);
        completed = sc_logic('1');
        wait(10, SC_NS);
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