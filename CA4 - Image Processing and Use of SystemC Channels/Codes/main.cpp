#include "TestBench.h"

int sc_main(int argc, char** argv){
    TestBench TB("test_bench");
    sc_start(512*51200*3, SC_NS);
    cout<<"THE END!\n";
    return 0;
}