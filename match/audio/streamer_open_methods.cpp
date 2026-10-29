// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x53E4F0.

#include "streamer_thread_flush_methods.h"

// LIBRARY: GAMEMD 0x7CA845 (decl; reloc) -- CRT fopen.
void* __cdecl FUN_007CA845(const char* path, const char* mode);

// STRING: GAMEMD 0x828138 -- "wb"
// FUNCTION: GAMEMD 0x53E4F0
//
// Open the streamer's output file once. Does nothing unless the streamer is
// running and no stream is open yet; under the critical section the file is
// opened for binary writing and, when that works, the state is set to 1.
// Returns whether a stream is now open.
int __fastcall FUN_0053E4F0(const char* path)
{
    if (DAT_00AA0448 != 0 && DAT_00AA0468 == 0) {
        EnterCriticalSection(&DAT_00AA0418);
        DAT_00AA0468 = FUN_007CA845(path, "wb");
        if (DAT_00AA0468 != 0) {
            DAT_00AA0444 = 1;
        }
        LeaveCriticalSection(&DAT_00AA0418);
        return DAT_00AA0468 != 0;
    }
    return 0;
}

// GLOBAL: GAMEMD 0xAA0460 -- the ring buffer whose pending bytes seed a new stream.
extern void* DAT_00AA0460;
// GLOBAL: GAMEMD 0xAA046C -- set when seeding the new stream failed.
extern int DAT_00AA046C;

// STRING: GAMEMD 0x82813C -- "rb"
// FUNCTION: GAMEMD 0x53E550
//
// Open the streamer's file for reading, then (state 2) try to push the bytes
// already pending in the ring into it. DAT_00AA046C records a short write.
// Returns whether a stream is now open.
int __fastcall FUN_0053E550(const char* path)
{
    if (DAT_00AA0448 != 0 && DAT_00AA0468 == 0) {
        EnterCriticalSection(&DAT_00AA0418);
        DAT_00AA0468 = FUN_007CA845(path, "rb");
        DAT_00AA046C = 0;
        if (DAT_00AA0468 != 0) {
            DAT_00AA0444 = 2;
            if (FUN_00409030(DAT_00AA0460, DAT_00AA0468, FUN_00409320(DAT_00AA0460), 0) != 1) {
                DAT_00AA046C = 1;
            }
        }
        LeaveCriticalSection(&DAT_00AA0418);
        return DAT_00AA0468 != 0;
    }
    return 0;
}

// LIBRARY: GAMEMD 0x7CA75B (decl; reloc) -- CRT fclose.
int __cdecl FUN_007CA75B(void* stream);

// FUNCTION: GAMEMD 0x53E5F0
//
// Close the streamer's file. Under the critical section, flush anything still
// pending in the ring (the same condition as the periodic flush), reset the
// state, then close and clear the stream. The lock is taken a second time
// around the flush, as retail does.
void __cdecl FUN_0053E5F0()
{
    if (DAT_00AA0448 != 0) {
        EnterCriticalSection(&DAT_00AA0418);
        if (DAT_00AA0448 != 0) {
            EnterCriticalSection(&DAT_00AA0418);
            if (DAT_00AA0468 != 0 && DAT_00AA045C != 0 && DAT_00AA0444 == 1
                && DAT_00AA0464 != 0) {
                FUN_00409030(DAT_00AA0464, DAT_00AA0468, FUN_00409320(DAT_00AA0464), 0);
                FUN_007CB19C(DAT_00AA0468);
            }
            LeaveCriticalSection(&DAT_00AA0418);
        }
        DAT_00AA0444 = 0;
        if (DAT_00AA0468 != 0) {
            FUN_007CA75B(DAT_00AA0468);
            DAT_00AA0468 = 0;
        }
        LeaveCriticalSection(&DAT_00AA0418);
    }
}
