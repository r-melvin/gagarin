// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x6805F0: the vector's Count `[EDI+0x10]` and Items
//   `[EDI+0x4]`, the COM slots `[ECX+0x10]` (Write, four args), `[ECX]`
//   (QueryInterface, three args) and `[ECX+0x8]` (Release, receiver only),
//   the IID at 0x7F7C80 (bytes 00000109-0000-0000-C000-000000000046 =
//   IID_IPersistStream, reconfirmed by `ghidra memory read`) and the IAT
//   slot 0x7E15F4 (OleSaveToStream). The name comes from the YRpp method
//   map (Unsorted::Save_Sides, static).
#ifndef GG_MATCH_CORE_SAVE_SIDES_METHODS_H
#define GG_MATCH_CORE_SAVE_SIDES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Stream_006805F0;
struct Side_006805F0;
struct Persist_006805F0;

// IStream::Write is slot +0x10 (after the three IUnknown slots and Read at
// +0x0C); __stdcall with the receiver pushed.
typedef long (__stdcall* StreamWrite_006805F0)(Stream_006805F0*, const void*,
                                               unsigned long, unsigned long*);
#define STREAM_WRITE(s, p, n) \
    ((*(StreamWrite_006805F0*)(*(char**)(s) + 0x10))(s, p, n, 0))

// IUnknown on the side objects and on the IPersistStream they hand back.
typedef long (__stdcall* Query_006805F0)(Side_006805F0*, const void*, void**);
typedef long (__stdcall* Release_006805F0)(Persist_006805F0*);
#define COM_QUERY(p, iid, ppv) \
    ((*(Query_006805F0*)(*(char**)(p) + 0x00))(p, iid, ppv))
#define COM_SLOT_08(p) \
    ((*(Release_006805F0*)(*(char**)(p) + 0x08))(p))

// DynamicVectorClass<SideClass*> head: vtable@0, Items@4, Count@0x10.
struct SideVector_006805F0
{
    void*             Vtbl;               // +0x0000
    Side_006805F0**   Items;              // +0x0004
    int               Capacity;           // +0x0008
    int               IsAllocated;        // +0x000C
    int               Count;              // +0x0010
    int               CapacityIncrement;  // +0x0014
};
GG_STATIC_ASSERT(offsetof(SideVector_006805F0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(SideVector_006805F0, Count) == 0x10);

// GLOBAL: GAMEMD 0x7F7C80 — IID_IPersistStream.
struct Guid_006805F0 { char Bytes[16]; };
extern const Guid_006805F0 IID_IPersistStream_007F7C80;

// OleSaveToStream, called through the IAT (0x7E15F4).
extern "C" __declspec(dllimport) long __stdcall OleSaveToStream(Persist_006805F0* pPStm,
                                                                Stream_006805F0* pStm);

// FUNCTION: GAMEMD 0x6805F0  (__fastcall — stream in ECX, vector in EDX)
long Save_Sides(Stream_006805F0* stream, SideVector_006805F0* sides);

#endif  // GG_MATCH_CORE_SAVE_SIDES_METHODS_H
