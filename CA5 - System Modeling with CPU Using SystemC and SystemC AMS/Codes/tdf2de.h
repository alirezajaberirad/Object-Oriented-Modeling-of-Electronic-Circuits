#include <systemc-ams.h>

#define NBits 16

SCA_TDF_MODULE(tdf2de){
    sca_tdf::sca_in<sc_dt::sc_int<NBits> > in;
    sca_tdf::sca_de::sca_out<sc_lv<NBits> > out;

    tdf2de(sc_module_name){set_timestep(sc_time(100, SC_NS));}
    void processing(){
        out.write(in.read());
    }
};