// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and vtable slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x577AB0: the house's
//   `[EAX+0x30]` (ArrayIndex) indexing `[0xA8022C]` (HouseClass::Array.Items,
//   the vector object at 0xA80228 + 4) and the byte `[ECX+0x241]`; the
//   current player `[0xA83D4C]` and its byte `[EAX+0x240]`; the log string
//   0x82AD48 ("We tried to reset the shroud without an owner") pushed into
//   the __cdecl 0x4068E0; `PUSH 0; PUSH 0; MOV ECX,0x87F7E8; CALL 0x4ADEE0`
//   and the same shape for 0x4ADCD0, plus CALL 0x657CE0 on the static map
//   object; the inlined cell-iterator start (`[ESI+0xF4]` copied to
//   `[ESI+0x110]`, minus one to `[ESI+0x114]`, `[ESI+0x10C] = 1`,
//   `[ESI+0x118] = [ESI+0x13C] + count*0x800 + 4`, byte-identical to the
//   out-of-line 0x578350) and the walk `CALL 0x578290` returning the next
//   cell; the per-cell `[EAX+0x12C] &= ~0x18`, `[EAX+0x130] = 1`,
//   `[EAX+0x134] = 0`, `[EAX+0x140] &= ~3`; and the final `PUSH 2; CALL
//   [EDX+0x38]` on `this`. Cell offsets agree with
//   match/map/cell_class_shroud_methods.h (AltFlags @0x12C, ShroudCounter
//   @0x130, Flags @0x140; not edited). YRpp names only
//   MapClass::Reshroud, HouseClass::ArrayIndex, HouseClass::Array
//   @0xA80228, HouseClass::CurrentPlayer @0xA83D4C, MapClass::
//   CellIteratorNext @0x578290, CellIteratorReset @0x578350.
#ifndef GG_MATCH_MAP_MAP_CLASS_RESHROUD_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_RESHROUD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// HouseClass view: the registry index and the two shroud bytes.
struct House_00577AB0
{
    char _pad000[0x30];            // +0x0000
    int  ArrayIndex;               // +0x0030
    char _pad034[0x240 - 0x34];    // +0x0034
    char At_240;                   // +0x0240
    char At_241;                   // +0x0241
};
GG_STATIC_ASSERT(offsetof(House_00577AB0, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(House_00577AB0, At_240)     == 0x240);
GG_STATIC_ASSERT(offsetof(House_00577AB0, At_241)     == 0x241);

// DynamicVectorClass<HouseClass*> view: only Items @+4 is read.
struct HouseVec_00577AB0
{
    void*             _vtable;   // +0x0000
    House_00577AB0**  Items;     // +0x0004
};
GG_STATIC_ASSERT(offsetof(HouseVec_00577AB0, Items) == 0x4);
// GLOBAL: GAMEMD 0xA80228 — HouseClass::Array (Items at 0xA8022C).
extern HouseVec_00577AB0 DAT_00A80228;
// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_00577AB0* DAT_00A83D4C;

// CellClass view: the four words the reshroud sweep resets.
struct Cell_00577AB0
{
    char _pad000[0x12C];           // +0x0000
    int  AltFlags;                 // +0x012C
    int  ShroudCounter;            // +0x0130
    int  At_134;                   // +0x0134
    char _pad138[0x140 - 0x138];   // +0x0138
    int  Flags;                    // +0x0140
};
GG_STATIC_ASSERT(offsetof(Cell_00577AB0, AltFlags)      == 0x12C);
GG_STATIC_ASSERT(offsetof(Cell_00577AB0, ShroudCounter) == 0x130);
GG_STATIC_ASSERT(offsetof(Cell_00577AB0, At_134)        == 0x134);
GG_STATIC_ASSERT(offsetof(Cell_00577AB0, Flags)         == 0x140);

// STRING: GAMEMD 0x82AD48 — "We tried to reset the shroud without an owner".
extern const char DAT_0082AD48[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// The static map object at 0x87F7E8, used for the three calls the retail
// body makes on the global rather than on `this`.
struct MapStatic_00577AB0
{
    // FUNCTION: GAMEMD 0x4ADEE0 (decl; reloc)
    void FUN_004ADEE0(int a, int b);
    // FUNCTION: GAMEMD 0x4ADCD0 (decl; reloc)
    void FUN_004ADCD0(int a, int b);
    // FUNCTION: GAMEMD 0x657CE0 (decl; reloc)
    void FUN_00657CE0();
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern MapStatic_00577AB0 MapInstance;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct MapVtbl_00577AB0;

struct MapClass
{
    MapVtbl_00577AB0* Vtbl;        // +0x0000
    char _pad004[0xF4 - 0x4];      // +0x0004
    int  At_F4;                    // +0x00F4  cell count the iterator walks
    char _padF8[0x10C - 0xF8];     // +0x00F8
    int  IterState;                // +0x010C
    int  IterCount;                // +0x0110
    int  IterLast;                 // +0x0114
    int  IterCursor;               // +0x0118
    char _pad11C[0x13C - 0x11C];   // +0x011C
    int  At_13C;                   // +0x013C  base the cursor is formed from

    // The out-of-line 0x578350 (CellIteratorReset), inlined here.
    void CellIteratorReset()
    {
        int count = this->At_F4;
        this->IterState  = 1;
        this->IterCount  = count;
        this->IterLast   = count - 1;
        this->IterCursor = this->At_13C + count * 0x800 + 4;
    }

    // FUNCTION: GAMEMD 0x578290 (decl; reloc) — next cell or null.
    Cell_00577AB0* CellIteratorNext();

    // FUNCTION: GAMEMD 0x577AB0
    void Reshroud(House_00577AB0* house);
};
GG_STATIC_ASSERT(offsetof(MapClass, At_F4)      == 0xF4);
GG_STATIC_ASSERT(offsetof(MapClass, IterState)  == 0x10C);
GG_STATIC_ASSERT(offsetof(MapClass, IterCount)  == 0x110);
GG_STATIC_ASSERT(offsetof(MapClass, IterLast)   == 0x114);
GG_STATIC_ASSERT(offsetof(MapClass, IterCursor) == 0x118);
GG_STATIC_ASSERT(offsetof(MapClass, At_13C)     == 0x13C);

typedef void (MapClass::*Fn38_00577AB0)(int mode);

struct MapVtbl_00577AB0
{
    char           _pad00[0x38];   // +0x0000
    Fn38_00577AB0  At_38;          // +0x0038
};
GG_STATIC_ASSERT(offsetof(MapVtbl_00577AB0, At_38) == 0x38);

#endif  // GG_MATCH_MAP_MAP_CLASS_RESHROUD_METHODS_H
