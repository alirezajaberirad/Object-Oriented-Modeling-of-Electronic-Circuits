#include "generateVerilog.h"

void simulate(fstream &file, vector<string> &inputs, vector<string> &outputs, map<string,gates*> &GATES, map<string,wire> &wires);

void simulate(int present_time, string str, vector<string> &inputs, vector<string> &outputs, map<string,gates*> &GATES, map<string,wire> &wires);
