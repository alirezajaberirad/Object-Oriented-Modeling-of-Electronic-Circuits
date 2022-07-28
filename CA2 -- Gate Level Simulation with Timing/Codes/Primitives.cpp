#include "Primitives.h"

#define MAX(a,b) ((a>b)?a:b)

int calculateEventTime(char lastValue, char newValue,
                       int in1LastEvent, int in2LastEvent,
                       int gateDelay, int lastEvent){

    if(lastValue == newValue)
        return lastEvent;
    else
        return gateDelay + MAX(in1LastEvent,in2LastEvent);
}

int calculateEventTime(char lastValue, char newValue,
                       int in1LastEvent, int gateDelay,
                       int lastEvent){
    if(lastValue==newValue)
        return lastEvent;
    else
        return gateDelay+in1LastEvent;
}

int wire::numberOfWires=1;

void gates::evl(){
    o1->value=i1->value;
    Level=MAX(i1->Level,i2->Level)+1;
    o1->Level=Level;
    gates::timingActivity1();
}

void gates::timingActivity1(){
    o1->eventTime = calculateEventTime(lastValue, o1->value,
                                       i1->eventTime, gateDelay, lastEvent);

    o1->activityCount = i1->activityCount + ((lastValue==o1->value)?0:1);

    lastEvent = o1->eventTime;
    lastValue = o1->value;
}

void gates::timingActivity2(){
    o1->eventTime = calculateEventTime(lastValue, o1->value,
                                       i1->eventTime, i2->eventTime,
                                       gateDelay, lastEvent);

    o1->activityCount = i1->activityCount + i2->activityCount + ((lastValue==o1->value)?0:1);

    lastEvent = o1->eventTime;
    lastValue = o1->value;
}

int gates::numberOfGates=1;


void NOT::evl() {

	if (i1->value == '0')
		o1->value = '1';
	else if (i1->value == '1')
		o1->value = '0';
	else
		o1->value = 'X';

    Level=i1->Level+1;
    o1->Level=Level;

    outputControllability = 1.0 - i1->controllability;
	o1->controllability = outputControllability;

	i1->observability = o1->observability;
	outputObservability=o1->observability;

	gates::timingActivity1();
}

void AND::evl(){
    if ((i1->value == '0') || (i2->value == '0'))
		o1->value = '0';
	else if ((i1->value == '1') && (i2->value == '1'))
		o1->value = '1';
	else
		o1->value = 'X';

    Level=MAX(i1->Level,i2->Level)+1;
    o1->Level=Level;

    outputControllability = i1->controllability * i2->controllability;
    o1->controllability  = outputControllability;

    i1->observability = o1->observability * i2->controllability;
    i2->observability = o1->observability * i1->controllability;

    outputObservability=o1->observability;

	gates::timingActivity2();
}

void NAND::evl(){
    if ((i1->value == '0') || (i2->value == '0'))
		o1->value = '1';
	else if ((i1->value == '1') && (i2->value == '1'))
		o1->value = '0';
	else
		o1->value = 'X';

    Level=MAX(i1->Level,i2->Level)+1;
    o1->Level=Level;

    outputControllability = 1 - i1->controllability * i2->controllability;
    o1->controllability  = outputControllability;

    i1->observability = o1->observability * i2->controllability;
    i2->observability = o1->observability * i1->controllability;

    outputObservability=o1->observability;

	gates::timingActivity2();
}

void OR::evl() {

	if ((i1->value == '1') || (i2->value == '1'))
		o1->value = '1';
	else if ((i1->value=='0')&&(i2->value=='0'))
		o1->value='0';
	else
		o1->value='X';

    Level=MAX(i1->Level,i2->Level)+1;
    o1->Level=Level;

    outputControllability = 1 - i1->controllability * i2->controllability;
	o1->controllability = outputControllability;

	i1->observability = o1->observability * (1 - i2->controllability);
    i2->observability = o1->observability * (1 - i1->controllability);

    outputObservability=o1->observability;

	gates::timingActivity2();
}

void NOR::evl() {

	if ((i1->value == '1') || (i2->value == '1'))
		o1->value = '0';
	else if ((i1->value=='0')&&(i2->value=='0'))
		o1->value='1';
	else
		o1->value='X';

    Level=MAX(i1->Level,i2->Level)+1;
    o1->Level=Level;

    outputControllability = i1->controllability * i2->controllability;
	o1->controllability = outputControllability;

    i1->observability = o1->observability * (1 - i2->controllability);
    i2->observability = o1->observability * (1 - i1->controllability);

    outputObservability=o1->observability;

	gates::timingActivity2();
}

void XOR::evl () {

	if ((i1->value == 'X') || (i2->value == 'X') ||
		(i1->value == 'Z') || (i2->value == 'Z'))
		o1->value = 'X';
	else if (i1->value==i2->value)
		o1->value='0';
	else
		o1->value='1';

    Level=MAX(i1->Level,i2->Level)+1;
    o1->Level=Level;

    outputControllability = 1 - 2 * i1->controllability * i2->controllability;
	o1->controllability = outputControllability;

	i1->observability = o1->observability * MAX(i2->controllability,(1-i2->controllability));
    i2->observability = o1->observability * MAX(i1->controllability,(1-i1->controllability));

    outputObservability=o1->observability;

	gates::timingActivity2();
}
