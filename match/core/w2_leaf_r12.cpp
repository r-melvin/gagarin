// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small leaf bodies
//   from the 0x54E000-0x6ABD00 range; receivers are placeholder views of the members touched.
//
// Address index: 0x5DAF20 0x69E070 0x5DA040 0x5DA080 0x5FA440 0x5FA470 0x660BB0 0x660C50 0x5BB260 0x5CB400 0x6ABD10 0x5FA2E0 0x5FA310 0x5F0010 0x5F0040

#include <stddef.h>
#include "../_layout/session_class.h"
#include "mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void __cdecl FUN_0048D080();
// FUNCTION: GAMEMD 0x5E00B0 (decl; reloc)
void __cdecl FUN_005E00B0();

// FUNCTION: GAMEMD 0x5DAF20
// Run the two shutdown helpers and answer false.
bool __cdecl FUN_005DAF20()
{
    FUN_0048D080();
    FUN_005E00B0();
    return false;
}


// SYNTHETIC: GAMEMD 0x0069E070
// GLOBAL: GAMEMD 0x00B077A0
MathTblZero4 DAT_00B077A0;

// FUNCTION: GAMEMD 0x5DA040
// Sum a weight for every flag set in the byte.
int __stdcall FUN_005DA040(unsigned char flags)
{
    int r = 0;
    if (flags & 0x01) r = 1;
    if (flags & 0x02) r += 2;
    if (flags & 0x04) r += 3;
    if (flags & 0x08) r += 10;
    if (flags & 0x10) r += 1;
    if (flags & 0x20) r += 2;
    return r;
}

// FUNCTION: GAMEMD 0x5DA080
// Base two, bumped by the flags set in the byte.
int __stdcall FUN_005DA080(unsigned char flags)
{
    int r = 2;
    if (flags & 0x01) r = 3;
    if (flags & 0x02) r += 1;
    if (flags & 0x04) r += 1;
    if (flags & 0x20) r += 5;
    return r;
}

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc)
void __cdecl FUN_004068E0(const char* format, const char* text);

// STRING: GAMEMD 0x82C45C -- "OFF"
extern char STR_0082C45C[];
// STRING: GAMEMD 0x82C460 -- "ON"
extern char STR_0082C460[];
// STRING: GAMEMD 0x832F74 -- "ScoreShuffle is %s\n"
extern char STR_00832F74[];
// STRING: GAMEMD 0x832F88 -- "ScoreRepeat is %s\n"
extern char STR_00832F88[];
// GLOBAL: GAMEMD 0xA83D20
extern char DAT_00A83D20;
// GLOBAL: GAMEMD 0xA83D22
extern char DAT_00A83D22;

// Jukebox option block: repeat flag at +0x44, shuffle flag at +0x46.
struct ScoreOptions_005FA440
{
    char unknown_00[0x44];
    char Repeat;         // +0x44
    char unknown_45;
    char Shuffle;        // +0x46

    void FUN_005FA440(char on);
    void FUN_005FA470(char on);
};
GG_STATIC_ASSERT(offsetof(ScoreOptions_005FA440, Repeat) == 0x44);
GG_STATIC_ASSERT(offsetof(ScoreOptions_005FA440, Shuffle) == 0x46);

// FUNCTION: GAMEMD 0x5FA440
// Store the shuffle flag, mirror it in the global and log it.
void ScoreOptions_005FA440::FUN_005FA440(char on)
{
    Shuffle = on;
    DAT_00A83D22 = on;
    FUN_004068E0(STR_00832F74, Shuffle == 1 ? STR_0082C460 : STR_0082C45C);
}

// FUNCTION: GAMEMD 0x5FA470
// Store the repeat flag, mirror it in the global and log it.
void ScoreOptions_005FA440::FUN_005FA470(char on)
{
    Repeat = on;
    DAT_00A83D20 = on;
    FUN_004068E0(STR_00832F88, Repeat == 1 ? STR_0082C460 : STR_0082C45C);
}

// GLOBAL: GAMEMD 0xB04D88
extern int DAT_00B04D88;
// GLOBAL: GAMEMD 0xB04DD8
extern int DAT_00B04DD8;
// GLOBAL: GAMEMD 0xB04D68
extern int DAT_00B04D68;
// GLOBAL: GAMEMD 0xB04D48 -- eight words
extern int DAT_00B04D48[8];

struct IntBox_00660BB0
{
    int Value;
    IntBox_00660BB0* FUN_00660BB0();
};

// FUNCTION: GAMEMD 0x660BB0
// Hand back the current table entry in the caller's box, or the default when none is selected.
IntBox_00660BB0* IntBox_00660BB0::FUN_00660BB0()
{
    if (DAT_00B04D88 == -1) {
        Value = DAT_00B04D68;
        return this;
    }
    int index = DAT_00B04D88;
    int entry = DAT_00B04D48[index];
    DAT_00B04DD8 = index;
    Value = entry;
    return this;
}

// FUNCTION: GAMEMD 0x660C50
// Clear the selection and refill the table with the default.
void __cdecl FUN_00660C50()
{
    DAT_00B04D88 = -1;
    DAT_00B04DD8 = -1;
    for (int i = 0; i < 8; i++) {
        DAT_00B04D48[i] = DAT_00B04D68;
    }
}

// Two-method view of the object the shutdown path tears down.
class Obj_005B9F30
{
public:
    void FUN_005B9F30(int flag);   // FUNCTION: GAMEMD 0x5B9F30 (decl; reloc)
    void FUN_005BA060(int flag);   // FUNCTION: GAMEMD 0x5BA060 (decl; reloc)
};
// GLOBAL: GAMEMD 0xABF10C
extern Obj_005B9F30* DAT_00ABF10C;

// FUNCTION: GAMEMD 0x5BB260
// Stop and release the held object when there is one, run the helper and answer false.
bool __cdecl FUN_005BB260()
{
    if (DAT_00ABF10C != 0) {
        DAT_00ABF10C->FUN_005B9F30(0);
        DAT_00ABF10C->FUN_005BA060(1);
    }
    FUN_0048D080();
    return false;
}

// GLOBAL: GAMEMD 0xA8B258
extern unsigned char DAT_00A8B258;
// FUNCTION: GAMEMD 0x5D6310 (decl; reloc)
bool __stdcall FUN_005D6310(int arg);

// FUNCTION: GAMEMD 0x5CB400
// True when the feature byte is set and the checker accepts the argument.
int __stdcall FUN_005CB400(int arg)
{
    if (DAT_00A8B258 && FUN_005D6310(arg)) {
        return 1;
    }
    return 0;
}

struct SlotTable_006ABD10
{
    char unknown_000[0x1598];
    int FirstCount;      // +0x1598, then every 0xF94 bytes
    int FUN_006ABD10();
};

// FUNCTION: GAMEMD 0x6ABD10
int SlotTable_006ABD10::FUN_006ABD10()
{
    for (int i = 0; i < 4; i++) {
        if (*(int*)((char*)this + 0x1598 + i * 0xF94) > 0) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5FA2E0
// Keep the low byte and move three of the four modifier bits into the second byte; bit 3 voids the value.
unsigned int __fastcall FUN_005FA2E0(unsigned int value)
{
    unsigned int result = value & 0xFF;
    unsigned int mods = (value >> 8) & 0xFF;
    if (mods & 0x04) result |= 0x400;
    if (mods & 0x02) result |= 0x200;
    if (mods & 0x01) result |= 0x100;
    if (mods & 0x08) result = 0;
    return result;
}

// FUNCTION: GAMEMD 0x5FA310
// Inverse of the above: fold the second byte's flags into a compact modifier byte.
unsigned int __fastcall FUN_005FA310(unsigned int value)
{
    unsigned int mods = 0;
    if (value & 0x400) mods = 4;
    if (value & 0x200) mods |= 2;
    if (value & 0x100) mods |= 1;
    if (value & 0x1000) mods |= 8;
    return (value & 0xFF) | (mods << 8);
}

// Object whose one method takes seven arguments (global instance at 0xA8EA70).
class Obj_005F16E0
{
public:
    int unknown_00;
    int FUN_005F16E0(int a, int b, int* c, int d, int e, int f, int g);   // FUNCTION: GAMEMD 0x5F16E0 (decl; reloc)
    void FUN_005F3170();                                                  // FUNCTION: GAMEMD 0x5F3170 (decl; reloc)
    void FUN_005F1B70();                                                  // FUNCTION: GAMEMD 0x5F1B70 (decl; reloc)
};
// GLOBAL: GAMEMD 0xA8EA70
extern Obj_005F16E0 DAT_00A8EA70;
// GLOBAL: GAMEMD 0xA8D5F8
extern unsigned char DAT_00A8D5F8;

struct Req_005F0010
{
    int A;                 // +0x00
    int B;                 // +0x04
    int C;                 // +0x08
    char unknown_0C[0x24];
    int Out;               // +0x30

    bool FUN_005F0010();
};
GG_STATIC_ASSERT(offsetof(Req_005F0010, Out) == 0x30);

// FUNCTION: GAMEMD 0x5F0010
// Submit the request to the global object; true when it answers non-zero.
bool Req_005F0010::FUN_005F0010()
{
    bool r = DAT_00A8EA70.FUN_005F16E0(A, B, &Out, C, 0, 8, 1) != 0;
    return r;
}

// FUNCTION: GAMEMD 0x5F0040
// Unless the flag bit is set and the mode is one, run the first helper; then the second.
void __cdecl FUN_005F0040()
{
    if (!(DAT_00A8D5F8 & 2) && Session_00A8B238.GameMode == 1) {
        DAT_00A8EA70.FUN_005F3170();
    }
    DAT_00A8EA70.FUN_005F1B70();
}
