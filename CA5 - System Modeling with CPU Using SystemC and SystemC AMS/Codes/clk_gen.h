#include <systemc.h>

SC_MODULE(clk_gen){
    sc_out<sc_logic> out;

    SC_CTOR(clk_gen){
        SC_THREAD(evl);
    }
 
    void evl(){
        while(true){
            out = SC_LOGIC_1;
            wait(500, SC_NS);
            out = SC_LOGIC_0;
            wait(500, SC_NS);
        }
    }
}; 