#include "lp_filter.h"
#include "ADC.h"
#include "tdf2de.h"

#define NBits 16 

SC_MODULE(sensor_frontend){
    sc_core::sc_in<double> in;
    sc_core::sc_out<sc_dt::sc_lv<NBits> > out;

    sca_tdf::sca_signal <double> sine_sig;
    sca_tdf::sca_signal <sc_dt::sc_int<NBits> > adc_sine;

    lp_filter* filter;
    ADC* adc;
    tdf2de* t2d;
    SC_CTOR(sensor_frontend){
        filter = new lp_filter("LowPassFilter",1000,100e-9);
        filter->in(in);
        filter->out(sine_sig);
        
        adc = new ADC("ADC", 5.0);
        adc->in(sine_sig);
        adc->out(adc_sine);
        
        t2d = new tdf2de("TDF2DE");
        t2d->in(adc_sine);
        t2d->out(out);
    }
}; 