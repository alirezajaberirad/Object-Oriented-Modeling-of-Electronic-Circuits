#include "GrayScaler.h"
#include <stdlib.h>

SC_MODULE(EdgeDetector){

    sc_in<sc_logic> clk;
    sc_in<sc_logic> start;
    sc_port<get_if> in;
    sc_port<put_if> out;

    sc_lv<8> segment[10][512];
    sc_lv<8> gx[8][510];
    sc_lv<8> gy[8][510];
    sc_lv<8> G[8][510];

    SC_CTOR(EdgeDetector){
        SC_THREAD(evl);
        sensitive<<start.pos();
    }

    void evl(){
        int Gx, Gy;
        //getting the first segment
        for(int i=2; i<10; i++){
            for(int j=0; j<512; j++){
                wait(clk->posedge_event());
                in->get(segment[i][j]);
            }
        }

        //processing the first segment
        for(int i=1; i<7; i++){
            int k=i+2;
            for(int j=1; j<511; j++){
                Gx=-segment[k-1][j-1].to_uint()-2*segment[k-1][j].to_uint()-segment[k-1][j+1].to_uint()+segment[k+1][j-1].to_uint()+2*segment[k+1][j].to_uint()+segment[k+1][j+1].to_uint();
                gx[i-1][j-1]=abs(Gx);
                Gy=-segment[k-1][j-1].to_uint()-2*segment[k][j-1].to_uint()-segment[k+1][j-1].to_uint()+segment[k-1][j+1].to_uint()+2*segment[k][j+1].to_uint()+segment[k+1][j+1].to_uint();
                gy[i-1][j-1]=abs(Gy);
                //gx[i-1][j-1]=abs(gx[i-1][j-1])
                G[i-1][j-1] = gx[i-1][j-1].to_uint() + gy[i-1][j-1].to_uint();
            }
        }

        //sending the first segment to file writer
        for(int i=0; i<6; i++){
            for(int j=0; j<510; j++){
                wait(clk->posedge_event());
                out->put(G[i][j]);
            }
        }


        //getting the rest and processing the received data and transfering the result to file writer
         for(int it=0; it<63; it++){
            
            //transfering 2 last rows to 2 first rows of the new segment
             for(int i=0; i<2; i++){
                for(int j=0; j<512; j++)
                    segment[i][j] = segment[i+8][j];
             }

            //getting 8 rows
             for(int i=2; i<10; i++){
                for(int j=0; j<512; j++){
                    wait(clk->posedge_event());
                    in->get(segment[i][j]);
                }
            }

            //processing the segment
            for(int i=1; i<9; i++){
                for(int j=1; j<511; j++){
                    Gx=-segment[i-1][j-1].to_uint()-2*segment[i-1][j].to_uint()-segment[i-1][j+1].to_uint()+segment[i+1][j-1].to_uint()+2*segment[i+1][j].to_uint()+segment[i+1][j+1].to_uint();
                    gx[i-1][j-1]=abs(Gx);
                    Gy=-segment[i-1][j-1].to_uint()-2*segment[i][j-1].to_uint()-segment[i+1][j-1].to_uint()+segment[i-1][j+1].to_uint()+2*segment[i][j+1].to_uint()+segment[i+1][j+1].to_uint();
                    gy[i-1][j-1]=abs(Gy);
                    G[i-1][j-1] = gx[i-1][j-1].to_uint() + gy[i-1][j-1].to_uint();
                }
            }

            //sending the segment to file writer
            for(int i=0; i<8; i++){
                for(int j=0; j<510; j++){
                    wait(clk->posedge_event());
                    out->put(G[i][j]);
                }
            }

         }
    }
};