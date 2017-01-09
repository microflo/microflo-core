/* microflo_component yaml
name: Delimit
description: ""
inports:
  in:
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
microflo_component */
class Delimit : public SingleOutputComponent {
public:
    Delimit(): startBracketRecieved(false) {}
    virtual void process(Packet in, MicroFlo::PortId port) {
        if (in.isSetup()) {
            delimiter = '\r';
        }
        if (startBracketRecieved) {
            if (in.isEndBracket()) {
                startBracketRecieved = false;
                send(Packet(delimiter));
            } else {
                send(in);
            }
        } else {
            if (in.isStartBracket()) {
                startBracketRecieved = true;
            } else if (in.isData()) {
                send(in);
                send(Packet(delimiter));
            }
        }
    }
private:
    bool startBracketRecieved;
    char delimiter;
};
