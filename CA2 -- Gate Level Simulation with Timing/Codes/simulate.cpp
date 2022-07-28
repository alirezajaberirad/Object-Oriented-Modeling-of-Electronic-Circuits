#include "simulate.h"

void simulate(fstream &file, vector<string> &inputs, vector<string> &outputs, map<string,gates*> &GATES, map<string,wire> &wires){
    string str;
    file>>str;
    for(int i=0; i<str.size(); i++){
        wires[inputs[i]].put(str[i]);
    }

    int gatesEncountered=0;
    int levelEncountered=0;
    while(gatesEncountered!=GATES.size()){
        levelEncountered++;
        for(auto it=GATES.begin(); it!=GATES.end(); ++it){
            if(it->second->Level == levelEncountered){
                gatesEncountered++;
                it->second->evl();
            }
        }
    }


    ofstream outputFile;
    outputFile.open("simulationResult.txt");

    cout<<"\nSimulation Input Values: "<<endl;
    for(int i=0; i<inputs.size(); i++){
        cout<<inputs[i]<<" is : "<<wires[inputs[i]].value<<endl;
    }

    cout<<"\nSimulation Output Values: "<<endl;
    for(int i=0; i<outputs.size(); i++){
        cout<<outputs[i]<<" is : "<<wires[outputs[i]].value<<endl;
        outputFile<<wires[outputs[i]].value;
    }

    outputFile.close();

    return;

}

void simulate(int present_time, string str, vector<string> &inputs, vector<string> &outputs, map<string,gates*> &GATES, map<string,wire> &wires){
    for(int i=0; i<str.size(); i++){
        wires[inputs[i]].put(str[i],present_time);
    }

    int gatesEncountered=0;
    int levelEncountered=0;
    while(gatesEncountered!=GATES.size()){
        levelEncountered++;
        for(auto it=GATES.begin(); it!=GATES.end(); ++it){
            if(it->second->Level == levelEncountered){
                gatesEncountered++;
                it->second->evl();
            }
        }
    }


    ofstream outputFile;
    outputFile.open("simulationResult.txt", ios_base::app);

    cout<<"\nSimulation Input Values at "<<present_time<<": "<<endl;
    for(int i=0; i<inputs.size(); i++){
        cout<<inputs[i]<<" is : "<<wires[inputs[i]].value<<endl;
    }

    cout<<"\nSimulation Output Values at "<<present_time<<": "<<endl;
    outputFile<<"At "<<present_time<<": ";
    for(int i=0; i<outputs.size(); i++){
        cout<<outputs[i]<<" is : "<<wires[outputs[i]].value<<endl;
        outputFile<<wires[outputs[i]].value;
    }
    outputFile<<'\n';
    outputFile.close();

    return;

}
