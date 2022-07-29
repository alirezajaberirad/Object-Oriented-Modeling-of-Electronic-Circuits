#include "findCriticalPath.h"

#define MAX(a,b) ((a>b)?a:b)

void findCriticalPath(vector<string> &criticalPath, vector<string> &intputs, vector<string> &outputs, map<string,gates*> &GATES, map<string,wire> &wires){
    int worstCaseDelay=0;
    for(int i=0; i<outputs.size(); i++){
        cout<<"\n\nworst case delay of "<<outputs[i]<<" is: "<<wireCriticalPath(criticalPath, wires[outputs[i]], wires, intputs, GATES)<<endl;
        cout<<"The path is: ";
        for(int i=criticalPath.size()-1; i>=0; i--)
            cout<<criticalPath[i]<<"   ";
        cout<<endl;
        criticalPath.clear();
    }
}

int wireCriticalPath(wire WIRE, map<string,wire> &wires, vector<string>&inputs, map<string,gates*> &GATES){
    gates* gate;
    if(find(inputs.begin(), inputs.end(), findWireName(WIRE,wires))==inputs.end()){
    gate = findGateFromOutputWire(WIRE, GATES);
    return gate->delay()+MAX(wireCriticalPath(gate->in1(),wires,inputs,GATES), wireCriticalPath(gate->in2(),wires,inputs,GATES));
    }
    else
        return 0;
}

int wireCriticalPath(vector<string>&criticalPath, wire WIRE, map<string,wire> &wires, vector<string>&inputs, map<string,gates*> &GATES){
    gates* gate;
    criticalPath.push_back(findWireName(WIRE,wires));
    if(find(inputs.begin(), inputs.end(), findWireName(WIRE,wires))==inputs.end()){
    gate = findGateFromOutputWire(WIRE, GATES);
    criticalPath.push_back(findGateName(gate, GATES));
    if(wireCriticalPath(gate->in1(),wires,inputs,GATES) > wireCriticalPath(gate->in2(),wires,inputs,GATES))
        return gate->delay()+wireCriticalPath(criticalPath,gate->in1(),wires,inputs,GATES);
    else
        return gate->delay()+wireCriticalPath(criticalPath,gate->in2(),wires,inputs,GATES);
    }
    else
        return 0;
}

string findGateName(gates* gate, map<string,gates*> &GATES){
    for(auto it=GATES.begin(); it!=GATES.end(); ++it){
        if(it->second == gate)
            return it->first;
    }
    return "";
}

gates* findGateFromOutputWire(wire WIRE, map<string, gates*> &GATES){
    for(auto it=GATES.begin(); it!=GATES.end(); ++it){
        if(it->second->out()==WIRE)
            return it->second;
    }
    return 0;
}
