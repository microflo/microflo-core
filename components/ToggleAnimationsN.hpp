/* microflo_component yaml
name: ToggleAnimationsN
description: "Animate between two states; one value for high, another for low"
inports:
  tracks:
    type: integer
    description: "Number of animation tracks. Max=100"
  animation:
    type: all
    description: "A bracketed animation definition [idx,val0,val1,period,dutycycle,offset,duration]"
  clock:
    type: integer
    description: "Input clock driving animations"
outports:
  value:
    type: all
    description: "Value of animations. Bracketed [idx,val]"
  clock:
    type: integer
    description: "Repeat of @clock input"
microflo_component */

static const MicroFlo::PortId packet2port[] = {
    -1, // start bracket
    -1, // track idx
    ToggleAnimationPorts::InPorts::value0,
    ToggleAnimationPorts::InPorts::value1,
    ToggleAnimationPorts::InPorts::period,
    ToggleAnimationPorts::InPorts::dutycycle,
    ToggleAnimationPorts::InPorts::start,
    ToggleAnimationPorts::InPorts::duration,
    -1 // end bracket
};


class ToggleAnimationsN : public Component {
    static const uint8_t MAX_TRACKS = 70;

public:
    ToggleAnimationsN()
        : Component(outPorts, ToggleAnimationsNPorts::OutPorts::clock+1)
        , tracks(0)
        , nTracks(0)
        , targetTrackIndex(0)
        , nextPacketNumber(0)
    {
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace ToggleAnimationsNPorts;

        if (port == InPorts::tracks) {
            if (in.asInteger() > MAX_TRACKS) {
                return;
            }
            reinitializeTracks(in.asInteger());

        } else if (port == InPorts::clock) {
            // Forward onto all tracks
            for (int i=0; i<nTracks; i++) {
                Component *target = tracks[i];
                //fprintf(stderr, "sending clock %d\n", i);
                if (target) target->process(in, ToggleAnimationPorts::InPorts::clock);
            }
            send(in, OutPorts::clock);

        // Parameters
        } else if (port == InPorts::animation) {
            if (in.isStartBracket()) {
                nextPacketNumber = 1;
            } else if (nextPacketNumber == 1) {
                targetTrackIndex = in.asInteger();
                nextPacketNumber++;
            } else if (nextPacketNumber > 1 && nextPacketNumber < 8) {
                // FIXME: make start port be current clock+offset??
                MicroFlo::PortId targetPort = packet2port[nextPacketNumber];
                if (targetTrackIndex < nTracks) {
                    Component *target = tracks[targetTrackIndex];
                    if (target) {
                        target->process(in, targetPort);
                    }
                }
                nextPacketNumber++;
            } else if (in.isEndBracket()) {

            } else {
                // avoid overflow
                nextPacketNumber = 0;
            }

        } else if (port >= 10) {
            const uint8_t sourceTrackIndex = port-10;
            const MicroFlo::PortId outPort = OutPorts::value;
            // TODO: a sendBracketed function?
            send(Packet(MsgBracketStart), outPort);
            send(Packet((long)sourceTrackIndex), outPort);
            send(in, outPort);
            send(Packet(MsgBracketEnd), outPort);
        } else {

        }
    }

private:
    void reinitializeTracks(uint8_t nNewTracks) {
        if (tracks) {
            for (int i=0; i<nTracks; i++) {
                delete tracks[i];
            }
            free(tracks);
        }
        nTracks = nNewTracks;
        tracks = (ToggleAnimation **)malloc(nTracks*sizeof(ToggleAnimation *));
        for (int i=0; i<nTracks; i++) {
            tracks[i] = (ToggleAnimation *)createComponent(IdToggleAnimation);
            network->addNode(tracks[i], 0);
            network->connect(tracks[i], ToggleAnimationPorts::OutPorts::value,
                             this, i+10);
        }
    }

private:
    Connection outPorts[ToggleAnimationsNPorts::OutPorts::clock+1];
    ToggleAnimation **tracks;
    uint8_t nTracks;

    // For keeping state while within bracketed indata
    uint8_t targetTrackIndex;
    uint8_t nextPacketNumber;
};


