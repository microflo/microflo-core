/* microflo_component yaml
name: Max
description: "Emits maximum value of @in and @threshold"
inports:
  in:
    ctype: long
    type: integer
    description: ""
  threshold:
    ctype: long
    type: integer
    description: ""
outports:
  out:
    type: integer
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
