/* microflo_component yaml
name: ArduinoUno
description: Convenient definition of pins available on Arduino Uno
inports:
  in:
    type: all
    description: ''
outports:
  pin0:
    type: all
    description: ""
  pin1:
    type: all
    description: ""
  pin2:
    type: all
    description: ""
  pin3:
    type: all
    description: ""
  pin4:
    type: all
    description: ""
  pin5:
    type: all
    description: ""
  pin6:
    type: all
    description: ""
  pin7:
    type: all
    description: ""
  pin8:
    type: all
    description: ""
  pin9:
    type: all
    description: ""
  pin10:
    type: all
    description: ""
  pin11:
    type: all
    description: ""
  pin12:
    type: all
    description: ""
  pin13:
    type: all
    description: ""
  pina0:
    type: all
    description: ""
  pina1:
    type: all
    description: ""
  pina2:
    type: all
    description: ""
  pina3:
    type: all
    description: ""
  pina4:
    type: all
    description: ""
  pina5:
    type: all
    description: ""
microflo_component */
class ArduinoUno : public Component {
public:
    ArduinoUno() : Component(outPorts, ArduinoUnoPorts::OutPorts::pina5+1) {}
    virtual void process(Packet in, MicroFlo::PortId port) {
        const MicroFlo::PortId digitalPins = 14;
        const MicroFlo::PortId analogPins = 6;
        if (port == ArduinoUnoPorts::InPorts::in) {
            for (MicroFlo::PortId outPort=0; outPort < digitalPins+analogPins; outPort++) {
                // Emit 0 for A0, 1 for A1, and so on
                const long val = (outPort < digitalPins) ? outPort : outPort - digitalPins;
                send(Packet(val), outPort);
            }
        }
    }
private:
    Connection outPorts[ArduinoUnoPorts::OutPorts::pina5+1];
};
