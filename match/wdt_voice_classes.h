// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at the addresses named below.
//   The two placeholder receivers of the cluster between WDTTerr.cpp and
//   WOLPersonaInformation.cpp (match/tu281_wdtvoice.cpp and
//   match/wdt_voice_ctor_00770270.cpp), shared so that neither file carries
//   its own view of them. The owning classes are unknown.
#ifndef GG_MATCH_WDT_VOICE_CLASSES_H
#define GG_MATCH_WDT_VOICE_CLASSES_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "string_class.h"
#include "randomizer.h"
#include "vector_class_mutation.h"
#include "game_timing_methods.h"
#include "_layout/elapsed_timer.h"
#include "_layout/ini_class.h"

// FUNCTION: GAMEMD 0x7529A0 (decl; reloc)
void __fastcall FUN_007529A0(bool dropQueue);

// FUNCTION: GAMEMD 0x7529E0 (decl; reloc)
bool FUN_007529E0();
// FUNCTION: GAMEMD 0x770CE0 (decl; reloc)
bool __fastcall FUN_00770CE0(int side, int line, Wstring* out);

// FUNCTION: GAMEMD 0x752480 (decl; reloc) -- ECX id, EDX and one stack word.
void FUN_00752480(int id, int a, int b);
// FUNCTION: GAMEMD 0x753250 (decl; reloc) -- parse a name into an index.
int FUN_00753250(const char* name);

extern const char STR_00889F64[];   // STRING: GAMEMD 0x889F64 ""
extern const char STR_00817F70[];   // STRING: GAMEMD 0x817F70 ","
extern const char DAT_008491F0[];   // STRING: GAMEMD 0x8491F0 "WWD_Allied"
extern const char DAT_008491FC[];   // STRING: GAMEMD 0x8491FC "WWD-Soviet"

// FUNCTION: GAMEMD 0x7AF2A0 (decl; reloc) -- the text of side `index`.
Wstring* __fastcall FUN_007AF2A0(int index);
// FUNCTION: GAMEMD 0x7B64E0 (decl; reloc) -- `left` followed by `right`.
Wstring __fastcall FUN_007B64E0(const Wstring& left, const Wstring& right);
// FUNCTION: GAMEMD 0x7B6320 (decl; reloc) -- zero-padded decimal text of `value`, `width` digits.
Wstring __fastcall FUN_007B6320(int value, int width);
// FUNCTION: GAMEMD 0x7B63C0 (decl; reloc) -- `prefix` followed by `suffix`.
Wstring __fastcall FUN_007B63C0(const char* prefix, const Wstring& suffix);

// The line picker shared by the voice-line getters below (0x770C10 is its out-of-line copy).
inline bool PickLine(int side, DynamicVectorClass<unsigned>* lines, Wstring& out)
{
    out.FUN_007B5340();
    int count = lines->Count;
    if (count <= 0) {
        return false;
    }
    int pick = count == 1 ? 0 : DAT_00886B88.RandomRanged(0, count - 1);
    unsigned line = lines->Items[pick];
    if (side == 3) {
        out = FUN_007B63C0(DAT_008491FC, FUN_007B6320(line, 2));
    } else {
        out = FUN_007B63C0(DAT_008491F0, FUN_007B6320(line, 2));
    }
    return true;
}

// Comma separated list of integers into a vector (0x770D70 is its out-of-line copy).
inline void ParseIntList(Wstring* text, DynamicVectorClass<unsigned>* lines)
{
    lines->Clear();
    Wstring token;
    int cursor = text->FUN_007B5F10(0, STR_00817F70, &token);
    while (cursor != -1) {
        unsigned value = token.FUN_007B6280();
        lines->AddItem(value);
        cursor = text->FUN_007B5F10(cursor, STR_00817F70, &token);
    }
}

// A string at +0x00 followed by six dynamic vectors of 4-byte items (stride 0x18);
// vectors 2n and 2n+1 hold the two line sets of kind n.
struct Obj_00407F80;

class Obj_00770E10 {
public:
    Obj_00770E10();                                                 // GAMEMD 0x770E10
    void FUN_00770E70(INIClass* ini, const Wstring* section, int side);   // GAMEMD 0x770E70
    bool FUN_00770F10(int side, int kind, Wstring& out);            // GAMEMD 0x770F10
    bool FUN_00770FE0(int side, int kind, Wstring& out);            // GAMEMD 0x770FE0
    void FUN_007710B0(INIClass* ini, const Wstring* section, int side, int kind, const Wstring* suffix); // GAMEMD 0x7710B0
    Wstring unknown_00;
    DynamicVectorClass<unsigned> unknown_04[6];
    // The win/lose/draw line sets (0x770E70 out of line, expanded in 0x770550).
    void ReadCases(INIClass* ini, const Wstring* section, int side)
    {
        {
            Wstring win("Win");
            FUN_007710B0(ini, section, side, 0, &win);
        }
        {
            Wstring lose("Lose");
            FUN_007710B0(ini, section, side, 1, &lose);
        }
        {
            Wstring draw("Draw");
            FUN_007710B0(ini, section, side, 2, &draw);
        }
    }
    bool PickA(int side, int kind, Wstring& out) { return PickLine(side, &unknown_04[kind * 2], out); }
    bool PickB(int side, int kind, Wstring& out) { return PickLine(side, &unknown_04[kind * 2 + 1], out); }
};
GG_STATIC_ASSERT(sizeof(Obj_00770E10) == 0x94);

// The owner: a side id, six line-set records, two more vectors, a timer and a
// string vector.
class Obj_00770430 {
public:
    Obj_00770430(int side);                                         // GAMEMD 0x770270
    void FUN_00770550(INIClass* ini, const Wstring* section);        // GAMEMD 0x770550
    void FUN_00770850(INIClass* ini, const Wstring* section, int index, const Wstring* key); // GAMEMD 0x770850
    bool FUN_00770970(int set, int kind, Wstring& out);             // GAMEMD 0x770970
    bool FUN_00770A50(int set, int kind, Wstring& out);             // GAMEMD 0x770A50
    bool FUN_00770B30(int index, Wstring& out);                     // GAMEMD 0x770B30
    void FUN_007714B0(int index, bool counted, int ticks);          // GAMEMD 0x7714B0
    void FUN_00771620();                                            // GAMEMD 0x771620
    void FUN_00771710();                                            // GAMEMD 0x771710
    void FUN_007717A0();                                            // GAMEMD 0x7717A0
    int unknown_00;
    Obj_00770E10 unknown_04[6];
    DynamicVectorClass<unsigned> unknown_37C[2];
    ScenarioElapsedTimer unknown_3AC;
    bool unknown_3B8;
    int unknown_3BC;
    DynamicVectorClass<Wstring> unknown_3C0;
    Obj_00407F80* unknown_3D8;
    // Drops the string entries above the kept count (0x771710 out of line, expanded in 0x7714B0).
    void DropExtra()
    {
        for (int i = unknown_3C0.Count; i-- > unknown_3BC; ) {
            unknown_3C0.Delete(i);
        }
        if (unknown_3BC == 0) {
            unknown_3B8 = true;
        }
    }
};
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_37C) == 0x37C);
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_3AC) == 0x3AC);
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_3B8) == 0x3B8);
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_3BC) == 0x3BC);
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_3C0) == 0x3C0);
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_3C0.Count) == 0x3D0);
GG_STATIC_ASSERT(offsetof(Obj_00770430, unknown_3D8) == 0x3D8);

#endif // GG_MATCH_WDT_VOICE_CLASSES_H
