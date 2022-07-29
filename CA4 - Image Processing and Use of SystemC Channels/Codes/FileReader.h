#include "interface.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

SC_MODULE(FileReader){

    sc_in<sc_logic> clk;
    sc_in<sc_logic> start;
    sc_in<sc_logic> writeDone;
    sc_port<put_if> out;

    sc_uint<8> red[512*512];
    sc_uint<8> green[512*512];
    sc_uint<8> blue[512*512];

    SC_CTOR(FileReader):clk("clock"),  out("out"){
        SC_THREAD(arraysInit);
        sensitive<<start.pos();
    }

    void arraysInit(){
        ifstream r_file("red_pixel.txt");
        ifstream g_file("green_pixel.txt");
        ifstream b_file("blue_pixel.txt");

        string pixel;

        int i=0,j=0;

        while(i<512*512){
            getline(r_file, pixel);
            red[i++]=stoi(pixel);
        }
        r_file.close();

        i=0;
        while(i<512*512){
            getline(g_file, pixel);
            green[i++]=stoi(pixel);
        }
        g_file.close();

        i=0;
        while(i<512*512){
            getline(b_file, pixel);
            blue[i++]=stoi(pixel);
        }
        b_file.close();

        //transferring r,g,b values to next module;
        for(i=0; i<512*512; i++){
            wait(clk->posedge_event());
            out->put(red[i]);
            wait(clk->posedge_event());
            out->put(green[i]);
            wait(clk->posedge_event());
            out->put(blue[i]);
        }

        wait(writeDone->posedge_event());
        //transferring r,g,b values to Median module;
        for(i=0; i<512*512; i++){
            wait(clk->posedge_event());
            out->put(red[i]);
            wait(clk->posedge_event());
            out->put(green[i]);
            wait(clk->posedge_event());
            out->put(blue[i]);
        }
    }
};