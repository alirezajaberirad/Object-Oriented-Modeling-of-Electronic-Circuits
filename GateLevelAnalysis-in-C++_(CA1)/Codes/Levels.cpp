#include "Levels.h"

void recognizeLevel(map<string,gates*> GATES){
    for(int i=0; i<GATES.size(); i++)
        for(auto it=GATES.begin(); it!=GATES.end(); it++)
            it->second->evl();

    for(auto it=GATES.begin(); it!=GATES.end(); it++)
        cout<<"Level of "<<it->first<<" is: "<<it->second->Level<<endl;
}
