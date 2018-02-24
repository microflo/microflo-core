/* microflo_component yaml
name: Route
description: "Pass packets to @out from input port number @port"
icon: "code-fork"
inports:
  port:
    type: integer
    description: ""
  in1:
    type: all
    description: ""
  in2:
    type: all
    description: ""
  in3:
    type: all
    description: ""
  in4:
    type: all
    description: ""
  in5:
    type: all
    description: ""
  in6:
    type: all
    description: ""
  in7:
    type: all
    description: ""
  in8:
    type: all
    description: ""
  in9:
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
microflo_component */
class Route : public SingleOutputComponent {

public:
    Route() : activePort(0) {
        for (MicroFlo::PortId i=0; i<RoutePorts::InPorts::in9; i++) {
            lastPackets[i] = Packet(MsgInvalid);
        }
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace RoutePorts;
        if (port == InPorts::port) {
            activePort = in.asInteger();
            if (activePort > 0 && activePort < InPorts::in9) {
                Packet &p = lastPackets[activePort];
                if (p.type() != MsgInvalid) {
                    send(p);
                }
            }
        } else {
            if (in.isData()) {
                lastPackets[port] = in;
                if (port == activePort) {
                    send(in);
                }
            }
        }
    }
private:
    Packet lastPackets[RoutePorts::InPorts::in9];
    MicroFlo::PortId activePort;
};
