// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, vtable slots and ABI read numerically off the user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (entry disassembly at 0x4AAD30, 0x4AAE90, 0x4AB9B0) and the DisplayClass vtable 0x7E6114 (50 slots, locator via
//   RTTI .?AVDisplayClass@@). Names are descriptive of observed behaviour.
//
// The command entries of DisplayClass (the class is in ui_display_chain.h). Members they touch:
//   +0x11A4 Pending (object pointer; byte +0x14 bit 0 tested)    +0x11A8 int   +0x11AC int (-1 = none)
//   +0x11B0..+0x11B4 five mode bytes (repair, sell, power, waypoint, beacon)
//   +0x11B8 int (-1 = none)   +0x11BC DisplayVec3* (written by the click handler)
//   +0x11CC..+0x11CE colour bytes (RGB triple)   +0x11D0 byte
#ifndef GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_COMMAND_H
#define GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_COMMAND_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "ui_display_chain.h"


class DisplayCmdTechno;
struct DisplayCmdHouse;
class DisplayCmdPendType;

// The object an anchor query returns; its sub-object at +0x24 is what the two selection routines take as `this`.
struct DisplayCmdSub
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x732600 (decl; reloc)
    void FUN_00732600();
    // FUNCTION: GAMEMD 0x7327D0 (decl; reloc)
    void FUN_007327D0();
};
struct DisplayCmdAnchor
{
    char unknown_00[0x24];            // +0x00
    DisplayCmdSub Sub;                // +0x24
};
GG_STATIC_ASSERT(offsetof(DisplayCmdAnchor, Sub) == 0x24);
class DisplayCmdAbstract;

class DisplayCmdObjectType
{
public:
    char unknown_0000[0xC8D];         // +0x0000
    bool unknown_C8D;                 // +0x0C8D
};
GG_STATIC_ASSERT(offsetof(DisplayCmdObjectType, unknown_C8D) == 0xC8D);

// The 236-slot vtable shared by every clickable thing the handlers dispatch through (only the slots called are typed).
class DisplayCmdAbstract
{
public:
    virtual void vf_0(); virtual void vf_1(); virtual void vf_2(); virtual void vf_3(); virtual void vf_4();
    virtual void vf_5(); virtual void vf_6(); virtual void vf_7(); virtual void vf_8(); virtual void vf_9();
    virtual void vf_10();
    virtual int WhatAmI();   // 0x2C
    virtual void vf_12(); virtual void vf_13(); virtual void vf_14();
    virtual DisplayCmdHouse* GetOwner();   // 0x3C
    virtual void vf_16(); virtual void vf_17(); virtual void vf_18(); virtual void vf_19(); virtual void vf_20();
    virtual void vf_21(); virtual void vf_22(); virtual void vf_23(); virtual void vf_24(); virtual void vf_25();
    virtual int vf_26(int a, int b);   // 0x68
    virtual void vf_27(); virtual void vf_28(); virtual void vf_29(); virtual void vf_30(); virtual void vf_31();
    virtual void vf_32();
    virtual DisplayCmdObjectType* vf_33();   // 0x84
    virtual DisplayCmdAnchor* vf_34();   // 0x88
    virtual void vf_35(); virtual void vf_36(); virtual void vf_37(); virtual void vf_38(); virtual void vf_39();
    virtual void vf_40(); virtual void vf_41(); virtual void vf_42(); virtual void vf_43(); virtual void vf_44();
    virtual void vf_45(); virtual void vf_46(); virtual void vf_47(); virtual void vf_48(); virtual void vf_49();
    virtual void vf_50(); virtual void vf_51(); virtual void vf_52(); virtual void vf_53(); virtual void vf_54();
    virtual void vf_55(); virtual void vf_56(); virtual void vf_57(); virtual void vf_58(); virtual void vf_59();
    virtual void vf_60(); virtual void vf_61(); virtual void vf_62(); virtual void vf_63(); virtual void vf_64();
    virtual void vf_65(); virtual void vf_66(); virtual void vf_67(); virtual void vf_68(); virtual void vf_69();
    virtual void vf_70(); virtual void vf_71(); virtual void vf_72(); virtual void vf_73(); virtual void vf_74();
    virtual void vf_75(); virtual void vf_76(); virtual void vf_77();
    virtual bool vf_78();   // 0x138
    virtual void vf_79(); virtual void vf_80(); virtual void vf_81(); virtual void vf_82();
    virtual void vf_83();   // 0x14C
    virtual void vf_84();   // 0x150
    virtual void vf_85(); virtual void vf_86(); virtual void vf_87(); virtual void vf_88(); virtual void vf_89();
    virtual void vf_90(); virtual void vf_91(); virtual void vf_92(); virtual void vf_93(); virtual void vf_94();
    virtual void vf_95(); virtual void vf_96(); virtual void vf_97(); virtual void vf_98(); virtual void vf_99();
    virtual void* vf_100(int a, int b);   // 0x190
    virtual void vf_101(); virtual void vf_102(); virtual void vf_103(); virtual void vf_104();
    virtual void vf_105(); virtual void vf_106(); virtual void vf_107(); virtual void vf_108(); virtual void vf_109();
    virtual void vf_110(); virtual void vf_111(); virtual void vf_112(); virtual void vf_113(); virtual void vf_114();
    virtual void vf_115(); virtual void vf_116(); virtual void vf_117(); virtual void vf_118(); virtual void vf_119();
    virtual void vf_120(); virtual void vf_121(); virtual void vf_122(); virtual void vf_123(); virtual void vf_124();
    virtual void vf_125(); virtual void vf_126(); virtual void vf_127(); virtual void vf_128(); virtual void vf_129();
    virtual void vf_130(); virtual void vf_131(); virtual void vf_132(); virtual void vf_133(); virtual void vf_134();
    virtual void vf_135(); virtual void vf_136(); virtual void vf_137(); virtual void vf_138(); virtual void vf_139();
    virtual void vf_140(); virtual void vf_141(); virtual void vf_142(); virtual void vf_143(); virtual void vf_144();
    virtual void vf_145(); virtual void vf_146(); virtual void vf_147(); virtual void vf_148(); virtual void vf_149();
    virtual void vf_150(); virtual void vf_151(); virtual void vf_152(); virtual void vf_153(); virtual void vf_154();
    virtual void vf_155(); virtual void vf_156(); virtual void vf_157(); virtual void vf_158(); virtual void vf_159();
    virtual void vf_160(); virtual void vf_161(); virtual void vf_162(); virtual void vf_163(); virtual void vf_164();
    virtual void vf_165(); virtual void vf_166(); virtual void vf_167(); virtual void vf_168(); virtual void vf_169();
    virtual void vf_170(); virtual void vf_171(); virtual void vf_172(); virtual void vf_173(); virtual void vf_174();
    virtual void vf_175(); virtual void vf_176(); virtual void vf_177(); virtual void vf_178(); virtual void vf_179();
    virtual void vf_180(); virtual void vf_181(); virtual void vf_182(); virtual void vf_183(); virtual void vf_184();
    virtual void vf_185(); virtual void vf_186(); virtual void vf_187(); virtual void vf_188(); virtual void vf_189();
    virtual void vf_190(); virtual void vf_191(); virtual void vf_192(); virtual void vf_193(); virtual void vf_194();
    virtual void vf_195(); virtual void vf_196(); virtual void vf_197(); virtual void vf_198(); virtual void vf_199();
    virtual void vf_200(); virtual void vf_201();
    virtual bool vf_202();   // 0x328
    virtual void vf_203(); virtual void vf_204(); virtual void vf_205(); virtual void vf_206(); virtual void vf_207();
    virtual void vf_208(); virtual void vf_209(); virtual void vf_210(); virtual void vf_211(); virtual void vf_212();
    virtual void vf_213(); virtual void vf_214(); virtual void vf_215(); virtual void vf_216(); virtual void vf_217();
    virtual void vf_218(); virtual void vf_219(); virtual void vf_220(); virtual void vf_221(); virtual void vf_222();
    virtual void vf_223(); virtual void vf_224(); virtual void vf_225(); virtual void vf_226(); virtual void vf_227();
    virtual void vf_228(); virtual void vf_229(); virtual void vf_230(); virtual void vf_231(); virtual void vf_232();
    virtual void vf_233(); virtual void vf_234();
    virtual bool vf_235(DisplayCmdAbstract* target);   // 0x3AC
    // FUNCTION: GAMEMD 0x40DD70 (decl; reloc)
    DisplayCmdTechno* FUN_0040DD70();
};

// An object with the standard flag byte at +0x14 (bit 0 tested); used for the pending placement (DisplayClass+0x11A4),
// the entries of the current-selection list (0xA8ECBC / 0xA8ECC8) and the clicked target.
class DisplayCmdObject : public DisplayCmdAbstract
{
public:
    char unknown_0004[0x10];          // +0x004
    unsigned char Flags;              // +0x014  bit 0
    char unknown_015[0x81 - 0x15];    // +0x015
    bool unknown_81;                  // +0x081
    char unknown_082;                 // +0x082
    bool unknown_83;                  // +0x083
    char unknown_084[0x21C - 0x84];   // +0x084
    DisplayCmdHouse* Owner;           // +0x21C
    char unknown_220[0x660 - 0x220];  // +0x220
    bool unknown_660;                 // +0x660
    char unknown_661[0x6ED - 0x661];  // +0x661
    unsigned char unknown_6ED;        // +0x6ED
    // FUNCTION: GAMEMD 0x4AC2B0 (decl; reloc) -- the per-object callback handed to the tactical view.
    void FUN_004AC2B0();
    // FUNCTION: GAMEMD 0x452670 (decl; reloc)
    bool FUN_00452670(DisplayCmdPendType* type, DisplayCmdHouse* house);
};
GG_STATIC_ASSERT(offsetof(DisplayCmdObject, Flags) == 0x14);
GG_STATIC_ASSERT(offsetof(DisplayCmdObject, unknown_83) == 0x83);
GG_STATIC_ASSERT(offsetof(DisplayCmdObject, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(DisplayCmdObject, unknown_660) == 0x660);
GG_STATIC_ASSERT(offsetof(DisplayCmdObject, unknown_6ED) == 0x6ED);

// Null-safe test of bit 0 at +0x14. The early-return form is what leaves retail's spilled byte
// (`AND AL,1; MOV [ESP+n],AL`) beside the branch; the single-expression `p && (p->Flags & 1)` does not.
inline bool DisplayCmdIsFlagged(DisplayCmdObject* p)
{
    if (p == 0)
        return false;
    return (p->Flags & 1) != 0;
}

// GLOBAL: GAMEMD 0xA8ECBC -- the selection list's item array.
extern DisplayCmdObject** DisplayCmdSelItems_00A8ECBC;
// GLOBAL: GAMEMD 0xA8ECC8 -- the selection list's count.
extern int DisplayCmdSelCount_00A8ECC8;

// The pending placement's type object (DisplayClass+0x11A8); only the slots called are typed.
class DisplayCmdPendType
{
public:
    virtual void vf_0(); virtual void vf_1(); virtual void vf_2(); virtual void vf_3(); virtual void vf_4();
    virtual void vf_5(); virtual void vf_6(); virtual void vf_7(); virtual void vf_8(); virtual void vf_9();
    virtual void vf_10();
    virtual int WhatAmI();   // 0x2C
    virtual void vf_12(); virtual void vf_13(); virtual void vf_14(); virtual void vf_15();
    virtual int vf_16(int flag, CellStruct* at);   // 0x40
    virtual void vf_17(); virtual void vf_18(); virtual void vf_19(); virtual void vf_20(); virtual void vf_21();
    virtual void vf_22(); virtual void vf_23(); virtual void vf_24(); virtual void vf_25(); virtual void vf_26();
    virtual void vf_27(); virtual void vf_28(); virtual void vf_29(); virtual void vf_30(); virtual void vf_31();
    virtual void vf_32(); virtual void vf_33(); virtual void vf_34(); virtual void vf_35();
    virtual DisplayCmdAnchor* vf_36(int arg);   // 0x90
};

// The 3-byte colour the palette code unpacks (ColorStruct, ui_display_chain.h).

// GLOBALs: the surface pixel-format shifts (Drawing::RedShiftLeft ... GreenShiftRight, see match/renderer/drawing.cpp).
// GLOBAL: GAMEMD 0x8A0DD0
extern int DisplayCmdRedShiftLeft_008A0DD0;
// GLOBAL: GAMEMD 0x8A0DD4
extern int DisplayCmdRedShiftRight_008A0DD4;
// GLOBAL: GAMEMD 0x8A0DD8
extern int DisplayCmdBlueShiftLeft_008A0DD8;
// GLOBAL: GAMEMD 0x8A0DDC
extern int DisplayCmdBlueShiftRight_008A0DDC;
// GLOBAL: GAMEMD 0x8A0DE0
extern int DisplayCmdGreenShiftLeft_008A0DE0;
// GLOBAL: GAMEMD 0x8A0DE4
extern int DisplayCmdGreenShiftRight_008A0DE4;

// Drawing::RGB_To_Int expanded inline (the retail body ORs green, blue, red in that order).
inline unsigned short DisplayCmdPack(unsigned char r, unsigned char g, unsigned char b)
{
    return (unsigned short)((g >> DisplayCmdGreenShiftRight_008A0DE4 << DisplayCmdGreenShiftLeft_008A0DE0)
                          | (b >> DisplayCmdBlueShiftRight_008A0DDC << DisplayCmdBlueShiftLeft_008A0DD8)
                          | (r >> DisplayCmdRedShiftRight_008A0DD4 << DisplayCmdRedShiftLeft_008A0DD0));
}

// GLOBAL: GAMEMD 0x885180 -- the 256-entry highlight colour ring (3 bytes each).
extern ColorStruct DisplayCmdRing_00885180[256];

// A world coordinate triple the waypoint cursor writes (X, Y in leptons, Z from the map).
struct DisplayCmdVec3
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
    void Set(int x, int y, int z) { X = x; Y = y; Z = z; }
};
GG_STATIC_ASSERT(sizeof(DisplayCmdVec3) == 0xC);

// The object that owns the palette the highlight animation rewrites.
struct DisplayCmdPalOwner
{
    char unknown_000[0x174];          // +0x000
    unsigned short* Palette;          // +0x174
};
GG_STATIC_ASSERT(offsetof(DisplayCmdPalOwner, Palette) == 0x174);
// GLOBAL: GAMEMD 0x87F6C8
extern DisplayCmdPalOwner* DisplayCmdPalOwner_0087F6C8;

// HouseClass as the click handler sees it (pointer global 0xA83D4C).
struct DisplayCmdHouse
{
    char unknown_000[0x30];           // +0x000
    int  unknown_30;                  // +0x030  index passed to the event constructors
    char unknown_034[0x20C - 0x34];   // +0x034
    int  unknown_20C;                 // +0x20C  highlight colour index (-1 = none)
    // FUNCTION: GAMEMD 0x5023B0 (decl; reloc)
    int GetPlanningWaypointAt_005023B0(CellStruct* cell);
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc)
    bool FUN_0050B6F0();
    // FUNCTION: GAMEMD 0x502460 (decl; reloc)
    void GetPlanningWaypointProperties_00502460(int waypoint, int* colourIndex, ColorStruct* colour);
    // FUNCTION: GAMEMD 0x4FB840 (decl; reloc) -- RET 8.
    void FUN_004FB840(void* target, DisplayCmdObject* object);
};
GG_STATIC_ASSERT(offsetof(DisplayCmdHouse, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(DisplayCmdHouse, unknown_20C) == 0x20C);
// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern DisplayCmdHouse* DisplayCmdPlayer_00A83D4C;

// CellClass: only the flags dword at +0x140 is read.
struct DisplayCmdCellObj : public DisplayCmdAbstract
{
    char unknown_004[0x11B - 4];      // +0x004
    signed char unknown_11B;          // +0x11B
    char unknown_11C[0x140 - 0x11C];  // +0x11C
    unsigned int Flags140;            // +0x140
};
GG_STATIC_ASSERT(offsetof(DisplayCmdCellObj, unknown_11B) == 0x11B);
GG_STATIC_ASSERT(offsetof(DisplayCmdCellObj, Flags140) == 0x140);

// The map instance (static object at 0x87F7E8; used as an immediate `this`).
struct DisplayCmdMap
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    DisplayCmdCellObj* GetCellAt_005657A0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x578460 (decl; reloc)
    bool IsWithinUsableArea_00578460(const CellStruct* cell, int flag);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc)
    int GetZPos_00578080(const DisplayCmdVec3* where);
    // FUNCTION: GAMEMD 0x4A8D50 (decl; reloc)
    void FUN_004A8D50(DisplayCmdAnchor* anchor);
    // FUNCTION: GAMEMD 0x4A8BF0 (decl; reloc)
    void SetActiveFoundation_004A8BF0(void* foundation);
    // FUNCTION: GAMEMD 0x4AC960 (decl; reloc)
    void SetBeaconMode_004AC960(int mode);
};
// GLOBAL: GAMEMD 0x87F7E8
extern DisplayCmdMap DisplayCmdMap_0087F7E8;
// GLOBAL: GAMEMD 0x8A03F8 -- the "no cell" sentinel pair.
extern CellStruct DisplayCmdNoCell_008A03F8;
// GLOBAL: GAMEMD 0x8A0730
extern int DisplayCmdZBias_008A0730;
// GLOBAL: GAMEMD 0xA8ED6B (byte)
extern bool DisplayCmdFlag_00A8ED6B;

// The object class the click handler resolves a clicked thing to.
class DisplayCmdTechnoType
{
public:
    char unknown_0000[0x1701];        // +0x0000
    bool unknown_1701;                // +0x1701
};
GG_STATIC_ASSERT(offsetof(DisplayCmdTechnoType, unknown_1701) == 0x1701);

class DisplayCmdTechno
{
public:
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02(); virtual void vf_03();
    virtual void vf_04(); virtual void vf_05(); virtual void vf_06(); virtual void vf_07();
    virtual void vf_08(); virtual void vf_09(); virtual void vf_10();
    virtual int WhatAmI();            // 0x2C
    char unknown_0004[0x431 - 4];     // +0x004
    bool unknown_431;                 // +0x431
    char unknown_432[0x520 - 0x432];  // +0x432
    DisplayCmdTechnoType* Type;       // +0x520
};
GG_STATIC_ASSERT(offsetof(DisplayCmdTechno, unknown_431) == 0x431);
GG_STATIC_ASSERT(offsetof(DisplayCmdTechno, Type) == 0x520);


// DisplayClass (slots 46, 48, 49, the members +0x1178..+0x11D0 and the mode setters) is declared in
// ui_display_chain.h.

// GLOBAL: GAMEMD 0x884D44
extern bool DisplayCmdFlag_00884D44;
// FUNCTION: GAMEMD 0x48DC90 (decl; reloc)
void __cdecl UnselectAll_0048DC90();

// FUNCTION: GAMEMD 0x70F0B0 (decl; reloc) -- __fastcall: action in ECX, cell in EDX, one stacked argument.
int FUN_0070F0B0(int action, CellStruct* cell, DisplayCmdAbstract* target);
// FUNCTION: GAMEMD 0x731CC0 (decl; reloc) -- returns the constant 0x16.
int __cdecl FUN_00731CC0();
// FUNCTION: GAMEMD 0x731CB0 (decl; reloc) -- returns the constant 0x47.
int __cdecl FUN_00731CB0();

// ---- 0x4AB9B0 (vf_48) support -----------------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x452670 (decl; reloc) lives on DisplayCmdObject.
// The queued network/replay event: 0x6F bytes (copied with REP MOVSD x27 + MOVSW + MOVSB), built by one of four
// constructors that each return the object (EAX = this).
struct DisplayCmdTarget
{
    int Id;                  // +0x00
    unsigned char Kind;      // +0x04
    // FUNCTION: GAMEMD 0x6E6AB0 (decl; reloc)
    DisplayCmdTarget(DisplayCmdObject* object);
    DisplayCmdTarget(const DisplayCmdTarget& other) { Id = other.Id; Kind = other.Kind; }
};
GG_STATIC_ASSERT(sizeof(DisplayCmdTarget) == 8);

struct DisplayCmdEvent
{
    char data[0x6F];
    // FUNCTION: GAMEMD 0x4C6AE0 (decl; reloc)
    DisplayCmdEvent(int house, int type, int rtti, int id);
    // FUNCTION: GAMEMD 0x4C65E0 (decl; reloc)
    DisplayCmdEvent(int house, int mode, DisplayCmdTarget target);
    // FUNCTION: GAMEMD 0x4C6650 (decl; reloc)
    DisplayCmdEvent(int house, int type, const CellStruct& cell);
    // FUNCTION: GAMEMD 0x4C6B60 (decl; reloc)
    DisplayCmdEvent(int house, int type, int arg, const CellStruct& cell);
};
GG_STATIC_ASSERT(sizeof(DisplayCmdEvent) == 0x6F);

// The outgoing event queue: a count, the ring head, 128 events of 0x6F bytes and the 128 time stamps that follow them
// (0xA802D4 + 128 * 0x6F == 0xA83A54).
struct DisplayCmdOutQueue
{
    int Count;                        // +0x0000  0xA802C8
    int unknown_04;                   // +0x0004
    int Head;                         // +0x0008  0xA802D0
    DisplayCmdEvent List[128];        // +0x000C  0xA802D4
    unsigned long Time[128];          // +0x378C  0xA83A54
};
GG_STATIC_ASSERT(offsetof(DisplayCmdOutQueue, Head) == 0x8);
GG_STATIC_ASSERT(offsetof(DisplayCmdOutQueue, List) == 0xC);
GG_STATIC_ASSERT(offsetof(DisplayCmdOutQueue, Time) == 0xA83A54 - 0xA802C8);
// GLOBAL: GAMEMD 0xA802C8
extern DisplayCmdOutQueue DisplayCmdOut_00A802C8;
// LIBRARY: winmm timeGetTime (import slot 0x7E1530)
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// The event-queue append expanded inline: copy the event into the ring, stamp it, advance.
inline void DisplayCmdQueueEvent(const DisplayCmdEvent& event)
{
    if (DisplayCmdOut_00A802C8.Count < 128)
    {
        DisplayCmdOut_00A802C8.List[DisplayCmdOut_00A802C8.Head] = event;
        DisplayCmdOut_00A802C8.Time[DisplayCmdOut_00A802C8.Head] = timeGetTime();
        DisplayCmdOut_00A802C8.Head = (DisplayCmdOut_00A802C8.Head + 1) & 127;
        DisplayCmdOut_00A802C8.Count++;
    }
}

struct DisplayCmdTactical
{
    char unknown_000[0xD7D];          // +0x000
    bool unknown_D7D;                 // +0xD7D
    // FUNCTION: GAMEMD 0x6DA080 (decl; reloc)
    int FUN_006DA080();
    // FUNCTION: GAMEMD 0x6D9FF0 (decl; reloc)
    void FUN_006D9FF0(void (DisplayCmdObject::*callback)());
    // FUNCTION: GAMEMD 0x6D6070 (decl; reloc) -- RET 4.
    void FUN_006D6070(const DisplayCmdVec3* where);
    // FUNCTION: GAMEMD 0x6D6190 (decl; reloc) -- fills and returns the 8-byte result; RET 4.
    Point2D* FUN_006D6190(Point2D* out);
    // FUNCTION: GAMEMD 0x6D6590 (decl; reloc) -- fills and returns the cell; RET 8.
    CellStruct* FUN_006D6590(CellStruct* out, const Point2D* where);
};
GG_STATIC_ASSERT(offsetof(DisplayCmdTactical, unknown_D7D) == 0xD7D);
// GLOBAL: GAMEMD 0x887324 -- the tactical view.
extern DisplayCmdTactical* DisplayCmdTactical_00887324;

struct DisplayCmdKeyboard
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x54F5C0 (decl; reloc)
    bool FUN_0054F5C0(int key);
};
// GLOBAL: GAMEMD 0x87F770
extern DisplayCmdKeyboard* DisplayCmdKeyboard_0087F770;

// An object the cursor-state tables return (field +0x98 feeds an event).
struct DisplayCmdActionInfo
{
    char unknown_00[0x98];            // +0x00
    int  unknown_98;                  // +0x98
};
GG_STATIC_ASSERT(offsetof(DisplayCmdActionInfo, unknown_98) == 0x98);

// A cell-sized thing at 0x89C3B0 that takes world coordinates by value.
struct DisplayCmdMarker
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x430F70 (decl; reloc)
    void FUN_00430F70(DisplayCmdVec3 where);
    // FUNCTION: GAMEMD 0x430BA0 (decl; reloc)
    void FUN_00430BA0(int house, DisplayCmdVec3 where, int arg);
};
// GLOBAL: GAMEMD 0x89C3B0
extern DisplayCmdMarker DisplayCmdMarker_0089C3B0;

// GLOBAL: GAMEMD 0xA8ED5C (byte)
extern bool DisplayCmdFlag_00A8ED5C;
// GLOBAL: GAMEMD 0xA8E9A0 (byte)
extern bool DisplayCmdFlag_00A8E9A0;
// GLOBAL: GAMEMD 0xA8ED9D (byte)
extern bool DisplayCmdFlag_00A8ED9D;
// GLOBAL: GAMEMD 0xA8B538
extern int DisplayCmdValue_00A8B538;
// GLOBAL: GAMEMD 0x8A0740
extern int DisplayCmdScale_008A0740;
// GLOBAL: GAMEMD 0x88098C
extern int DisplayCmdValue_0088098C;
// GLOBAL: GAMEMD 0x880990
extern int DisplayCmdValue_00880990;
// GLOBAL: GAMEMD 0x880994
extern int DisplayCmdValue_00880994;

// FUNCTION: GAMEMD 0x752700 (decl; reloc) -- VoxClass::Play, __fastcall: name in ECX, -1 in EDX, -1 pushed.
void FUN_00752700(const char* name, int a, int b);
// GLOBAL: GAMEMD 0x82012C -- the cue name string ("EVA_CannotDeployHere").
extern const char DisplayCmdCue_0082012C[];
// FUNCTION: GAMEMD 0x731CF0 (decl; reloc)
void __cdecl FUN_00731CF0();
// FUNCTION: GAMEMD 0x70D150 (decl; reloc)
void __cdecl FUN_0070D150();
// FUNCTION: GAMEMD 0x639040 (decl; reloc)
bool __cdecl FUN_00639040();
// FUNCTION: GAMEMD 0x639130 (decl; reloc)
bool __cdecl FUN_00639130();
// FUNCTION: GAMEMD 0x732D00 (decl; reloc)
bool __cdecl FUN_00732D00();
// FUNCTION: GAMEMD 0x734270 (decl; reloc)
void FUN_00734270(DisplayCmdObject* building);
// FUNCTION: GAMEMD 0x6CEEB0 (decl; reloc)
DisplayCmdActionInfo* FUN_006CEEB0(int action);

// RTTI type descriptors (addresses only).
// GLOBAL: GAMEMD 0x817F78 -- .?AVObjectTypeClass@@
extern char TypeDesc_ObjectTypeClass_00817F78[];
// GLOBAL: GAMEMD 0x817F98 -- .?AVTechnoTypeClass@@
extern char TypeDesc_TechnoTypeClass_00817F98[];
// LIBRARY: GAMEMD 0x7CAAE4 (LIBRARY) -- __RTDynamicCast
extern "C" void* __cdecl FUN_007CAAE4(void* object, long vfDelta, void* srcType, void* dstType, int isReference);

// The technotype fields the placement test reads.
struct DisplayCmdTechnoTypeView
{
    char unknown_000[0xCCE];          // +0x000
    bool unknown_CCE;                 // +0xCCE
};
GG_STATIC_ASSERT(offsetof(DisplayCmdTechnoTypeView, unknown_CCE) == 0xCCE);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_COMMAND_H
