// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit AbsType.cpp. The name is the source-file string at 0x817830
//   in retail gamemd.exe v1.001, passed by the assert at 0x410994 inside this object's
//   code range (0x410610-0x410e4f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   /Ob2: the scalar deleting destructor 0x410C30 carries this destructor
//   inline, while 0x4109C0 also exists out of line for the derived
//   destructors (0x726E00, 0x6E5CA0, ...). Both call ~AbstractClass 0x4101F0.
// AbstractTypeClass destructor: unregister from the type registry at 0xA8E968
// (RTTI DynamicVectorClass<AbstractTypeClass*> per the existing view), whose
// slot +0x10 finds the item's index.
//
// Native 0x410A60 selects the ID section, reads Name/UIName through a 1024-byte
// scratch buffer, then copies bounded temporaries into the fields. It resolves
// a nonempty UI label through 0x734E60 or uses the empty wide string.
//
// AbstractTypeClass body for slot 13 of its primary table 0x7E2000
// (abstract_type_class.h); the name is a placeholder.

#include "../_layout/abstract_type_class.h"
#include "mathtbl_init_shapes.h"
#include "../_layout/obj_004a1d30.h"

#include "free_and_compare_methods.h"
#include "../platform/ccini_class_methods.h"
#include <string.h>



// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"
#include <stdio.h>
#include "vector_add_item_free.h"
#include "bounded_text.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E1FC0
extern const double DAT_007E1FC0;
// GLOBAL: GAMEMD 0x8876D8
extern double DAT_008876D8;
// GLOBAL: GAMEMD 0x887710
extern double DAT_00887710;
// GLOBAL: GAMEMD 0x887728
extern double DAT_00887728;

// SYNTHETIC: GAMEMD 0x00410640
// dynamic initializer for DAT_00887728

// GLOBAL: GAMEMD 0x00887728
double DAT_00887728 = DAT_008876D8 / DAT_007E1FC0;

// SYNTHETIC: GAMEMD 0x00410660
// dynamic initializer for DAT_00887710

// GLOBAL: GAMEMD 0x00887710
double DAT_00887710 = DAT_007E1718 / DAT_00887728;

// SYNTHETIC: GAMEMD 0x004107E0
// GLOBAL: GAMEMD 0x00887718
MathTblCoord DAT_00887718;

// GLOBAL: GAMEMD 0xA8E968
extern DynamicVectorClass<AbstractTypeClass*> DAT_00A8E968;
// GLOBAL: GAMEMD 0x887734
extern const wchar_t DAT_00887734[];

// FUNCTION: GAMEMD 0x410800
AbstractTypeClass::AbstractTypeClass(const char* id)
{
    if (id == 0) {
        char generated[16];
        // STRING: GAMEMD 0x817828
        sprintf(generated, "%08X", this);
        GgBoundedText<25>(generated).CopyTo(ID);
    } else {
        GgBoundedText<25>(id).CopyTo(ID);
    }
    GgBoundedText<49>(ID).CopyTo(Name);
    UIName = DAT_00887734;
    DynamicVectorAddItemFree(&DAT_00A8E968, this);
}

// FUNCTION: GAMEMD 0x4109C0
AbstractTypeClass::~AbstractTypeClass()
{
    DynamicVectorClass<AbstractTypeClass*>* registry = &DAT_00A8E968;
    int index = registry->FindItemIndex(this);
    if (index != -1 && index < registry->Count) {
        --registry->Count;
        for (int i = index; i < registry->Count; ++i)
            registry->Items[i] = registry->Items[i + 1];
    }
}

// FUNCTION: GAMEMD 0x410A40
// `NEG EAX; SBB EAX,EAX; INC EAX` after the call is the bool form of `== 0`,
// so the comparison is an equality test rather than an ordering one. Argument
// order is (other, ID) — the pushes put the caller's string first.
bool AbstractTypeClass::FUN_00410A40(const char* other) const
{
    return FUN_007C8D20(other, ID) == 0;
}

// STRING: GAMEMD 0x817830 -- native source-file tag for the text lookup.
extern const char STR_00817830[];
// GLOBAL: GAMEMD 0x887734 -- shared empty wide string.
extern const wchar_t DAT_00887734[];
// FUNCTION: GAMEMD 0x734E60 (decl; reloc), ECX=label, EDX=output-or-null.
wchar_t* __fastcall StringTable_LoadString(const char* label, int* output,
                                               const char* file, int line);

GG_STATIC_ASSERT(sizeof(GgBoundedText<49>) == 49);
GG_STATIC_ASSERT(sizeof(GgBoundedText<32>) == 32);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->ID) == 25);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, UINameLabel) == 0x3D);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->UINameLabel) == 32);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, UIName) == 0x60);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->UIName) == 4);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, Name) == 0x64);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->Name) == 49);

// FUNCTION: GAMEMD 0x410A60
bool AbstractTypeClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (ini->GetSection(ID) != 0)
    {
        char buffer[1024];
        // STRING: GAMEMD 0x817854
        ini->FUN_00528A10(ID, "Name", Name, buffer, 49);
        GgBoundedText<49>(buffer).CopyTo(Name);
        // STRING: GAMEMD 0x81784C
        ini->FUN_00528A10(ID, "UIName", UINameLabel, buffer, 32);
        GgBoundedText<32>(buffer).CopyTo(UINameLabel);
        if (UINameLabel[0])
            UIName = StringTable_LoadString(UINameLabel, 0, STR_00817830, 0xD7);
        else
            UIName = DAT_00887734;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x410B90
bool AbstractTypeClass::vf_26(CCINIClass* ini)
{
    ini->Clear(ID, 0);
    // STRING: GAMEMD 0x817854
    ini->WriteString(ID, "Name", Name);
    if (UINameLabel[0])
    {
        // STRING: GAMEMD 0x81784C
        ini->WriteString(ID, "UIName", UINameLabel);
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x410BE0
// The base fields through AbstractClass's slot 13 (a direct call), then the
// ID, Name and the +0x3D text field into the checksum sink.
void AbstractTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1DB0(ID);
    crc->FUN_004A1DB0(Name);
    crc->FUN_004A1DB0(UINameLabel);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x410C20
// Empty function that pops its stack arguments. Vtable slot 24 of AbstractTypeClass (RTTI) and 27 derived vtable(s).
void AbstractTypeClass::vf_24(int value)
{
}

// SYNTHETIC: GAMEMD 0x410C30 -- compiler-generated scalar deleting destructor.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E1FC0
extern const double DAT_007E1FC0 = 60.0;
// GLOBAL: GAMEMD 0x817830
extern const char STR_00817830[] = "D:\\ra2mdpost\\AbsType.cpp";
// END defined globals
