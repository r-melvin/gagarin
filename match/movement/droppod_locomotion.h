// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, tables and member offsets read from the retail gamemd.exe v1.001:
//   RTTI.?AVDropPodLocomotionClass@@ (TD 0x8202F8; COLs 0x8000A8 / 0x800040 /
//   0x800028 at base offsets 0 / 4 / 24), tables 0x7E8344 (primary, 10 slots),
//   0x7E8278 (ILocomotion, 50) and 0x7E8254 (IPiggyback, 8), the constructor
//   0x4B5AB0 and its only allocation (`PUSH 0x30; CALL 0x7C8E17` at 0x6C493C).
//   Names follow YRpp where the bodies confirm the behaviour.
//
// DropPodLocomotionClass: the locomotor that drops a unit from the sky. It
// piggybacks the unit's previous locomotor (IPiggyback) and hands it back when
// the descent ends.
//
//   +0x00  vptr  primary table   0x7E8344  (LocomotionClass / IPersistStream)
//   +0x04  vptr  ILocomotion     0x7E8278  (LocomotionClass)
//   +0x08..+0x17  LocomotionClass members (loco_base.h)
//   +0x18  vptr  IPiggyback      0x7E8254
//   +0x1C  unknown_1C  byte      ctor 0; MoveTo sets 1; DrawingCode reads it
//   +0x20  DestCoord   LocoCoord ctor copies the empty coordinate 0x8A0820
//   +0x2C  Piggybackee ILocomotionPtr  (_com_ptr_t: AddRef/Release/QI pattern)
//   sizeof == 0x30 (allocation 0x6C493C)
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_DROPPOD_LOCOMOTION_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_DROPPOD_LOCOMOTION_H

#include "loco_base.h"
#include "loco_com.h"
#include "droppod_support_views.h"
#include "../core/coordinate_storage_008a0820.h"
#include "../core/frame_counter.h"
#include "../core/randomizer.h"
#include "../core/rules_class.h"
#include "../core/type_class_findoralloc_methods.h"
#include "../core/find_by_name_methods.h"
#include "../combat/weapon_type_class.h"
#include "../map/map_class_traversable_methods.h"
#include "../map/map_class_random_coords_methods.h"

// The piggybacked locomotor smart pointer (ILocomotionPtr, loco_com.h). Retail's AddRef/Release/QI
// shapes at 0x4B63B0 (assignment), 0x4B6400 (Detach), 0x4B6240 (operator&) and the destructor
// 0x4B66F0 are _com_ptr_t's.

// Address-scoped empty-coordinate storage is declared once in
// ../core/coordinate_storage_008a0820.h; no second typed global alias is used.
// True while a coordinate still equals the empty coordinate (0x4B6055..0x4B6077).
inline bool DropPodIsEmptyCoord(const LocoCoord& c)
{
    return c.X == DAT_008A0820.X && c.Y == DAT_008A0820.Y && c.Z == DAT_008A0820.Z;
}

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) - table lookup over 4096 entries (DropPod only).
extern "C" double __cdecl FUN_004CAD50(double angle);

// FUNCTION: GAMEMD 0x489280 (decl; reloc) - area damage (RET 0x10): where in ECX,
// damage in EDX, then source, warhead, two flags.
void DropPod_DamageArea(LocoCoord* where, int damage, DropPodFootView* source,
                        WarheadTypeClass* warhead, int flagA, int flagB);
// FUNCTION: GAMEMD 0x48A4F0 (decl; reloc) - picks the impact anim (RET 8).
void* DropPod_SelectDamageAnim(int damage, WarheadTypeClass* warhead,
                                                      int a, LocoCoord* where);
// FUNCTION: GAMEMD 0x48ACE0 (decl; reloc) - returns the constant -15 (RET 0xC).
int __stdcall DropPod_ZAdjust(LocoCoord where);

// FUNCTION: GAMEMD 0x49F420 (decl; reloc) - random coordinate near a coordinate
// (hidden result pointer in ECX, source in EDX, RET 8).
LocoCoord DropPod_RandomCoordsNear(const LocoCoord& coord, int distance, bool center);
// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) - sample playback ABI view (index in ECX,
// coordinate in EDX, final zero/controller argument on stack).
void DropPod_PlaySample(int sample, LocoCoord* where, int zero);

// VTABLE: GAMEMD 0x7E8344 (primary), 0x7E8278 (ILocomotion), 0x7E8254 (IPiggyback)
class DropPodLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    // FUNCTION: GAMEMD 0x4B5AB0
    DropPodLocomotionClass();
    // No-init constructor (Load re-runs it through placement new): only the
    // piggyback pointer is initialised (retail 0x4B6240 stores it, then the
    // three vptrs).
    DropPodLocomotionClass(int) : LocomotionClass(0) {}
    // Primary slot 8: an explicit empty inline destructor (an implicit one drops
    // the vptr stores, which retail has). The scalar deleting destructor
    // 0x4B66F0 is compiler output (the body is inlined into it); the standalone
    // body 0x4B5B00 is scored by ComRel_004B5B00 (multi_vtable_dtor_family_methods.cpp).
    virtual ~DropPodLocomotionClass() {}

    // ---- IUnknown: one body, adjustor thunks for the two other tables -------
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0x4B6470
    virtual ULONG   __stdcall AddRef();                                   // 0x4B66A0
    virtual ULONG   __stdcall Release();                                  // 0x4B66B0

    // ---- primary table ------------------------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 0x4B6200
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 0x4B6240
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 0x4B62C0
    virtual int Size();                                                   // 0x4B66E0

    // ---- ILocomotion overrides ---------------------------------------------
    virtual bool __stdcall IsMoving();                                    // 0x4B5B30
    virtual LocoCoord __stdcall Destination();                            // 0x4B5B40
    virtual bool __stdcall Process();                                     // 0x4B5B70
    virtual void __stdcall MoveTo(LocoCoord to);                          // 0x4B6040
    virtual void __stdcall StopMoving();                                  // 0x4B63A0
    virtual int __stdcall InWhichLayer();                                 // 0x4B64D0
    virtual int __stdcall DrawingCode();                                  // 0x4B65F0

    // ---- IPiggyback --------------------------------------------------------
    virtual HRESULT __stdcall BeginPiggyback(ILocomotion* loco);          // 0x4B63B0
    virtual HRESULT __stdcall EndPiggyback(ILocomotion** out);            // 0x4B6400
    virtual bool __stdcall IsOkToEnd();                                   // 0x4B6440
    virtual HRESULT __stdcall PiggybackCLSID(CLSID* out);                 // 0x4B64E0
    virtual bool __stdcall IsPiggybacking();                              // 0x4B66C0

    // ---- members (complete-object offsets) ----------------------------------
    // +0x18 is the IPiggyback vptr.
    bool            unknown_1C;
    LocoCoord       DestCoord;
    ILocomotionPtr  Piggybackee;
};

GG_STATIC_ASSERT(offsetof(DropPodLocomotionClass, unknown_1C)  == 0x1C);
GG_STATIC_ASSERT(offsetof(DropPodLocomotionClass, DestCoord)   == 0x20);
// _com_ptr_t overloads operator&, which breaks offsetof(); take the member's
// address as a char reference instead.
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((DropPodLocomotionClass*)0)->Piggybackee) == 0x2C);
GG_STATIC_ASSERT(sizeof(DropPodLocomotionClass) == 0x30);   // allocation 0x6C493C

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_DROPPOD_LOCOMOTION_H
