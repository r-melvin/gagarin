// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4381D0 and 0x438300.

#include "lazy_sink_forward_methods.h"

// FUNCTION: GAMEMD 0x4381D0
//
// Create the sink on first use, then forward. The `JMP` over `XOR EAX,EAX` at
// 0x4381EF is the null-checked new expression: the allocation result is
// constructed if it is non-null and replaced by null if it is not, and the one
// store at 0x4381F3 takes whichever survived.
//
// The member is re-read after the store rather than reusing the constructed
// pointer - retail's `MOV ECX,[ESI+0xC]` at 0x4381F6 is on the common path, so
// it also serves the already-created case.
void Owner_004381D0::FUN_004381D0(int first, int second)
{
    if (Sink == 0) {
        void* raw = FUN_007C8E17(4);

        Sink = raw ? ((Sink_00437F50*)raw)->FUN_00437F50() : 0;
    }

    Sink_00437F50* sink = Sink;

    if (sink) {
        sink->FUN_00437FD0(first, second);
    }
}

// FUNCTION: GAMEMD 0x438300
//
// The same routine at a second address, with the same allocation size and the
// same two call targets. Written out rather than shared.
void Owner_004381D0::FUN_00438300(int first, int second)
{
    if (Sink == 0) {
        void* raw = FUN_007C8E17(4);

        Sink = raw ? ((Sink_00437F50*)raw)->FUN_00437F50() : 0;
    }

    Sink_00437F50* sink = Sink;

    if (sink) {
        sink->FUN_00437FD0(first, second);
    }
}
