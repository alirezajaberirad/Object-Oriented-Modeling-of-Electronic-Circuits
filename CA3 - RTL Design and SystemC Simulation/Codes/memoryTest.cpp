#include "LRU_updater_components.h"
#include <string>

SC_MODULE(testBench){
sc_signal <sc_logic > read, write;
    sc_signal <sc_lv<4> > datawrite, dataread, addr;

    Memory* top1;

    SC_CTOR(testBench){
        top1 = new Memory("top_module_instance");
            top1->read(read);
            top1->write(write);
            top1->dataWrite(datawrite);
            top1->dataRead(dataread);
            top1->addr(addr);
        
        SC_THREAD(newPageInsertion);
        SC_THREAD(start);
        //SC_THREAD(clocking);
    }

    void newPageInsertion();
    void start();
    //void clocking();
};

void testBench::newPageInsertion(){
    cout<<"hello\n";
    while(true){
        datawrite = sc_lv<4>("0100");
        addr = sc_lv<4>("0000");
        wait(200, SC_NS);
        datawrite = sc_lv<4>("0101");
        addr = sc_lv<4>("0001");
        wait();
    }
}

void testBench::start(){
        cout<<"hello\n";

    while(true){
        write = sc_logic('0');
        wait(7, SC_NS);
        write = sc_logic('1');
        wait(21, SC_NS);
        write = sc_logic('0');
        wait(420, SC_NS);
        read = sc_logic('1');
        wait(21, SC_NS);
        read = sc_logic('0');
        wait();
    }
}

// void testBench::clocking(){
//         cout<<"hello\n";

//     while(true){
//         wait(10, SC_NS);
//         clk = sc_logic('1');
//         wait(10, SC_NS);
//         clk = sc_logic('0');
//     }
// }

int sc_main(int argc, char** argv){
    testBench* TB1 = new testBench("testBench1");

    sc_trace_file* FILE;
    FILE = sc_create_vcd_trace_file("TopModuleTest");
    sc_trace(FILE, TB1->dataread, "dataread");
    sc_trace(FILE, TB1->datawrite, "datawrite");
    sc_trace(FILE, TB1->read, "read");
    sc_trace(FILE, TB1->write, "write");

    for(int i=0; i<16; i++)
        sc_trace(FILE, TB1->top1->mem[i], "Memory_"+ std::to_string(i) );
    // cout<<"hello";
    // sc_trace(FILE, TB1->top1->mem[0], "Memory_1");

    sc_start(600, SC_NS);
    return 0;
}