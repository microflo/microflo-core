/* microflo_component yaml
name: ATUSBKEY
description: Convenient definition of pins available on Atmel AT90USBKEY
inports: {}
outports:
  porta0:
    type: all
    description: ""
  porta1:
    type: all
    description: ""
  porta2:
    type: all
    description: ""
  porta3:
    type: all
    description: ""
  porta4:
    type: all
    description: ""
  porta5:
    type: all
    description: ""
  porta6:
    type: all
    description: ""
  porta7:
    type: all
    description: ""
  portb0:
    type: all
    description: ""
  portb1:
    type: all
    description: ""
  portb2:
    type: all
    description: ""
  portb3:
    type: all
    description: ""
  portb4:
    type: all
    description: ""
  portb5:
    type: all
    description: ""
  portb6:
    type: all
    description: ""
  portb7:
    type: all
    description: ""
  portc0:
    type: all
    description: ""
  portc1:
    type: all
    description: ""
  portc2:
    type: all
    description: ""
  portc3:
    type: all
    description: ""
  portc4:
    type: all
    description: ""
  portc5:
    type: all
    description: ""
  portc6:
    type: all
    description: ""
  portc7:
    type: all
    description: ""
  portd0:
    type: all
    description: ""
  portd1:
    type: all
    description: ""
  portd2:
    type: all
    description: ""
  portd3:
    type: all
    description: ""
  portd4:
    type: all
    description: ""
  portd5:
    type: all
    description: ""
  portd6:
    type: all
    description: ""
  portd7:
    type: all
    description: ""
  porte0:
    type: all
    description: ""
  porte1:
    type: all
    description: ""
  porte2:
    type: all
    description: ""
  porte3:
    type: all
    description: ""
  porte4:
    type: all
    description: ""
  porte5:
    type: all
    description: ""
  porte6:
    type: all
    description: ""
  porte7:
    type: all
    description: ""
  portf0:
    type: all
    description: ""
  portf1:
    type: all
    description: ""
  portf2:
    type: all
    description: ""
  portf3:
    type: all
    description: ""
  portf4:
    type: all
    description: ""
  portf5:
    type: all
    description: ""
  portf6:
    type: all
    description: ""
  portf7:
    type: all
    description: ""
microflo_component */
class ATUSBKEY : public Component {
public:
    ATUSBKEY() : Component(outPorts, ATUSBKEYPorts::OutPorts::portf7) {}
    virtual void process(Packet in, MicroFlo::PortId port) {
        // FIXME: separate between analog/digital capable ports (also PWM etc)
        if (in.isSetup()) {
            for (int outPort=0; outPort < ATUSBKEYPorts::OutPorts::portf7; outPort++) {
                const long val = outPort;
                send(Packet(val), outPort);
            }
        }
    }
private:
    Connection outPorts[ATUSBKEYPorts::OutPorts::portf7];
};
