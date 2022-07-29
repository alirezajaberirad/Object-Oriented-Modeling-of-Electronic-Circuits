#include<systemc-ams.h>
#include<systemc.h>

SC_MODULE(timer){
    sc_in<sc_logic> clk, outEnable, startTimer;
    sc_out_rv<16> timeOut;
    sc_signal<sc_logic> flag;
    SC_CTOR(timer){
        SC_THREAD(evl);
        sensitive<<clk.pos();
        SC_THREAD(tristate);
        sensitive << outEnable;
    }

    void evl(){
        while(true){
            wait(startTimer.posedge_event());
            flag=SC_LOGIC_0;
            wait(1, SC_MS);
            flag=SC_LOGIC_1;
            wait();
        }
    }

    void tristate(){
        while(true){
            if(outEnable == SC_LOGIC_1){
                if(flag==SC_LOGIC_0)
                    timeOut.write("0000000000000000");
                else if(flag==SC_LOGIC_1)
                    timeOut.write("0000000000000001");
            }
            else 
                timeOut.write("ZZZZZZZZZZZZZZZZ");
            wait();
        }
    }
}; 