#include "LRU_updater_components.h"

void MUX::muxing(){
    if(sel->read()==SC_LOGIC_1)
        out->write(bin);
    else
        out->write(ain);
}

void plusOne::increment(){
    out->write(in->read().to_uint() + 1);
}

void dRegister::registering(){
    if(clk->event() && clk->read()==SC_LOGIC_1){
        if(ld->read()==SC_LOGIC_1)
            regout->write(regin->read());
    }
}

void counter::counting(){
    if(rst->read()==SC_LOGIC_1)
        out = "0000";
    else if(clk->event() && clk->read()==SC_LOGIC_1){
        if(inc->read()==SC_LOGIC_1)
            out->write(out->read().to_uint()+1);
    }
}

void CMP::compare(){
    if(in1->read().to_uint()<in2->read().to_uint())
        lt->write(SC_LOGIC_1);
    else
        lt->write(SC_LOGIC_0);
}

void fourBitAND::anding(){
    if(in->read()=="1111")
        out->write(SC_LOGIC_1);
    else
        out->write(SC_LOGIC_0);
}

void Memory::memread(){
    if(read->read()==SC_LOGIC_1)
        dataRead = mem[addr->read().to_uint()];
}

void Memory::memwrite(){
    if(write->read()==SC_LOGIC_1)
        mem[addr->read().to_uint()] = dataWrite;
}

void Memory::meminit(){
    int i;
    for(i=0; i<16; i++)
        mem[i] = i;
}