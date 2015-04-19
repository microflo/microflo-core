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
    default: false
  value1:
    type: all
    description: "Value outputted when animation goes high"
    default: true
  start:
    type: integer
    description: "Time for the start of the animation (in clocks)"
    default: 0
  period:
    type: integer
    description: "One period of the animation (in clocks)"
    default: 0
  duration:
    type: integer
    description: "Duration of the entire animation (from start, in clocks)"
    default: 0
  dutycycle:
    type: integer
    description: "Percentage of the period which the animation is high"
    default: 50
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
        : Component(outPorts, ToggleAnimationPorts::OutPorts::running+1)
        , value0((bool)false)
        , value1((bool)true)
        , dutycycle(50)
        , start(0)
        , duration(0)
        , period(0)
    {
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace ToggleAnimationPorts;

        if (port == InPorts::clock) {
            const long clock = in.asInteger();
            const long position = clock-start; // position inside animation
            const long end = (start+duration);
            const bool running = position > 0 && clock < end;
            send(Packet(running), OutPorts::running);

            if (!running) {
                send(value0, OutPorts::value);
            } else {
                // determine if we are inside high part of period
                const long highPeriod = (period*dutycycle)/100;
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
    Connection outPorts[ToggleAnimationPorts::OutPorts::running+1];
    Packet value0;
    Packet value1;
    int8_t dutycycle;
    long start;
    long duration;
    long period;
};
