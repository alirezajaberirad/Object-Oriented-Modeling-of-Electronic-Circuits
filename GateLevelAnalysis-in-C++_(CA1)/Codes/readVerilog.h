#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "Primitives.h"

void readVerilog(fstream &file, vector<string> &inputs, vector<string> &outputs, vector<string> &otherWires, map<string,gates*> &GATES, map<string,wire> &wires);
void handleWires(string line, string type, vector<string>& inputNames, map<string,wire>& wires);
void handleGates(string line, map<string,gates*>& GATES, map<string,wire>& wires);
void handleCSV(string str, map<string,wire>& wires);
void handleCSV(string str, vector<string>& inputNames, map<string,wire>& wires);
bool isNot(string str);
