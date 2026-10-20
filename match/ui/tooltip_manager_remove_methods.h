// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x724730. On the manager (EBP): `MOV EDX,[EBP]` (the
//   vptr) and `CALL [EDX+0x8]` with `LEA EAX,[EBP+0x18]` pushed;
//   `MOV ECX,[EBP+0x4]` (the tip currently on screen);
//   `MOV EAX,[EBP+0x234]` / `LEA ESI,[EBP+0x234]` (the pointer vector, whose
//   Items are at rel +0x4 and Count at rel +0x10, i.e. 0x238 and 0x244); and
//   `LEA ESI,[EBP+0x24C]` for the sorted key table, whose Items are at rel
//   +0x0, Count at +0x4, the sorted flag at +0xC and the cached entry at
//   +0x10 (0x24C / 0x250 / 0x258 / 0x25C) — the same table already confirmed
//   in match/ui/tooltip_manager_find_methods.h. Entries are eight bytes
//   (`SAR EAX,3` on the pointer difference, `LEA EAX,[EDX+ECX*8]`, `PUSH 0x8`
//   as the qsort element size). Helpers: `MOV ECX,ESI; PUSH &key;
//   CALL 0x724FC0` (the table lookup, __thiscall), `MOV ECX,[ESI];
//   MOV EDX,[ESI+0x4]; PUSH &key; CALL 0x725070` (the sorted search,
//   __fastcall with items/count in ECX/EDX and no caller-side ADD ESP), the
//   CRT `qsort` at 0x7C8B48 with the comparison function at 0x725040, and
//   the CRT free at 0x7C8B3D. The default tip is the pointer global at
//   0xB78820. Names cross-checked against YRpp ToolTipManager (consult-only,
//   NO LICENSE).
#ifndef GG_MATCH_UI_TOOLTIP_MANAGER_REMOVE_METHODS_H
#define GG_MATCH_UI_TOOLTIP_MANAGER_REMOVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// One tool tip; its first dword repeats the table key.
struct ToolTipData_00724730
{
    unsigned int Key;        // +0x0000
    int          Fields[6];  // +0x0004
};
GG_STATIC_ASSERT(sizeof(ToolTipData_00724730) == 0x1C);

// One entry of the sorted table.
struct ToolTipEntry_00724730
{
    unsigned int           Key;   // +0x0000
    ToolTipData_00724730*  Data;  // +0x0004
};
GG_STATIC_ASSERT(sizeof(ToolTipEntry_00724730) == 8);

// GLOBAL: GAMEMD 0xB78820 — the tool tip handed back when the key is absent.
extern ToolTipData_00724730* DAT_00B78820;

// FUNCTION: GAMEMD 0x7C8B48 (decl; reloc) — CRT qsort.
extern "C" void __cdecl gg_qsort(void* base, unsigned int count, unsigned int size,
                                 int (__cdecl* compare)(const void*, const void*));
// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);
// FUNCTION: GAMEMD 0x725040 (decl; reloc) — the key comparison handed to qsort.
int __cdecl FUN_00725040(const void* a, const void* b);
// FUNCTION: GAMEMD 0x725070 (decl; reloc) — the sorted search over the table.
ToolTipEntry_00724730* __fastcall FUN_00725070(ToolTipEntry_00724730* items, int count,
                                               ToolTipEntry_00724730* probe);

// The sorted key table living at manager+0x24C.
struct ToolTipTable_00724730
{
    ToolTipEntry_00724730* Items;      // +0x0000  (manager +0x24C)
    int                    Count;      // +0x0004  (manager +0x250)
    int                    At_8;       // +0x0008  (manager +0x254)
    char                   IsSorted;   // +0x000C  (manager +0x258)
    char                   _pad00D[3]; // +0x000D
    ToolTipEntry_00724730* Cached;     // +0x0010  (manager +0x25C)

    // FUNCTION: GAMEMD 0x724FC0 (decl; reloc) — the table lookup.
    ToolTipEntry_00724730* Search(unsigned int* key);

    // The cached-entry preamble, expanded twice: the cached entry when it
    // still carries the key, otherwise the out-of-line lookup, whose result
    // is cached. Returns only whether the key is present, because retail
    // never materialises the entry pointer at either expansion.
    bool Ensure(unsigned int& key)
    {
        ToolTipEntry_00724730* cached = Cached;
        if (cached == 0 || cached->Key != key) {
            ToolTipEntry_00724730* found = Search(&key);
            if (found == 0) {
                return false;
            }
            Cached = found;
        }
        return true;
    }

    // The tip a key names, or the shared default when it names none. The
    // select is on the address, not the value: retail loads &Cached->Data or
    // the address of the default and dereferences once at the join.
    ToolTipData_00724730*& GetTip(unsigned int& key)
    {
        if (Count != 0) {
            if (Ensure(key)) {
                return Cached->Data;
            }
        }
        return DAT_00B78820;
    }

    // The by-key removal, expanded inline at 0x7247FF: sort on demand, find
    // the entry, slide the tail down over it, blank the freed slot and drop
    // the cache.
    void RemoveEntry(ToolTipData_00724730* data);
};
GG_STATIC_ASSERT(offsetof(ToolTipTable_00724730, Items)    == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTipTable_00724730, Count)    == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipTable_00724730, IsSorted) == 0x0C);
GG_STATIC_ASSERT(offsetof(ToolTipTable_00724730, Cached)   == 0x10);

// DynamicVectorClass<ToolTipData*> at manager+0x234; only slot 4
// (FindItemIndex) is called here, the rest are declared to pin the layout.
struct DynVec_00724730
{
    virtual ~DynVec_00724730();
    virtual int  operator==(const DynVec_00724730& other) const;
    virtual bool SetCapacity(int capacity, void* pMem);
    virtual void Clear();
    virtual int  FindItemIndex(ToolTipData_00724730* const& item) const;

    ToolTipData_00724730** Items;             // +0x04
    int                    Capacity;          // +0x08
    unsigned char          IsInitialized;     // +0x0c
    unsigned char          IsAllocated;       // +0x0d
    int                    Count;             // +0x10
    int                    CapacityIncrement; // +0x14

    bool RemoveItem(ToolTipData_00724730* const& item)
    {
        int index = FindItemIndex(item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index)
                Items[index] = Items[index + 1];
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(DynVec_00724730, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynVec_00724730, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(DynVec_00724730) == 0x18);

struct MgrVtbl_00724730;

class ToolTipManager_00724730
{
public:
    MgrVtbl_00724730*      Vptr;                     // +0x0000
    ToolTipData_00724730*  At_4;                     // +0x0004  tip on screen
    char                   _pad008[0x18 - 8];        // +0x0008
    int                    At_18;                    // +0x0018
    char                   _pad01C[0x234 - 0x1C];    // +0x001C
    DynVec_00724730        Vec;                      // +0x0234
    ToolTipTable_00724730  Table;                    // +0x024C

    // FUNCTION: GAMEMD 0x724730 — ToolTipManager::Remove.
    void Remove(unsigned int key);
};
typedef void (ToolTipManager_00724730::*Fn8_00724730)(void* out);

struct MgrVtbl_00724730
{
    char          _pad000[8];   // +0x0000
    Fn8_00724730  At_8;         // +0x0008
};
GG_STATIC_ASSERT(offsetof(MgrVtbl_00724730, At_8) == 0x8);
GG_STATIC_ASSERT(offsetof(ToolTipManager_00724730, At_4)  == 0x4);
GG_STATIC_ASSERT(offsetof(ToolTipManager_00724730, At_18) == 0x18);
GG_STATIC_ASSERT(offsetof(ToolTipManager_00724730, Vec)   == 0x234);
GG_STATIC_ASSERT(offsetof(ToolTipManager_00724730, Table) == 0x24C);

inline void ToolTipTable_00724730::RemoveEntry(ToolTipData_00724730* data)
{
    if (Count != 0) {
        if (!IsSorted) {
            gg_qsort(Items, Count, 8, FUN_00725040);
            Cached = 0;
            IsSorted = 1;
        }
        ToolTipEntry_00724730 probe;
        probe.Key = data->Key;
        ToolTipEntry_00724730* entry = FUN_00725070(Items, Count, &probe);
        if (entry != 0) {
            int index = entry - Items;
            if (index != -1) {
                for (int j = index + 1; j < Count; ++j) {
                    Items[j - 1] = Items[j];
                }
                int last = Count - 1;
                ToolTipEntry_00724730* items = Items;
                ToolTipEntry_00724730 blank;
                blank.Key = 0;
                Count = last;
                blank.Data = 0;
                items[last] = blank;
                Cached = (ToolTipEntry_00724730*)blank.Data;
            }
        }
    }
}

#endif  // GG_MATCH_UI_TOOLTIP_MANAGER_REMOVE_METHODS_H
