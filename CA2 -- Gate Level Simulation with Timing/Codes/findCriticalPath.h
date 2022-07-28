#include "simulate.h"
#include <algorithm>

struct pathAndDelay{
    vector<string> path;
    int delay;
};

void findCriticalPath(vector<string> &criticalPath, vector<string> &inputs, vector<string> &outputs, map<string,gates*> &GATES, map<string,wire> &wires);

int wireCriticalPath(vector<string>&criticalPath, wire WIRE, map<string,wire> &wires, vector<string>&inputs, map<string,gates*> &GATES);
int wireCriticalPath(wire WIRE, map<string,wire> &wires, vector<string>&inputs, map<string,gates*> &GATES);

string findGateName(gates* gate, map<string,gates*> &GATES);

gates* findGateFromOutputWire(wire WIRE, map<string, gates*> &GATES);
