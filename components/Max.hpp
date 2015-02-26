/* microflo_component yaml
name: Max
description: "Emits maximum value of @in and @threshold"
inports:
  in:
    ctype: long
    type: all
    description: ""
  threshold:
    ctype: long
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
type: pure2
microflo_component */
// Functor for PureFunctionComponent2
struct Max {
    Packet operator() (long input, long threshold) {
        if (input <= threshold)
            return Packet(threshold);
        else
            return Packet(input);
    }
};
