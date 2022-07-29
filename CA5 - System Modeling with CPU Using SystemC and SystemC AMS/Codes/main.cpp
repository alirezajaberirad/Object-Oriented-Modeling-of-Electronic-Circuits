#include "processor.h"
#include "sensor.h"
#include "timer.h"
#include "bus_if.h"

int sc_main(int argc, char** argv){
    sc_set_time_resolution(10, SC_NS);
    sca_util::sca_trace_file* File = sca_util::sca_create_vcd_trace_file("completeCircuitTB");

    sc_signal<sc_logic> sensorEnable;
    sc_signal_rv<16> dataBus;
    sc_signal<sc_logic> clk, startTimer, timerEnable;
    sc_signal<sc_logic> readIO, writeIO;
    sc_signal<sc_lv<16> > addrBus;

    sensor S("sensor");
    timer T("timer");
    processor P("processor");
    clk_gen C("clock");
    bus_if B("Bus");

    C.out(clk);

    S.outEnable(sensorEnable);
    S.datafromslave(dataBus);

    T.clk(clk); 
    T.startTimer(startTimer);
    T.outEnable(timerEnable);
    T.timeOut(dataBus);
 
    B.readIO(readIO);
    B.writeIO(writeIO);
    B.addrBus(addrBus);
    B.timerEnable(timerEnable);
    B.sensorEnable(sensorEnable);
    B.startTimer(startTimer);

    P.clk(clk);
    P.dataBus(dataBus);
    P.readIO(readIO);
    P.writeIO(writeIO);
    P.addrBus(addrBus);

    sca_util::sca_trace(File, S.SF->out,"sensorOut");
    sca_util::sca_trace(File, P.readIO,"processor_read_req");
    sca_util::sca_trace(File, P.writeIO,"processor_write_req");

    sca_util::sca_trace(File, T.outEnable,"timer_out_enable");
    sca_util::sca_trace(File, T.clk,"timer_clk");
    sca_util::sca_trace(File, T.timeOut,"timer_timeOut");

    sc_start(100, SC_MS);
    sca_util::sca_close_vcd_trace_file(File);
    return 0;
}