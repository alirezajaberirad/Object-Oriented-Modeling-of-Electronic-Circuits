#include<systemc.h>
#include<systemc-ams.h>

SC_MODULE(squareWave){
    sc_out <double> out;

    SC_CTOR(squareWave){
        SC_THREAD(wave);
    }
    void wave(){
        while(true){
            out->write(-5.0);
            wait(5, SC_US);
            out->write(5.0);
            wait(5, SC_US);
        }
    }
}; 