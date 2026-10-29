// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor FUN_0x0041C8B0,
//   "AircraftTypeClass (start 0xDF8, size 0xE10) -- ctor 0x41C8B0"; parent ctor
//   TechnoTypeClass 0x710AF0). Anchored member-access sites ArrayIndex@0xDF8,
//   Trailer@0xE00, SpawnDelay@0xE04, cross-checked vs YRpp.
//
// AircraftTypeClass - leaf blueprint for aircraft object types. Derives
// TechnoTypeClass (sizeof 0xDF8) at offset 0 and adds the aircraft-specific
// flags (carryall / rotor / landing behaviour) from 0xDF8 to 0xE0F.
//
// Trailer reads as undefined4 in the decomp (a 64-bit truncation site); modelled
// here as a real 4-byte opaque pointer so every offset stays byte-exact.
#ifndef GG_MATCH_LAYOUT_AIRCRAFT_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_AIRCRAFT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_type_class.h"
#include "../core/vector_class.h"   // TechnoTypeClass (sizeof 0xDF8), AnimTypeClass

// ---------------------------------------------------------------------------
// AircraftTypeClass  (0xDF8..0xE0F, sizeof = 0xE10)
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7E2868 (IPersistStream side)
// VTABLE: GAMEMD 0x7E284C (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E2844 (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E283C (INoticeSource side, +0x0C)
class AircraftTypeClass : public TechnoTypeClass
{
public:
    // CALLEE: GAMEMD 0x0041C8B0 (decl; reloc) -- constructor as the class factory calls it.
    AircraftTypeClass(int unknown_arg0 = 0);
    // FUNCTION: GAMEMD 0x41C8B0 (declaration; constructor)
    AircraftTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x41C9F0 (declaration; no-initialisation constructor)
    AircraftTypeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x41CA20 (declaration; destructor; slot 8 = 0x41CFE0)
    ~AircraftTypeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x41CEB0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x41CE20
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x41CE90
    virtual int vf_11();                                                  // 11  0x41CFB0
    virtual int vf_12();                                                  // 12  0x41CFC0
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x41CDB0
    virtual int vf_16();                                                  // 16  0x41CFD0
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x41CC20
    virtual CoordStruct vf_31();                                          // 31  0x41CBF0
    virtual bool vf_32(const CellStruct* cell, HouseClass* house);                                   // 32  0x41CBE0
    virtual ObjectClass* vf_35(HouseClass* house);                                     // 35  0x41CB20
    virtual bool vf_40();                                                 // 40  0x41CB50
    virtual bool vf_41();                                                 // 41  0x41CB60

    int            ArrayIndex;     // +0xDF8
    bool           Carryall;       // +0xDFC
    unsigned char  _pad_DFD[3];    // +0xDFD
    AnimTypeClass* Trailer;        // +0xE00 (AnimTypeClass*, truncation site)
    int            SpawnDelay;     // +0xE04
    bool           Rotors;         // +0xE08
    bool           CustomRotor;    // +0xE09
    bool           Landable;       // +0xE0A
    bool           FlyBy;          // +0xE0B
    bool           FlyBack;        // +0xE0C
    bool           AirportBound;   // +0xE0D
    bool           Fighter;        // +0xE0E
    unsigned char  align_E0F[1];   // +0xE0F

    // GLOBAL: GAMEMD 0xA8B218
    static DynamicVectorClass<AircraftTypeClass*> Array;
};

// --- Representative offset asserts (spanning the struct) + final sizeof ------
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, ArrayIndex)   == 0xDF8);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Carryall)     == 0xDFC);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Trailer)      == 0xE00);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, SpawnDelay)   == 0xE04);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Rotors)       == 0xE08);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, CustomRotor)  == 0xE09);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Landable)     == 0xE0A);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, AirportBound) == 0xE0D);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, Fighter)      == 0xE0E);
GG_STATIC_ASSERT(offsetof(AircraftTypeClass, align_E0F)    == 0xE0F);
GG_STATIC_ASSERT(sizeof(AircraftTypeClass)                 == 0xE10);

#endif  // GG_MATCH_LAYOUT_AIRCRAFT_TYPE_CLASS_H
