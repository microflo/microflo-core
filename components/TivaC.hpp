/* microflo_component yaml
name: TivaC
description: Convenient definition of pins available for GPIO Texas Instruments Tiva-C
inports: {}
outports:
  pa0:
    type: all
    description: ""
  pa1:
    type: all
    description: ""
  pa2:
    type: all
    description: ""
  pa3:
    type: all
    description: ""
  pa4:
    type: all
    description: ""
  pa5:
    type: all
    description: ""
  pa6:
    type: all
    description: ""
  pa7:
    type: all
    description: ""
  pb0:
    type: all
    description: ""
  pb1:
    type: all
    description: ""
  pb2:
    type: all
    description: ""
  pb3:
    type: all
    description: ""
  pb4:
    type: all
    description: ""
  pb5:
    type: all
    description: ""
  pb6:
    type: all
    description: ""
  pb7:
    type: all
    description: ""
  pc0:
    type: all
    description: ""
  pc1:
    type: all
    description: ""
  pc2:
    type: all
    description: ""
  pc3:
    type: all
    description: ""
  pc4:
    type: all
    description: ""
  pc5:
    type: all
    description: ""
  pc6:
    type: all
    description: ""
  pc7:
    type: all
    description: ""
  pd0:
    type: all
    description: ""
  pd1:
    type: all
    description: ""
  pd2:
    type: all
    description: ""
  pd3:
    type: all
    description: ""
  pd4:
    type: all
    description: ""
  pd5:
    type: all
    description: ""
  pd6:
    type: all
    description: ""
  pd7:
    type: all
    description: ""
  pe0:
    type: all
    description: ""
  pe1:
    type: all
    description: ""
  pe2:
    type: all
    description: ""
  pe3:
    type: all
    description: ""
  pe4:
    type: all
    description: ""
  pe5:
    type: all
    description: ""
  pe6:
    type: all
    description: ""
  pe7:
    type: all
    description: ""
  pf0:
    type: all
    description: ""
  pf1:
    type: all
    description: ""
  pf2:
    type: all
    description: ""
  pf3:
    type: all
    description: ""
  pf4:
    type: all
    description: ""
  pf5:
    type: all
    description: ""
  pf6:
    type: all
    description: ""
  pf7:
    type: all
    description: ""
microflo_component */

class TivaC : public Component {
public:
    TivaC() : Component(outPorts, TivaCPorts::OutPorts::pf7+1) {}
    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace TivaCPorts;
        if (in.isSetup()) {
            for (int outPort=0; outPort < TivaCPorts::OutPorts::pf7; outPort++) {
                const long val = outPort;
                send(Packet(val), outPort);
            }
        }
    }
private:
    Connection outPorts[TivaCPorts::OutPorts::pf7+1];
};
