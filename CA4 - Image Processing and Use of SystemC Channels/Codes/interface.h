#include <systemc.h>

class put_if : virtual public sc_interface{
    public:
        virtual void put(sc_lv<8>) = 0;
};

class get_if : virtual public sc_interface{
    public:
        virtual void get(sc_lv<8> &) = 0;
};

class channel : public put_if, public get_if{
    bool full;
    sc_lv<8> data;
    sc_event put_event, get_event;

public:
    channel():full(false) {};
    ~channel(){};

    void put(sc_lv<8> in_data){
        if(full == true) wait(get_event);
        data = in_data;
        full = true;
        put_event.notify();
    }

    void get(sc_lv<8> &out_data){
        if(full == false) wait(put_event);
        out_data = data;
        full = false;
        get_event.notify();
    }

};