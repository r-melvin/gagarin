// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x48D080: the pump gate 0xB45B68 with the object list
//   0xB45B5C (COM slot +0x8), the session mode 0xA8B238 tested against 1..4,
//   the flag byte 0xA8DAB8 bit 0, the message queue object 0xA8EA70 with
//   0x5F1C60 (drain) and 0x5F1C30 (pop into a message and a flag), the
//   scenario pointer 0xA8B230 with its byte at +0x3598, the local player
//   index 0xA8DB30, the audio object 0xAC4F58 with 0x643C50 (flag, a double
//   from the message's unaligned int at +0x19, then two -1s), the
//   screensaver guards 0xB77DC2 / 0xB77DCC, the last-tick store 0x89E9B0
//   fed by the CRT clock 0x7CA67F, and the two COM pointers 0xAC116C
//   (slot +0xC) and 0xAC1170 (slot +0x1C). The frame is eight-aligned
//   because of the FILD/FSTP pair.
#ifndef GG_MATCH_CORE_UNSORTED_CALLBACK_METHODS_H
#define GG_MATCH_CORE_UNSORTED_CALLBACK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One message popped off the queue: only the kind, the sender byte and the
// payload int are read, and the payload sits one byte into the sender word,
// so the record is packed.
#pragma pack(push, 1)
struct Message_0048D080
{
    int  Kind;                 // +0x0000
    char _pad004[0x18 - 0x04]; // +0x0004
    union
    {
        int SenderWord;        // +0x0018  low byte is the sender
        struct
        {
            char Sender;       // +0x0018
            int  Payload;      // +0x0019  unaligned
        } Packed;
    };
    char _pad01D[0xFC - 0x1D]; // +0x001D
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Message_0048D080, SenderWord) == 0x18);
GG_STATIC_ASSERT(sizeof(Message_0048D080) == 0xFC);

// The message queue.
struct Queue_0048D080
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5F1C60 (decl; reloc) — refill the queue.
    void FUN_005F1C60();
    // FUNCTION: GAMEMD 0x5F1C30 (decl; reloc) — pop one message.
    int FUN_005F1C30(Message_0048D080* message, int* flag);
};
// GLOBAL: GAMEMD 0xA8EA70 — the queue.
extern Queue_0048D080 DAT_00A8EA70;

// The audio object the chat blip is played through.
struct Audio_0048D080
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x643C50 (decl; reloc) — play a sound.
    void FUN_00643C50(int flag, double value, int a3, int a4);
};
// GLOBAL: GAMEMD 0xAC4F58 — the audio object.
extern Audio_0048D080 DAT_00AC4F58;

// The scenario; only the byte at +0x3598 is read.
struct Scenario_0048D080
{
    char _pad000[0x3598];   // +0x0000
    char At_3598;           // +0x3598
};
GG_STATIC_ASSERT(offsetof(Scenario_0048D080, At_3598) == 0x3598);
// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_0048D080* DAT_00A8B230;

// An object in the pump list; only the slot at +0x8 is called.
struct PumpVtbl_0048D080;
struct Pump_0048D080
{
    PumpVtbl_0048D080* Vptr;   // +0x0000
};
typedef void (Pump_0048D080::*Fn08_0048D080)();
struct PumpVtbl_0048D080
{
    char           _pad000[0x8];   // +0x0000
    Fn08_0048D080  At_08;          // +0x0008
};
GG_STATIC_ASSERT(offsetof(PumpVtbl_0048D080, At_08) == 0x8);

// GLOBAL: GAMEMD 0xB45B68 — how many objects the pump list holds.
extern int DAT_00B45B68;
// GLOBAL: GAMEMD 0xB45B5C — the pump list.
extern Pump_0048D080** DAT_00B45B5C;
// GLOBAL: GAMEMD 0xA8B238 — SessionClass::Instance.GameMode.
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xA8DAB8 — the pump-enable flags.
extern unsigned char DAT_00A8DAB8;
// GLOBAL: GAMEMD 0xA8DB30 — the local player's index.
extern int DAT_00A8DB30;
// GLOBAL: GAMEMD 0xB77DC2 — set while the screensaver guard is off.
extern char DAT_00B77DC2;
// GLOBAL: GAMEMD 0xB77DCC — non-zero while the first device is busy.
extern int DAT_00B77DCC;
// GLOBAL: GAMEMD 0x89E9B0 — the tick the guard last ran at.
extern int DAT_0089E9B0;

// The two COM objects the guard pokes; each call pushes the receiver.
struct ComVtbl_0048D080;
struct Com_0048D080
{
    ComVtbl_0048D080* Vptr;   // +0x0000
};
struct ComVtbl_0048D080
{
    char  _pad000[0x0C];                                   // +0x0000
    void (__stdcall* At_0C)(Com_0048D080* self);           // +0x000C
    char  _pad010[0x1C - 0x10];                            // +0x0010
    void (__stdcall* At_1C)(Com_0048D080* self);           // +0x001C
};
GG_STATIC_ASSERT(offsetof(ComVtbl_0048D080, At_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ComVtbl_0048D080, At_1C) == 0x1C);
// GLOBAL: GAMEMD 0xAC116C — the first guarded device.
extern Com_0048D080* DAT_00AC116C;
// GLOBAL: GAMEMD 0xAC1170 — the second guarded device.
extern Com_0048D080* DAT_00AC1170;

// FUNCTION: GAMEMD 0x406F70 (decl; reloc) — service the audio engine.
void __cdecl FUN_00406F70();
// FUNCTION: GAMEMD 0x48D1E0 (decl; reloc) — the in-game callback half.
void __cdecl FUN_0048D1E0();
// FUNCTION: GAMEMD 0x7CA67F (decl; reloc) — CRT time.
extern "C" int __cdecl gg_time(int* out);

// FUNCTION: GAMEMD 0x48D080 — Unsorted::CallBack.
void __cdecl Unsorted_CallBack();

#endif  // GG_MATCH_CORE_UNSORTED_CALLBACK_METHODS_H
