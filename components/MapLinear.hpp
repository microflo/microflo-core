/* microflo_component yaml
name: MapLinear
description: "Map the integer @in from range [@inmin,@inmax] to [@outmin,@outmax]"
inports:
  in:
    type: integer
    description: ""
    triggering: true
  inmin:
    type: integer
    description: ""
  inmax:
    type: integer
    description: ""
  outmin:
    type: integer
    description: ""
  outmax:
    type: integer
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

        if (port == InPorts::inmin) {
            inmin = in.asInteger();
        } else if (port == InPorts::inmax) {
            inmax = in.asInteger();
        } else if (port == InPorts::outmin) {
            outmin = in.asInteger();
        } else if (port == InPorts::outmax) {
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
