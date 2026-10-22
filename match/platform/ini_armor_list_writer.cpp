// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Derived from the retail gamemd.exe v1.001 disassembly at 0x475C70.
//   No /GX: retail opens with a bare SUB ESP and has no unwind frame for the
//   by-value list parameter.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D - operator delete.
void __cdecl operator delete(void* p);

// FUNCTION: GAMEMD 0x751590 (decl; reloc) - armour index -> name text.
const char* __fastcall FUN_00751590(int index);

// A growable list of ints passed by value (0x24 bytes of arguments in total
// with the two strings: RET 0x24 proves the 0x1C-byte copy).
struct IntList_00475C70
{
    void* Vtable;            // +0x0000
    int*  Items;             // +0x0004
    int   Capacity;          // +0x0008
    bool  IsValid;           // +0x000C
    bool  IsAllocated;       // +0x000D
    char  unknown_0E[2];     // +0x000E
    int   Count;             // +0x0010
    int   Growth;            // +0x0014
    int   unknown_18;        // +0x0018

    ~IntList_00475C70()
    {
        if (Items != 0 && IsAllocated) {
            operator delete(Items);
        }
    }
};
GG_STATIC_ASSERT(offsetof(IntList_00475C70, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(IntList_00475C70, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(IntList_00475C70, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(IntList_00475C70) == 0x1C);   // RET 0x24 = 8 + 0x1C

class IniFile_00475C70
{
public:
    // FUNCTION: GAMEMD 0x528660 (decl) - write a string entry.
    bool WriteString(const char* section, const char* entry, const char* value);

    bool WriteArmorList(const char* section, const char* entry, IntList_00475C70 list);
};

// FUNCTION: GAMEMD 0x475C70
// Writes the list as a comma-separated line of armour names.
// PARTIAL 13.3% (positional; 89 of 90 instructions present): retail pushes EBP/ESI
// inside the count>0 arm and copies the count with MOV EBP,EAX; cl allocates the
// count straight into EBP and pushes EBP in the prologue, shifting the stream.
// Tried: for-loop over Items[i], hoisted count/items locals, operator[] with a
// named temp, strlen guard, this while form; flags /O1 /Ox /Op /Oy- /G5 /G6 /Gr /Ob2.
bool IniFile_00475C70::WriteArmorList(const char* section, const char* entry,
                                      IntList_00475C70 list)
{
    char buffer[128] = "";
    int i = 0;
    while (i < list.Count) {
        if (buffer[0] != '\0') {
            strcat(buffer, ",");
        }
        strcat(buffer, FUN_00751590(list.Items[i++]));
    }
    return WriteString(section, entry, buffer);
}
