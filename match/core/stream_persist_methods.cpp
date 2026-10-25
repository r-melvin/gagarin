// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x410320 and 0x410380.

#include "stream_persist_methods.h"
#include "../_layout/swizzle_manager_class.h"

// FUNCTION: GAMEMD 0x410320
//
// FRAME-LAYOUT DELTA (status partial, 62.5% - 25/40). Everything from the first
// stream call onward is exact, the second write and the dirty-flag clear
// included. Two things differ, both in the prologue and both frame decisions
// rather than code: retail stages the identity word in the *stream* parameter's
// own stack home (`LEA ECX,[ESP+0x14]`) while we reserve a fresh slot
// (`[ESP+0x10]`), and retail writes the staged value immediately before the
// call where we write it before the guard. Five phrasings were tried - the
// local declared before and after the guard, assigned separately from its
// declaration, the subject routed through a second local, and the guard
// inverted into a positive `if`. Only the form below reaches 62.5%; the rest
// sit at 7.5-10%. The sibling loader at 0x410380 has the same shape without a
// staged value and matches exactly. The cause is NOT the toolchain: our objects
// stamp @comp.id 0x000b20ff, i.e. build 8447.
//
// The identity word written first is the subject pointer itself, staged in the
// stream argument's own stack home - retail takes that slot's address for the
// buffer and stores the subject into it, which is the parameter-home reuse
// pattern.
long __stdcall FUN_00410320(Subject_00410320* subject, Stream_00410320* stream,
                            int clearDirty)
{
    // The staging local is declared and initialised ahead of the guard. That is
    // what makes VC6 save EDI in the prologue as retail does rather than
    // shrink-wrapping the push into the guarded block; written after the guard
    // the whole function still assembles correctly but the prologue diverges
    // and the score drops to 10%.
    void* identity = subject;

    if (stream == 0) {
        return 0x80004003;
    }

    long hr = STREAM_WRITE(stream, &identity, 4);

    if (hr >= 0) {
        hr = STREAM_WRITE(stream, subject, subject->vt_030());

        if (hr >= 0 && clearDirty) {
            subject->Dirty = 0;
        }
    }

    return hr;
}

// FUNCTION: GAMEMD 0x410380
//
// The mirror. The body read lands straight over the object, so the field at
// +0x1C is saved beforehand and put back afterwards - it holds something the
// stream's copy must not overwrite.
long __stdcall FUN_00410380(Subject_00410320* subject, Stream_00410320* stream)
{
    if (stream == 0) {
        return 0x80004003;
    }

    int identity;

    long hr = STREAM_READ(stream, &identity, 4);

    if (hr >= 0) {
        DAT_00B0C110.SwizzleManagerClass::vf_6(identity, subject);

        void* restored = subject->Restored;

        hr = STREAM_READ(stream, subject, subject->vt_030());

        subject->Restored = restored;
    }

    return hr;
}
