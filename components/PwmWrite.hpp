/* microflo_component yaml
name: PwmWrite
description: "Set duty cycle [0-100%] of PWM pin"
inports:
  dutycycle:
    type: all
    description: ""
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
    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace PwmWritePorts;
        if (in.isSetup()) {
            // no defaults
        } else if (port == InPorts::dutycycle && in.isData()) {
            io->PwmWrite(outPin, in.asInteger());
            send(in, OutPorts::out);
        } else if (port == InPorts::pin && in.isNumber()) {
            outPin = in.asInteger();
            io->PinSetMode(outPin, IO::OutputPin);
        }
    }
private:
    MicroFlo::PortId outPin;
};
