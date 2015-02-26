/* microflo_component yaml
name: BooleanOr
description: "Emits true if either @a OR @b is true, else false"
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
struct BooleanOr {
    Packet operator() (bool a, bool b) { return Packet(a || b); }
};
