#include "LRU_updater_components.h"

SC_MODULE(datapath){
    sc_in <sc_logic> read, write;
    sc_in <sc_logic> clk;
    sc_in <sc_logic> AP_ld;
    sc_in <sc_logic> AB_sel;
    sc_in <sc_logic> DWB_sel;
    sc_in <sc_logic> cnt_rst, cnt_inc;
    sc_in <sc_logic> APR_ld;
    sc_in <sc_lv<4> > NewPageBus;

    sc_out<sc_logic> is_15;
    sc_out<sc_logic> lt;

    sc_signal<sc_lv<4> > DataReadBus;
    sc_signal<sc_lv<4> > AddressBus;
    sc_signal<sc_lv<4> > DataWriteBus;
    sc_signal<sc_lv<4> > AccessedPage, AccessedPageRate;
    sc_signal<sc_lv<4> > cnt, incByOne;

    dRegister* AccessedPageReg;
    dRegister* AccessedPageRateReg;
    MUX* muxAB;
    MUX* muxDWB;
    plusOne* POne;
    counter* CounterReg;
    CMP* cmp;
    fourBitAND* AND;
    Memory* mem;

    sc_signal<sc_lv<4> > zero;

    SC_CTOR(datapath){
        AccessedPageReg = new dRegister("AccessedPageReg");
            AccessedPageReg->clk(clk);
            AccessedPageReg->ld(AP_ld);
            AccessedPageReg->regin(NewPageBus);
            AccessedPageReg->regout(AccessedPage);
        
        AccessedPageRateReg = new dRegister("AccessedPageRateReg");
            AccessedPageRateReg->clk(clk);
            AccessedPageRateReg->ld(APR_ld);
            AccessedPageRateReg->regin(DataReadBus);
            AccessedPageRateReg->regout(AccessedPageRate);

        muxAB = new MUX("mux_address_bus");
            muxAB->sel(AB_sel);
            muxAB->ain(AccessedPage);
            muxAB->bin(cnt);
            muxAB->out(AddressBus);

        muxDWB = new MUX("mux_data_write_bus");
            muxDWB->sel(DWB_sel);
            muxDWB->ain(incByOne);
            muxDWB->bin(zero);
            //muxDWB->bin(sc_signal<sc_lv<4> >("0000"));
            muxDWB->out(DataWriteBus);

        POne = new plusOne("plus_one_module");
            POne->in(DataReadBus);
            POne->out(incByOne);

        CounterReg = new counter("counter");
            CounterReg->clk(clk);
            CounterReg->rst(cnt_rst);
            CounterReg->inc(cnt_inc);
            CounterReg->out(cnt);

        cmp = new CMP("less_than_module");
            cmp->in1(DataReadBus);
            cmp->in2(AccessedPageRate);
            cmp->lt(lt);

        AND = new fourBitAND("four_bit_and");
            AND->in(cnt);
            AND->out(is_15);

        mem = new Memory("memory");
            mem->addr(AddressBus);
            mem->dataWrite(DataWriteBus);
            mem->dataRead(DataReadBus);
            mem->read(read);
            mem->write(write);
        
        SC_THREAD(setZero);
    }
    void setZero(){
        while(true){
            zero = "0000";
            wait();
        }
    }
};