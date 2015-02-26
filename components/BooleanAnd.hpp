/* microflo_component yaml
name: BooleanAnd
description: "Emits true if @a AND @b is true, else false"
inports:
  a:
    ctype: bool
    type: all
    description: ""
  b:
    ctype: bool
    type: all
    description: ""
outports:
  out:
    type: all
    description: ""
type: pure2
microflo_component */
// Functor for PureFunctionComponent2
struct BooleanAnd {
    Packet operator() (bool a, bool b) { return Packet(a && b); }
};
