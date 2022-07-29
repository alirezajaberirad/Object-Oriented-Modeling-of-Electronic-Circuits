#include "controller.h"
#include "datapath.h"

SC_MODULE(topModule){
    sc_in<sc_logic> clk,completed;
    sc_in<sc_lv<4> > NewPageBus;

    sc_out<sc_logic> free;

    sc_signal<sc_logic> lt, is_15;
    sc_signal<sc_logic> read, write, AP_ld, AB_sel, cnt_rst, cnt_inc, DWB_sel, APR_ld;

    datapath* dp;
    controller* ctrl;

    SC_CTOR(topModule){
        dp = new datapath("datapath");
            dp->read(read);
            dp->write(write);
            dp->clk(clk);
            dp->AP_ld(AP_ld);
            dp->AB_sel(AB_sel);
            dp->DWB_sel(DWB_sel);
            dp->cnt_rst(cnt_rst);
            dp->cnt_inc(cnt_inc);
            dp->APR_ld(APR_ld);
            dp->NewPageBus(NewPageBus);
            dp->is_15(is_15);
            dp->lt(lt);

        ctrl = new controller("controller");
            ctrl->clk(clk);
            ctrl->completed(completed);
            ctrl->lt(lt);
            ctrl->is_15(is_15);
            ctrl->read(read);
            ctrl->write(write);
            ctrl->AP_ld(AP_ld);
            ctrl->AB_sel(AB_sel);
            ctrl->cnt_rst(cnt_rst);
            ctrl->cnt_inc(cnt_inc);
            ctrl->DWB_sel(DWB_sel);
            ctrl->APR_ld(APR_ld);
            ctrl->free(free);
    }
};