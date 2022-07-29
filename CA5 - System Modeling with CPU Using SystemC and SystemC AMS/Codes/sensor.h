#include "squareWave.h"
#include "sensor_frontend.h"
#include "reg.h"
#include "clk_gen.h"
#include <systemc.h>

SC_MODULE(sensor){
    sc_in<sc_logic> outEnable;
    sc_out_rv<NBits> datafromslave;

    squareWave* SW;
    sensor_frontend* SF;
    reg* R;
    clk_gen* c_gen;

    sc_signal<double> Q_sig;
    sc_signal<sc_lv<NBits> > sine_lv;
    sc_signal<sc_logic> clk;

    SC_CTOR(sensor){
        c_gen = new clk_gen("clock_gen");
        c_gen->out(clk);

        SW = new squareWave("SquareSource");
        SW->out(Q_sig);

        SF = new sensor_frontend("InternalSensor");
        SF->in(Q_sig);
        SF->out(sine_lv);
  
        R  = new reg("SensorRegister");
        R->clk(clk);
        R->in(sine_lv);
        R->out(datafromslave);
        R->outEnable(outEnable);
    }
};