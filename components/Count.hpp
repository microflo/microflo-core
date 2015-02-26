/* microflo_component yaml
name: Count
description: "Count upwards from 0, with step 1"
inports:
  in:
    type: all
    description: ""
  reset:
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
microflo_component */
class Count : public SingleOutputComponent {
public:
    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace CountPorts;
        if (in.isSetup()) {
            current = 0;
            isReset = false;
            send(Packet(current));
        } else if (port == InPorts::in) {
            if (!isReset) {
                current += 1;
                send(Packet(current));
            }
        } else if (port == InPorts::reset) {
            if (in.isBool()) {
                isReset = in.asBool();
            }
            if (isReset || in.isVoid()) {
                current = 0;
                send(Packet(current));
            }
        }
    }
private:
    long current;
    bool isReset;
};
