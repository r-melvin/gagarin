// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Every address, offset and vtable slot below was read numerically off the
//   user's retail gamemd.exe v1.001 with the local Ghidra CLI over
//   0x5CEDD0..0x5CF8D6 and the vtable block at 0x7EEAB4..0x7EEB54. 0x5CF830 is a one-line
//   forwarder into the container's own virtual Add.
//
// WHAT THIS IS. The campaign map screen keeps its stages in a container that
// IS a vector: the runtime type information under 0x7EEAB4 reads
// `.?AV?$VectorClass@PAVMapStage@@@@` and under 0x7EEA94
// `.?AV?$DynamicVectorClass@PAVMapStage@@@@`, so the object's own first 0x18
// bytes are a `DynamicVectorClass<MapStage*>`. Two more string vectors follow
// at +0x2C and +0x44 (base vtables 0x7EEAD4 and 0x7EEAF4), with a name string
// at +0x28 and a 640x400 rectangle at +0x18.
//
// ELEMENT TYPES CORRECTED (whole-image RTTI sweep). The
// two trailing vectors were annotated `VectorClass<Obj_007B4620*>`. That was a
// guess from how their elements are USED, not a read of the binary. The
// locators under those two tables say otherwise, re-read here with
// `ghidra memory read` rather than taken on the sweep's word:
//   [0x7EEAD0] = 0x008069C0 -> TD 0x008301A0 `.?AV?$VectorClass@PAVMSAnimEntry@@@@`
//   [0x7EEAF0] = 0x00806A20 -> TD 0x00830270 `.?AV?$VectorClass@PAVMSSfxEntry@@@@`
// with the DERIVED tables 0x7EEA74 / 0x7EEA54 naming
// `DynamicVectorClass<MSAnimEntry*>` / `<MSSfxEntry*>` to match. So the
// elements are `MSAnimEntry*` and `MSSfxEntry*` -- two of the movie/menu/score
// `MS*` family the sweep recovers -- NOT `Obj_007B4620*`.
//
// The element POINTEE is still spelled `Obj_007B4620` in the code below, and
// that is deliberate: every access retail makes to an element in this run is a
// `char*` read at offset +0x00 of the entry, so `MSAnimEntry`/`MSSfxEntry`
// cannot be laid out from this TU alone -- only their first member can. The
// vector types carry the proven names; the element pointee keeps the shape
// that is actually evidenced here, and is a worklist item, not a claim.
//
// THE CONTAINER LAYOUT, every offset from a member access in this run:
//
//   +0x00  vptr                     `MOV [ESI],0x7EEAB4` at 0x5CEEC0
//   +0x04  MapStage** Vector        `MOV EAX,[EDI+4]` then `[EAX+ESI*4]`
//   +0x08  int Capacity            `MOV [ESI+8],EBX` at 0x5CEEDE
//   +0x0C  bool IsValid
//   +0x0D  bool IsAllocated         `CMP BL,[ESI+0xD]` at 0x5CEECA
//   +0x10  int Count          `MOV EAX,[EDI+0x10]` at 0x5CF6C7
//   +0x14  int CapacityIncrement           `MOV [ESI+0x14],0xA` at 0x5CEDF0
//   +0x18  int  BoundsX             zeroed at 0x5CF629
//   +0x1C  int  BoundsY             zeroed at 0x5CF630
//   +0x20  int  BoundsW             set to 0x280 at 0x5CF637
//   +0x24  int  BoundsH             set to 0x190 at 0x5CF63E
//   +0x28  Obj_007B4620 Name         `LEA ECX,[ESI+0x28]` into 0x7B46F0
//   +0x2C  VectorClass<MSAnimEntry*> items +0x30, count +0x3C, flag +0x39
//   +0x44  VectorClass<MSSfxEntry*>  items +0x48, count +0x54, flag +0x51
//   sizeof 0x5C
//
// The vector destructors seat the BASE `VectorClass` vtable, never the derived
// `DynamicVectorClass` one: the derived seat is a dead store cl kills against
// the base's. That is why the three vectors are modelled as flat stand-ins
// with no base class rather than as a two-level hierarchy -- cl declines to
// inline any destructor whose base has a user-declared destructor, which is
// exactly what this container's destructor needs it to do three times over.
#ifndef GG_MATCH_MAP_MAP_STAGE_LIST_METHODS_H
#define GG_MATCH_MAP_MAP_STAGE_LIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/string_class.h"

// One stage of the campaign map. Only its two leading strings are reached from
// this run: the key the name lookup compares at +0x00 and the title the second
// lookup compares at +0x04 (`ADD ECX,4` at 0x5CF799 is the whole difference
// between the two searches).
// The container's own name string, wrapped so that its release runs as an
// ordinary member destructor. Member destruction order is what puts retail's
// `LEA ECX,[ESI+0x28]; CALL 0x7B46F0` between the +0x2C vector's teardown and
// the +0x00 one's; the same call written in the destructor body would run
// ahead of all three.
class StringMember
{
public:
    Obj_007B4620 Text;   // +0x00

    __forceinline ~StringMember() throw() { Text.Destruct(); }
};
GG_STATIC_ASSERT(sizeof(StringMember) == 4);

class MapStage
{
public:
    Obj_007B4620 Name;    // +0x00
    Obj_007B4620 Title;   // +0x04

    // FUNCTION: GAMEMD 0x5D0070 (decl; reloc) — the stage destructor.
    void Destruct();
};
GG_STATIC_ASSERT(offsetof(MapStage, Title) == 0x04);

// GLOBAL: GAMEMD 0x87E728 — non-null once the campaign session exists.
// FUNCTION: GAMEMD 0x407000 (decl; reloc) — its presence test. Declared as an
// int rather than a bool: the caller at 0x5CF84C tests the full EAX
// (`TEST EAX,EAX`), which a bool return narrows to `TEST AL,AL`.
int SessionExists();

// One vtable seat per vector, the same layout-compatible stand-in the
// animation family uses. The container is built by a named method rather than
// by a real constructor -- a real one registers a full `/GX` unwind frame the
// moment two members with destructors are built in sequence, and retail's body
// has no trace of one (measured: 1.9 percent, with five funclet jumps cl adds
// and retail does not have) -- so every vtable seat in that build-up has to be
// written by hand.
class VectorVptrSeatA
{
public:
    virtual int Seat();
    __forceinline ~VectorVptrSeatA() throw() {}
};

class VectorVptrSeatB
{
public:
    virtual int Seat();
    __forceinline ~VectorVptrSeatB() throw() {}
};

class VectorVptrSeatC
{
public:
    virtual int Seat();
    __forceinline ~VectorVptrSeatC() throw() {}
};

// The three vector stand-ins. Each carries its own vtable, which is what the
// enclosing destructor seats; the relocation normalises, and the retail
// constant is named in the comment beside each one. `Clear` is slot 3, read
// off `CALL [EDX+0xC]` at 0x5CF626, 0x5CF676 and 0x5CF6A8.
//
// Clear's body as retail has it: release the block only when this vector
// allocated it, then forget the block and the capacity unconditionally.

// VTABLE: GAMEMD 0x7EEAB4 — VectorClass<MapStage*>
class MapStageVector
{
public:
    virtual int  Slot0();
    virtual int  Slot1();
    virtual int  Slot2();
    virtual void Clear();
    // Slot 4, reached through `CALL [EAX+0x10]` at 0x5CF837 with the address
    // of the caller's pointer pushed -- an `Add(T const& object)` shape.
    virtual int  Add(MapStage* const& stage);

    MapStage** Vector;       // +0x04
    int        Capacity;    // +0x08
    bool       IsValid;      // +0x0C
    bool       IsAllocated;  // +0x0D
    int        Count;  // +0x10
    int        CapacityIncrement;   // +0x14

    // The empty setup, expanded into the container's build-up at
    // 0x5CEDDB..0x5CEDF9 and its two siblings. The seat sits between the flag
    // pair and the growth step exactly as retail has it, and it names the
    // DERIVED vtable 0x7EEA94 where the destructor's names the base one --
    // retail's own asymmetry, and both relocations normalise.
    __forceinline void Init()
    {
        Vector = 0;
        Capacity = 0;
        IsValid = true;
        IsAllocated = false;
        ((VectorVptrSeatA*)this)->VectorVptrSeatA::~VectorVptrSeatA();
        CapacityIncrement = 10;
        Count = 0;
    }

    __forceinline ~MapStageVector() throw()
    {
        if (Vector != 0 && IsAllocated) {
            delete[] Vector;
            Vector = 0;
        }

        IsAllocated = false;
        Capacity = 0;
    }
};
GG_STATIC_ASSERT(sizeof(MapStageVector) == 0x18
              && offsetof(MapStageVector, Vector) == 0x04
              && offsetof(MapStageVector, Capacity) == 0x08
              && offsetof(MapStageVector, IsValid) == 0x0C
              && offsetof(MapStageVector, IsAllocated) == 0x0D
              && offsetof(MapStageVector, Count) == 0x10
              && offsetof(MapStageVector, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7EEAD4 — VectorClass<MSAnimEntry*>, the vector at +0x2C
class MSAnimEntryVector
{
public:
    virtual int  Slot0();
    virtual int  Slot1();
    virtual int  Slot2();
    virtual void Clear();

    Obj_007B4620** Vector;       // +0x04
    int           Capacity;    // +0x08
    bool          IsValid;      // +0x0C
    bool          IsAllocated;  // +0x0D
    int           Count;  // +0x10
    int           CapacityIncrement;   // +0x14

    // The empty setup, expanded into the container's build-up at
    // 0x5CEDDB..0x5CEDF9 and its two siblings. The seat sits between the flag
    // pair and the growth step exactly as retail has it, and it names the
    // DERIVED vtable 0x7EEA74 where the destructor's names the base one --
    // retail's own asymmetry, and both relocations normalise.
    __forceinline void Init()
    {
        Vector = 0;
        Capacity = 0;
        IsValid = true;
        IsAllocated = false;
        ((VectorVptrSeatB*)this)->VectorVptrSeatB::~VectorVptrSeatB();
        CapacityIncrement = 10;
        Count = 0;
    }

    __forceinline ~MSAnimEntryVector() throw()
    {
        if (Vector != 0 && IsAllocated) {
            delete[] Vector;
            Vector = 0;
        }

        IsAllocated = false;
        Capacity = 0;
    }
};
GG_STATIC_ASSERT(sizeof(MSAnimEntryVector) == 0x18);

// VTABLE: GAMEMD 0x7EEAF4 — VectorClass<MSSfxEntry*>, the vector at +0x44
class MSSfxEntryVector
{
public:
    virtual int  Slot0();
    virtual int  Slot1();
    virtual int  Slot2();
    virtual void Clear();

    Obj_007B4620** Vector;       // +0x04
    int           Capacity;    // +0x08
    bool          IsValid;      // +0x0C
    bool          IsAllocated;  // +0x0D
    int           Count;  // +0x10
    int           CapacityIncrement;   // +0x14

    // The empty setup, expanded into the container's build-up at
    // 0x5CEDDB..0x5CEDF9 and its two siblings. The seat sits between the flag
    // pair and the growth step exactly as retail has it, and it names the
    // DERIVED vtable 0x7EEA54 where the destructor's names the base one --
    // retail's own asymmetry, and both relocations normalise.
    __forceinline void Init()
    {
        Vector = 0;
        Capacity = 0;
        IsValid = true;
        IsAllocated = false;
        ((VectorVptrSeatC*)this)->VectorVptrSeatC::~VectorVptrSeatC();
        CapacityIncrement = 10;
        Count = 0;
    }

    __forceinline ~MSSfxEntryVector() throw()
    {
        if (Vector != 0 && IsAllocated) {
            delete[] Vector;
            Vector = 0;
        }

        IsAllocated = false;
        Capacity = 0;
    }
};
GG_STATIC_ASSERT(sizeof(MSSfxEntryVector) == 0x18);

class MapStageList
{
public:
    MapStageVector Stages;      // +0x00 (the object's own vector base)
    // Plain ints. ClearAll (0x5CF5F0) resets them and is a recorded partial:
    // retail issues these four stores before the next loop's Count load and cl
    // hoists the load above them.
    int            BoundsX;     // +0x18
    int            BoundsY;     // +0x1C
    int            BoundsW;     // +0x20
    int            BoundsH;     // +0x24
    StringMember   Name;        // +0x28
    MSAnimEntryVector  Strings;     // +0x2C
    MSSfxEntryVector  Titles;      // +0x44

    MapStageList* Construct();                      // 0x5CEDD0
    ~MapStageList() throw();                        // 0x5CEE60
    void       ClearAll();                          // 0x5CF5F0
    MapStage*  FindByName(Obj_007B4620* key);        // 0x5CF6B0
    MapStage*  FindByTitle(Obj_007B4620* key);       // 0x5CF760
    MapStage*  GetAt(unsigned short index);         // 0x5CF810
    int        AddStage(MapStage* stage);           // 0x5CF830
    Obj_007B4620* FindTitle(Obj_007B4620* key);       // 0x5CF840
};
GG_STATIC_ASSERT(offsetof(MapStageList, BoundsX) == 0x18
              && offsetof(MapStageList, BoundsH) == 0x24
              && offsetof(MapStageList, Name) == 0x28
              && offsetof(MapStageList, Strings) == 0x2C
              && offsetof(MapStageList, Titles) == 0x44);

#endif  // GG_MATCH_MAP_MAP_STAGE_LIST_METHODS_H
