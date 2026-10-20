// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x401580: [ESI], [ESI+0x10C], [ESI+0x110].
//
// The AudioIDXData teardown at 0x401580.
//
// Naming: YRpp Audio.h binds this address to `~AudioIDXData()`. It cannot be a
// destructor — the last thing it does is hand `this` itself to the deallocator
// at 0x4015B3. A destructor never frees its own storage; the caller's `delete`
// does that afterwards, and doing both would be a double free. So this is a
// destroy helper and it keeps its Ghidra placeholder name.
#ifndef GG_MATCH_AUDIO_AUDIO_IDX_DATA_DESTROY_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_IDX_DATA_DESTROY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The deallocator, __cdecl with one pointer argument and `ADD ESP,4` after.
// Same one BufferIOFileClass's destructor uses.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// The two owned sub-objects are released through slot 0 of their own vtables
// with an argument of 1 (`MOV EAX,[ECX]; PUSH 1; CALL [EAX]`). That is MSVC's
// scalar-deleting-destructor call — i.e. a plain `delete`, not a hand-written
// virtual call — so they are modelled as classes with a virtual destructor and
// released with `delete`.
struct AudioSampleTable  { virtual ~AudioSampleTable(); };
struct AudioSampleHeader { virtual ~AudioSampleHeader(); };

struct AudioIDXData
{
    void*              RawData;       // +0x0000
    char               _pad04[0x10C - 0x04];
    AudioSampleTable*  Samples;       // +0x010C
    AudioSampleHeader* Headers;       // +0x0110

    // A member, not a free function taking the record: the record is the only
    // register argument, so this is an ordinary __thiscall member.
    // FUNCTION: GAMEMD 0x401580
    void FUN_00401580();
};
GG_STATIC_ASSERT(offsetof(AudioIDXData, RawData) == 0x00);
GG_STATIC_ASSERT(offsetof(AudioIDXData, Samples) == 0x10C);
GG_STATIC_ASSERT(offsetof(AudioIDXData, Headers) == 0x110);

#endif  // GG_MATCH_AUDIO_AUDIO_IDX_DATA_DESTROY_METHODS_H
