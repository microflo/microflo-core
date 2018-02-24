/* microflo_component yaml
name: Count
description: "Count upwards from 0, with step 1"
icon: "sort-numeric-asc"
inports:
  in:
    type: bang
    description: ""
    triggering: true
  reset:
    type: bool
    description: ""
    triggering: true
outports:
  out:
    type: integer
    description: ""
microflo_component */
class Count : public SingleOutputComponent {
public:
    Count()
        : current(-1)
        , isReset(false)
    {}

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace CountPorts;
        if (port == InPorts::in) {
            if (!isReset) {
                current += 1;
            }
            send(Packet(current));
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
