// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//
// Two callbacks over the streamed-sample slot table at 0x887778 (0xBC-byte
// slots, indexed by the sample's +0x34 field): the position query installed
// at 0x759435 and the multimedia-timer refill routine passed from 0x411CA2.
// Both talk to the slot's DirectSound buffer through its C-style vtable and
// serialise on the slot's critical section.
//
// LIBRARY: IAT 0x7E11C8 KERNEL32!InterlockedIncrement, 0x7E11CC
//   InterlockedDecrement, 0x7E11E8 EnterCriticalSection, 0x7E11EC
//   LeaveCriticalSection.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct StreamCriticalSection
{
    char unknown_00[0x18];
};

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long* value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long* value);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(StreamCriticalSection* section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(StreamCriticalSection* section);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x4E24A0 (decl; reloc) -- millisecond clock.
unsigned FUN_004e24a0();

struct StreamBufferView;

// C-style sound-buffer vtable (slots used here only).
struct StreamBufferVtbl
{
    void* unknown_00[4];
    long (__stdcall* GetCurrentPosition)(StreamBufferView* self, unsigned* play, unsigned* write);   // +0x10
    void* unknown_14[4];
    long (__stdcall* GetStatus)(StreamBufferView* self, unsigned* status);                           // +0x24
    void* unknown_28[2];
    long (__stdcall* Play)(StreamBufferView* self, unsigned reserved, unsigned priority, unsigned flags); // +0x30
    long (__stdcall* SetCurrentPosition)(StreamBufferView* self, unsigned position);                 // +0x34
    void* unknown_38[4];
    long (__stdcall* Stop)(StreamBufferView* self);                                                  // +0x48
    void* unknown_4C;
    long (__stdcall* Restore)(StreamBufferView* self);                                               // +0x50
};
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, GetCurrentPosition) == 0x10);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, GetStatus) == 0x24);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, Play) == 0x30);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, SetCurrentPosition) == 0x34);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, Stop) == 0x48);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, Restore) == 0x50);

struct StreamBufferView
{
    StreamBufferVtbl const* lpVtbl;
};

// The sample handle the callbacks receive.
struct StreamSampleView
{
    char           unknown_00[0x34];
    int            Slot;          // +0x34
    unsigned       unknown_38;    // +0x38
    unsigned short Rate;          // +0x3C
    unsigned char  Channels;      // +0x3E
    unsigned char  Bits;          // +0x3F
    char           unknown_40[0x5C];
    unsigned       unknown_9C;    // +0x9C
    char           unknown_A0[0x24];
    unsigned       unknown_C4;    // +0xC4
};
GG_STATIC_ASSERT(offsetof(StreamSampleView, Slot) == 0x34);
GG_STATIC_ASSERT(offsetof(StreamSampleView, Rate) == 0x3C);
GG_STATIC_ASSERT(offsetof(StreamSampleView, Channels) == 0x3E);
GG_STATIC_ASSERT(offsetof(StreamSampleView, Bits) == 0x3F);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_C4) == 0xC4);

struct StreamSlot
{
    char                  unknown_00[0x14];
    unsigned              LastBytes;       // +0x14
    unsigned              LastTime;        // +0x18
    unsigned              StartTime;       // +0x1C
    unsigned              Ticks;           // +0x20
    char                  unknown_24[4];
    unsigned char         Flags;           // +0x28
    char                  unknown_29[0x1B];
    int                   Current;         // +0x44
    int                   Ready[2];        // +0x48
    void*                 Chunk[2];        // +0x50
    char                  unknown_58[8];
    unsigned              TimerID;         // +0x60
    char                  unknown_64[0x28];
    StreamBufferView*     Buffer;          // +0x8C
    unsigned              BufferSize;      // +0x90
    unsigned              Fills;           // +0x94
    unsigned              unknown_98;      // +0x98
    unsigned              unknown_9C;      // +0x9C
    StreamCriticalSection Lock;            // +0xA0
    long                  Busy;            // +0xB8
};
GG_STATIC_ASSERT(offsetof(StreamSlot, LastBytes) == 0x14);
GG_STATIC_ASSERT(offsetof(StreamSlot, Ticks) == 0x20);
GG_STATIC_ASSERT(offsetof(StreamSlot, Flags) == 0x28);
GG_STATIC_ASSERT(offsetof(StreamSlot, Current) == 0x44);
GG_STATIC_ASSERT(offsetof(StreamSlot, Ready) == 0x48);
GG_STATIC_ASSERT(offsetof(StreamSlot, Chunk) == 0x50);
GG_STATIC_ASSERT(offsetof(StreamSlot, TimerID) == 0x60);
GG_STATIC_ASSERT(offsetof(StreamSlot, Buffer) == 0x8C);
GG_STATIC_ASSERT(offsetof(StreamSlot, Lock) == 0xA0);
GG_STATIC_ASSERT(offsetof(StreamSlot, Busy) == 0xB8);
GG_STATIC_ASSERT(sizeof(StreamSlot) == 0xBC);   // slot index scaled by 0xBC

// GLOBAL: GAMEMD 0x887778
extern StreamSlot DAT_00887778[];
// GLOBAL: GAMEMD 0x88776C / 0x887770 -- refill hooks.
extern void (__cdecl* DAT_0088776C)(StreamSampleView* sample);
extern void (__cdecl* DAT_00887770)(StreamSampleView* sample, void* chunk);

// FUNCTION: GAMEMD 0x4116A0
unsigned __cdecl FUN_004116a0(StreamSampleView* sample)
{
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    if (slot->Flags & 1)
    {
        FUN_004068E0("Ahandle: Paused %ld\n", slot->Ticks);
        return slot->Ticks;
    }
    unsigned elapsed = FUN_004e24a0() - slot->StartTime;
    unsigned size = slot->BufferSize;
    EnterCriticalSection(&slot->Lock);
    unsigned position = slot->Fills * sample->unknown_9C;
    unsigned played = sample->unknown_38;
    unsigned looping = slot->unknown_98;
    unsigned play;
    unsigned write;
    if (slot->Buffer != 0 && slot->Buffer->lpVtbl->GetCurrentPosition(slot->Buffer, &play, &write) == 0)
    {
        if (looping != 0)
        {
            position += play;
        }
        else
        {
            unsigned half = size >> 1;
            if (play < half)
            {
                if (position > 0)
                {
                    position += half + play;
                }
            }
            else
            {
                position += play - half;
            }
        }
    }
    LeaveCriticalSection(&slot->Lock);
    unsigned bytes = position - played * sample->unknown_9C;
    if (bytes > position)
    {
        bytes = 0;
    }
    else if (bytes != 0 && bytes <= slot->LastBytes)
    {
        if (elapsed > slot->LastTime)
        {
            unsigned delta = elapsed - slot->LastTime;
            slot->LastTime = elapsed;
            slot->Ticks += delta;
            return slot->Ticks;
        }
        return slot->Ticks;
    }
    slot->LastBytes = bytes;
    slot->LastTime = elapsed;
    slot->Ticks = bytes / ((sample->Bits >> 3) * sample->Channels) * 60 / sample->Rate;
    if (slot->Ticks >= sample->unknown_C4)
    {
        slot->Ticks -= sample->unknown_C4;
        return slot->Ticks;
    }
    slot->Ticks = 0;
    return slot->Ticks;
}

// FUNCTION: GAMEMD 0x4123A0
void __stdcall FUN_004123a0(unsigned timer_id, unsigned message, StreamSampleView* sample,
                            unsigned param1, unsigned param2)
{
    bool replay = false;
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    if (InterlockedIncrement(&slot->Busy) == 1 && !(slot->Flags & 1))
    {
        EnterCriticalSection(&slot->Lock);
        if (slot->Buffer != 0 && slot->TimerID == timer_id)
        {
            unsigned status;
            slot->Buffer->lpVtbl->GetStatus(slot->Buffer, &status);
            if (status & 5)
            {
                bool restarted = false;
                unsigned play;
                unsigned write;
                if (slot->Buffer->lpVtbl->GetCurrentPosition(slot->Buffer, &play, &write) == 0x88780096)
                {
                    slot->Buffer->lpVtbl->Restore(slot->Buffer);
                    slot->Buffer->lpVtbl->Stop(slot->Buffer);
                    replay = true;
                    slot->Buffer->lpVtbl->SetCurrentPosition(slot->Buffer, 0);
                    slot->unknown_98 = 0;
                    slot->unknown_9C = 0;
                    restarted = true;
                }
                if (play < slot->unknown_9C
                    || (play >= (slot->BufferSize >> 1) && slot->unknown_9C == 0)
                    || restarted == true)
                {
                    int current = slot->Current;
                    DAT_00887770(sample, slot->Chunk[current]);
                    slot->Fills++;
                    int next = current + 1;
                    if (next >= 2)
                    {
                        next = 0;
                    }
                    slot->Ready[current] = 0;
                    DAT_0088776C(sample);
                    if (slot->Ready[next] != 0)
                    {
                        slot->Current = next;
                    }
                    if (replay == true)
                    {
                        slot->Buffer->lpVtbl->Play(slot->Buffer, 0, 0, 1);
                    }
                }
            }
        }
        LeaveCriticalSection(&slot->Lock);
    }
    InterlockedDecrement(&slot->Busy);
}
