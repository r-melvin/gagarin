// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI not present for this type
//   The 0x148-byte sound descriptor a sound.ini entry configures. Offsets read numerically off the user's
//   retail gamemd.exe v1.001 from the INI reader 0x750440 (every setter call and its key string), the
//   setters / getters 0x405130..0x405170 and 0x406520..0x406650, the sample appender 0x4064A0 ("Missing
//   sample %s\n" at 0x816218; at most 0x20 sample indices at +0xB4, count at +0x134) and the allocation
//   0x4063B0 (operator_new(0x148)).
//   Field names are the sound.ini key each setter is fed from (Control, Type, Volume, Priority, Limit, Loop,
//   Range, MinVolume, Delay, FShift, VShift, Attack, Decay, Sounds); the type name AudioEventType and the
//   unreferenced words are placeholders. Setters keep their address names.
#ifndef GG_MATCH__LAYOUT_AUDIO_EVENT_TYPE_H
#define GG_MATCH__LAYOUT_AUDIO_EVENT_TYPE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/triple_timer_init_methods.h"

struct AudioEventType
{
    // FUNCTION: GAMEMD 0x405130 -- Range, 0 while audio is off
    int FUN_00405130() const;
    // FUNCTION: GAMEMD 0x405140 -- MinVolume, 0 while audio is off
    float FUN_00405140() const;
    // FUNCTION: GAMEMD 0x405160 -- Type flags, 0 while audio is off
    int FUN_00405160() const;
    // FUNCTION: GAMEMD 0x405170 -- the name ("no events" while audio is off)
    const char* FUN_00405170() const;
    // FUNCTION: GAMEMD 0x4064A0 -- append a sample by name; 1 unless the list is full
    int __fastcall FUN_004064A0(const char* name);
    // FUNCTION: GAMEMD 0x406520 -- Attack
    void __fastcall FUN_00406520(int value);
    // FUNCTION: GAMEMD 0x406530 -- Decay
    void __fastcall FUN_00406530(int value);
    // FUNCTION: GAMEMD 0x406540 -- Priority
    void __fastcall FUN_00406540(int value);
    // FUNCTION: GAMEMD 0x406550 -- Volume (runs the ramp resets on the sub-object at +0x18)
    void __fastcall FUN_00406550(int value);
    // FUNCTION: GAMEMD 0x406570 -- Control (arms / clears the two latches from bits 0x20 / 0x40)
    void __fastcall FUN_00406570(int value);
    // FUNCTION: GAMEMD 0x4065C0 -- Type flags
    void __fastcall FUN_004065C0(int value);
    // FUNCTION: GAMEMD 0x4065D0 -- Limit
    void __fastcall FUN_004065D0(int value);
    // FUNCTION: GAMEMD 0x4065E0 -- Range
    void __fastcall FUN_004065E0(int value);
    // FUNCTION: GAMEMD 0x4065F0 -- MinVolume
    void FUN_004065F0(float value);
    // FUNCTION: GAMEMD 0x406600 -- Delay
    void __fastcall FUN_00406600(int first, int second);
    // FUNCTION: GAMEMD 0x406610 -- FShift
    void __fastcall FUN_00406610(int first, int second);
    // FUNCTION: GAMEMD 0x406620 -- VShift, clamped to 0..100
    void __fastcall FUN_00406620(int value);
    // FUNCTION: GAMEMD 0x406640 -- Loop
    void __fastcall FUN_00406640(int value);
    // FUNCTION: GAMEMD 0x406650 -- true when Control bit 0 is set and Loop is clear
    int FUN_00406650() const;

    char           unknown_00[0x0C];   // +0x000  list link (re-armed by 0x4072D0)
    int            unknown_0C;         // +0x00C  cleared when a sample name does not resolve
    int            Control;            // +0x010  "Control": bit 0x20 arms Attack, 0x40 arms Decay
    int            Type;               // +0x014  "Type" flags
    Timer_00401000 Volume;             // +0x018  "Volume" ramp (0x28 bytes)
    int            Priority;           // +0x040  "Priority"
    int            unknown_44;         // +0x044
    int            Limit;              // +0x048  "Limit"
    int            Loop;               // +0x04C  "Loop"
    int            Range;              // +0x050  "Range"
    float          MinVolume;          // +0x054  "MinVolume"
    int            DelayLow;           // +0x058  "Delay"
    int            DelayHigh;          // +0x05C
    int            FShiftLow;          // +0x060  "FShift"
    int            FShiftHigh;         // +0x064
    int            VShift;             // +0x068  "VShift", 0..100
    char           Name[0x20];         // +0x06C
    char           unknown_8C[0xB4 - 0x8C];
    unsigned int   Sounds[0x20];       // +0x0B4  "Sounds": sample indices
    int            SampleCount;        // +0x134
    int            Attack;             // +0x138  "Attack"
    int            Decay;              // +0x13C  "Decay"
    char           unknown_140[8];     // +0x140
};
GG_STATIC_ASSERT(offsetof(AudioEventType, Control)     == 0x10);
GG_STATIC_ASSERT(offsetof(AudioEventType, Type)        == 0x14);
GG_STATIC_ASSERT(offsetof(AudioEventType, Volume)      == 0x18);
GG_STATIC_ASSERT(offsetof(AudioEventType, Priority)    == 0x40);
GG_STATIC_ASSERT(offsetof(AudioEventType, Limit)       == 0x48);
GG_STATIC_ASSERT(offsetof(AudioEventType, Loop)        == 0x4C);
GG_STATIC_ASSERT(offsetof(AudioEventType, Range)       == 0x50);
GG_STATIC_ASSERT(offsetof(AudioEventType, MinVolume)   == 0x54);
GG_STATIC_ASSERT(offsetof(AudioEventType, DelayLow)    == 0x58);
GG_STATIC_ASSERT(offsetof(AudioEventType, FShiftLow)   == 0x60);
GG_STATIC_ASSERT(offsetof(AudioEventType, VShift)      == 0x68);
GG_STATIC_ASSERT(offsetof(AudioEventType, Name)        == 0x6C);
GG_STATIC_ASSERT(offsetof(AudioEventType, Sounds)      == 0xB4);
GG_STATIC_ASSERT(offsetof(AudioEventType, SampleCount) == 0x134);
GG_STATIC_ASSERT(offsetof(AudioEventType, Attack)      == 0x138);
GG_STATIC_ASSERT(offsetof(AudioEventType, Decay)       == 0x13C);
GG_STATIC_ASSERT(sizeof(AudioEventType)                == 0x148);

#endif
