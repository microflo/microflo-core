/* microflo_component yaml
name: NumberEquals
description: "Emits true if @a EQUALS @b is true, else false"
inports:
  a:
    ctype: long
    type: all
    description: ""
  b:
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
struct NumberEquals {
    Packet operator() (long a, long b) { return Packet(a == b); }
};
