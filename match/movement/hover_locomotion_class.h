// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001, confirmed from entry-origin instructions, RTTI, and pinned PE data. | YRpp-cross-check | behaviour-confirmed-name
//   Layout, tables and constructor read from the retail gamemd.exe v1.001:
//   RTTI .?AVHoverLocomotionClass@@ (TD 0x8254B8; COL 0x803288 for the primary
//   table 0x7EADC8 and COL 0x803228 for the ILocomotion table 0x7EACFC),
//   constructor 0x513C20 (allocation `push 0x78; call 0x7C8E17` at 0x6C433C),
//   Load 0x5170B0 and the member accesses of the entries in
//   hover_locomotion_class.cpp. Member names are behavioural (the binary gives
//   no names); anything not proven is named by its offset.
//   YRpp was consulted for familiar locomotion names only; no declarations or
//   layouts were copied. Each retained ABI/layout fact is independently checked
//   against the retail instructions or RTTI.
//
// HoverLocomotionClass: the hovercraft locomotor. No IPiggyback base.
//
//   +0x00 vptr (IPersistStream side, 0x7EADC8)   +0x04 vptr (ILocomotion side, 0x7EACFC)
//   +0x08 Owner  +0x0C LinkedTo  +0x10 Powered  +0x11 Dirty  +0x14 RefCount (LocomotionClass)
//   +0x18 Destination (3 dwords)    +0x24 HeadTo (3 dwords)
//   +0x30 Facing (FacingClass, 0x18)
//   +0x48 Speed (double)  +0x50 SpeedFactor (double)  +0x58 / +0x60 doubles (ctor: 1.0 / 0.0)
//   +0x68 IsRocking (byte)  +0x6C RockAmount (int)  +0x70 Blocked (byte)   sizeof 0x78
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_HOVER_LOCOMOTION_CLASS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_HOVER_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_base.h"
#include "hover_locomotion_support.h"

// ---------------------------------------------------------------------------
// Hover-specific values and views are scoped in hover_locomotion_support.h;
// LocoCoord and Matrix3D are the canonical shared value declarations.
// ---------------------------------------------------------------------------

// A world coordinate with the retail helpers that take it as `this`.
struct HoverCoordView : public LocoCoord
{
    HoverCoordView() {}
    HoverCoordView(const LocoCoord& coord) : LocoCoord(coord) {}
    HoverCoordView& operator=(const LocoCoord& coord) { LocoCoord::operator=(coord); return *this; }

    // FUNCTION: GAMEMD 0x517310 (decl; reloc) - compares the X and Y components
    bool Fun_00517310(const LocoCoord* other);
    // FUNCTION: GAMEMD 0x413A30 (decl; reloc) - cell containing this coordinate, through a hidden pointer
    HoverCellCoord* Fun_00413A30(HoverCellCoord* out);
};
GG_STATIC_ASSERT(sizeof(HoverCoordView) == sizeof(LocoCoord));

// GLOBAL: GAMEMD 0x87F7E8 is declared once as LocoMap in loco_foot.h; Hover
// accesses that storage through the narrow HoverMapView accessor.
// GLOBAL: GAMEMD 0x8871E0 - rules pointer read by Hover Process
extern HoverRulesView* DAT_008871E0;
// GLOBAL: GAMEMD 0xA8B230 - scenario pointer used by Hover PowerOff/Shove
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0xA8ED84 - frame counter read by Hover Process
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0xA8F180 - three-dword coordinate value read by Hover bodies
extern LocoCoord DAT_00A8F180;
// GLOBAL: GAMEMD 0xA8F160 - two-short cell-coordinate value read by Hover Process
extern HoverCellCoord DAT_00A8F160;
// GLOBAL: GAMEMD 0xA8F1B4 - height adjustment read by Hover Process/MoveTo/Push
extern int DAT_00A8F1B4;
// GLOBAL: GAMEMD 0xA8F1C0 - height threshold read by Hover Process/Push/IsMovingHere
extern int DAT_00A8F1C0;
// DAT_0089F688 is the shared step table from core/cell_step_tables.h.

// Hover calls Foot slot +0x48 with a coordinate out pointer and receives that
// pointer back. This address-local member-pointer layout retains the observed dispatch.
struct HoverCoordSlotVtbl;
struct HoverCoordSlotView
{
    HoverCoordSlotVtbl* Vtbl;   // +0x000
};
typedef HoverCoordView* (HoverCoordSlotView::*HoverCoordSlotFn)(HoverCoordView*);
struct HoverCoordSlotVtbl
{
    char             unknown_000[0x48];
    HoverCoordSlotFn At_048;    // +0x048
};
GG_STATIC_ASSERT(offsetof(HoverCoordSlotView, Vtbl) == 0x00);
GG_STATIC_ASSERT(sizeof(HoverCoordSlotView) == 0x04);
GG_STATIC_ASSERT(sizeof(HoverCoordSlotFn) == 0x04);
GG_STATIC_ASSERT(offsetof(HoverCoordSlotVtbl, At_048) == 0x48);
GG_STATIC_ASSERT(sizeof(HoverCoordSlotVtbl) == 0x4C);
#define HoverUnitCoord(foot, out) \
    ((((HoverCoordSlotView*)(foot))->*((HoverCoordSlotView*)(foot))->Vtbl->At_048)(out))

// The only permitted cast: LinkedTo/Owner are declared FootClass* by the foundation.
inline HoverFootView* HoverFoot(FootClass* f) { return (HoverFootView*)f; }

// VTABLE: GAMEMD 0x7EADC8 (IPersistStream side)
// VTABLE: GAMEMD 0x7EACFC (ILocomotion side)
class HoverLocomotionClass : public LocomotionClass
{
public:
    // FUNCTION: GAMEMD 0x513C20
    HoverLocomotionClass();
    // No-init constructor used by the placement construction in Load (inline in retail).
    HoverLocomotionClass(int) : LocomotionClass(0) {}

    // SYNTHETIC: GAMEMD 0x5172C0 -- compiler-generated scalar deleting destructor.
    virtual ~HoverLocomotionClass() {}

    // ---- primary table ----
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // slot 3, 0x517070
    virtual HRESULT __stdcall Load(IStream* pStm);                        // slot 5, 0x5170B0
    virtual int Size();                                                   // slot 9, 0x5172B0

    // ---- ILocomotion overrides ----
    virtual HRESULT __stdcall LinkToObject(FootClass* object);            // 3   0x513CB0
    virtual bool __stdcall IsMoving();                                    // 4   0x514C30
    virtual LocoCoord __stdcall Destination();                            // 5   0x514CB0
    virtual LocoCoord __stdcall HeadToCoord();                            // 6   0x514D10
    virtual Matrix3D __stdcall DrawMatrix(unsigned int* key);         // 9   0x513F40
    virtual Matrix3D __stdcall ShadowMatrix(unsigned int* key);       // 10  0x5142A0
    virtual bool __stdcall Process();                                     // 16  0x514310
    virtual void __stdcall MoveTo(LocoCoord to);                          // 17  0x514D90
    virtual void __stdcall StopMoving();                                  // 18  0x516320
    virtual void __stdcall DoTurn(unsigned long dir);                     // 19  0x516370
    virtual bool __stdcall PowerOff();                                    // 23  0x516BF0
    virtual bool __stdcall IsPowered();                                   // 24  0x516C70
    virtual bool __stdcall IsIonSensitive();                              // 25  0x516CA0
    virtual bool __stdcall Push(unsigned long dir);                       // 26  0x516E10
    virtual bool __stdcall Shove(unsigned long dir);                      // 27  0x516FC0
    virtual int __stdcall InWhichLayer();                                 // 29  0x517100
    virtual bool __stdcall IsMovingNow();                                 // 32  0x514C80
    virtual void __stdcall MarkAllOccupationBits(int mark);               // 39  0x5171C0
    virtual bool __stdcall IsMovingHere(LocoCoord to);                    // 40  0x517210

    // ---- unowned retail helpers of this class (called, not defined here) ----
    void Fun_00513D20();            // FUNCTION: GAMEMD 0x513D20 (decl; reloc)
    int Fun_00514F70(int flag);     // FUNCTION: GAMEMD 0x514F70 (decl; reloc)
    void Fun_00515ED0();            // FUNCTION: GAMEMD 0x515ED0 (decl; reloc)
    void Fun_005164D0(int flag);    // FUNCTION: GAMEMD 0x5164D0 (decl; reloc)
    void StartRocking();            // FUNCTION: GAMEMD 0x517020
    void ClearSpeed();              // FUNCTION: GAMEMD 0x515E30
    void ClearSpeedAndHeading();    // FUNCTION: GAMEMD 0x515E60
    void StartMoving();             // FUNCTION: GAMEMD 0x517110
    bool Fun_005163A0();            // FUNCTION: GAMEMD 0x5163A0
    bool Fun_005163B0();            // FUNCTION: GAMEMD 0x5163B0

    // ---- members (complete-object offsets) ----
    HoverCoordView Destination_;    // +0x18
    HoverCoordView HeadTo;          // +0x24
    HoverFacingView Facing;          // +0x30
    double      Speed;              // +0x48
    double      SpeedFactor;        // +0x50
    double      Field_58;           // +0x58 (ctor 1.0)
    double      Field_60;           // +0x60 (ctor 0.0)
    bool        IsRocking;          // +0x68
    int         RockAmount;         // +0x6C
    bool        Blocked;            // +0x70
};

GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, Destination_) == 0x18);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, HeadTo) == 0x24);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, Facing) == 0x30);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, Speed) == 0x48);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, SpeedFactor) == 0x50);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, Field_58) == 0x58);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, Field_60) == 0x60);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, IsRocking) == 0x68);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, RockAmount) == 0x6C);
GG_STATIC_ASSERT(offsetof(HoverLocomotionClass, Blocked) == 0x70);
// Allocation request at 0x6C433C; the allocated object is passed to this
// constructor at 0x6C434C. Caller body ends at 0x6C4382.
GG_STATIC_ASSERT(sizeof(HoverLocomotionClass) == 0x78);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_HOVER_LOCOMOTION_CLASS_H
