/* microflo_component yaml
name: UltrasoundSR04
description: "Read distance using a HC-SR04 ultrasonic sensor"
inports:
  trigger:
    type: bang
    description: "Trigger a new read-out"
  trigpin:
    type: integer
    description: "Pin connected to Trig on SR04 board"
  echopin:
    type: integer
    description: "Ping connected to Echo on SR04 board"
  maxdistance:
    type: integer
    description: "Maximum distance that is considered valid (in cm)"
outports:
  triggered:
    type: bang
    description: "A read-out was just triggered"
  distance:
    type: number
    description: "Distance to object (in cm)"
microflo_component */

#ifdef ARDUINO
#include <NewPing.h>
#endif


class UltrasoundSR04 : public Component {

public:
#ifdef ARDUINO
    static void echoCheck(NewPing *ping) {
        if (!ping || !ping->user_data) {
            return;
        }
        // If ping received, set the sensor distance to array.
        if (ping->check_timer()) {
            ping->timer_stop(); // avoid new interrupts until retriggered
            const long distance = ping->ping_result / US_ROUNDTRIP_CM;
            UltrasoundSR04 *component = (UltrasoundSR04 *)ping->user_data;
            component->sendDistance(distance);
        }
    }
#endif

public:
    UltrasoundSR04()
        : Component(outPorts, UltrasoundSR04Ports::OutPorts::distance+1)
        , echoPin(-1)
        , trigPin(-1)
        , maxDistance(200)
#ifdef ARDUINO
        , ping(trigPin, echoPin, maxDistance)
#endif
    {
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace UltrasoundSR04Ports;

        if (port == InPorts::trigger) {
            if (!pinsValid()) {
                return;
            }
#ifdef ARDUINO
            ping.ping_timer(echoCheck); // setup callback
#endif
            send((bool)true, OutPorts::triggered);
        } else if (port == InPorts::trigpin && in.isNumber()) {
            trigPin = in.asInteger();
            checkInitialize();
        } else if (port == InPorts::echopin && in.isNumber()) {
            echoPin = in.asInteger();
            checkInitialize();
        }
    }

    void sendDistance(long distance) {
        using namespace UltrasoundSR04Ports;
        send(distance, OutPorts::distance);
    }
private:
    inline const bool pinsValid() {
        return (echoPin > 0 && trigPin > 0);
    }

    bool checkInitialize() {
        if (!pinsValid()) {
            return false;
        }
#ifdef ARDUINO
        ping = NewPing(trigPin, echoPin, maxDistance);
        ping.user_data = (void *)this;
#endif
        return true;
    }

private:
    int8_t echoPin;
    int8_t trigPin;
#ifdef ARDUINO
    NewPing ping;
#endif
    long maxDistance;
    Connection outPorts[UltrasoundSR04Ports::OutPorts::distance+1];
};
