/* microflo_component yaml
name: MbedLPC
description: Convenient definition of pins available on Mbed LPC1768
inports:
  in:
    type: bang
    description: ""
    triggering: true
outports:
  led1:
    type: all
    description: ""
  led2:
    type: all
    description: ""
  led3:
    type: all
    description: ""
  led4:
    type: all
    description: ""
  pin21:
    type: all
    description: ""
  pin22:
    type: all
    description: ""
  pin23:
    type: all
    description: ""
  pin24:
    type: all
    description: ""
microflo_component */
#ifdef TARGET_LPC1768
#include <mbed.h>
#endif

#ifdef TARGET_LPC1768

class MbedLPC : public Component {
public:
    MbedLPC() : Component(outPorts, MbedLPCPorts::OutPorts::pin24+1) {}
    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace MbedLPCPorts;
        if (port == InPorts::in) {
            send(Packet((long)LED1), OutPorts::led1);
            send(Packet((long)LED2), OutPorts::led2);
            send(Packet((long)LED3), OutPorts::led3);
            send(Packet((long)LED4), OutPorts::led4);
            send(Packet((long)p21), OutPorts::pin21);
            send(Packet((long)p22), OutPorts::pin22);
            send(Packet((long)p23), OutPorts::pin23);
            send(Packet((long)p24), OutPorts::pin24);
        }
    }
private:
    Connection outPorts[MbedLPCPorts::OutPorts::pin24+1];
};

#else
class MbedLPC : public DummyComponent { };
#endif
