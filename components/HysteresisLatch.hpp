/* microflo_component yaml
name: HysteresisLatch
description: "Emit true if @in < @highthreshold, false if @in < @lowthreshold, else keep previous state"
inports:
  in:
    type: number
    description: ""
  lowthreshold:
    type: number
    description: ""
  highthreshold:
    type: number
    description: ""
outports:
  out:
    type: all
    description: ""
microflo_component */
class HysteresisLatch : public SingleOutputComponent
{
enum State {
    Unknown,
    Low,
    High,
};

public:
    HysteresisLatch()
        : mHighThreshold(0)
        , mLowThreshold(0)
        , mCurrentState(Unknown)
    {
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace HysteresisLatchPorts;

        if (port == InPorts::lowthreshold && in.isNumber()) {
            mLowThreshold = in.asFloat();
        } else if (port == InPorts::highthreshold && in.isNumber()) {
            mHighThreshold = in.asFloat();
        } else if (port == InPorts::in && in.isNumber()) {
            updateValue(in.asFloat());
        }
    }

private:
    void updateValue(float input) {
        if (mCurrentState == Unknown) {
            mCurrentState = (input >= mLowThreshold) ? High : Low;
        } else if (mCurrentState == High && input <= mLowThreshold) {
            mCurrentState = Low;
        } else if (mCurrentState == Low && input >= mHighThreshold) {
            mCurrentState = High;
        }
        send(Packet(mCurrentState == High));
    }

private:
    float mHighThreshold;
    float mLowThreshold;
    State mCurrentState;
};
