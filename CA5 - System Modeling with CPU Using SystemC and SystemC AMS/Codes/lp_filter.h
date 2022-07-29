#include <systemc.h>
#include <systemc-ams.h>

SC_MODULE(lp_filter){
private:
    sca_eln::sca_node a;
    sca_eln::sca_node b;
    sca_eln::sca_node_ref gnd;
public:
    sc_in<double> in;
    sca_tdf::sca_out<double> out;
 
    sca_eln::sca_r r1; 
    sca_eln::sca_c c1;
    sca_eln::sca_de::sca_vsource vin;
    sca_eln::sca_tdf::sca_vsink vout;

    SC_HAS_PROCESS(sc_module_name);
    lp_filter(sc_module_name, double r1_value, double c1_value):
        r1("r1", r1_value), c1("c1", c1_value), vin("vin",5.0), vout("vout",5.0){
            vin.p(a);
            vin.n(gnd);
            vin.inp(in);
            vin.set_timestep(100, SC_NS);

            r1.n(a);
            r1.p(b);

            c1.n(b);
            c1.p(gnd);

            vout.p(b);
            vout.n(gnd);
            vout.outp(out);
        }
};