#include "readVerilog.h"

void readVerilog(fstream& file, vector<string> &inputs, vector<string> &outputs, vector<string> &otherWires, map<string,gates*> &GATES, map<string,wire> &wires){
    string line;
    cout<<"Input Verilog file is: \n"<<endl;
    while(!file.eof()){
        getline(file, line);
        cout<<line<<endl;
        handleWires(line,"input",inputs,wires);
        handleWires(line,"output",outputs,wires);
        handleWires(line,"wire",otherWires,wires);
        handleGates(line,GATES,wires);
    }
}

void handleWires(string line, string type, vector<string>& outputNames, map<string,wire>& wires){
    string outputNamesStr;
    regex ex("^[ ]*"+type+"[ ]+(.+)[ ]*[;].*");
    if(!regex_match(line,ex))
        return;

    //extracting the input names from the expression
    smatch match;
    regex_search(line,match,ex);
    outputNamesStr=match[1];
    handleCSV(outputNamesStr,outputNames,wires);
    return;
}



void handleCSV(string str, vector<string>& inputNames, map<string,wire>& wires){
    stringstream ss(str);

    while (ss.good()) {
        wire a;
        string substr;
        getline(ss, substr, ',');
        wires.insert(pair<string,wire>(substr,a));
        inputNames.push_back(substr);
        //cout<<(--wires.end())->first<<endl;
    }
    //for(auto it=inputNames.begin(); it!=inputNames.end(); it++)
      //  cout<<*it<<endl;
}

void handleGates(string line, map<string,gates*>& GATES, map<string,wire>& wires){
    if(!isNot(line)){
        regex ex("^[ ]*nand[ ]+([[:w:]]+)[ ]*[\(][ ]*([[:w:]]+)[ ]*[,][ ]*([[:w:]]+)[ ]*,[ ]*([[:w:]]+)[ ]*[\)][ ]*[;].*");
        smatch match;
        if(regex_search(line, match, ex)){
            GATES.insert(pair<string,gates*>(match[1],new NAND(wires.find(match[3])->second, wires.find(match[4])->second, wires.find(match[2])->second)));
            return;
        }

        ex="^[ ]*and[ ]+([[:w:]]+)[ ]*[\(][ ]*([[:w:]]+)[ ]*[,][ ]*([[:w:]]+)[ ]*,[ ]*([[:w:]]+)[ ]*[\)][ ]*[;].*";
        if(regex_search(line, match, ex)){
            GATES.insert(pair<string,gates*>(match[1],new AND(wires.find(match[3])->second, wires.find(match[4])->second, wires.find(match[2])->second)));
            return;
        }

        ex="^[ ]*or[ ]+([[:w:]]+)[ ]*[\(][ ]*([[:w:]]+)[ ]*[,][ ]*([[:w:]]+)[ ]*,[ ]*([[:w:]]+)[ ]*[\)][ ]*[;].*";
        if(regex_search(line, match, ex)){
            GATES.insert(pair<string,gates*>(match[1],new OR(wires.find(match[3])->second, wires.find(match[4])->second, wires.find(match[2])->second)));
            return;
        }

        ex="^[ ]*nor[ ]+([[:w:]]+)[ ]*[\(][ ]*([[:w:]]+)[ ]*[,][ ]*([[:w:]]+)[ ]*,[ ]*([[:w:]]+)[ ]*[\)][ ]*[;].*";
        if(regex_search(line, match, ex)){
            GATES.insert(pair<string,gates*>(match[1],new NOR(wires.find(match[3])->second, wires.find(match[4])->second, wires.find(match[2])->second)));
            return;
        }

        ex="^[ ]*xor[ ]+([[:w:]]+)[ ]*[\(][ ]*([[:w:]]+)[ ]*[,][ ]*([[:w:]]+)[ ]*,[ ]*([[:w:]]+)[ ]*[\)][ ]*[;].*";
        if(regex_search(line, match, ex)){
            GATES.insert(pair<string,gates*>(match[1],new XOR(wires.find(match[3])->second, wires.find(match[4])->second, wires.find(match[2])->second)));
            return;
        }

        return;
    }
    else{
        regex ex("^[ ]*not[ ]+([[:w:]]+)[ ]*[\(][ ]*([[:w:]]+)[ ]*[,][ ]*([[:w:]]+)[ ]*[\)][ ]*[;].*");
        smatch match;
        if(regex_search(line, match, ex)){
            GATES.insert(pair<string,gates*>(match[1],new NOT(wires.find(match[3])->second, wires.find(match[2])->second)));
            return;
        }
    }
}

bool isNot(string str){
    regex ex("^[ ]*not.+");
    return regex_match(str,ex);
}
