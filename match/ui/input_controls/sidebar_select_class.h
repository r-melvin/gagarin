// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Entry, span, ABI and field facts read from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x6AAD00, 0x6AB990, 0x6AB9E0 and
//   0x6ABA40. RTTI: SidebarClass::StripClass::SelectClass (type 0x83F8F8, COL
//   0x809568, vtable 0x7F2FCC) derives ControlClass -> GadgetClass -> LinkClass;
//   SidebarClass::SBGadgetClass (type 0x83F8C8, COL 0x809510, vtable 0x7F2F44)
//   derives GadgetClass -> LinkClass. ControlClass (match/ui/control_class.h)
//   is used unchanged: its sizeof 0x2C and 34-slot table agree with SelectClass
//   (34 slots, first own member at +0x2C).
#ifndef GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_SELECT_CLASS_H
#define GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_SELECT_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../control_class.h"
#include "sidebar_class_layout.h"

// The tooltip manager singleton (ToolTipManager_Instance, GLOBAL 0x887368) is declared in sidebar_class_layout.h.


// GLOBAL: GAMEMD 0x884B8F -- "sidebar needs a full redraw" byte.
extern unsigned char SidebarNeedsRedraw_00884B8F;
// GLOBAL: GAMEMD 0xB0B518 -- byte set when a select gadget changes hover state.
extern unsigned char SelectHoverChanged_00B0B518;

// One 0x34-byte build entry of the strip (the "cameo": what a select gadget stands for).
struct SelectBuildEntry
{
    int Item;                                   // +0x00 index within the type list
    int Type;                                   // +0x04 abstract type id (0x1F: super weapon)
    int Category;                               // +0x08
    SelectFactory* Factory;                     // +0x0C the factory building it, if any
    int State;                                  // +0x10 (1 queued, 2 on hold)
    int Progress;                               // +0x14
    char _pad018[0x1C - 0x18];
    int TimerStart;                             // +0x1C
    int TimerAux;                               // +0x20
    int TimerDelay;                             // +0x24
    int Frames;                                 // +0x28
    char _pad02C[0x34 - 0x2C];
};
GG_STATIC_ASSERT(sizeof(SelectBuildEntry) == 0x34);
GG_STATIC_ASSERT(offsetof(SelectBuildEntry, Factory) == 0x0C);
GG_STATIC_ASSERT(offsetof(SelectBuildEntry, State) == 0x10);
GG_STATIC_ASSERT(offsetof(SelectBuildEntry, Progress) == 0x14);
GG_STATIC_ASSERT(offsetof(SelectBuildEntry, TimerStart) == 0x1C);
GG_STATIC_ASSERT(offsetof(SelectBuildEntry, Frames) == 0x28);

// The strip that owns a select gadget (SidebarClass::StripClass, 0xF94 bytes).
struct SelectOwnerStrip
{
    char _pad000[0x38];
    int RowBase;                                // +0x38
    unsigned char At_3C;                        // +0x3C
    char _pad03D[0x44 - 0x3D];
    int TopRowIndex;                            // +0x44
    char _pad048[0x54 - 0x48];
    int CameoCount;                             // +0x54
    SelectBuildEntry Entries[75];               // +0x58
};
GG_STATIC_ASSERT(offsetof(SelectOwnerStrip, RowBase) == 0x38);
GG_STATIC_ASSERT(offsetof(SelectOwnerStrip, At_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(SelectOwnerStrip, TopRowIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(SelectOwnerStrip, CameoCount) == 0x54);
GG_STATIC_ASSERT(offsetof(SelectOwnerStrip, Entries) == 0x58);

// FactoryClass (match/economy/factory_class_methods): only the calls used here.
struct SelectTechno;
struct SelectFactory
{
    char _pad000[0x38];
    SelectTechno* Object;                       // +0x38 (tested)
    char _pad03C[0x50 - 0x3C];
    int At_50;                                  // +0x50
    char _pad054[0x58 - 0x54];
    SelectTechno* At_58;                        // +0x58
    char _pad05C[0x70 - 0x5C];
    unsigned char At_70;                        // +0x70
    // FUNCTION: GAMEMD 0x4CA120 (decl; reloc) -- FactoryClass::GetProgress.
    int GetProgress() const;
    // FUNCTION: GAMEMD 0x4CA130 (decl; reloc) -- FactoryClass::IsDone.
    bool IsDone() const;
    // FUNCTION: GAMEMD 0x4CA160 (decl; reloc) -- the object being produced.
    SelectTechno* FUN_004CA160();
    // FUNCTION: GAMEMD 0x4CA170 (decl; reloc) -- FactoryClass::GetOriginalBalance.
    int GetOriginalBalance() const;
    // FUNCTION: GAMEMD 0x4CA6B0 (decl; reloc) -- FactoryClass::IsQueued; RET 4.
    bool IsQueued(SelectTechnoType* type) const;
    // FUNCTION: GAMEMD 0x4C9FB0 (decl; reloc) -- FactoryClass::GetBuildTimeFrames.
    int GetBuildTimeFrames() const;
};
GG_STATIC_ASSERT(offsetof(SelectFactory, Object) == 0x38);
GG_STATIC_ASSERT(offsetof(SelectFactory, At_50) == 0x50);
GG_STATIC_ASSERT(offsetof(SelectFactory, At_58) == 0x58);
GG_STATIC_ASSERT(offsetof(SelectFactory, At_70) == 0x70);

// A TechnoClass being produced (vtable slots +0x2C WhatAmI, +0x38, +0x190).
struct SelectTechnoVtbl;
struct SelectTechno
{
    SelectTechnoVtbl* Vtbl;
};
typedef int (SelectTechno::*SelectTechnoFn2C)();
typedef int (SelectTechno::*SelectTechnoFn38)();
typedef SelectTechno* (SelectTechno::*SelectTechnoFn190)(int a, int b);
struct SelectTechnoVtbl
{
    char _pad000[0x2C];
    SelectTechnoFn2C At_2C;                     // +0x2C WhatAmI
    char _pad030[0x38 - 0x30];
    SelectTechnoFn38 At_38;                     // +0x38
    char _pad03C[0x190 - 0x3C];
    SelectTechnoFn190 At_190;                   // +0x190
};
GG_STATIC_ASSERT(offsetof(SelectTechnoVtbl, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(SelectTechnoVtbl, At_38) == 0x38);
GG_STATIC_ASSERT(offsetof(SelectTechnoVtbl, At_190) == 0x190);

// A TechnoTypeClass (vtable slots +0x2C, +0x84, +0x88, +0x94).
struct SelectTechnoTypeVtbl;
struct SelectTechnoType
{
    SelectTechnoTypeVtbl* Vtbl;
    char _pad004[0xCCE - 4];
    unsigned char At_CCE;                       // +0xCCE
    char _padCCF[0x1571 - 0xCCF];
    unsigned char At_1571;                      // +0x1571
};
typedef int (SelectTechnoType::*SelectTypeFn2C)();
typedef int (SelectTechnoType::*SelectTypeFn84)(SidebarHouse* house);
typedef int (SelectTechnoType::*SelectTypeFn88)();
typedef int (SelectTechnoType::*SelectTypeFn94)(int a, int b, int c, SidebarHouse* house);
struct SelectTechnoTypeVtbl
{
    char _pad000[0x2C];
    SelectTypeFn2C At_2C;                       // +0x2C WhatAmI
    char _pad030[0x84 - 0x30];
    SelectTypeFn84 At_84;                       // +0x84
    SelectTypeFn88 At_88;                       // +0x88
    char _pad08C[0x94 - 0x8C];
    SelectTypeFn94 At_94;                       // +0x94
};
GG_STATIC_ASSERT(offsetof(SelectTechnoType, At_CCE) == 0xCCE);
GG_STATIC_ASSERT(offsetof(SelectTechnoType, At_1571) == 0x1571);
GG_STATIC_ASSERT(offsetof(SelectTechnoTypeVtbl, At_84) == 0x84);
GG_STATIC_ASSERT(offsetof(SelectTechnoTypeVtbl, At_88) == 0x88);
GG_STATIC_ASSERT(offsetof(SelectTechnoTypeVtbl, At_94) == 0x94);

// A super weapon instance (reached through the player's +0x258 array) and its type.
struct SelectSuperType
{
    char _pad000[0x98];
    int At_98;                                  // +0x98
    char _pad09C[0xBC - 0x9C];
    int At_BC;                                  // +0xBC
};
GG_STATIC_ASSERT(offsetof(SelectSuperType, At_98) == 0x98);
GG_STATIC_ASSERT(offsetof(SelectSuperType, At_BC) == 0xBC);
struct SelectSuper
{
    char _pad000[0x28];
    SelectSuperType* Type;                      // +0x28
    // FUNCTION: GAMEMD 0x6CC360 (decl; reloc) -- SuperClass::CanFire.
    bool CanFire() const;
    // FUNCTION: GAMEMD 0x6CC070 (decl; reloc) -- empty function.
    void FUN_006CC070();
};
GG_STATIC_ASSERT(offsetof(SelectSuper, Type) == 0x28);

// An EventClass local (0x6F bytes); only the constructors used here are declared.
struct SelectEvent
{
    unsigned char _data[0x6F];
    // FUNCTION: GAMEMD 0x4C6970 (decl; reloc) -- EventClass::EventClass(PLACE a); RET 0x14.
    SelectEvent* Construct(int house, int type, int rtti, int index, int flag);
    // FUNCTION: GAMEMD 0x4C6AE0 (decl; reloc) -- EventClass::EventClass(PLACE d); RET 0x18.
    SelectEvent* ConstructAt(int house, int type, int rtti, int index, int flag, const void* cell);
    // FUNCTION: GAMEMD 0x4C6B60 (decl; reloc) -- EventClass::EventClass(SPECIAL_PLACE); RET 0x10.
    SelectEvent* ConstructSpecial(int house, int type, int index, const void* cell);
    void Queue();
};
GG_STATIC_ASSERT(sizeof(SelectEvent) == 0x6F);

// VTABLE: GAMEMD 0x7F2FCC
struct SidebarSelectClass : public ControlClass
{
    // FUNCTION: GAMEMD 0x6AACB0 -- default constructor (id 0, 0x3C x 0x30 box, flags 0x19).
    SidebarSelectClass();
    // FUNCTION: GAMEMD 0x6AACE0 -- store both words at +0x2C and +0x30; RET 8.
    void FUN_006AACE0(SelectOwnerStrip* owner, int value);

    SelectOwnerStrip* Owner;                    // +0x2C
    int unknown_30;                             // +0x30
    unsigned char Hover;                        // +0x34

    // FUNCTION: GAMEMD 0x6AB990 -- slot 28 (OnMouseEnter; retail vtable 0x7F2FC8 field 29).
    virtual void OnMouseEnter();
    // FUNCTION: GAMEMD 0x6AB9E0 -- slot 29 (OnMouseLeave; retail vtable 0x7F2FC8 field 30).
    virtual void OnMouseLeave();
    // FUNCTION: GAMEMD 0x6AAD00 -- slot 31 (Action).
    virtual int Action(unsigned flags, unsigned* key, int modifier);
};
GG_STATIC_ASSERT(offsetof(SidebarSelectClass, Owner) == 0x2C);
GG_STATIC_ASSERT(offsetof(SidebarSelectClass, Hover) == 0x34);

// VTABLE: GAMEMD 0x7F2F44
struct SidebarSBGadgetClass : public GadgetClass
{
    SidebarSBGadgetClass(int x, int y, int width, int height, unsigned int flags,
                         char sticky)
        : GadgetClass(x, y, width, height, flags, sticky)
    {
    }
    // FUNCTION: GAMEMD 0x6ABA40 -- slot 31 (Action).
    virtual int Action(unsigned flags, unsigned* key, int modifier);
};

#endif  // GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_SELECT_CLASS_H
