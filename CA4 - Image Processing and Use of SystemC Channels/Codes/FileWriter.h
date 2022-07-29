#include "EdgeDetector.h"

SC_MODULE(FileWriter){
    sc_in<sc_logic> clk;
    sc_in<sc_logic> start;
    sc_out<sc_logic> done;
    sc_port<get_if> in;

    sc_lv<8> finalPicture[510*510];

    sc_lv<8> finalPicture_r[510*510];
    sc_lv<8> finalPicture_g[510*510];
    sc_lv<8> finalPicture_b[510*510];

    SC_CTOR(FileWriter){
        SC_THREAD(evl);
        sensitive<<start.pos();
    }

    void evl(){
        while(true){
            done = SC_LOGIC_0;
            for(int i=0; i<510*510; i++){
                wait(clk.posedge_event());
                in->get(finalPicture[i]);
            }
            ofstream File1("finalPicture1.txt");
            for(int i=0; i<510*510; i++)
                File1<<finalPicture[i].to_uint()<<endl;
            File1.close();

            wait(clk.posedge_event());
            done = SC_LOGIC_1;
            wait(clk.posedge_event());
            wait(clk.posedge_event());
            done = SC_LOGIC_0;

            for(int i=0; i<510*510; i++){
                wait(clk.posedge_event());
                in->get(finalPicture_r[i]);
                wait(clk.posedge_event());
                in->get(finalPicture_g[i]);
                wait(clk.posedge_event());
                in->get(finalPicture_b[i]);
            }
            ofstream FileR("red_median.txt");
            ofstream FileG("green_median.txt");
            ofstream FileB("blue_median.txt");
            for(int i=0; i<510*510; i++){
                FileR<<finalPicture_r[i].to_uint()<<endl;
                FileG<<finalPicture_g[i].to_uint()<<endl;
                FileB<<finalPicture_b[i].to_uint()<<endl;
            }
            FileR.close();
            FileG.close();
            FileB.close();

            wait();
        }
    }
};