// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   `AudioIDXData` / `AudioController` (every
//   offset reconfirmed numerically from the disassembly below).
//
// Two cooperating audio types:
//   * AudioIDXData      — the loaded sample index (sorted name table + the
//                         currently-streamed sample file).
//   * AudioController   — a per-object handle onto a live audio event, validated
//                         against the global event pool before use.
#ifndef GG_MATCH_AUDIO_AUDIO_H
#define GG_MATCH_AUDIO_AUDIO_H

#include <stddef.h>  // offsetof, size_t
#include "../_rt/gg_static_assert.h"

struct VocClass;   // opaque (only handled by pointer)

// ---------------------------------------------------------------------------
// AudioFileStub — the streamed-sample file object (RawFileClass in YRpp). Only
// its virtual destructor (vtable slot 0) is needed: ClearCurrentSample @0x401910
// `delete`s it, which MSVC lowers to the scalar-deleting-destructor call
// `MOV EAX,[ECX]; PUSH 1; CALL [EAX]`. Never instantiated here (full layout = P2).
// ---------------------------------------------------------------------------
struct AudioFileStub
{
    virtual ~AudioFileStub();   // slot 0 — declared only (no body / no vtable emitted)
};

// ---------------------------------------------------------------------------
// AudioIDXEntry — one fixed-size record in the sorted sample table. sizeof must
// be 0x24: FindSampleIndex @0x4015C0 passes 0x24 as the bsearch element width
// and divides the found byte-offset by 0x24 (magic 0x38E38E39 >> 3). The bsearch
// key is compared with `_strcmpi`, and Name sits at offset 0 so the entry
// address doubles as the name pointer.
// ---------------------------------------------------------------------------
struct AudioIDXEntry
{
    char         Name[16];      // +0x00
    int          Offset;        // +0x10
    int          Size;          // +0x14
    unsigned int SampleRate;    // +0x18
    unsigned int Flags;         // +0x1C
    unsigned int ChunkSize;     // +0x20
};
GG_STATIC_ASSERT(offsetof(AudioIDXEntry, Name)       == 0x00);
GG_STATIC_ASSERT(offsetof(AudioIDXEntry, ChunkSize)  == 0x20);
GG_STATIC_ASSERT(sizeof(AudioIDXEntry)               == 0x24);  // bsearch element width

// ---------------------------------------------------------------------------
// AudioIDXData
//   +0x00 Samples           (MOV ECX,[ESI]      @0x4015CD — bsearch base)
//   +0x04 SampleCount       (MOV EAX,[ESI+4]    @0x4015CA — bsearch num)
//   +0x110 CurrentSampleFile(MOV ECX,[ESI+0x110]@0x401913 — the deleted object)
//   +0x118 CurrentSampleSize(MOV [ESI+0x118],0  @0x401919)
// The 0x108-byte gap and the +0x114 hole are P2 (Path[MAX_PATH], BagFile, etc.).
// ---------------------------------------------------------------------------
struct AudioSampleData;

struct AudioIDXData
{
    // FUNCTION: GAMEMD 0x401640 — GetSampleInformation, a member rather than a
    // free function taking the record: retail puts the record in ECX, the
    // index in EDX and the buffer on the stack with `RET 4`, which is
    // `__fastcall` on a member (this in ECX, the first explicit argument in
    // EDX). A plain __thiscall member would push the index too and return
    // `RET 8`. Defined in match/audio/audio_sample_methods.cpp.
    AudioSampleData* __fastcall GetSampleInformation(int index,
                                                     AudioSampleData* pBuffer) const;

    // static so that `this` lands in ECX and pName in EDX (the retail __fastcall
    // calling convention for this leaf), exactly as the disasm shows.
    static int __fastcall FindSampleIndex(const AudioIDXData* pThis, const char* pName);  // GAMEMD 0x4015C0
    void ClearCurrentSample();                                                            // GAMEMD 0x401910 __thiscall

    AudioIDXEntry* Samples;             // +0x00
    int            SampleCount;         // +0x04
    char           _gap_08[0x110 - 0x08];
    AudioFileStub* CurrentSampleFile;   // +0x110
    char           _gap_114[0x118 - 0x114];
    int            CurrentSampleSize;   // +0x118
};
GG_STATIC_ASSERT(offsetof(AudioIDXData, SampleCount)      == 0x04);
GG_STATIC_ASSERT(offsetof(AudioIDXData, CurrentSampleSize)== 0x118);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(AudioIDXData, Samples)          == 0x00);
GG_STATIC_ASSERT(offsetof(AudioIDXData, CurrentSampleFile)== 0x110);
#endif

// ---------------------------------------------------------------------------
// AudioController
//   +0x00 Event      (MOV [ECX],EDX     @0x4060FD ; MOV EAX,[ECX] @0x406142)
//   +0x04 Stamp      (MOV [ECX+4],ESI   @0x40610D ; MOV EDX,[ECX+4] @0x406153)
//   +0x08 EventType  (MOV [ECX+8],EAX   @0x406101 ; MOV EAX,[ECX+8] @0x406182)
//   +0x0C AudioIndex (CMP [ECX+0xc],0x87E294 @0x4060F0)
// AudioIndex is an AudioIDXData** that, when valid, points at the global
// AudioIDXData::Instance (address 0x87E294 — the CMP immediate).
// ---------------------------------------------------------------------------
struct AudioController
{
    static void __fastcall SetEvent(AudioController* pThis, void* event, VocClass* eventType);  // GAMEMD 0x4060F0
    void*      GetEvent();                                          // GAMEMD 0x406130 __thiscall
    VocClass*  GetEventType();                                      // GAMEMD 0x406170 __thiscall
    static VocClass* __fastcall GetEventType(void* event);         // GAMEMD 0x406310 __fastcall

    void*          Event;       // +0x00
    unsigned int   Stamp;       // +0x04
    VocClass*      EventType;    // +0x08
    AudioIDXData** AudioIndex;   // +0x0C
    unsigned int   Unused;      // +0x10
};
GG_STATIC_ASSERT(offsetof(AudioController, Stamp) == 0x04);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(AudioController, Event)      == 0x00);
GG_STATIC_ASSERT(offsetof(AudioController, EventType)  == 0x08);
GG_STATIC_ASSERT(offsetof(AudioController, AudioIndex) == 0x0C);
#endif

#endif  // GG_MATCH_AUDIO_AUDIO_H
