/* microflo_component yaml
name: MapLinear
description: "Map the integer @in from range [@inmin,@inmax] to [@outmin,@outmax]"
inports:
  in:
    type: all
    description: ""
  inmin:
    type: all
    description: ""
  inmax:
    type: all
    description: ""
  outmin:
    type: all
    description: ""
  outmax:
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
microflo_component */
class MapLinear : public SingleOutputComponent {
public:
    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace MapLinearPorts;
        if (in.isSetup()) {
            // no defaults
        } else if (port == InPorts::inmin && in.isData()) {
            inmin = in.asInteger();
        } else if (port == InPorts::inmax && in.isData()) {
            inmax = in.asInteger();
        } else if (port == InPorts::outmin && in.isData()) {
            outmin = in.asInteger();
        } else if (port == InPorts::outmax && in.isData()) {
            outmax = in.asInteger();
        } else if (port == InPorts::in && in.isNumber()) {
            send(Packet(map(in.asInteger())));
        }
    }
private:
    long map(long in) {
        return (in-inmin) * (outmax-outmin) / (inmax-inmin) + outmin;
    }
    long inmin;
    long inmax;
    long outmax;
    long outmin;
};
