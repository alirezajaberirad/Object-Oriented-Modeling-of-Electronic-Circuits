#include <systemc.h>

SC_MODULE(controller){
    sc_in <sc_logic> clk, completed, lt, is_15;
    sc_out <sc_logic> read, write, AP_ld, AB_sel, cnt_rst, cnt_inc, DWB_sel, APR_ld, free;

    enum states {st0, st1, st2, st3, st4, st5, st6, st7, st8};
    sc_signal <states> ps, ns;

    SC_CTOR(controller){
        SC_METHOD(comb_s_function);
        sensitive<< clk<< completed<< lt<< is_15;
        SC_METHOD(comb_o_function);
        sensitive<< ps;
        SC_THREAD(seq_function);
        sensitive<< clk;
    }

    void comb_s_function();
    void comb_o_function();
    void seq_function();
};