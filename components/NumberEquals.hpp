/* microflo_component yaml
name: NumberEquals
description: "Emits true if @a EQUALS @b is true, else false"
inports:
  a:
    ctype: long
    type: integer
    description: ""
  b:
    ctype: long
    type: integer
    description: ""
outports:
  out:
    type: boolean
    description: ""
type: pure2
microflo_component */
// Functor for PureFunctionComponent2
struct NumberEquals {
    Packet operator() (long a, long b) { return Packet(a == b); }
};
