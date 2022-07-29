#include <iostream>
#include <systemc.h>

SC_MODULE(LRU_updater){
    sc_in<sc_lv<4> > NewPageBus;
    sc_in<sc_logic> completed, clk;

    sc_uint<4> *mem;

    SC_CTOR(LRU_updater){
        mem = new sc_uint<4>[16];
        SC_THREAD(meminit);
        SC_THREAD(operation);
        sensitive<< clk;
    }
    void meminit(){
        int i;
        for(i=0; i<16; i++)
            mem[i] = i;
    }
    void operation(){
        while(true){
            if(completed=='1' && clk=='1' && clk->event()){
                int i=0;
                while(mem[i]!=sc_uint<4>(NewPageBus))
                    i++;
                for(int j=i; j>0; j--){
                    mem[j]=mem[j-1];
                }
                mem[0]=sc_uint<4>(NewPageBus);
            }
            wait();
        }
    }
};