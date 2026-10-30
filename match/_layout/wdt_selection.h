// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WorldDominationTour::Selection (RTTI .?AVSelection@WorldDominationTour@@, vtable 0x7F72B4, base MSEngine): the
//   World Domination Tour screen, built on the stack by the factories 0x76ECD0 / 0x76ED10 through its constructor
//   0x76C290 (engine at +0x00, rc_ptr members from +0x48). That constructor calls the voice-animation factory 0x771800
//   with itself as the owner, so it is the object WorldDominationTour::Voices::Anim keeps at +0x1C. Only the members
//   the voice animation's slots and the helper 0x771620 touch are named.
#ifndef GG_MATCH_LAYOUT_WDT_SELECTION_H
#define GG_MATCH_LAYOUT_WDT_SELECTION_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ms_engine.h"
#include "../core/string_class.h"
#include "../core/wide_string_class.h"
#include "../network/wdt_map.h"
#include "../network/world_domination_tour.h"

class MSSfxEntry;
class INIClass;
class MSBitPrintAnim;

namespace WorldDominationTour {

// The polymorphic member at +0x3C0 (a queue of voice names); only its slot 3 is run.
struct SelectionQueue
{
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
};


// The 0x354-byte block at +0x58 (built by 0x770270). Only the INI reader 0x770550 is called from this unit.
struct SelectionVoices
{
    // FUNCTION: GAMEMD 0x770550 (decl; reloc) -- RET 8.
    void FUN_00770550(INIClass* ini, const Wstring& section);
    char unknown_00[0x354];
};
GG_STATIC_ASSERT(sizeof(SelectionVoices) == 0x354);

// VTABLE: GAMEMD 0x7F72B4
class Selection : public MSEngine
{
public:
    // FUNCTION: GAMEMD 0x76C290 (decl; reloc) -- RET 8.
    Selection(const rc_ptr<Campaign>& campaign, unsigned int seed);
    // FUNCTION: GAMEMD 0x76C6E0 (decl; reloc) -- the destructor body; the deleting wrapper is 0x76EFE0.
    ~Selection();

    // FUNCTION: GAMEMD 0x771620 (decl; reloc)
    void FUN_00771620();

    // FUNCTION: GAMEMD 0x76C970 (decl; reloc) -- read the four score thresholds, RET 8.
    void FUN_0076C970(INIClass* ini, const Wstring& section);
    // FUNCTION: GAMEMD 0x76D470 (decl; reloc) -- RET 4.
    void FUN_0076D470(const WDTPoint* point);
    // FUNCTION: GAMEMD 0x76DAD0 (decl; reloc) -- RET 4.
    bool FUN_0076DAD0(const rc_ptr<Territory>& territory);
    // FUNCTION: GAMEMD 0x76DFD0 (decl; reloc)
    void FUN_0076DFD0();
    // FUNCTION: GAMEMD 0x76E090 (decl; reloc)
    void FUN_0076E090();
    // FUNCTION: GAMEMD 0x76E750 (decl; reloc) -- RET 4.
    void FUN_0076E750(unsigned int arg);
    // FUNCTION: GAMEMD 0x76E9D0 (decl; reloc)
    void FUN_0076E9D0();
    // FUNCTION: GAMEMD 0x76EAF0 (decl; reloc) -- RET 4.
    void FUN_0076EAF0(const Obj_007B66D0& text);
    // FUNCTION: GAMEMD 0x76EBE0 (decl; reloc) -- RET 4.
    void FUN_0076EBE0(const Wstring& name);

    rc_ptr<Campaign> CampaignRef;   // +0x48 (pointer +0x4C)
    char           unknown_050[8];
    SelectionVoices Voices;        // +0x58
    MSTimer        Stopwatch;      // +0x3AC
    char           unknown_3B8[8];
    SelectionQueue Queue;          // +0x3C0
    char           unknown_3C4[12];
    int            Count;          // +0x3D0
    char           unknown_3D4[0x434 - 0x3D4];
    int            WinningThreshold;      // +0x434
    int            LosingThreshold;       // +0x438
    int            MegaWinningThreshold;  // +0x43C
    int            MegaLosingThreshold;   // +0x440
    bool           unknown_444;           // +0x444
    char           unknown_445[3];
    int            unknown_448;           // +0x448
    int            unknown_44C;           // +0x44C
    int            unknown_450;           // +0x450
    int            unknown_454;           // +0x454
    rc_ptr<Map>    MapRef;                // +0x458 (pointer +0x45C)
    int            unknown_460;           // +0x460
    rc_ptr<Territory> TerritoryRef;       // +0x464 (pointer +0x468)
    char           unknown_46C[0x47C - 0x46C];
    MSBitPrintAnim* unknown_47C;          // +0x47C
    MSBitPrintAnim* unknown_480;          // +0x480
    char           unknown_484[0x494 - 0x484];
    DynamicVectorClass<MSSfxEntry*> Sfxs; // +0x494
    int            unknown_4AC;           // +0x4AC
};
GG_STATIC_ASSERT(offsetof(Selection, CampaignRef) == 0x48 && offsetof(Selection, Voices) == 0x58 && offsetof(Selection, Stopwatch) == 0x3AC
              && offsetof(Selection, Queue) == 0x3C0 && offsetof(Selection, Count) == 0x3D0
              && offsetof(Selection, WinningThreshold) == 0x434 && offsetof(Selection, unknown_444) == 0x444
              && offsetof(Selection, MapRef) == 0x458 && offsetof(Selection, unknown_460) == 0x460
              && offsetof(Selection, unknown_47C) == 0x47C && offsetof(Selection, Sfxs) == 0x494
              && offsetof(Selection, unknown_4AC) == 0x4AC && sizeof(Selection) == 0x4B0);

}  // namespace WorldDominationTour

#endif  // GG_MATCH_LAYOUT_WDT_SELECTION_H
