#include "FileWriter.h"

SC_MODULE(Median){
    sc_in<sc_logic> start;
    sc_in<sc_logic> clk;
    sc_port<get_if> in;
    sc_port<put_if> out;

    sc_lv<8> segment_r[10][512];
    sc_lv<8> segment_g[10][512];
    sc_lv<8> segment_b[10][512];

    sc_lv<8> result_r[8][510];
    sc_lv<8> result_g[8][510];
    sc_lv<8> result_b[8][510];

    SC_CTOR(Median){
        SC_THREAD(evl);
        sensitive<<start.pos();
    }

    void evl(){
        wait(start.posedge_event());
        for(int i=2; i<10; i++){
            for(int j=0; j<512; j++){
                wait(clk->posedge_event());
                in->get(segment_r[i][j]);
                wait(clk->posedge_event());
                in->get(segment_g[i][j]);
                wait(clk->posedge_event());
                in->get(segment_b[i][j]);
            }
        }

        int arr[9];
        //processing the first segment
        for(int i=1; i<7; i++){
            int k=i+2;
            for(int j=1; j<511; j++){
                arr[0]=segment_r[k-1][j-1].to_uint(); arr[1]=segment_r[k-1][j].to_uint(); arr[2]=segment_r[k-1][j+1].to_uint();
                arr[3]=segment_r[k][j-1].to_uint()  ; arr[4]=segment_r[k][j].to_uint()  ; arr[5]=segment_r[k][j+1].to_uint();
                arr[6]=segment_r[k+1][j-1].to_uint(); arr[7]=segment_r[k+1][j].to_uint(); arr[8]=segment_r[k+1][j+1].to_uint();
                result_r[i-1][j-1]=findMedian(arr);

                arr[0]=segment_g[k-1][j-1].to_uint(); arr[1]=segment_g[k-1][j].to_uint(); arr[2]=segment_g[k-1][j+1].to_uint();
                arr[3]=segment_g[k][j-1].to_uint()  ; arr[4]=segment_g[k][j].to_uint()  ; arr[5]=segment_g[k][j+1].to_uint();
                arr[6]=segment_g[k+1][j-1].to_uint(); arr[7]=segment_g[k+1][j].to_uint(); arr[8]=segment_g[k+1][j+1].to_uint();
                result_g[i-1][j-1]=findMedian(arr);

                arr[0]=segment_b[k-1][j-1].to_uint(); arr[1]=segment_b[k-1][j].to_uint(); arr[2]=segment_b[k-1][j+1].to_uint();
                arr[3]=segment_b[k][j-1].to_uint()  ; arr[4]=segment_b[k][j].to_uint()  ; arr[5]=segment_b[k][j+1].to_uint();
                arr[6]=segment_b[k+1][j-1].to_uint(); arr[7]=segment_b[k+1][j].to_uint(); arr[8]=segment_b[k+1][j+1].to_uint();
                result_b[i-1][j-1]=findMedian(arr);
            }
        }

        //sending the first segment to file writer
        for(int i=0; i<6; i++){
            for(int j=0; j<510; j++){
                wait(clk->posedge_event());
                out->put(result_r[i][j]);
                wait(clk->posedge_event());
                out->put(result_g[i][j]);
                wait(clk->posedge_event());
                out->put(result_b[i][j]);
            }
        }

        //getting the rest and processing the received data and transfering the result to file writer
         for(int it=0; it<63; it++){
            
            //transfering 2 last rows to 2 first rows of the new segment
             for(int i=0; i<2; i++){
                for(int j=0; j<512; j++){
                    segment_r[i][j] = segment_r[i+8][j];
                    segment_g[i][j] = segment_g[i+8][j];
                    segment_b[i][j] = segment_b[i+8][j];
                }
             }

            //getting 8 rows
             for(int i=2; i<10; i++){
                for(int j=0; j<512; j++){
                    wait(clk->posedge_event());
                    in->get(segment_r[i][j]);
                    wait(clk->posedge_event());
                    in->get(segment_g[i][j]);
                    wait(clk->posedge_event());
                    in->get(segment_b[i][j]);
                }
            }

            //processing the segment
            for(int i=1; i<9; i++){
                for(int j=1; j<511; j++){
                    arr[0]=segment_r[i-1][j-1].to_uint(); arr[1]=segment_r[i-1][j].to_uint(); arr[2]=segment_r[i-1][j+1].to_uint();
                    arr[3]=segment_r[i][j-1].to_uint()  ; arr[4]=segment_r[i][j].to_uint()  ; arr[5]=segment_r[i][j+1].to_uint();
                    arr[6]=segment_r[i+1][j-1].to_uint(); arr[7]=segment_r[i+1][j].to_uint(); arr[8]=segment_r[i+1][j+1].to_uint();
                    result_r[i-1][j-1]=findMedian(arr);

                    arr[0]=segment_g[i-1][j-1].to_uint(); arr[1]=segment_g[i-1][j].to_uint(); arr[2]=segment_g[i-1][j+1].to_uint();
                    arr[3]=segment_g[i][j-1].to_uint()  ; arr[4]=segment_g[i][j].to_uint()  ; arr[5]=segment_g[i][j+1].to_uint();
                    arr[6]=segment_g[i+1][j-1].to_uint(); arr[7]=segment_g[i+1][j].to_uint(); arr[8]=segment_g[i+1][j+1].to_uint();
                    result_g[i-1][j-1]=findMedian(arr);

                    arr[0]=segment_b[i-1][j-1].to_uint(); arr[1]=segment_b[i-1][j].to_uint(); arr[2]=segment_b[i-1][j+1].to_uint();
                    arr[3]=segment_b[i][j-1].to_uint()  ; arr[4]=segment_b[i][j].to_uint()  ; arr[5]=segment_b[i][j+1].to_uint();
                    arr[6]=segment_b[i+1][j-1].to_uint(); arr[7]=segment_b[i+1][j].to_uint(); arr[8]=segment_b[i+1][j+1].to_uint();
                    result_b[i-1][j-1]=findMedian(arr);
                }
            }

            //sending the segment to file writer
            for(int i=0; i<8; i++){
                for(int j=0; j<510; j++){
                    wait(clk->posedge_event());
                    out->put(result_r[i][j]);
                    wait(clk->posedge_event());
                    out->put(result_g[i][j]);
                    wait(clk->posedge_event());
                    out->put(result_b[i][j]);
                }
            }

         }
    }

    int findMedian(int a[])
    {
        sort(a, a + 9);
        return a[4];
    }
};