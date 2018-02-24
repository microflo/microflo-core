/* microflo_component yaml
name: ForwardIf
description: "Forward a packet only if it contains a Boolean 'true' value."
icon: "forward"
inports:
  in:
    type: all
    description: ""
outports:
  out:
    type: bool
    description: ""
microflo_component */
/**
 * Component that only forwards a packet if it contains a Boolean true value.
 */
class ForwardIf : public SingleOutputComponent {
public:
    virtual void process(Packet in, MicroFlo::PortId port) {
        if (in.isData()) {
            bool input = (bool) in.asBool();
            if (input) {
                Packet p =  Packet(input);
                send(p);
            }
            
        }
    }
};
