/* microflo_component yaml
name: ToggleAnimation
description: "Animate between two states; one value for high, another for low"
inports:
  clock:
    type: integer
    description: "Clock to calculate @value for"
  value0:
    type: all
    description: "Value outputted when animation goes low"
  value1:
    type: all
    description: "Value outputted when animation goes high"
  start:
    type: integer
    description: "Time for the start of the animation (in clocks)"
  period:
    type: integer
    description: "One period of the animation (in clocks)"
  duration:
    type: integer
    description: "Duration of the entire animation (from start, in clocks)"
  dutycycle:
    type: integer
    description: "Percentage of the period which the animation is high"
outports:
  value:
    type: all
    description: "Value of the animation"
  running:
    type: boolean
    description: "Whether animation is running or not"
microflo_component */
/**
 *                 ___      ___       ___                 value -> value1
 *             ____|  ______|  _______|  |_____________   value -> value0
 *
 *                 ^                    ^
 *             start                 start+duration
 *                 |  period | period |
 *                 |du|-cycle|
 *
 * running=false   | running=true        | running=false
 *
 */
class ToggleAnimation : public Component {
public:
    ToggleAnimation()
        : Component(outPorts, ToggleAnimation::OutPorts::running+1)
    {
        start = 0;
        duration = 0;
        period = 0;
        dutycycle = 50;
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace ToggleAnimation;

        if (port == InPorts::clock) {
            const long clock = in.asInteger();
            const long position = clock-start; // position inside animation
            const bool running = position > 0 && position < (start+duration);
            send(Packet(running), OutPorts::running);

            if (!running) {
                send(value0, OutPorts::value);
            } else {
                // determine if we are inside high part of period
                const long highPeriod = period*dutycycle;
                const long periodPosition = position%period;
                const bool high = running && periodPosition < highPeriod;
                send((high) ? value1 : value0, OutPorts::value);
            }

        // Parameters
        } else if (port == InPorts::value0) {
            value0 = in;
        } else if (port == InPorts::value1) {
            value1 = in;
        } else if (port == InPorts::start) {
            start = in.asInteger();
        } else if (port == InPorts::duration) {
            duration = in.asInteger();
        } else if (port == InPorts::period) {
            period = in.asInteger();
        } else if (port == InPorts::dutycycle) {
            dutycycle = in.asInteger();
        } else {

        }
    }
private:
    Connection outPorts[ToggleAnimation::OutPorts::running+1];
    Packet value0;
    Packet value1;
    long start;
    long period;
    long duration;
    int8_t dutycycle;
};
