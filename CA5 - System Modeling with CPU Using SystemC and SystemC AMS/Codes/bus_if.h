#include <systemc.h>

SC_MODULE(bus_if){
    sc_in<sc_logic> readIO, writeIO;
    sc_in<sc_lv<16> > addrBus;
 
    sc_out<sc_logic> timerEnable, sensorEnable, startTimer;
    sc_lv<16> mask, mask_;
    SC_CTOR(bus_if){
        SC_THREAD(timer);
        sensitive<< readIO<< writeIO<< addrBus;
        SC_THREAD(sensor);
        sensitive<< readIO<< writeIO<< addrBus;
    }
 
    void timer(){
        while(true){
            timerEnable = SC_LOGIC_0;
            startTimer = SC_LOGIC_0;
            mask= addrBus.read().to_uint() & 0x00FF;
            if(mask == 0x0010 || mask == 0x0011 || mask == 0x0012 || mask == 0x0013 ){
                if(readIO == SC_LOGIC_1)
                    timerEnable = SC_LOGIC_1;
                else if(writeIO == SC_LOGIC_1)
                    startTimer = SC_LOGIC_1;
            }
            wait();
        }
    }

    void sensor(){
        while(true){
            sensorEnable = SC_LOGIC_0;
            mask_= addrBus.read().to_uint() & 0x00FF;
            if(mask_ == 0x0018 || mask_ == 0x0019 || mask_ == 0x001A || mask_ == 0x001B ){
                if(readIO == SC_LOGIC_1){
                    sensorEnable = SC_LOGIC_1;
                }
            }
            wait();
        }
    }
};