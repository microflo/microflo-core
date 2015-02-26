/* microflo_component yaml
name: InvertBoolean
description: "Invert incoming boolean value. Logical equivalent: NOT"
inports:
  in:
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
microflo_component */
class InvertBoolean : public SingleOutputComponent {
public:
    virtual void process(Packet in, MicroFlo::PortId port) {
        if (in.isData()) {
            Packet p = Packet((bool)!in.asBool());
            send(p);
        }
    }
};
