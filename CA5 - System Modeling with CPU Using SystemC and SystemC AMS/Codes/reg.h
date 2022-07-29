#include <systemc.h>

#define NBits 16

SC_MODULE(reg){
    sc_in<sc_logic> outEnable,clk;
    sc_in<sc_lv<NBits> > in;

    sc_out_rv<NBits> out;

    sc_signal<sc_lv<NBits> > reg_val;

    SC_CTOR(reg){
        SC_THREAD(ld_reg);
        sensitive<<clk.pos();
        SC_THREAD(tristate);
        sensitive<<outEnable<<reg_val;
    } 
 
    void ld_reg(){
        while(true){
            reg_val = in;
            wait();
        }
    }
    void tristate(){
        out.write("ZZZZZZZZZZZZZZZZ");
        while(true){
            if(outEnable==SC_LOGIC_1)
                out.write(reg_val.read());
            else
                out.write("ZZZZZZZZZZZZZZZZ");
            wait();
        }
    }
};