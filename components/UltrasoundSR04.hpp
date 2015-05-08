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

#include <NewPing.h>


void echoCheck() {
    // If ping received, set the sensor distance to array.
    if (ping.check_timer()) {
        const long distance = ping.ping_result / US_ROUNDTRIP_CM;
        // TODO: send on component outport as packet
    }
}

class UltrasoundSR04 : public SingleOutputComponent {

public:
    UltrasoundSR04()
        : echoPin(-1)
        , trigPin(-1)
        , maxDistance(200)
        , ping(-1, -1, maxDistance)
    {
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace UltrasoundSR04Ports;

        if (port == InPorts::trigger) {
            ping.timer_stop(); // assurance
            ping.ping_timer(echoCheck);
            send(true, OutPorts::triggered);
        } else if (port == InPorts::trigpin && in.isNumber()) {
            trigPin = in.asInteger();
            checkInitialize();
        } else if (port == InPorts::echopin && in.isNumber()) {
            echoPin = in.asInteger();
            checkInitialize();
        }
    }
private:
    inline const bool pinsValid() {
        return (echoPin > 0 && trigPin > 0);
    }

    void checkInitialize() {
        if (!pinsValid()) {
            return;
        }
        ping = NewPing(echoPin, trigPin, MAX_DISTANCE);
    }

private:
    int8_t echoPin;
    int8_t trigPin;
    NewPing ping;
    long maxDistance;
};
