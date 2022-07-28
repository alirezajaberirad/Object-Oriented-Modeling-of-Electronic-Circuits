#include "generateVerilog.h"

void generateVerilog(vector<string> &inputs, vector<string> &outputs, vector<string> &otherWires, map<string,gates*> &GATES, map<string,wire> &wires){
    ofstream file;
    file.open("generatedVerilogFile.v");
    file<<"module generatedModule";

    //module input and output wires
    file<<'('<<inputs[0];
    for(auto i=++inputs.begin(); i!=inputs.end(); ++i)//input wires
        file<<", "<<*i;
    for(auto i=outputs.begin(); i!=outputs.end(); ++i)//output wires
        file<<", "<<*i;
    file<<");\n\n";

    //input ...
    file<<"input ";
    file<<inputs[0];
    for(auto i=++inputs.begin(); i!=inputs.end(); ++i)//input wires
        file<<", "<<*i;
    file<<";\n\n";

    //output ...
    file<<"output ";
    file<<outputs[0];
    for(auto i=++outputs.begin(); i!=outputs.end(); ++i)//input wires
        file<<", "<<*i;
    file<<";\n\n";

    //wire ...
    if(!otherWires.empty()){
        file<<"wire ";
        file<<otherWires[0];
        for(auto i=++otherWires.begin(); i!=otherWires.end(); ++i)//input wires
            file<<", "<<*i;
        file<<";\n\n";
    }

    //Gates code generator
    generateGates(file, GATES, wires);

    file<<"\nendmodule";
    return;
}

void generateGates(ofstream &file, map<string,gates*> &GATES, map<string,wire> &wires){
    int gatesEncountered=0;
    int printingLevel=1;
    while(gatesEncountered!=GATES.size()){
        for(auto it=GATES.begin(); it!=GATES.end(); ++it){
            if(it->second->Level == printingLevel){
                gatesEncountered++;
                file<<it->second->type()<<' '<<it->first<<'(';
                if(it->second->type()!="not"){//any gate rather than "not" gate
                    file<<findWireName(it->second->out(), wires)<<", ";
                    file<<findWireName(it->second->in1(), wires)<<", ";
                    file<<findWireName(it->second->in2(), wires);
                }
                else{//if it is not gate
                    file<<findWireName(it->second->out(), wires)<<", ";
                    file<<findWireName(it->second->in1(), wires);
                }
                file<<"); //its controllability is: "<<it->second->outputControllability<<endl;
            }
        }
        printingLevel++;
    }
}

string findWireName(wire WIRE, map<string,wire>& wires){
    string str;

    for(auto it=wires.begin(); it!=wires.end(); ++it){
        if(it->second == WIRE){
            str=it->first;
            break;
        }
    }

    return str;
}
