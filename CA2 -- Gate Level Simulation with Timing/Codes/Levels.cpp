#include "Levels.h"

#define MAX(a,b) ((a>b)?a:b)

void recognizeLevel(map<string,gates*> GATES){
    int maxLevel=0;
    cout<<"\n\n";
    for(int i=0; i<GATES.size(); i++)
        for(auto it=GATES.begin(); it!=GATES.end(); it++){
            it->second->evl();
            maxLevel=MAX(maxLevel, it->second->Level);
        }

    for(auto it=GATES.begin(); it!=GATES.end(); it++)
        cout<<"Level of "<<it->first<<" is: "<<it->second->Level<<endl;

    int gatesEncountered=0;
    while(gatesEncountered!=GATES.size()){
        for(auto it=GATES.begin(); it!=GATES.end(); ++it){
            if(it->second->Level == maxLevel){
                gatesEncountered++;
                it->second->evl();
            }
        }
        maxLevel--;
    }
}
