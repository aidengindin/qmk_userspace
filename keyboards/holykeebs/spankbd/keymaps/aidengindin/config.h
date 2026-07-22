#pragma once

// Timeless home row mods - based on https://old.reddit.com/r/ErgoMechKeyboards/comments/1q1jo3c/urobs_zmk_timeless_home_row_mods_ported_to_native/

#undef TAPPING_TERM
#define TAPPING_TERM 250

#undef FLOW_TAP_TERM
#define FLOW_TAP_TERM 150

#define PERMISSIVE_HOLD
#define CHORDAL_HOLD

// Enable per-key control of hold-on-other-key-press for thumb keys only
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define QUICK_TAP_TERM 100

#define SPECULATIVE_HOLD
