/* microflo_component yaml
name: BooleanOr
description: "Emits true if either @a OR @b is true, else false"
inports:
  a:
    ctype: bool
    type: boolean
    description: ""
  b:
    ctype: bool
    type: boolean
    description: ""
outports:
  out:
    type: boolean
    description: ""
type: pure2
microflo_component */
// Functor for PureFunctionComponent2
struct BooleanOr {
    Packet operator() (bool a, bool b) { return Packet(a || b); }
};
