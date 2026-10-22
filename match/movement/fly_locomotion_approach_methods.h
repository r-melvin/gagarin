// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Eighth translation unit of the FlyLocomotionClass cluster: the
//   __thiscall member at 0x4CE680 that steers the flyer through the last two
//   thirds of its approach. Its one caller is the member at 0x4CD2A0, which
//   is itself reached only from the per-frame step at 0x4CCB40 with the
//   object's own `this` in ECX - that chain is what establishes this body as
//   a member of the class.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// These are object-relative, because the body receives the object's own
// `this` in ECX:
//   +0x0C LinkedTo      `MOV ECX,[ESI+0xC]`, seven times
//   +0x1C Destination.X `MOV EDX,[ESI+0x1C]`            at 0x4CE7AE
//   +0x20 Destination.Y `FISUB DWORD PTR [ESI+0x20]`    at 0x4CE7D0
//   +0x38 FlightLevel  `MOV ECX,[ESI+0x38]`            at 0x4CE746
//   +0x40 Ramp          the constant double pair at 0x4CE80F/0x4CE816
//   +0x50 IsTakingOff   `MOV BYTE PTR [ESI+0x50],0x0`   at 0x4CE756
//   +0x51 IsLanding     `MOV BYTE PTR [ESI+0x51],0x0`   at 0x4CE763
// The client's members: +0x8C a gate byte, +0x9C its location, +0x388 and
// +0x3A0 the two facing slots; its vtable slots +0x48 (where it is aiming,
// returned through a hidden pointer) and +0x1C8 (the remaining travel).
// The cell's flag word is the dword at +0x140, tested as `TEST CH,0x1`.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_APPROACH_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_APPROACH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A world coordinate: three ints.
struct Coord_004CE680
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
    Coord_004CE680() {}
};
GG_STATIC_ASSERT(sizeof(Coord_004CE680) == 0xC);

// CellClass — only the flag dword @0x140 is touched.
struct Cell_004CE680
{
    char _pad000[0x140];   // +0x0000
    int  Flags;            // +0x0140
};
GG_STATIC_ASSERT(offsetof(Cell_004CE680, Flags) == 0x140);

// MapClass singleton — opaque; only the coordinate-to-cell lookup is called.
struct Map_004CE680
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x565730 (decl; reloc) — MapClass::GetCellAt(coord).
    Cell_004CE680* GetCellAt(const Coord_004CE680& coord);
};

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_004CE680 MapInstance_004CE680;
// GLOBAL: GAMEMD 0x8B3CAC — the bridge height the approach discounts.
extern int BridgeHeight_008B3CAC;

// The value a facing slot's reader hands back through a hidden pointer, and
// the value its writer takes. Retail stores only sixteen bits into the
// temporary it passes and then copies the whole dword, so the written member
// is a short beside an unwritten one.
struct Dir_004CE680
{
    short Raw;         // +0x00
    short Unknown02;   // +0x02
};
GG_STATIC_ASSERT(sizeof(Dir_004CE680) == 4);

struct FacingSlot_004CE680
{
    // FUNCTION: GAMEMD 0x4C9470 (decl; reloc) — the desired direction.
    Dir_004CE680* Desired(Dir_004CE680* out);
    // FUNCTION: GAMEMD 0x4C9220 (decl; reloc) — set the desired direction.
    void SetDesired(Dir_004CE680* value);
};

// The interface the client aggregates. Only IUnknown's three slots and the
// clearance reader at +0x0C are reached.
struct IFace_004CE680;

struct IFaceVtbl_004CE680
{
    long (__stdcall* QueryInterface)(IFace_004CE680*, const void* riid,
                                     void** ppv);                    // +0x00
    unsigned long (__stdcall* AddRef)(IFace_004CE680*);              // +0x04
    unsigned long (__stdcall* Release)(IFace_004CE680*);             // +0x08
    int (__stdcall* GetGroundClearance)(IFace_004CE680*);            // +0x0C
};
GG_STATIC_ASSERT(offsetof(IFaceVtbl_004CE680, Release) == 0x8 &&
                 offsetof(IFaceVtbl_004CE680, GetGroundClearance) == 0xC);

struct IFace_004CE680 { IFaceVtbl_004CE680* Vtbl; };

// GLOBAL: GAMEMD 0x822410 — the interface id the client is queried for.
extern const char riid_00822410[16];

// LIBRARY: GAMEMD 0x7DC720 (decl; reloc) — report a failed HRESULT.
void __stdcall FUN_007DC720(long hr);
// FUNCTION: GAMEMD 0x4CAE30 (decl; reloc) — two-argument arctangent, __cdecl.
double __cdecl FUN_004CAE30(double y, double x);

// The one-pointer smart holder the release helper operates on.
struct Holder_004CE680
{
    IFace_004CE680* Held;   // +0x00

    // Defined in-class so cl expands it at the scope exit; the release is
    // scope-exit order in retail, not a statement the body could have
    // written. The no-throw specification is not enough on its own - see the
    // VC6FLAGS note in the .cpp.
    ~Holder_004CE680() throw()
    {
        if (Held != 0) {
            Held->Vtbl->Release(Held);
        }
    }
};
GG_STATIC_ASSERT(sizeof(Holder_004CE680) == 4);

// FUNCTION: GAMEMD 0x4D0430 (decl; reloc) — release whatever the holder holds.
void FUN_004D0430(Holder_004CE680* self);

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CE680;

struct Foot_004CE680
{
    FootVtbl_004CE680*  Vtbl;                    // +0x0000
    char                _pad004[0x8C - 0x4];     // +0x0004
    char                IsOnBridgeDeck;          // +0x008C
    char                _pad08D[0x9C - 0x8D];    // +0x008D
    Coord_004CE680      Location;                // +0x009C
    char                _pad0A8[0x388 - 0xA8];   // +0x00A8
    FacingSlot_004CE680 PrimaryFacing;           // +0x0388
    char                _pad389[0x3A0 - 0x389];  // +0x0389
    FacingSlot_004CE680 SecondaryFacing;         // +0x03A0
};
GG_STATIC_ASSERT(offsetof(Foot_004CE680, IsOnBridgeDeck) == 0x8C &&
                 offsetof(Foot_004CE680, Location) == 0x9C &&
                 offsetof(Foot_004CE680, PrimaryFacing) == 0x388 &&
                 offsetof(Foot_004CE680, SecondaryFacing) == 0x3A0);

typedef int (Foot_004CE680::*FnInt_004CE680)();
// The slot takes the buffer as an explicit out-parameter and hands it back:
// retail reads both components straight off the returned register
// (`MOV ECX,[EAX]`, `FILD [EAX+4]`), which a by-value return would copy into
// a local first.
typedef Coord_004CE680* (Foot_004CE680::*FnCoord_004CE680)(Coord_004CE680*);

struct FootVtbl_004CE680
{
    // Slot 0 is IUnknown::QueryInterface: the client is COM-aggregated.
    long (__stdcall* QueryInterface)(Foot_004CE680*, const void* riid,
                                     void** ppv);                   // +0x0000
    char             _pad004[0x48 - 0x4];       // +0x0004
    FnCoord_004CE680 At_48;                     // +0x0048
    char             _pad04C[0x1C8 - 0x4C];     // +0x004C
    FnInt_004CE680   At_1C8;                    // +0x01C8
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CE680, At_48) == 0x48 &&
                 offsetof(FootVtbl_004CE680, At_1C8) == 0x1C8);

// FlyLocomotionClass through its own `this`.
struct FlyLocoApproach
{
    void*           _vtable_persist;        // +0x0000
    void*           _vtable_locomotor;      // +0x0004
    char            _pad008[0x4];           // +0x0008
    Foot_004CE680*  LinkedTo;               // +0x000C
    char            _pad010[0x1C - 0x10];   // +0x0010
    Coord_004CE680  Destination;            // +0x001C
    char            _pad028[0x38 - 0x28];   // +0x0028
    int             FlightLevel;           // +0x0038
    char            _pad03C[0x4];           // +0x003C
    double          Ramp;                   // +0x0040
    char            _pad048[0x50 - 0x48];   // +0x0048
    char            IsTakingOff;            // +0x0050
    char            IsLanding;              // +0x0051

    // FUNCTION: GAMEMD 0x4CE680
    char Approach();
};
GG_STATIC_ASSERT(offsetof(FlyLocoApproach, LinkedTo) == 0x0C &&
                 offsetof(FlyLocoApproach, Destination) == 0x1C &&
                 offsetof(FlyLocoApproach, FlightLevel) == 0x38 &&
                 offsetof(FlyLocoApproach, Ramp) == 0x40 &&
                 offsetof(FlyLocoApproach, IsTakingOff) == 0x50 &&
                 offsetof(FlyLocoApproach, IsLanding) == 0x51);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_APPROACH_METHODS_H
