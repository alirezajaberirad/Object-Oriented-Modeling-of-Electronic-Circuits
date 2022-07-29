#include<systemc.h>
#include<iostream>

using namespace std;

SC_MODULE(processor){
    sc_in <sc_logic> clk;

    sc_out<sc_logic> readIO, writeIO;
    sc_out<sc_lv<16> > addrBus;

    sc_inout_rv <16> dataBus;

    SC_CTOR(processor){
        SC_THREAD(bracketing);
        sensitive<<clk.pos();
    }
 
    void bracketing(){
        int arr[100];
        while(true){
            for(int i=0; i<100; i++){
                wait();
                writeIO = SC_LOGIC_1;
                readIO = SC_LOGIC_0;
                addrBus = 0x0010;
                wait();
                cout<<"1"<<endl;
 
                writeIO = SC_LOGIC_0;
                readIO = SC_LOGIC_1;
                wait();
                cout<<"2"<<endl;

                while(dataBus.read().to_uint() != 1)
                    wait();
                cout<<"3"<<endl;
                writeIO = SC_LOGIC_0;
                readIO = SC_LOGIC_1;
                addrBus = 0x0018;
                wait();
                arr[i]=dataBus.read().to_uint();
            }
            double avg = 0;
            for(int i=0; i<100; i++)
                avg+=arr[i];
            avg=avg/100;

            cout<<"average is: "<<avg<<endl;
        }
    }
};