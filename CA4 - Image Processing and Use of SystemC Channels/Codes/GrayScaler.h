#include "FileReader.h"

SC_MODULE(GrayScaler){

    sc_in<sc_logic> clk;
    sc_in<sc_logic> start;
    sc_port<get_if> in;
    sc_port<put_if> out;

    sc_uint<8> avg[512*512];

    SC_CTOR(GrayScaler){
        SC_THREAD(evl);
        sensitive<<start.pos();
    }

    void evl(){
        sc_lv<8> r,g,b;
        int temp;

        for(int i=0; i<512*512; i++){
            temp=0;

            wait(clk->posedge_event());
            in->get(r);
            temp+=r.to_uint();

            wait(clk->posedge_event());
            in->get(g);
            temp+=g.to_uint();

            wait(clk->posedge_event());
            in->get(b);
            temp+=b.to_uint();

            avg[i] = temp/3;
            wait(clk->posedge_event());
            out->put(avg[i]);

        }

        //writing the gray scaled file in a text file
        ofstream File("grayScaled.txt");
        for(int i=0; i<512*512; i++)
            File<<avg[i]<<endl;
        File.close();
    }
};