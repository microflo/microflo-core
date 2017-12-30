/* microflo_component yaml
name: Constrain
description: "Constrain a number to the range [@lower,@upper]"
inports:
  in:
    type: integer
    description: ""
    triggering: true
  lower:
    type: integer
    description: ""
  upper:
    type: integer
    description: ""
outports:
  out:
    type: integer
    description: ""
microflo_component */

class Constrain : public SingleOutputComponent {

public:
    Constrain()
        : lower(0)
        , upper(0)
    {}

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace ConstrainPorts;
        if (port == InPorts::lower) {
            lower = in.asInteger();
        } else if (port == InPorts::upper) {
            upper = in.asInteger();
        } else if (port == InPorts::in && in.isNumber()) {
            const auto input = in.asInteger();
            send(Packet(this->_constrain(input)));
        }
    }
private:
    long _constrain(long input) {
        if (input > upper)
            return upper;
        else if (input < lower)
            return lower;
        else
            return input;
    }
    long lower;
    long upper;
};
