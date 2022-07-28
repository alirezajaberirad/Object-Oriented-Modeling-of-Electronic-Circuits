#include <iostream>
#include <string>
using namespace std;

class wire{
protected:
    static int numberOfWires;
public:
    char value;
    int eventTime=0;
    int Level=0;
    int activityCount=0;
    float controllability=0.5;

    int wireID;

    wire(char c, int d):value(c), eventTime(d){
        wireID=numberOfWires;
        numberOfWires++;
    }
    wire(){
        wireID=numberOfWires;
        numberOfWires++;
    }
    void put(char a){value=a;}
    void put(char a, int d){ value=a; eventTime=d;}
    void get(char &a){a=value;}
    void get(char& a, int& d){ a=value; d=eventTime;}
    int activity(){return activityCount;}
    friend bool operator==(wire& a, wire& b){if(a.wireID == b.wireID) return true;  else return false;}
};

class gates{
protected:
    wire *i1, *i2, *o1;
    int gateDelay, lastEvent;
    char lastValue;

    void timingActivity2();
    void timingActivity1();
    static int numberOfGates;

public:
    int Level;
    int gateID;
    float outputControllability=1.0;
    gates(wire& a, wire& b, wire& w, int d):
        i1(&a), i2(&b), o1(&w), gateDelay(d){
        gateID=numberOfGates;
        numberOfGates++;
        }
    gates(wire& a, wire& b, wire& w):
        i1(&a), i2(&b), o1(&w), gateDelay(0){
        gateID=numberOfGates;
        numberOfGates++;
        }
    gates(wire& a, wire& w, int d):
        i1(&a), o1(&w), gateDelay(d){
        gateID=numberOfGates;
        numberOfGates++;
        }
    gates(wire& a, wire& w):
        i1(&a), o1(&w), gateDelay(0){
        gateID=numberOfGates;
        numberOfGates++;
        }
    gates(){};
    ~gates(){};
    virtual wire out(){return *o1;}
    virtual wire in1(){return *i1;}
    virtual wire in2(){return *i2;}
    virtual wire in(){return *i1;}
    virtual string type()=0;
    virtual void evl();
};

float getProb(gates*);
float evl(gates*);

class NOT: public gates{
public:
    NOT(wire& a, wire& w, int d): gates(a,w,d){};
    NOT(wire& a, wire& w): gates(a,w){};
    ~NOT();
    string type(){return "not";};
    void evl();
};

class AND: public gates{
public:
    AND(wire& a, wire& b, wire& w, int d): gates(a,b,w,d){};
    AND(wire& a, wire& b, wire& w): gates(a,b,w){};
    ~AND();
    string type(){return "and";};
    void evl();
};

class NAND: public gates{
public:
    NAND(wire& a, wire& b, wire& w, int d): gates(a,b,w,d){};
    NAND(wire& a, wire& b, wire& w): gates(a,b,w){};
    ~NAND();
    string type(){return "nand";};
    void evl();
};

class OR: public gates{
public:
    OR(wire& a, wire& b, wire& w, int d): gates(a,b,w,d){};
    OR(wire& a, wire& b, wire& w): gates(a,b,w){};
    ~OR();
    string type(){return "or";};
    void evl();
};

class NOR: public gates{
public:
    NOR(wire& a, wire& b, wire& w, int d): gates(a,b,w,d){};
    NOR(wire& a, wire& b, wire& w): gates(a,b,w){};
    ~NOR();
    string type(){return "nor";};
    void evl();
};

class XOR: public gates{
public:
    XOR(wire& a, wire& b, wire& w, int d): gates(a,b,w,d){};
    XOR(wire& a, wire& b, wire& w): gates(a,b,w){};
    ~XOR();
    string type(){return "xor";};
    void evl();
};
