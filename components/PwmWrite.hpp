/* microflo_component yaml
name: PwmWrite
description: "Set duty cycle [0-100%] of PWM pin"
inports:
  dutycycle:
    type: all
    description: ""
    triggering: true
  pin:
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
microflo_component */
class PwmWrite : public SingleOutputComponent {
public:
    PwmWrite()
        : outPin(-1)
    {}

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace PwmWritePorts;

        if (port == InPorts::dutycycle && in.isData()) {
            io->PwmWrite(outPin, in.asInteger());
            send(in, OutPorts::out);
        } else if (port == InPorts::pin && in.isNumber()) {
            outPin = in.asInteger();
            io->PinSetMode(outPin, IO::OutputPin);
        }
    }
private:
    int8_t outPin;
};
