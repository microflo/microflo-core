/* microflo_component yaml
name: BoolToInt
description: "Convert boolean input to integer. true->1, false->0"
inports:
  in:
    type: bool
    description: ""
outports:
  out:
    type: integer
    description: ""
microflo_component */
// Functor for PureFunctionComponent1
struct BoolToIntF {
    Packet operator() (Packet in) { return Packet((long)(in.asBool() ? 1 : 0)); }
};

class BoolToInt : public SingleOutputComponent {
public:
    virtual void process(Packet in, MicroFlo::PortId port) {
        if (in.isBool()) {
            send(BoolToIntF()(in));
        }
    }
};
