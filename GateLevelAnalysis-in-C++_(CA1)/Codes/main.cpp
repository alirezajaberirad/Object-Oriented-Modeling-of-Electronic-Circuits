#include "simulate.h"

using namespace std;

int main()
{
    vector<string>inputs;
    vector<string>outputs;
    vector<string>otherWires;
    map<string,wire> allWires;
    map<string,gates*> GATES;

    fstream verilogFile;
    verilogFile.open("test.v");

    fstream TBFile;
    TBFile.open("TB.txt");

    readVerilog(verilogFile, inputs, outputs, otherWires, GATES, allWires);
    recognizeLevel(GATES);
    generateVerilog(inputs, outputs, otherWires, GATES, allWires);
    simulate(TBFile, inputs, outputs, GATES, allWires);

    /*cout<<"inputs: ";
    for(auto i=inputs.begin(); i!=inputs.end(); ++i)
        cout<<*i<<"  ";
    cout<<endl;

    cout<<"outputs: ";
    for(auto i=outputs.begin(); i!=outputs.end(); ++i)
        cout<<*i<<"  ";
    cout<<endl;

    cout<<"Internal Wires: ";
    for(auto i=otherWires.begin(); i!=otherWires.end(); ++i)
        cout<<*i<<"  ";
    cout<<endl;*/


    //setInputsValue(inputs,allWires);
    /*while(1){
    string str;
    string matchedStr;
    regex ex("^[ ]*input[ ]+(.+)[ ]*[;].*");
    smatch match;
    getline(cin,str);
    cout<<str<<endl;
    cout<<regex_match(str,ex)<<endl;
    regex_search(str,match,ex);
    matchedStr=match[1];
    cout<<matchedStr;
    }*/
    return 0;
}
