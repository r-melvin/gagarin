// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
//   No /GX. The by-value TypeList parameters of this file carry a
//   destructor, and under /GX cl registers an unwind frame to release them
//   if a callee throws: `PUSH -1; PUSH handler; PUSH FS:[0]; MOV FS:[0],ESP`
//   ahead of the frame. Retail's bodies open with a bare `SUB ESP,imm`, so
//   the retail build of this translation unit had exception handling off.
//   Measured: with /GX the 0x475C70 writer scores 13 of 247 bytes because
//   every offset after the prologue shifts; without it, 100%.
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x475F30 and
//   0x476240.

#include "ccini_class_type_list_methods.h"

// FUNCTION: GAMEMD 0x475C70
//
// Write a list of armour indices out as a comma-separated line of armour
// names. The list arrives by value, which is what lets the compiler hoist
// Items and Count into registers and walk the array by pointer; the release
// of that copy is the inlined free at the tail, after the write result has
// been parked in BL.
//
// PARTIAL, one instruction short of the retail stream. Every instruction of
// the body, both inlined strcats, the resolver call, the countdown loop and
// the inlined release are identical; the single residual is that retail
// shrink-wraps EBP as well as ESI, pushing both inside the count>0 arm and
// copying the count across with `MOV EBP,EAX`, while cl 8804 allocates the
// count straight into EBP and therefore pushes EBP in the prologue. That
// shifts every byte after offset 0x0B, so the byte oracle reads 20 of 247.
// Five materially different spellings were measured and none moved it: the
// plain `for (i = 0; i < list.Count; ++i)` over `list.Items[i]`; a named
// `count` local with a do-while pointer walk (the spelling below); the same
// with the guard reading `list.Count` directly so the two reads might not
// coalesce; an early `return` for the empty case, which is worse still
// because it duplicates the WriteString tail; and a forced-inline helper
// taking the count as a parameter of its own, which is what split the live
// range in the sibling reader and does not split it here. The single-exit
// lever that fixed 0x475A60 is the mirror of what is needed here and does
// not apply: this body already has one exit. What would fix it is anything
// that keeps the count out of a callee-saved register until after the test,
// since retail's `MOV EBP,EAX` is a live-range split cl declines to make.
bool CCINI_00475C70::WriteArmorList(const char* section, const char* key,
                                    TypeListInt list)
{
    char buffer[128] = "";

    int count = list.Count;

    if (count > 0) {
        const int* p = list.Items;
        int remaining = count;

        do {
            if (buffer[0] != '\0') {
                strcat(buffer, STR_00817F70);
            }

            const char* name = FUN_00751590(*p);

            strcat(buffer, name);
            ++p;
        } while (--remaining != 0);
    }

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x475D70
//
// Read a comma-separated list of decimal integers. Each token is parsed and
// appended; a token that is empty ends the walk, as does a missing key,
// which returns the caller's list unchanged. Both the list built here and
// the list that arrived by value are released inline at the tail, which is
// why the body ends in two interleaved copies of the same free.
TypeListInt CCINI_00475C70::ReadIntegerList(const char* section, const char* key,
                                            TypeListInt defaultValue)
{
    char buffer[512];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        TypeListInt list(0, 0);

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            int value = FUN_007C9BFD(token);

            list.AddItem(value);
        }

        return TypeListInt(list, 0);
    }

    return defaultValue;
}

// Append one resolved record to a list as a packed identity. Retail expands
// this twice, once per registry, and cross-jumps only the constructor call
// the two copies share, which is why each copy keeps a temporary of its own.
static __forceinline void AddTypeId(TypeListInt& list, AbstractType_006E6AB0* type)
{
    const TypeId_00476240& id = TypeId_00476240(type);

    int  value = id.ID;
    char rtti = id.RTTI;

    if (rtti != 0) {
        int packed = ((int)(unsigned char)rtti << 24) | (value & 0xFFFFFF);

        list.AddItem(packed);
    }
}

// FUNCTION: GAMEMD 0x476020
//
// Read a comma-separated list of record names into packed identities. Each
// token is looked up in the first registry and then, failing that, in the
// second; a name in neither is skipped, as is a record whose abstract-type
// tag comes back zero.
//
// PARTIAL, 132 of 540 bytes identical. The prologue, the token loop, the
// packing, the append, the return copy and both inlined releases are all
// the retail stream; the residual is one structural fact about the two
// registry arms. Retail keeps a separate identity temporary per arm (the
// two `LEA ECX` seats are eight bytes apart, which is what makes its frame
// 0x234 rather than 0x22C) and then cross-jumps everything from the shared
// `CALL 0x6E6AB0` onwards, so the body after the constructor exists once.
// cl 8804 does the opposite in both halves: it merges the two temporaries
// into one stack slot and then emits the tail twice, which shifts every
// stack displacement by eight and duplicates ninety bytes. Three materially
// different spellings were measured: the two arms written out with a
// forced-inline helper per arm (the spelling below, 132 bytes); the same
// with the append forced inline as well, which makes the two arms literally
// identical and still does not get them merged (125 bytes); and a reference
// bound to a conditional expression of two constructor temporaries, which
// is the shape that should produce two temporaries and does not (128
// bytes). The next thing to try is whether the tail can be made to end in a
// shape cl will cross-jump, since the temporary count follows from that
// rather than the other way round.
TypeListInt CCINI_00475C70::ReadTypeIdList(const char* section, const char* key,
                                           TypeListInt defaultValue)
{
    char buffer[512];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        TypeListInt list(0, 0);

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            int index = FUN_00523C90(token);

            if (index != -1) {
                AddTypeId(list, DAT_00A8E34C[index]);
            } else {
                index = FUN_00747370(token);

                if (index != -1) {
                    AddTypeId(list, DAT_00A83CE4[index]);
                }
            }
        }

        return TypeListInt(list, 0);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x475F30
//
// Write a list of plain integers out as a comma-separated line. The
// separator append and the value append are both the /O2 inlined strcat; the
// value itself goes through the C library formatter into a twelve-byte
// scratch buffer, which is what fixes the frame at 512 + 12 + 4 bytes.
bool CCINI_00475C70::WriteIntegerList(const char* section, const char* key,
                                      const TypeListInt* list)
{
    char temp[12];
    char buffer[512] = "";

    for (int i = 0; i < list->Count; ++i) {
        if (buffer[0] != '\0') {
            strcat(buffer, STR_00817F70);
        }

        sprintf(temp, STR_00817F6C, list->Items[i]);
        strcat(buffer, temp);
    }

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x476240
//
// Write a list of packed type identities out by name. Each element is split
// back into its abstract-type tag and its registry index, handed to the
// resolver at 0x6E7330 in ECX, and the record's inline ID text appended.
bool CCINI_00475C70::WriteTypeIdList(const char* section, const char* key,
                                     const TypeListInt* list)
{
    char buffer[512] = "";

    for (int i = 0; i < list->Count; ++i) {
        if (buffer[0] != '\0') {
            strcat(buffer, STR_00817F70);
        }

        TypeId_00476240 id;
        int packed = list->Items[i];

        id.RTTI = (char)(packed >> 24);
        id.ID = packed & 0xFFFFFF;

        ObjectType_00476240* type = FUN_006E7330(&id);

        strcat(buffer, type->ID);
    }

    return WriteString(section, key, buffer);
}
