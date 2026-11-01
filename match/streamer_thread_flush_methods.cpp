// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x53E6B0.

#include "streamer_thread_flush_methods.h"

// FUNCTION: GAMEMD 0x53E6B0
//
// Flush the audio streamer's ring buffer to its file. Nothing happens unless
// the streamer is running; under the critical section, if a stream and a ring
// are attached, the 0xAA045C flag is set and the state is 1, everything
// pending in the ring is written out and the CRT stream is flushed.
//
// The ring and stream globals are re-read after the byte count call rather
// than kept live - the call could have changed them.
void __cdecl FUN_0053E6B0()
{
    if (DAT_00AA0448 != 0) {
        EnterCriticalSection(&DAT_00AA0418);

        if (DAT_00AA0468 != 0 && DAT_00AA045C != 0 && DAT_00AA0444 == 1
            && DAT_00AA0464 != 0) {
            FUN_00409030(DAT_00AA0464, DAT_00AA0468, FUN_00409320(DAT_00AA0464), 0);
            FUN_007CB19C(DAT_00AA0468);
        }

        LeaveCriticalSection(&DAT_00AA0418);
    }
}
