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
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include "_rt/gg_static_assert.h"
#include "leaf_accessor_methods.h"
#include "dsound_access_methods.h"
#include "trivial_tu155_b_methods.h"
#include "small_misc29_methods.h"

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x4E24A0 (decl; reloc) -- millisecond clock.
unsigned FUN_004e24a0();

struct StreamBufferView;

// C-style sound-buffer vtable (slots used here only).
struct StreamBufferVtbl
{
    void* unknown_00[2];
    long (__stdcall* Release)(StreamBufferView* self);                                               // +0x08
    void* unknown_0C;
    long (__stdcall* GetCurrentPosition)(StreamBufferView* self, unsigned* play, unsigned* write);   // +0x10
    void* unknown_14[4];
    long (__stdcall* GetStatus)(StreamBufferView* self, unsigned* status);                           // +0x24
    void* unknown_28[2];
    long (__stdcall* Play)(StreamBufferView* self, unsigned reserved, unsigned priority, unsigned flags); // +0x30
    long (__stdcall* SetCurrentPosition)(StreamBufferView* self, unsigned position);                 // +0x34
    void* unknown_38;
    long (__stdcall* SetVolume)(StreamBufferView* self, long volume);                                 // +0x3C
    void* unknown_40[2];
    long (__stdcall* Stop)(StreamBufferView* self);                                                  // +0x48
    void* unknown_4C;
    long (__stdcall* Restore)(StreamBufferView* self);                                               // +0x50
};
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, GetCurrentPosition) == 0x10);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, GetStatus) == 0x24);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, Play) == 0x30);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, SetCurrentPosition) == 0x34);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, SetVolume) == 0x3C);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, Stop) == 0x48);
GG_STATIC_ASSERT(offsetof(StreamBufferVtbl, Restore) == 0x50);

struct StreamBufferView
{
    StreamBufferVtbl const* lpVtbl;
};
GG_STATIC_ASSERT(offsetof(StreamBufferView, lpVtbl) == 0);

// The sample handle the callbacks receive.
struct StreamSampleView
{
    char           unknown_00[0xE];
    unsigned short unknown_0E;    // +0x0E
    char           unknown_10[0x24];
    int            Slot;          // +0x34
    unsigned       unknown_38;    // +0x38
    unsigned short Rate;          // +0x3C
    unsigned char  Channels;      // +0x3E
    unsigned char  Bits;          // +0x3F
    char           unknown_40[0x10];
    void*          unknown_50;    // +0x50 (clock hook)
    char           unknown_54[0x1C];
    unsigned       unknown_70;    // +0x70
    char           unknown_74[4];
    int            unknown_78;    // +0x78
    char           unknown_7C[0x20];
    unsigned       unknown_9C;    // +0x9C
    unsigned       unknown_A0;    // +0xA0
    unsigned       unknown_A4;    // +0xA4
    char           unknown_A8[0x1C];
    unsigned       unknown_C4;    // +0xC4
};
GG_STATIC_ASSERT(offsetof(StreamSampleView, Slot) == 0x34);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(StreamSampleView, Rate) == 0x3C);
GG_STATIC_ASSERT(offsetof(StreamSampleView, Channels) == 0x3E);
GG_STATIC_ASSERT(offsetof(StreamSampleView, Bits) == 0x3F);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(StreamSampleView, unknown_C4) == 0xC4);

struct StreamSlot
{
    unsigned char         Active;          // +0x00
    char                  unknown_01[3];
    unsigned              unknown_04;      // +0x04
    unsigned short        Rate;            // +0x08
    unsigned char         Channels;        // +0x0A
    unsigned char         Bits;            // +0x0B
    char                  unknown_0C[8];
    unsigned              LastBytes;       // +0x14
    unsigned              LastTime;        // +0x18
    unsigned              StartTime;       // +0x1C
    unsigned              Ticks;           // +0x20
    unsigned              unknown_24;      // +0x24
    unsigned              Flags;           // +0x28 (bit 0: paused)
    char                  unknown_2C[0x14];
    int                   unknown_40;      // +0x40
    int                   Current;         // +0x44
    int                   Ready[2];        // +0x48
    void*                 Chunk[2];        // +0x50
    char                  unknown_58[8];
    unsigned              TimerID;         // +0x60
    DSBUFFERDESC          Desc;            // +0x64
    WAVEFORMATEX          Format;          // +0x78
    char                  unknown_8A[2];
    StreamBufferView*     Buffer;          // +0x8C
    unsigned              BufferSize;      // +0x90
    unsigned              Fills;           // +0x94
    unsigned              unknown_98;      // +0x98
    unsigned              unknown_9C;      // +0x9C
    CRITICAL_SECTION      Lock;            // +0xA0
    long                  Busy;            // +0xB8
};
GG_STATIC_ASSERT(offsetof(StreamSlot, Active) == 0x00);
GG_STATIC_ASSERT(offsetof(StreamSlot, LastBytes) == 0x14);
GG_STATIC_ASSERT(offsetof(StreamSlot, LastTime) == 0x18);
GG_STATIC_ASSERT(offsetof(StreamSlot, StartTime) == 0x1C);
GG_STATIC_ASSERT(offsetof(StreamSlot, Ticks) == 0x20);
GG_STATIC_ASSERT(offsetof(StreamSlot, Flags) == 0x28);
GG_STATIC_ASSERT(offsetof(StreamSlot, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(StreamSlot, Current) == 0x44);
GG_STATIC_ASSERT(offsetof(StreamSlot, Ready) == 0x48);
GG_STATIC_ASSERT(offsetof(StreamSlot, Chunk) == 0x50);
GG_STATIC_ASSERT(sizeof(((StreamSlot*)0)->Ready) == 8);
GG_STATIC_ASSERT(sizeof(((StreamSlot*)0)->Chunk) == 8);
GG_STATIC_ASSERT(offsetof(StreamSlot, TimerID) == 0x60);
GG_STATIC_ASSERT(offsetof(StreamSlot, Buffer) == 0x8C);
GG_STATIC_ASSERT(offsetof(StreamSlot, BufferSize) == 0x90);
GG_STATIC_ASSERT(offsetof(StreamSlot, Fills) == 0x94);
GG_STATIC_ASSERT(offsetof(StreamSlot, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(StreamSlot, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(sizeof(CRITICAL_SECTION) == 0x18);
GG_STATIC_ASSERT(offsetof(StreamSlot, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(StreamSlot, Rate) == 0x08);
GG_STATIC_ASSERT(offsetof(StreamSlot, Channels) == 0x0A);
GG_STATIC_ASSERT(offsetof(StreamSlot, Bits) == 0x0B);
GG_STATIC_ASSERT(offsetof(StreamSlot, Desc) == 0x64);
GG_STATIC_ASSERT(offsetof(StreamSlot, Format) == 0x78);
GG_STATIC_ASSERT(offsetof(StreamSlot, Lock) == 0xA0);
GG_STATIC_ASSERT(offsetof(StreamSlot, Busy) == 0xB8);
GG_STATIC_ASSERT(sizeof(StreamSlot) == 0xBC);   // slot index scaled by 0xBC

// GLOBAL: GAMEMD 0xA8EB9C -- the movie volume scale.
extern float DAT_00A8EB9C;
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
            size >>= 1;
            if (play >= size)
            {
                position += play - size;
            }
            else if (position > 0)
            {
                position += play + size;
            }
        }
    }
    LeaveCriticalSection(&slot->Lock);
    unsigned bytes = position - played * sample->unknown_9C;
    if (bytes > position)
    {
        bytes = 0;
    }
    else if (bytes > 0 && bytes <= slot->LastBytes)
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

// Open parameters block handed to the open handler (size-checked against 0x10).
struct StreamOpenParams
{
    unsigned short Rate;          // +0x00
    unsigned char  Channels;      // +0x02
    unsigned char  Bits;          // +0x03
    unsigned       unknown_04;    // +0x04
    void (__cdecl* Hook0)(StreamSampleView* sample);                 // +0x08
    void (__cdecl* Hook1)(StreamSampleView* sample, void* chunk);    // +0x0C
};
GG_STATIC_ASSERT(offsetof(StreamOpenParams, Channels) == 0x02);
GG_STATIC_ASSERT(offsetof(StreamOpenParams, Bits) == 0x03);
GG_STATIC_ASSERT(offsetof(StreamOpenParams, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(StreamOpenParams, Hook0) == 0x08);
GG_STATIC_ASSERT(offsetof(StreamOpenParams, Hook1) == 0x0C);
GG_STATIC_ASSERT(sizeof(StreamOpenParams) == 0x10);

// FUNCTION: GAMEMD 0x412000 (decl; reloc)
int __cdecl FUN_00412000(StreamSampleView* sample, void* arg, int size);
// FUNCTION: GAMEMD 0x412540 (decl; reloc) -- retail's one-jump wrapper around the clock.
unsigned FUN_00412540();
// FUNCTION: GAMEMD 0x4123A0 (decl) -- the timer callback, defined below.
void __stdcall FUN_004123a0(unsigned timer_id, unsigned message, StreamSampleView* sample,
                            unsigned param1, unsigned param2);
int __cdecl FUN_00411b20(StreamSampleView* sample, StreamOpenParams* params, int size);
int __cdecl FUN_00411df0(StreamSampleView* sample);
int __cdecl FUN_00411ce0(StreamSampleView* sample);
int __cdecl FUN_00412230(StreamSampleView* sample);

// Stop the slot's sound buffer and release it (the block shared by the close handler and
// command 7). The slot is looked up from the sample again, as in retail.
static int StopSlotBuffer(StreamSampleView* sample)
{
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    if (slot->Buffer != 0)
    {
        EnterCriticalSection(&slot->Lock);
        slot->Buffer->lpVtbl->Stop(slot->Buffer);
        slot->Buffer->lpVtbl->Release(slot->Buffer);
        slot->Buffer = 0;
        slot->unknown_40 = 0;
        slot->Current = 0;
        for (int i = 0; i < 2; i++)
        {
            slot->Ready[i] = 0;
        }
        LeaveCriticalSection(&slot->Lock);
    }
    return -1;
}

// Restart a paused slot's buffer (shared by the play handler's paused path and command 8).
static int ResumeSlot(StreamSampleView* sample)
{
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    if (slot->Active != 0 && slot->Buffer != 0)
    {
        int result;
        EnterCriticalSection(&slot->Lock);
        if (slot->Buffer->lpVtbl->Play(slot->Buffer, 0, 0, 1) == 0)
        {
            slot->StartTime = FUN_004e24a0() - slot->LastTime;
            FUN_004068E0("Ahandle: PauseAdjust %ld\n", slot->StartTime);
            slot->Flags &= ~1;
            result = -1;
        }
        else
        {
            result = -13;
        }
        LeaveCriticalSection(&slot->Lock);
        return result;
    }
    return -13;
}

// FUNCTION: GAMEMD 0x411820
// The VQ audio handler's command dispatcher (command in the second argument).
int __cdecl FUN_00411820(StreamSampleView* sample, int command, StreamOpenParams* arg, int size)
{
    int result = -1;
    switch (command)
    {
    case 1:
        sample->unknown_50 = (void*)FUN_00412540;
        sample->unknown_78 = 0x3C;
        break;
    case 2:
        result = FUN_00411b20(sample, arg, size);
        break;
    case 3:
        result = FUN_00411ce0(sample);
        break;
    case 4:
        result = FUN_00411df0(sample);
        break;
    case 5:
        result = FUN_00412000(sample, arg, size);
        break;
    case 6:
        result = FUN_00412230(sample);
        break;
    case 8:
        result = ResumeSlot(sample);
        break;
    case 7:
        result = StopSlotBuffer(sample);
        break;
    }
    return result;
}

// FUNCTION: GAMEMD 0x411B20
int __cdecl FUN_00411b20(StreamSampleView* sample, StreamOpenParams* params, int size)
{
    void* ds = FUN_0040A7A0();
    FUN_004068E0("Opening VQ audio handler\n");
    FUN_004068E0("Current thread ID is %08x\n", GetCurrentThreadId());
    if (!FUN_00407000())
    {
        return -13;
    }
    int i;
    for (i = 0; i < 1; i++)
    {
        if (!DAT_00887778[i].Active)
        {
            break;
        }
    }
    if (i == 1 || size != sizeof(StreamOpenParams))
    {
        return -13;
    }
    StreamSlot* slot = &DAT_00887778[i];
    sample->Slot = i;
    memset(slot, 0, sizeof(StreamSlot));
    slot->Active = 1;
    slot->unknown_04 = sample->unknown_A4;
    InitializeCriticalSection(&slot->Lock);
    if (sample->unknown_A0 != (unsigned)-1)
    {
        slot->Rate = (unsigned short)sample->unknown_A0;
    }
    else if (sample->unknown_70 != sample->unknown_0E)
    {
        slot->Rate = (unsigned short)(params->Rate * sample->unknown_70 / sample->unknown_0E);
    }
    else
    {
        slot->Rate = params->Rate;
    }
    DSCAPS caps;
    memset(&caps, 0, sizeof(caps));
    caps.dwSize = sizeof(DSCAPS);
    ((DirectSoundResource_00409FF0*)ds)->Vptr->GetCaps((DirectSoundResource_00409FF0*)ds, &caps);
    if (caps.dwFlags & DSCAPS_EMULDRIVER)
    {
        FUN_004068E0("Ahandle detected emulated sound driver. LatencyAdjustment = %ld ticks\n", sample->unknown_C4);
    }
    else
    {
        sample->unknown_C4 = 0;
    }
    slot->Channels = params->Channels;
    slot->Bits = params->Bits;
    slot->unknown_24 = params->unknown_04;
    DAT_0088776C = params->Hook0;
    DAT_00887770 = params->Hook1;
    FUN_004068E0("Calling timeBeginPeriod\n");
    if (timeBeginPeriod(16) == TIMERR_NOCANDO)
    {
        return -13;
    }
    FUN_004068E0("Creating VQ audio timer thread\n");
    slot->TimerID = timeSetEvent(16, 1, (LPTIMECALLBACK)FUN_004123a0, (DWORD)sample, TIME_PERIODIC);
    FUN_004068E0("VQ audio handler opened OK\n");
    return slot->TimerID ? -1 : -13;
}

// FUNCTION: GAMEMD 0x411CE0
int __cdecl FUN_00411ce0(StreamSampleView* sample)
{
    FUN_004068E0("Closing VQ audio handler\n");
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    if (slot->Active == 1)
    {
        if (slot->Buffer != 0)
        {
            FUN_004068E0("Stop_Audio_Handler\n");
            StopSlotBuffer(sample);
        }
        FUN_004068E0("Calling timeKillEvent\n");
        timeKillEvent(slot->TimerID);
        slot->TimerID = 0;
        FUN_004068E0("Calling timeEndPeriod\n");
        timeEndPeriod(16);
        slot->Active = 0;
        FUN_004068E0("Deleting the critical section object\n");
        DeleteCriticalSection(&slot->Lock);
    }
    FUN_004068E0("VQ audio handler closed OK\n");
    return -1;
}

// FUNCTION: GAMEMD 0x411DF0
int __cdecl FUN_00411df0(StreamSampleView* sample)
{
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    if (slot->Flags & 1)
    {
        return ResumeSlot(sample);
    }
    EnterCriticalSection(&slot->Lock);
    if (slot->Buffer != 0)
    {
        slot->Buffer->lpVtbl->Stop(slot->Buffer);
        slot->Buffer->lpVtbl->Release(slot->Buffer);
        slot->Buffer = 0;
    }
    slot->BufferSize = sample->unknown_9C * 2;
    memset(&slot->Desc, 0, sizeof(slot->Desc));
    slot->Desc.dwSize = sizeof(DSBUFFERDESC);
    slot->Desc.dwFlags = 0x100E0;
    slot->Desc.dwBufferBytes = slot->BufferSize;
    slot->Desc.lpwfxFormat = &slot->Format;
    memset(&slot->Format, 0, sizeof(slot->Format));
    slot->Format.wFormatTag = WAVE_FORMAT_PCM;
    slot->Format.wBitsPerSample = slot->Bits;
    slot->Format.nBlockAlign = (unsigned short)((slot->Format.wBitsPerSample >> 3) * slot->Channels);
    slot->Format.nSamplesPerSec = slot->Rate;
    slot->Format.nChannels = slot->Channels;
    slot->Format.nAvgBytesPerSec = slot->Format.nBlockAlign * slot->Format.nSamplesPerSec;
    DirectSoundResource_00409FF0* ds = (DirectSoundResource_00409FF0*)FUN_0040A7A0();
    ds->Vptr->CreateBuffer(ds, &slot->Desc, (SoundBuffer_0040A7B0**)&slot->Buffer, 0);
    if (slot->Buffer == 0)
    {
        LeaveCriticalSection(&slot->Lock);
        return -13;
    }
    DAT_0088776C(sample);
    DAT_0088776C(sample);
    slot->Current = 0;
    slot->unknown_9C = 0;
    slot->Fills = 0;
    slot->Buffer->lpVtbl->SetCurrentPosition(slot->Buffer, 0);
    int volume = (int)(DAT_00A8EB9C * 255.0f);
    slot->unknown_04 = volume;
    slot->Buffer->lpVtbl->SetVolume(slot->Buffer, FUN_0040A900(volume & 0xFF));
    int r = slot->Buffer->lpVtbl->Play(slot->Buffer, 0, 0, 1);
    LeaveCriticalSection(&slot->Lock);
    return r ? -13 : -1;
}

// FUNCTION: GAMEMD 0x412230
// Pause a streaming sample: stop its sound buffer under the slot's lock and
// flag the slot as paused. Always returns -1.
int __cdecl FUN_00412230(StreamSampleView* sample)
{
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    EnterCriticalSection(&slot->Lock);
    if (slot->Active == 1 && slot->Buffer != 0)
    {
        slot->Buffer->lpVtbl->Stop(slot->Buffer);
    }
    slot->Flags |= 1;
    LeaveCriticalSection(&slot->Lock);
    return -1;
}

// FUNCTION: GAMEMD 0x4123A0
void __stdcall FUN_004123a0(unsigned timer_id, unsigned message, StreamSampleView* sample,
                            unsigned param1, unsigned param2)
{
    bool replay = false;
    StreamSlot* slot = &DAT_00887778[sample->Slot];
    if (InterlockedIncrement(&slot->Busy) != 1 || (slot->Flags & 1))
    {
        InterlockedDecrement(&slot->Busy);
        return;
    }
    {
        EnterCriticalSection(&slot->Lock);
        if (slot->Buffer == 0 || slot->TimerID != timer_id)
        {
            LeaveCriticalSection(&slot->Lock);
            InterlockedDecrement(&slot->Busy);
            return;
        }
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
                    DAT_00887770(sample, slot->Chunk[slot->Current]);
                    int current = slot->Current;
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

// FUNCTION: GAMEMD 0x412550
// PARTIAL: 88.2%. Same instructions; retail pushes the Leave argument after the OR.
// Stop the first slot's sound buffer under its lock and flag the slot as
// paused. Does nothing unless the slot is active and has a buffer.
void __cdecl FUN_00412550()
{
    if (DAT_00887778[0].Active == 1 && DAT_00887778[0].Buffer != 0)
    {
        EnterCriticalSection(&DAT_00887778[0].Lock);
        DAT_00887778[0].Buffer->lpVtbl->Stop(DAT_00887778[0].Buffer);
        DAT_00887778[0].Flags |= 1;
        LeaveCriticalSection(&DAT_00887778[0].Lock);
    }
}

// FUNCTION: GAMEMD 0x4125A0
// PARTIAL: 80.0%. Same instructions; retail pushes the Leave argument after the AND.
// Resume the first slot's sound buffer (looping play) under its lock and clear
// the paused flag. Does nothing unless the slot is active and has a buffer.
void __cdecl FUN_004125a0()
{
    if (DAT_00887778[0].Active == 1 && DAT_00887778[0].Buffer != 0)
    {
        EnterCriticalSection(&DAT_00887778[0].Lock);
        DAT_00887778[0].Buffer->lpVtbl->Play(DAT_00887778[0].Buffer, 0, 0, 1);
        DAT_00887778[0].Flags &= ~1;
        LeaveCriticalSection(&DAT_00887778[0].Lock);
    }
}
