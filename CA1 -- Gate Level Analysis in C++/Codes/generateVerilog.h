#include "Levels.h"

void generateVerilog(vector<string> &inputs, vector<string> &outputs, vector<string> &otherWires, map<string,gates*> &GATES, map<string,wire> &wires);
void generateGates(ofstream&, map<string,gates*> &GATES, map<string,wire> &wires);
string findWireName(wire, map<string,wire>&);
