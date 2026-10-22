// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Copy constructor (__thiscall, `ret 4`, returns this) of a record of two
// words (+0x00, +0x04) and a growable list of 0x18-byte entries at +0x08
// (count +0x08, capacity +0x0C, data +0x10: the list shape of
// window_list_collect_methods.cpp). Each entry holds an id (+0x00), two wide
// strings (+0x04, +0x08; default constructor 0x7B66C0, destructor 0x7B6760,
// assignment 0x7B68E0 -- the Obj_007B66D0 of
// core/wide_string_class.h, which does not declare the first two) and
// three words (+0x0C = -1, +0x10 = 0, +0x14 = -1 when default-built). The
// list's grow step (0x624810) and the entry copy constructor (0x6247D0) are
// called out of line here. No EH frame in retail although the staging entry
// has destructors, hence no /GX.
#include <new.h>
#include <string.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class WideString_006255F0
{
public:
    unsigned short* Buffer;   // +0x00

    // FUNCTION: GAMEMD 0x7B66C0 (decl; reloc)
    WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B6760 (decl; reloc)
    ~WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B68E0 (decl; reloc)
    WideString_006255F0& operator=(const WideString_006255F0& other);
};
GG_STATIC_ASSERT(sizeof(WideString_006255F0) == 4);

struct ListEntry_006255F0
{
    int Id;                       // +0x00
    WideString_006255F0 Name;     // +0x04
    WideString_006255F0 Text;     // +0x08
    int unknown_0C;               // +0x0C
    int unknown_10;               // +0x10
    int unknown_14;               // +0x14

    ListEntry_006255F0() { Id = 0; unknown_0C = -1; unknown_10 = 0; unknown_14 = -1; }
    // FUNCTION: GAMEMD 0x6247D0 (decl; reloc)
    ListEntry_006255F0(const ListEntry_006255F0& other);
};
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, Name) == 0x04);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, Text) == 0x08);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(ListEntry_006255F0) == 0x18);

class EntryList_006255F0
{
public:
    int Count;                   // +0x00
    int Capacity;                // +0x04
    ListEntry_006255F0* Data;    // +0x08

    EntryList_006255F0() : Count(0), Capacity(0), Data(NULL) {}

    // FUNCTION: GAMEMD 0x624810 (decl; reloc)
    void Grow();

    void Clear()
    {
        for (int index = 0; index < Count; index++) {
            Data[index].~ListEntry_006255F0();
        }
        Count = 0;
    }

    void Get(int index, ListEntry_006255F0& entry) const
    {
        if (index >= 0 && index < Count) {
            entry = Data[index];
        }
    }

    void Insert(int index, const ListEntry_006255F0& entry)
    {
        if (Count >= Capacity) Grow();
        if (index < Count) {
            memmove(&Data[index + 1], &Data[index], (Count - index) * sizeof(ListEntry_006255F0));
        }
        new (&Data[index]) ListEntry_006255F0(entry);
        Count++;
    }

    void Add(const ListEntry_006255F0& entry)
    {
        int index = Count;
        if (Count >= Capacity) Grow();
        Insert(index, entry);
    }
};

class EntryRecord_006255F0
{
public:
    int unknown_00;              // +0x00
    int unknown_04;              // +0x04
    EntryList_006255F0 List;     // +0x08

    EntryRecord_006255F0(const EntryRecord_006255F0& other);
};
GG_STATIC_ASSERT(offsetof(EntryRecord_006255F0, List) == 0x08);

// FUNCTION: GAMEMD 0x6255F0
EntryRecord_006255F0::EntryRecord_006255F0(const EntryRecord_006255F0& other) :
    unknown_00(other.unknown_00),
    unknown_04(other.unknown_04)
{
    ListEntry_006255F0 entry;
    List.Clear();
    for (int index = 0; index < other.List.Count; index++) {
        other.List.Get(index, entry);
        List.Add(entry);
    }
}
