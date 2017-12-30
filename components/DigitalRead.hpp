/* microflo_component yaml
name: DigitalRead
description: "Read a boolean value from pin. Value is read on @trigger"
inports:
  trigger:
    type: bang
    description: ""
    triggering: true
  pin:
    type: integer
    description: ""
    triggering: true
  pullup:
    type: true
    description: ""
    triggering: true
outports:
  out:
    type: bool
    description: ""
microflo_component */
class DigitalRead : public SingleOutputComponent {
public:
    DigitalRead()
        : pin(-1)
        , pullup(true)
    {
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace DigitalReadPorts;

        if (port == InPorts::trigger) {
            const bool isHigh = io->DigitalRead(pin);
            send(Packet(isHigh));
        } else if (port == InPorts::pin && in.isNumber()) {
            setPinAndPullup(in.asInteger(), pullup);
        } else if (port == InPorts::pullup && in.isBool()) {
            setPinAndPullup(pin, in.asBool());
        }
    }
private:
    void setPinAndPullup(int newPin, bool newPullup) {
        pin = newPin;
        pullup = newPullup;
        if (pin != -1) {
            io->PinSetMode(pin, IO::InputPin);
            io->PinSetPullup(pin, pullup ? IO::PullUp : IO::PullNone);
        }
    }
    int8_t pin;
    bool pullup;
};
