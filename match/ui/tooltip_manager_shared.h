// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Canonical ToolTipManager family layout recovered from retail gamemd.exe
//   v1.001. RTTI at 0x844998 identifies ToolTipManager; its COL is 0x80C888
//   and its primary vtable address point is 0x7F57AC. Constructor/member
//   accesses at 0x724000, 0x7240B0, 0x724580, 0x724730, 0x7241A0 and 0x724AD0
//   confirm the offsets asserted below. The separately address-local Find
//   view remains in tooltip_manager_find_methods.h pending its own cleanup.
#ifndef GG_MATCH_UI_TOOLTIP_MANAGER_SHARED_H
#define GG_MATCH_UI_TOOLTIP_MANAGER_SHARED_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/geometry2d.h"
#include "../core/vector_class_operations.h"
#include "../core/sort_then_search_sweep.h"
#include "../core/sorted_pair_search_family_methods.h"

// Add copies this 0x1C-byte descriptor. The caller at 0x6D09C0 writes the
// fields at these offsets; Process reads GadgetID and Text from the record.
// Add at 0x724580 copies this four-DWORD group using pointers to +0x04
// of each descriptor. The reconstructed Bounds name describes that group.
struct ToolTipBounds
{
    int X;
    int Y;
    int Width;
    int Height;

    // Edge-inclusive hit test, inlined by 0x724A30 and its two copies in 0x724200.
    bool Contains(const Point2D& point) const
    {
        return point.X >= X && point.X <= X + Width
            && point.Y >= Y && point.Y <= Y + Height;
    }
};
GG_STATIC_ASSERT(offsetof(ToolTipBounds, X) == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTipBounds, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipBounds, Width) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTipBounds, Height) == 0x0C);
GG_STATIC_ASSERT(sizeof(ToolTipBounds) == 0x10);

class ToolTip
{
public:
    ToolTip() {}
    // Member-wise copy, inlined by Add (0x724580): the bounds group is copied
    // as one four-dword block between the id and the text.
    ToolTip(const ToolTip& other)
        : GadgetID(other.GadgetID), Bounds(other.Bounds), Text(other.Text),
          field_18(other.field_18) {}
    unsigned int GadgetID; // +0x00
    ToolTipBounds Bounds;   // +0x04
    const char* Text;       // +0x14
    bool field_18;          // +0x18
};
GG_STATIC_ASSERT(offsetof(ToolTip, GadgetID) == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTip, Bounds) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTip, Bounds) + offsetof(ToolTipBounds, X) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTip, Bounds) + offsetof(ToolTipBounds, Y) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTip, Bounds) + offsetof(ToolTipBounds, Width) == 0x0C);
GG_STATIC_ASSERT(offsetof(ToolTip, Bounds) + offsetof(ToolTipBounds, Height) == 0x10);
GG_STATIC_ASSERT(offsetof(ToolTip, Text) == 0x14);
GG_STATIC_ASSERT(offsetof(ToolTip, field_18) == 0x18);
GG_STATIC_ASSERT(sizeof(ToolTip) == 0x1C);

// Rectangle dimensions followed by a 256-code-unit UTF-16 help string.
struct ToolTipManagerData
{
    int X;                   // +0x00
    int Y;                   // +0x04
    int Width;               // +0x08
    int Height;              // +0x0C
    wchar_t HelpText[0x100]; // +0x10
};
GG_STATIC_ASSERT(offsetof(ToolTipManagerData, X) == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTipManagerData, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipManagerData, Width) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTipManagerData, Height) == 0x0C);
GG_STATIC_ASSERT(offsetof(ToolTipManagerData, HelpText) == 0x10);
GG_STATIC_ASSERT(sizeof(ToolTipManagerData) == 0x210);
GG_STATIC_ASSERT(sizeof(wchar_t) == 2);

struct ToolTipTableEntry
{
    // Add's array new (0x724580) passes an out-of-line empty constructor,
    // 0x724F90, to the vector-construct helper 0x4068F0; Remove (0x724730)
    // builds entries with no call. Declaring it out of line costs Remove its
    // match, so it stays inline here and 0x724F90 is not claimed.
    ToolTipTableEntry() {}
    unsigned int Key; // +0x00
    ToolTip* Data;    // +0x04
};
GG_STATIC_ASSERT(offsetof(ToolTipTableEntry, Key) == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTipTableEntry, Data) == 0x04);
GG_STATIC_ASSERT(sizeof(ToolTipTableEntry) == 0x08);

// GLOBAL: GAMEMD 0x00B78820 — default tooltip record returned on a miss.
extern ToolTip* DAT_00B78820;

// FUNCTION: GAMEMD 0x7C8B3D (LIBRARY, CRT free)
extern "C" void __cdecl gg_free(void* block);

struct ToolTipTable
{
    // Inlined initialization recovered from constructor 0x724000.
    ToolTipTable() : Items(0), Count(0), Capacity(0), IsSorted(0), Cached(0) {}
    // Inlined release recovered from destructor 0x7240B0, which runs it once
    // in its body and once more as this member's destructor.
    ~ToolTipTable() { Clear(); }
    void Clear()
    {
        gg_free(Items);
        Items = 0;
        Count = 0;
        Capacity = 0;
        IsSorted = 0;
        Cached = 0;
    }
    ToolTipTableEntry* Items; // +0x00, manager +0x24C
    int Count;                // +0x04, manager +0x250
    int Capacity;             // +0x08, manager +0x254
    unsigned char IsSorted;   // +0x0C, manager +0x258
    unsigned char unknown_0D[3];
    ToolTipTableEntry* Cached; // +0x10, manager +0x25C

    // Inline search half of 0x724FC0; no independent retail entry claimed.
    ToolTipTableEntry* SearchSorted(const unsigned int* key)
    {
        ToolTipTableEntry* base = Items;
        unsigned int k = *key;
        int count;
        for (count = Count; count > 0; ) {
            int half = count / 2;
            ToolTipTableEntry* mid = base + half;
            if (mid->Key > k) {
                count = half;
            } else {
                if (mid->Key == k)
                    return mid;
                base = mid + 1;
                count = count - 1 - half;
            }
        }
        return 0;
    }

    // FUNCTION: GAMEMD 0x724FA0 (decl; reloc) — compare the cached key.
    bool HasCachedKey(const unsigned int* key);

    // FUNCTION: GAMEMD 0x724FC0 (decl; reloc) — the table lookup.
    ToolTipTableEntry* Search(unsigned int* key);

    bool Ensure(unsigned int& key)
    {
        ToolTipTableEntry* cached = Cached;
        if (cached == 0 || cached->Key != key) {
            ToolTipTableEntry* found = Search(&key);
            if (found == 0)
                return false;
            Cached = found;
        }
        return true;
    }

    ToolTip*& GetTip(unsigned int& key)
    {
        if (Count != 0 && Ensure(key))
            return Cached->Data;
        return DAT_00B78820;
    }

    // Retail's inline removal: sort on demand, find this key, slide the tail
    // down and clear the newly unused entry.
    void RemoveEntry(const ToolTip* data)
    {
        if (Count != 0) {
            if (!IsSorted) {
                FUN_007C8B48(Items, Count, 8, CompareToolTipTableEntries);
                Cached = 0;
                IsSorted = 1;
            }
            ToolTipTableEntry probe;
            probe.Key = data->GadgetID;
            SortedEntryU_00725070* found = FUN_00725070(
                (SortedEntryU_00725070*)Items, Count, &probe.Key);
            ToolTipTableEntry* entry = (ToolTipTableEntry*)found;
            if (entry != 0) {
                int index = entry - Items;
                if (index != -1) {
                    for (int j = index + 1; j < Count; ++j)
                        Items[j - 1] = Items[j];
                    int last = Count - 1;
                    ToolTipTableEntry* items = Items;
                    ToolTipTableEntry blank;
                    blank.Key = 0;
                    Count = last;
                    blank.Data = 0;
                    items[last] = blank;
                    Cached = (ToolTipTableEntry*)blank.Data;
                }
            }
        }
    }
};

GG_STATIC_ASSERT(offsetof(ToolTipTable, Items) == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTipTable, Count) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipTable, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTipTable, IsSorted) == 0x0C);
GG_STATIC_ASSERT(offsetof(ToolTipTable, unknown_0D) == 0x0D);
GG_STATIC_ASSERT(offsetof(ToolTipTable, Cached) == 0x10);
GG_STATIC_ASSERT(sizeof(ToolTipTable) == 0x14);

// RTTI confirms the embedded vector's const-qualified element type and
// offset-zero VectorClass base (COLs 0x80C840 and 0x80C8B8).
// VTABLE: GAMEMD 0x7F57E8 — VectorClass<const ToolTip*>
// VTABLE: GAMEMD 0x7F57C8 — DynamicVectorClass<const ToolTip*>
// Actual-template offset/size assertions live in vector_class_layout_asserts.cpp.
typedef VectorClass<const ToolTip*> ToolTipVectorStorage;
typedef DynamicVectorClass<const ToolTip*> ToolTipVector;

// Primary vtable layout at 0x7F57AC: six slots precede the vector COL.
struct ToolTipManagerVtableLayout
{
    void* Slot0; void* Slot1; void* Slot2;
    void* Slot3; void* Slot4; void* Slot5;
};
GG_STATIC_ASSERT(offsetof(ToolTipManagerVtableLayout, Slot0) == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTipManagerVtableLayout, Slot1) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipManagerVtableLayout, Slot2) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTipManagerVtableLayout, Slot3) == 0x0C);
GG_STATIC_ASSERT(offsetof(ToolTipManagerVtableLayout, Slot4) == 0x10);
GG_STATIC_ASSERT(offsetof(ToolTipManagerVtableLayout, Slot5) == 0x14);
GG_STATIC_ASSERT(sizeof(ToolTipManagerVtableLayout) == 0x18);

// Embedded-vector vtable layout at 0x7F57C8: seven slots precede COL 0x7F57E4.
struct ToolTipVectorVtableLayout
{
    void* Slot0; void* Slot1; void* Slot2; void* Slot3;
    void* Slot4; void* Slot5; void* Slot6;
};
GG_STATIC_ASSERT(offsetof(ToolTipVectorVtableLayout, Slot0) == 0x00);
GG_STATIC_ASSERT(offsetof(ToolTipVectorVtableLayout, Slot1) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipVectorVtableLayout, Slot2) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTipVectorVtableLayout, Slot3) == 0x0C);
GG_STATIC_ASSERT(offsetof(ToolTipVectorVtableLayout, Slot4) == 0x10);
GG_STATIC_ASSERT(offsetof(ToolTipVectorVtableLayout, Slot5) == 0x14);
GG_STATIC_ASSERT(offsetof(ToolTipVectorVtableLayout, Slot6) == 0x18);
GG_STATIC_ASSERT(sizeof(ToolTipVectorVtableLayout) == 0x1C);

struct tagMSG;

class ToolTipManager
{
public:
    // VTABLE: GAMEMD 0x7F57AC (primary ToolTipManager address point)
    // FUNCTION: GAMEMD 0x7240B0 — regular destructor (unlisted entry).
    virtual ~ToolTipManager(); // slot 0: 0x724C10 deleting dtor
    virtual bool Update(ToolTipManagerData& from); // slot 1: 0x724AA0
    virtual void MarkToRedraw(ToolTipManagerData& from); // slot 2: 0x724AB0
    virtual void Draw(bool onSidebar); // slot 3: 0x724B80
    virtual void DrawText(ToolTipManagerData& from); // slot 4: 0x724BB0
    virtual wchar_t* GetToolTipText(unsigned int id); // slot 5: 0x724BD0

    ToolTip* CurrentToolTip;                 // +0x04
    void* hWnd;                              // +0x08
    bool IsActive;                           // +0x0C
    unsigned char unknown_0D;
    unsigned char unknown_0E[2];
    Point2D CurrentMousePosition;            // +0x10
    ToolTipManagerData CurrentToolTipData;   // +0x18
    int ToolTipDelay;                        // +0x228
    int LastToolTipDelay;                    // +0x22C
    int unknown_230;                         // +0x230
    ToolTipVector ToolTips;                  // +0x234
    ToolTipTable Table;                      // +0x24C

    // FUNCTION: GAMEMD 0x724000 — constructor, one pointer argument, RET 4.
    ToolTipManager(void* window);
    // FUNCTION: GAMEMD 0x7241A0
    void SetState(bool state);
    // FUNCTION: GAMEMD 0x724520
    void SetTimerDelay(int value);
    // FUNCTION: GAMEMD 0x724530
    void SaveTimerDelay();
    // FUNCTION: GAMEMD 0x724540
    void RestoreTimeDelay();
    // FUNCTION: GAMEMD 0x724200 (declaration) -- the window-message hook, RET 4.
    void FUN_00724200(const tagMSG* msg);
    // FUNCTION: GAMEMD 0x724510 (declaration)
    int FUN_00724510() const;
    // FUNCTION: GAMEMD 0x724550 (declaration)
    int FUN_00724550() const;
    // FUNCTION: GAMEMD 0x724560 (declaration)
    void FUN_00724560(int value);
    // FUNCTION: GAMEMD 0x724570 (declaration)
    int FUN_00724570() const;
    // FUNCTION: GAMEMD 0x724580
    bool Add(ToolTip& tip);
    // FUNCTION: GAMEMD 0x724A30 (declaration) -- the first tip whose bounds hold the point.
    const ToolTip* FUN_00724A30(const Point2D& point) const;
    // FUNCTION: GAMEMD 0x724730
    void Remove(unsigned int key);
    // FUNCTION: GAMEMD 0x724AD0
    bool Process();
    // FUNCTION: GAMEMD 0x724BE0
    void FUN_00724BE0();
    // FUNCTION: GAMEMD 0x724C00
    bool IsToolTipShowing() const;
};

GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTip) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipManager, hWnd) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTipManager, IsActive) == 0x0C);
GG_STATIC_ASSERT(offsetof(ToolTipManager, unknown_0D) == 0x0D);
GG_STATIC_ASSERT(offsetof(ToolTipManager, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentMousePosition) == 0x10);
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTipData) == 0x18);
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTipData)
                 + offsetof(ToolTipManagerData, HelpText) == 0x28);
GG_STATIC_ASSERT(offsetof(ToolTipManager, ToolTipDelay) == 0x228);
GG_STATIC_ASSERT(offsetof(ToolTipManager, LastToolTipDelay) == 0x22C);
GG_STATIC_ASSERT(offsetof(ToolTipManager, unknown_230) == 0x230);
GG_STATIC_ASSERT(offsetof(ToolTipManager, ToolTips) == 0x234);
GG_STATIC_ASSERT(offsetof(ToolTipManager, Table) == 0x24C);
GG_STATIC_ASSERT(offsetof(ToolTipManager, Table) + sizeof(ToolTipTable) == 0x260);
// Exact sizeof(ToolTipManager) remains unasserted: retail constructs it as a
// base of a larger 0x268-byte singleton object, and no base boundary is pinned.

inline void ClearDimension(ToolTipManagerData& data)
{
    data.X = 0;
    data.Y = 0;
    data.Width = 0;
    data.Height = 0;
}

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) — StringTable::LoadString.
wchar_t* __fastcall StringTable_LoadString(const char* label, int* out,
                                           const char* file, int line);
// LIBRARY: GAMEMD 0x7CA405 (CRT wcslen).
extern "C" unsigned int __cdecl wcslen(const wchar_t* text);
// FUNCTION: GAMEMD 0x7CA422 (LIBRARY, CRT wcsncpy).
extern "C" wchar_t* __cdecl wcsncpy(wchar_t* dst, const wchar_t* src,
                                    unsigned int count);

#endif // GG_MATCH_UI_TOOLTIP_MANAGER_SHARED_H
