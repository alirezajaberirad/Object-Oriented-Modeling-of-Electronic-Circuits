#include "findCriticalPath.h"

using namespace std;

static int present_time=0;
static int time_resolution=5;

int main()
{
    vector<string>inputs;
    vector<string>outputs;
    vector<string>otherWires;
    vector<string>criticalPath;
    map<string,wire> allWires;
    map<string,gates*> GATES;

    fstream verilogFile;
    verilogFile.open("C17.v");

    readVerilog(verilogFile, inputs, outputs, otherWires, GATES, allWires);
    recognizeLevel(GATES);
    generateVerilog(inputs, outputs, otherWires, GATES, allWires);
    findCriticalPath(criticalPath, inputs, outputs, GATES, allWires);

    string line;
    int targetTime;
    fstream TBFile;
    TBFile.open("input.txt");
    string inputValuesStr="XXXXX";
    while(!TBFile.eof()){
        getline(TBFile, line);
        regex ex("^[ ]*[#]([[:w:]]+)[ ]+([[:w:]]+)");
        smatch match;
        regex_search(line,match,ex);

        targetTime+=stoi(match[1]);
        for(;present_time<targetTime;present_time+=time_resolution)
            simulate(present_time,inputValuesStr, inputs, outputs, GATES, allWires);
        inputValuesStr=match[2];
    }

    return 0;
}
