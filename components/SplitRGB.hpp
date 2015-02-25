#define RGB_CHANNELS 3

class SplitRGB : public Component {
public:
    SplitRGB() : Component(outPorts, RGB_CHANNELS) {}

    virtual void process(Packet in, MicroFlo::PortId inport) {
        using namespace SplitRGBPorts;
        if (!in.isData()) {
            return;
        }
        uint32_t rgb = in.asInteger();
        send((uint8_t)rgb<<0, OutPorts::r);
        send((uint8_t)rgb<<8, OutPorts::g);
        send((uint8_t)rgb<<16, OutPorts::b);
    }
private:
    Connection outPorts[RGB_CHANNELS];
};
