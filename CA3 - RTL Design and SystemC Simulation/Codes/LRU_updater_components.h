#include <iostream>
#include <systemc.h>

SC_MODULE(MUX){
    sc_in<sc_logic> sel;
    sc_in<sc_lv<4> > ain, bin;
    sc_out<sc_lv<4> > out;

    SC_CTOR(MUX){
        SC_METHOD(muxing);
        sensitive<< ain<< bin<< sel;
    }
    void muxing();
};

SC_MODULE(plusOne){
    sc_in<sc_lv<4> > in;
    sc_out<sc_lv<4> > out;

    SC_CTOR(plusOne){
        SC_METHOD(increment);
        sensitive<< in;
    }
    void increment();
};

SC_MODULE(dRegister){
    sc_in<sc_logic> clk, ld;
    sc_in<sc_lv<4> > regin;
    sc_out<sc_lv<4> > regout;

    SC_CTOR(dRegister){
        SC_METHOD(registering);
        sensitive<< clk<< ld;
    }
    void registering();
};

SC_MODULE(counter){
    sc_in<sc_logic> clk, rst, inc;
    sc_out<sc_lv<4> > out;

    SC_CTOR(counter){
        SC_METHOD(counting);
        sensitive<< clk<< rst<< inc;
    }

    void counting();
};

SC_MODULE(CMP){
    sc_in<sc_lv<4> > in1, in2;
    sc_out<sc_logic> lt;

    SC_CTOR(CMP){
        SC_METHOD(compare);
        sensitive<< in1<< in2;
    }

    void compare();
};

SC_MODULE(fourBitAND){
    sc_in<sc_lv<4> > in;
    sc_out<sc_logic> out;

    SC_CTOR(fourBitAND){
        SC_METHOD(anding);
        sensitive<< in;
    }

    void anding();
};

SC_MODULE(Memory){
    sc_in<sc_lv<4> > addr;
    sc_in<sc_lv<4> > dataWrite;
    sc_out<sc_lv<4> > dataRead;
    sc_in<sc_logic> read, write;

    sc_uint<4> *mem;

    SC_CTOR(Memory){
        mem = new sc_uint<4>[16];
        SC_THREAD(meminit);
        SC_METHOD(memread);
        sensitive<<addr<<read;
        SC_METHOD(memwrite);
        sensitive<<addr<<dataWrite<<write;
    } 

    void meminit();
    void memread();
    void memwrite();
};