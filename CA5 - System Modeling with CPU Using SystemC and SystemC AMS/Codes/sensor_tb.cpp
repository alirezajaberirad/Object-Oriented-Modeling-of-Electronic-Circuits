#include"sensor.h"

int sc_main(int argc, char** argv){
    sc_set_time_resolution(100, SC_NS);

    sc_signal_rv<NBits> out;
    sc_signal<sc_logic> en;
    en.write(SC_LOGIC_1);

    sensor*CUT = new sensor("sens");
    CUT->outEnable(en);
    CUT->datafromslave(out);
    
    sca_util::sca_trace_file* FILE;
    FILE = sca_util::sca_create_vcd_trace_file("sensor_test");
    sca_util::sca_trace(FILE, CUT->datafromslave, "out");
    sca_util::sca_trace(FILE, CUT->SF->out, "sensor_frontend_out");
    sca_util::sca_trace(FILE, CUT->SF->filter->out, "lp_filter_out");
    sca_util::sca_trace(FILE, CUT->SW->out, "squarewave_gen_out");
    sca_util::sca_trace(FILE, CUT->R->in, "register_in");
    sca_util::sca_trace(FILE, CUT->R->out, "register_out");
    sca_util::sca_trace(FILE, CUT->R->clk, "register_clk");
    sca_util::sca_trace(FILE, CUT->R->outEnable, "register_en");
    sca_util::sca_trace(FILE, CUT->SF->adc->out, "adc_out");

    sc_start(10, SC_MS);
    sca_util::sca_close_vcd_trace_file(FILE);
    return 0;
}  