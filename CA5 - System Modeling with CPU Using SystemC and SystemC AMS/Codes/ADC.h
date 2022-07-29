#include <systemc-ams.h>

#define NBits 16
#define Vs 1000

SCA_TDF_MODULE(ADC)
{
public:
    sca_tdf::sca_in<double> in;
    sca_tdf::sca_out<sc_dt::sc_int<NBits> > out;
    ADC(sc_core::sc_module_name nm, double v_max_)
    : in("in"), out("out"), v_max(v_max_){set_timestep(sc_time(100, SC_NS));};
    
    void processing()
    { 
        using namespace std;

        double v_in = in.read();

        if (v_in < -v_max) {
            out.write(-Vs);
        } else if (v_in > v_max) {
            out.write(Vs);
        } else {
            sc_dt::sc_int<NBits> q_v_in;
            q_v_in = lround((v_in / v_max) * Vs);
            out.write(q_v_in);
        }
    }
 
private:
    const double v_max;
};

