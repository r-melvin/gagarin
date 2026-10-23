// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Walk of a sibling-linked list of child objects (first child at +0x54 of the
// owner, next sibling at +0x5D8 of a child): every child whose virtual slot 11
// returns 1 and whose type (virtual slot 33; identifier text at +0x24) equals a
// fixed name receives a pointer chosen by the index a global lookup object
// returns (stored at +0x6C4); finally the owner's flag at +0x80 is set. Two
// copies at different addresses with their own name and lookup object (the two
// globals are swapped between them); owner, child and type are placeholders and
// each address is verified separately.

#include <stddef.h>
#include "vector_class.h"
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT case-insensitive string compare (cdecl, two pointers).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

struct Type_006EE230 {
    unsigned char unknown_00[0x24];
    char unknown_24[1];
};
GG_STATIC_ASSERT(offsetof(Type_006EE230, unknown_24) == 0x24);

struct Child_006EE230 {
    virtual void vf_00();
    virtual void vf_01();
    virtual void vf_02();
    virtual void vf_03();
    virtual void vf_04();
    virtual void vf_05();
    virtual void vf_06();
    virtual void vf_07();
    virtual void vf_08();
    virtual void vf_09();
    virtual void vf_10();
    virtual int vf_11();
    virtual void vf_12();
    virtual void vf_13();
    virtual void vf_14();
    virtual void vf_15();
    virtual void vf_16();
    virtual void vf_17();
    virtual void vf_18();
    virtual void vf_19();
    virtual void vf_20();
    virtual void vf_21();
    virtual void vf_22();
    virtual void vf_23();
    virtual void vf_24();
    virtual void vf_25();
    virtual void vf_26();
    virtual void vf_27();
    virtual void vf_28();
    virtual void vf_29();
    virtual void vf_30();
    virtual void vf_31();
    virtual void vf_32();
    virtual Type_006EE230* vf_33();
    unsigned char unknown_04[0x5D4];
    Child_006EE230* unknown_5D8;
    unsigned char unknown_5DC[0xE8];
    void* unknown_6C4;
};
GG_STATIC_ASSERT(offsetof(Child_006EE230, unknown_5D8) == 0x5D8);
GG_STATIC_ASSERT(offsetof(Child_006EE230, unknown_6C4) == 0x6C4);

struct Lookup_00747370 {
    // FUNCTION: GAMEMD 0x747370 (decl; reloc) -- __thiscall, returns an index.
    int FUN_00747370();
};

extern VectorClass<void*> DAT_00A83CE0;

struct Owner_006EE230 {
    unsigned char unknown_00[0x54];
    Child_006EE230* unknown_54;
    unsigned char unknown_58[0x28];
    bool unknown_80;
    void FUN_006EE230(int a, int b);
    void FUN_006EE2A0(int a, int b);
};
GG_STATIC_ASSERT(offsetof(Owner_006EE230, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Owner_006EE230, unknown_80) == 0x80);

extern Lookup_00747370 DAT_00842DCC;
extern char DAT_00842DD4[];

// FUNCTION: GAMEMD 0x006EE230
void Owner_006EE230::FUN_006EE230(int a, int b)
{
    for (Child_006EE230* child = unknown_54; child != 0; child = child->unknown_5D8) {
        if (child->vf_11() == 1) {
            const char* name = child->vf_33()->unknown_24;
            if (strcmpi(name, DAT_00842DD4) == 0)
                child->unknown_6C4 = DAT_00A83CE0[DAT_00842DCC.FUN_00747370()];
        }
    }
    unknown_80 = true;
}

extern char DAT_00842DCC_name[];
extern Lookup_00747370 DAT_00842DD4_obj;

// FUNCTION: GAMEMD 0x006EE2A0
void Owner_006EE230::FUN_006EE2A0(int a, int b)
{
    for (Child_006EE230* child = unknown_54; child != 0; child = child->unknown_5D8) {
        if (child->vf_11() == 1) {
            const char* name = child->vf_33()->unknown_24;
            if (strcmpi(name, DAT_00842DCC_name) == 0)
                child->unknown_6C4 = DAT_00A83CE0[DAT_00842DD4_obj.FUN_00747370()];
        }
    }
    unknown_80 = true;
}
