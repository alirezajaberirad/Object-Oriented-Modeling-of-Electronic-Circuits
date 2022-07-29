#include "controller.h"

void controller::comb_s_function(){
    ns = st0;
    switch(ps){
        case st0:
            if(completed->read()=='1')
                ns = st1;
            else
                ns = st0;
            break;
        
        case st1:
            ns=st2;
            break;
        
        case st2:
            ns=st3;
            break;

        case st3:
            ns = st4;
            break;

        case st4:
            if(lt->read()=='1')
                ns=st5;
            else
                ns=st6;
            break;
        
        case st5:
            ns=st6;
            break;

        case st6:
            if(is_15.read()=='1')
                ns=st8;
            else
                ns=st7;
            break;
        
        case st7:
            ns=st4;
            break;
        
        case st8:
            ns=st0;
            break;

        default:
            ns=st0;
            break;

    }
}

void controller::comb_o_function(){
    read = SC_LOGIC_0;
    write = SC_LOGIC_0;
    AP_ld = SC_LOGIC_0;
    AB_sel = SC_LOGIC_0;
    cnt_rst = SC_LOGIC_0;
    cnt_inc = SC_LOGIC_0;
    DWB_sel = SC_LOGIC_0;
    APR_ld = SC_LOGIC_0;
    free = SC_LOGIC_0;

    switch(ps){
        case st0:
            free = SC_LOGIC_1;
            break;
        
        case st1:
            AP_ld = SC_LOGIC_1;
            break;
        
        case st2:
            read = SC_LOGIC_1;
            break;

        case st3:
            APR_ld = SC_LOGIC_1;
            cnt_rst = SC_LOGIC_1;
            break;
        
        case st4:
            AB_sel = SC_LOGIC_1;
            read = SC_LOGIC_1;
            break;

        case st5:
            AB_sel = SC_LOGIC_1;
            write = SC_LOGIC_1;
            break;
        
        case st6:
            break;
        
        case st7:
            cnt_inc = SC_LOGIC_1;
            break;

        case st8:
            DWB_sel = SC_LOGIC_1;
            write = SC_LOGIC_1;
            break;
        
        default:
            read = SC_LOGIC_0;
            write = SC_LOGIC_0;
            AP_ld = SC_LOGIC_0;
            AB_sel = SC_LOGIC_0;
            cnt_rst = SC_LOGIC_0;
            cnt_inc = SC_LOGIC_0;
            DWB_sel = SC_LOGIC_0;
            APR_ld = SC_LOGIC_0;
            free = SC_LOGIC_0; 
            break;
    }
}

void controller::seq_function(){
    while(true){
        if(clk->event() && clk->read()=='1')
            ps=ns;
        wait();
    }
}