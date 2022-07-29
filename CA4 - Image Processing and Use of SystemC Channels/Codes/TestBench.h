#include "Median.h"

SC_MODULE(Top){
    sc_in<sc_logic> clk, start;
    sc_signal<sc_logic> writeDone;

    channel *reader2gray, *gray2edge, *edge2writer;
    FileReader *FR;
    GrayScaler *GS;
    EdgeDetector *ED;
    FileWriter *FW;
    Median *MED;

    SC_CTOR(Top){
        reader2gray = new channel();
        gray2edge = new channel();
        edge2writer = new channel();

        FR = new FileReader("file_reader");
        FR->clk(clk);
        FR->start(start);
        FR->out(*reader2gray);
        FR->writeDone(writeDone);

        GS = new GrayScaler("gray_scaler");
        GS->clk(clk);
        GS->start(start);
        GS->in(*reader2gray);
        GS->out(*gray2edge);

        ED = new EdgeDetector("edge_detector");
        ED->clk(clk);
        ED->start(start);
        ED->in(*gray2edge);
        ED->out(*edge2writer);

        FW = new FileWriter("file_writer");
        FW->clk(clk);
        FW->start(start);
        FW->in(*edge2writer);
        FW->done(writeDone);

        MED = new Median("median");
        MED->clk(clk);
        MED->start(writeDone);
        MED->in(*reader2gray);
        MED->out(*edge2writer);

    }

};

SC_MODULE(TestBench){

    sc_signal<sc_logic> clk;
    sc_signal<sc_logic> start;

    Top *top;

    SC_CTOR(TestBench){
        top = new Top("top_module");
        top->clk(clk);
        top->start(start);

        SC_THREAD(clocking);
        SC_THREAD(signaling);
    }

    void clocking(){
        while(true){
            clk = SC_LOGIC_0;
            wait(5, SC_NS);
            clk = SC_LOGIC_1;
            wait(5, SC_NS);
        }
    }

    void signaling(){
        while(true){
            start = SC_LOGIC_0;
            wait(20, SC_NS);
            start = SC_LOGIC_1;
            wait(20, SC_NS);
            start = SC_LOGIC_0;
            wait();
        }
    }

};