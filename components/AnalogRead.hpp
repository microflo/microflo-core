/* microflo_component yaml
name: AnalogRead
description: "Read analog value from pin. Value=[0-1023]"
inports:
  trigger:
    type: bang
    description: ""
  pin:
    type: integer
    description: ""
outports:
  out:
    type: integer
    description: ""
microflo_component */
class AnalogRead : public SingleOutputComponent {
public:
    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace AnalogReadPorts;

        if (port == InPorts::trigger) {
            const long val = io->AnalogRead(pin);
            send(Packet(val));
        } else if (port == InPorts::pin && in.isNumber()) {
            pin = in.asInteger();
            io->PinSetMode(pin, IO::InputPin);
        }
    }
private:
    MicroFlo::PortId pin;
};
