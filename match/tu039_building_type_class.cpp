// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU039 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x45afa0-0x4660cf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// BuildingTypeClass entries (layout and evidence: types_building_type_class.h).
//
// Retail RTTI names VectorClass/DynamicVectorClass over Cell, BaseNodeClass, TPoint3D<int>, Point2D,
// TRect<int> and DirtyAreaStruct. Element layouts and compare shapes are read from the FindItemIndex,
// Slot5, Slot6 and SetCapacity bodies; field names are placeholders.
//
// Find-by-name walks, ordered ascending by retail address, written out longhand
// per the family rule.
//
// Buffer-holder deleting destructors, ordered ascending by retail address.
//
// The buffer-release template, ordered ascending by retail address.
//
// Constant-return and identity leaves, ordered ascending by retail address.
//
// FindOrAllocate, ordered ascending by retail address, written out longhand per
// the family rule.
//
// The whole body sits inside one positive guard so that the single `return 0`
// lands in the trailing block, where retail has it at the very end. Written as
// three early `return 0` statements it scores 15.8% - every rejection gets its
// own inline epilogue and everything after shifts.
//
//   Bytes compared against retail gamemd.exe v1.001 at each address below.
//
// Leaf accessors, ordered ascending by retail address.
//
// BuildingTypeClass::ReadINI (0x45FE50, 0x4C06 bytes): the rules-INI reader. Every key string, default and
// member offset was read from the retail instructions; the statement order is the retail order. The art-INI
// (global 0x887180) reads use the object's image name as their section; the rules reads use the object ID.
//
// The 18 animation slots are expanded by the local macros below, one invocation per slot. A function-style
// helper changes the generated code (the compiler stops expanding it after a few uses), so the repeated shape is
// kept as macros: read the three names (the damaged and garrisoned names fall back to the base name), then, if
// any name is set, the placement values and (where the slot has them) the four power flags. The four SuperAnim
// slots read their X and Y defaults from other slots' values (retail loads them from ActiveAnimFour, ActiveAnimTwo
// and ActiveAnimThree); TYPES_READ_ANIM_QUIRK reproduces that.
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include "types_building_shared.h"
#include "_layout/building_class.h"
#include "_layout/obj_004a1d30.h"
#include "_layout/swizzle_manager_class.h"
#include "display_objects_globals.h"
#include "shared_constants_globals.h"

// LIBRARY: GAMEMD 0x7C8B3D - CRT free.
extern "C" void __cdecl gg_free(void*);

// GLOBAL: GAMEMD 0x7E95C0 - CLSID of BuildingTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_BuildingType =
    { 0xAE8B33DB, 0x061C, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

#include "guarded_forward_methods.h"

#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "_layout/cell.h"

// VTABLE: GAMEMD 0x007E38D0 -- VectorClass<Cell>.
// VTABLE: GAMEMD 0x007E3890 -- DynamicVectorClass<Cell>.
template class VectorClass<Cell>;
template class DynamicVectorClass<Cell>;

#include "_layout/base_node_class.h"

// VTABLE: GAMEMD 0x007E38F0 -- VectorClass<BaseNodeClass>.
// VTABLE: GAMEMD 0x007E38B0 -- DynamicVectorClass<BaseNodeClass>.
template class VectorClass<BaseNodeClass>;
template class DynamicVectorClass<BaseNodeClass>;

#include "_layout/tpoint3d.h"

// VTABLE: GAMEMD 0x007E4638 -- VectorClass<TPoint3D<int>>.
template class VectorClass<TPoint3D<int> >;

#include "_layout/geometry2d.h"
template class DynamicVectorClass<Point2D>;

template class DynamicVectorClass<TRect<int> >;

#include "_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "_rt/gg_static_assert.h"


void __cdecl FUN_0045EC80();


#include "find_by_name_methods.h"
#include "ccini_class_methods.h"
#include "_layout/dib_surface.h"
#include "_layout/iso_tile_type_class.h"
// GLOBAL: GAMEMD 0x89DDC0 - the building-art surface.
extern DibSurface* DAT_0089DDC0;

#include "small_misc51_methods.h"


#include "buffer_holder_dtor_methods.h"

#include "buffer_release_methods.h"

#include "const_return_stub_methods.h"

#include "find_or_allocate_methods.h"

#include "leaf_accessor_methods.h"

#include "name_value_lookup_methods.h"

#include "small_misc50_methods.h"

#include <stdio.h>
#include <stdlib.h>
#include "types_building_shared.h"

#define TYPES_ANIM_NAME(INI, SECTION, FIELD, KEY)                           \
    (INI).ReadString(SECTION, KEY, TypesEmptyText, animName, 0x10);          \
    if (strlen(animName))                                                    \
        strcpy(FIELD, animName);

#define TYPES_ANIM_NAMES(INI, SECTION, ANIM, PREFIX)                         \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Anim, PREFIX)                       \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Damaged, PREFIX "Damaged")          \
    if (!strlen((ANIM).Damaged))                                             \
        strcpy((ANIM).Damaged, (ANIM).Anim);                                 \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Garrisoned, PREFIX "Garrisoned")    \
    if (!strlen((ANIM).Garrisoned))                                          \
        strcpy((ANIM).Garrisoned, (ANIM).Anim);

#define TYPES_ANIM_PRESENT(ANIM) \
    (strlen((ANIM).Anim) || strlen((ANIM).Damaged) || strlen((ANIM).Garrisoned))

#define TYPES_ANIM_VALUES(INI, SECTION, ANIM, PREFIX, DEFX, DEFY)            \
    (ANIM).X = (INI).ReadInteger(SECTION, PREFIX "X", DEFX);                     \
    (ANIM).Y = (INI).ReadInteger(SECTION, PREFIX "Y", DEFY);                     \
    (ANIM).ZAdjust = (INI).ReadInteger(SECTION, PREFIX "ZAdjust", (ANIM).ZAdjust); \
    (ANIM).YSort = (INI).ReadInteger(SECTION, PREFIX "YSort", (ANIM).YSort);

#define TYPES_ANIM_FLAGS(INI, SECTION, ANIM, PREFIX)                         \
    (ANIM).Powered = (INI).ReadBool(SECTION, PREFIX "Powered", (ANIM).Powered); \
    (ANIM).PoweredLight = (INI).ReadBool(SECTION, PREFIX "PoweredLight", (ANIM).PoweredLight); \
    (ANIM).PoweredEffect = (INI).ReadBool(SECTION, PREFIX "PoweredEffect", (ANIM).PoweredEffect); \
    (ANIM).PoweredSpecial = (INI).ReadBool(SECTION, PREFIX "PoweredSpecial", (ANIM).PoweredSpecial);

#define TYPES_READ_ANIM(ANIM, PREFIX)                                        \
    TYPES_ANIM_NAMES(DAT_00887180, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(DAT_00887180, ImageFile, ANIM, PREFIX, (ANIM).X, (ANIM).Y) \
        TYPES_ANIM_FLAGS(DAT_00887180, ImageFile, ANIM, PREFIX)               \
    }

#define TYPES_READ_ANIM_QUIRK(ANIM, PREFIX, DEFX, DEFY)                      \
    TYPES_ANIM_NAMES(DAT_00887180, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(DAT_00887180, ImageFile, ANIM, PREFIX, DEFX, DEFY)  \
        TYPES_ANIM_FLAGS(DAT_00887180, ImageFile, ANIM, PREFIX)               \
    }

#define TYPES_READ_ANIM_NOBOOLS(ANIM, PREFIX)                                \
    TYPES_ANIM_NAMES(DAT_00887180, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(DAT_00887180, ImageFile, ANIM, PREFIX, (ANIM).X, (ANIM).Y) \
    }

// The turret slot is read from the rules INI under the object ID.
#define TYPES_READ_ANIM_NOBOOLS_RULES(ANIM, PREFIX)                          \
    TYPES_ANIM_NAMES(*ini, ID, ANIM, PREFIX)                                 \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(*ini, ID, ANIM, PREFIX, (ANIM).X, (ANIM).Y)        \
    }

// CAPPED at 72.2% aligned-instruction match (4204 of 5819 retail instructions; 5861 compiled); 91.0% when
// register names are ignored. Observed delta, all of it layout and scheduling rather than missing statements:
//  - the stack frame is 12 bytes larger than retail's (sub esp,0x364 against 0x358), which shifts every
//    esp-relative local and the incoming argument by 12; with that shift removed the frame-text and
//    default-text buffers (0x140/0x180 in retail) are swapped;
//  - retail keeps `this` in EBP, the section pointer in EBX (ESI early on) and the reader in ESI (EDI early on);
//    this build puts `this` in EBX, the section pointer in EBP and the reader in ESI;
//  - the MuzzleFlash / DamageFireOffset loops: retail walks the member array through a pointer kept in a stack
//    slot and compares against a register holding 0xFFFF that is also the default's source; this build indexes
//    the array and compares against immediates (the pointer-walking form was tried and scored 71.6%);
//  - the RemoveOccupy / AddOccupy defaults and the coordinate defaults are built in different stack temporaries.
// Forms tried: (1) every buffer declared inside its own block (66.6%); (2) every buffer declared once at function
// scope, giving the key and name buffers retail's shared addresses (72.2%, kept); (3) the occupancy loops with a
// running pointer (71.6%, dropped). The anim-slot macros, the unmodified statement order and all key strings
// are as retail.

#include "font_bias_methods.h"
#include "beacon_manager_class_art_methods.h"
#include "smudge_type_class_load_methods.h"
// GLOBAL: GAMEMD 0x89DDC4 - the power-off overlay shape.
extern void* DAT_0089DDC4;
// GLOBAL: GAMEMD 0x89DDC8 - the repair wrench shape.
extern void* DAT_0089DDC8;

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E4530
extern const double DAT_007E4530;
// GLOBAL: GAMEMD 0x89C8B8
extern double DAT_0089C8B8;

// SYNTHETIC: GAMEMD 0x45AFD0
// GLOBAL: GAMEMD 0x89D360
double DAT_0089D360 = DAT_0089C8B8 / DAT_007E4530;

// SYNTHETIC: GAMEMD 0x45AFF0
// GLOBAL: GAMEMD 0x89C8F8
double DAT_0089C8F8 = DAT_007E1718 / DAT_0089D360;

// SYNTHETIC: GAMEMD 0x45B1B0 -- initialiser entry: tail-jumps to the table build
// SYNTHETIC: GAMEMD 0x45B1C0 -- table build: constructs the 22 foundation lists in place
// SYNTHETIC: GAMEMD 0x465D80 -- FoundationCell's empty default constructor, out of line for the vector-constructor calls
// GLOBAL: GAMEMD 0x89C900
// The foundation cell lists: 22 lists of 30 cells, each the listed offsets, the 0x7FFF end marker and
// default-constructed cells after it.
FoundationCell TypesFoundationCells[22][30] = {
    { FoundationCell(0, 0), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(0, 1), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(0, 1), FoundationCell(1, 1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(0, 1), FoundationCell(1, 1),
      FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(0, 1),
      FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(0, 1),
      FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(0, 2), FoundationCell(1, 2),
      FoundationCell(2, 2), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(0, 1),
      FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(0, 2), FoundationCell(1, 2),
      FoundationCell(2, 2), FoundationCell(0, 3), FoundationCell(1, 3), FoundationCell(2, 3),
      FoundationCell(0, 4), FoundationCell(1, 4), FoundationCell(2, 4), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(3, 0),
      FoundationCell(0, 1), FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(3, 1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(0, 1),
      FoundationCell(1, 1), FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(2, 2),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(0, 1), FoundationCell(0, 2), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(3, 0),
      FoundationCell(0, 1), FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(3, 1),
      FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(2, 2), FoundationCell(3, 2),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(0, 1), FoundationCell(0, 2), FoundationCell(0, 3),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(0, 1), FoundationCell(0, 2), FoundationCell(0, 3),
      FoundationCell(0, 4), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(0, 1), FoundationCell(1, 1),
      FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(0, 3), FoundationCell(1, 3),
      FoundationCell(0, 4), FoundationCell(1, 4), FoundationCell(0, 5), FoundationCell(1, 5),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(0, 1), FoundationCell(1, 1),
      FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(0, 3), FoundationCell(1, 3),
      FoundationCell(0, 4), FoundationCell(1, 4), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(3, 0),
      FoundationCell(4, 0), FoundationCell(0, 1), FoundationCell(1, 1), FoundationCell(2, 1),
      FoundationCell(3, 1), FoundationCell(4, 1), FoundationCell(0, 2), FoundationCell(1, 2),
      FoundationCell(2, 2), FoundationCell(3, 2), FoundationCell(4, 2), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(3, 0),
      FoundationCell(0, 1), FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(3, 1),
      FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(2, 2), FoundationCell(3, 2),
      FoundationCell(0, 3), FoundationCell(1, 3), FoundationCell(2, 3), FoundationCell(3, 3),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(0, 1),
      FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(0, 2), FoundationCell(1, 2),
      FoundationCell(2, 2), FoundationCell(0, 3), FoundationCell(1, 3), FoundationCell(2, 3),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(1, 0), FoundationCell(2, 0), FoundationCell(3, 0),
      FoundationCell(4, 0), FoundationCell(5, 0), FoundationCell(0, 1), FoundationCell(1, 1),
      FoundationCell(2, 1), FoundationCell(3, 1), FoundationCell(4, 1), FoundationCell(5, 1),
      FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(2, 2), FoundationCell(3, 2),
      FoundationCell(4, 2), FoundationCell(5, 2), FoundationCell(0, 3), FoundationCell(1, 3),
      FoundationCell(2, 3), FoundationCell(3, 3), FoundationCell(4, 3), FoundationCell(5, 3),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0x7FFF, 0x7FFF) }
};

// SYNTHETIC: GAMEMD 0x45C2F0 -- initialiser entry: tail-jumps to the table build
// SYNTHETIC: GAMEMD 0x45C300 -- table build: constructs the 22 outside lists in place
// GLOBAL: GAMEMD 0x89D368
// The cells just outside each foundation, in the same list layout.
FoundationCell TypesFoundationOutsideCells[22][30] = {
    { FoundationCell(0, 1), FoundationCell(-1, 1), FoundationCell(1, 1), FoundationCell(-1, 0),
      FoundationCell(1, 0), FoundationCell(0, -1), FoundationCell(-1, -1), FoundationCell(1, -1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 1), FoundationCell(1, 1), FoundationCell(-1, 1), FoundationCell(2, 1),
      FoundationCell(-1, 0), FoundationCell(2, 0), FoundationCell(0, -1), FoundationCell(1, -1),
      FoundationCell(-1, -1), FoundationCell(2, -1), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(-1, 2), FoundationCell(-1, 1),
      FoundationCell(1, 1), FoundationCell(-1, 0), FoundationCell(1, 0), FoundationCell(0, -1),
      FoundationCell(-1, -1), FoundationCell(1, -1), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(-1, 2), FoundationCell(2, 2),
      FoundationCell(-1, 1), FoundationCell(2, 1), FoundationCell(-1, 0), FoundationCell(2, 0),
      FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(-1, -1), FoundationCell(2, -1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 3), FoundationCell(1, 3), FoundationCell(-1, 3), FoundationCell(2, 3),
      FoundationCell(-1, 2), FoundationCell(2, 2), FoundationCell(-1, 1), FoundationCell(2, 1),
      FoundationCell(-1, 0), FoundationCell(2, 0), FoundationCell(0, -1), FoundationCell(1, -1),
      FoundationCell(-1, -1), FoundationCell(2, -1), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(2, 2), FoundationCell(-1, 2),
      FoundationCell(3, 2), FoundationCell(-1, 1), FoundationCell(3, 1), FoundationCell(-1, 0),
      FoundationCell(3, 0), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(2, -1),
      FoundationCell(-1, -1), FoundationCell(3, -1), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 3), FoundationCell(1, 3), FoundationCell(2, 3), FoundationCell(-1, 3),
      FoundationCell(3, 3), FoundationCell(-1, 2), FoundationCell(3, 2), FoundationCell(-1, 1),
      FoundationCell(3, 1), FoundationCell(-1, 0), FoundationCell(3, 0), FoundationCell(0, -1),
      FoundationCell(1, -1), FoundationCell(2, -1), FoundationCell(-1, -1), FoundationCell(3, -1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(2, -1),
      FoundationCell(3, -1), FoundationCell(-1, 0), FoundationCell(3, 0), FoundationCell(-1, 1),
      FoundationCell(3, 1), FoundationCell(-1, 2), FoundationCell(3, 2), FoundationCell(-1, 3),
      FoundationCell(3, 3), FoundationCell(-1, 4), FoundationCell(3, 4), FoundationCell(-1, 5),
      FoundationCell(0, 5), FoundationCell(1, 5), FoundationCell(2, 5), FoundationCell(3, 5),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 2), FoundationCell(1, 2), FoundationCell(2, 2), FoundationCell(3, 2),
      FoundationCell(-1, 2), FoundationCell(4, 2), FoundationCell(-1, 1), FoundationCell(4, 1),
      FoundationCell(-1, 0), FoundationCell(4, 0), FoundationCell(0, -1), FoundationCell(1, -1),
      FoundationCell(2, -1), FoundationCell(3, -1), FoundationCell(-1, -1), FoundationCell(4, -1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 0), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(-1, 0),
      FoundationCell(1, 0), FoundationCell(-1, 1), FoundationCell(1, 1), FoundationCell(-1, 2),
      FoundationCell(1, 2), FoundationCell(-1, 3), FoundationCell(0, 3), FoundationCell(1, 3),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(2, -1),
      FoundationCell(3, -1), FoundationCell(-1, 0), FoundationCell(3, 0), FoundationCell(-1, 1),
      FoundationCell(0, 1), FoundationCell(1, 1), FoundationCell(2, 1), FoundationCell(3, 1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 3), FoundationCell(1, 3), FoundationCell(2, 3), FoundationCell(-1, 3),
      FoundationCell(3, 3), FoundationCell(-1, 2), FoundationCell(3, 2), FoundationCell(-1, 1),
      FoundationCell(3, 1), FoundationCell(-1, 0), FoundationCell(3, 0), FoundationCell(0, -1),
      FoundationCell(1, -1), FoundationCell(2, -1), FoundationCell(-1, -1), FoundationCell(3, -1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(-1, 0),
      FoundationCell(1, 0), FoundationCell(-1, 1), FoundationCell(1, 1), FoundationCell(-1, 2),
      FoundationCell(1, 2), FoundationCell(-1, 3), FoundationCell(1, 3), FoundationCell(-1, 4),
      FoundationCell(0, 4), FoundationCell(1, 4), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(-1, 0),
      FoundationCell(1, 0), FoundationCell(-1, 1), FoundationCell(1, 1), FoundationCell(-1, 2),
      FoundationCell(1, 2), FoundationCell(-1, 3), FoundationCell(1, 3), FoundationCell(-1, 4),
      FoundationCell(1, 4), FoundationCell(-1, 5), FoundationCell(0, 5), FoundationCell(1, 5),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(2, -1),
      FoundationCell(-1, 0), FoundationCell(2, 0), FoundationCell(-1, 1), FoundationCell(2, 1),
      FoundationCell(-1, 2), FoundationCell(2, 2), FoundationCell(-1, 3), FoundationCell(2, 3),
      FoundationCell(-1, 5), FoundationCell(2, 5), FoundationCell(-1, 6), FoundationCell(0, 6),
      FoundationCell(1, 6), FoundationCell(2, 6), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(2, -1),
      FoundationCell(-1, 0), FoundationCell(2, 0), FoundationCell(-1, 1), FoundationCell(2, 1),
      FoundationCell(-1, 2), FoundationCell(2, 2), FoundationCell(-1, 3), FoundationCell(2, 3),
      FoundationCell(-1, 5), FoundationCell(0, 5), FoundationCell(1, 5), FoundationCell(2, 5),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(2, -1),
      FoundationCell(3, -1), FoundationCell(4, -1), FoundationCell(5, -1), FoundationCell(-1, 0),
      FoundationCell(5, 0), FoundationCell(-1, 1), FoundationCell(5, 1), FoundationCell(-1, 2),
      FoundationCell(5, 2), FoundationCell(-1, 3), FoundationCell(0, 3), FoundationCell(1, 3),
      FoundationCell(2, 3), FoundationCell(3, 3), FoundationCell(4, 3), FoundationCell(5, 3),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(-1, -1), FoundationCell(0, -1), FoundationCell(1, -1), FoundationCell(2, -1),
      FoundationCell(3, -1), FoundationCell(4, -1), FoundationCell(-1, 4), FoundationCell(0, 4),
      FoundationCell(1, 4), FoundationCell(2, 4), FoundationCell(3, 4), FoundationCell(4, 4),
      FoundationCell(-1, 0), FoundationCell(-1, 1), FoundationCell(-1, 2), FoundationCell(-1, 3),
      FoundationCell(-1, 4), FoundationCell(4, 0), FoundationCell(4, 1), FoundationCell(4, 2),
      FoundationCell(4, 3), FoundationCell(4, 4), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0, 4), FoundationCell(1, 4), FoundationCell(2, 4), FoundationCell(-1, 4),
      FoundationCell(3, 4), FoundationCell(-1, 2), FoundationCell(3, 2), FoundationCell(-1, 1),
      FoundationCell(3, 1), FoundationCell(-1, 0), FoundationCell(3, 0), FoundationCell(0, -1),
      FoundationCell(1, -1), FoundationCell(2, -1), FoundationCell(-1, -1), FoundationCell(3, -1),
      FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(2, -1), FoundationCell(0x7FFF, 0x7FFF) },
    { FoundationCell(0x7FFF, 0x7FFF) }
};

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45DD50
//
// The same scan over the smaller table. Written out rather than shared.
int FUN_0045DD50(const char* name)
{
    for (int i = 0; i < 6; i++) {
        if (FUN_007C8D20(DAT_00819288[i].Name, name) == 0) {
            return DAT_00819288[i].Value;
        }
    }

    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// PARTIAL: 82.9% positional, 90.2% aligned (348 of 386 retail instructions; 383 compiled). ChargedAnimTime
// defaults to 999.0f in retail (0x4479C000). Occupy-cell and muzzle/fire-offset points are built through the
// by-value point helper, as retail copies each pair from a temporary. Observed delta: retail reserves an
// 8-byte stack local and keeps three separate zero registers for the docking element; the anim-slot loop
// stores through EBP-based pointers with two zero registers where this build uses one; the array-registration
// tail differs by a jump and a register. Forms tried for the anim-slot loop: struct constructor (66.8%,
// dropped), memset/assignment variants (82.6% to 83.4% on the older shape).
// FUNCTION: GAMEMD 0x45DD90
BuildingTypeClass::BuildingTypeClass(const char* id)
    : TechnoTypeClass(id, 0), ArrayIndex(-1), FoundationData(0), Buildup(0),
      BuildupLoaded(false), BuildCat(0), HalfDamageSmokeLocation1(TypesZeroCoord),
      HalfDamageSmokeLocation2(TypesZeroCoord), GateCloseDelay(0.0), LightVisibility(5000),
      LightIntensity(0), LightRedTint(1000000), LightGreenTint(1000000), LightBlueTint(1000000),
      PrimaryFirePixelOffset(TypesMakePoint(0xFFFF, 0xFFFF)), SecondaryFirePixelOffset(TypesMakePoint(0xFFFF, 0xFFFF)), ToOverlay(0), ToTile(0), BuildupSound(-1), PackupSound(-1), CreateUnitSound(-1),
      UnitEnterSound(-1), UnitExitSound(-1), WorkingSound(-1), NotWorkingSound(-1), FreeUnit(0),
      SecretInfantry(0), SecretUnit(0), SecretBuilding(0), field_EB0(-1), Adjacent(3), Factory(0),
      TargetCoordOffset(0, 0, 0), ExitCoord(0, 0, 0), FoundationOutside(0), field_ED8(0), DeployFacing(0x80), PowerBonus(0), PowerDrain(0),
      ExtraPowerBonus(0), ExtraPowerDrain(0), Foundation(0), Height(2), OccupyHeight(2), MidPoint(0),
      DoorStages(0), Upgrades(0), DeployingAnim(0), UnderDoorAnim(0), Rubble(0), RoofDeployingAnim(0),
      UnderRoofDoorAnim(0), DoorAnim(0), SpecialZOverlay(0), SpecialZOverlayZAdjust(0), BibShape(0),
      BibShapeLoaded(false), NormalZAdjust(0), AntiAirValue(0), AntiArmorValue(0),
      AntiInfantryValue(0), ZShapePointMove(TypesMakePoint(0, 0)), unknown_1538(TypesZeroQuad), ExtraLight(0), TogglePower(true),
      HasSpotlight(false), IsTemple(false), IsPlug(false), HoverPad(false), BaseNormal(true),
      EligibileForAllyBuilding(false), EligibleForDelayKill(false), NeedsEngineer(false),
      CaptureEvaEvent(-1), ProduceCashStartup(0), ProduceCashAmount(0), ProduceCashDelay(0),
      InfantryGainSelfHeal(0), UnitsGainSelfHeal(0), RefinerySmokeFrames(25), Bib(false), Wall(false),
      Capturable(false), Powered(false), PoweredSpecial(false), Overpowerable(false), Spyable(false),
      CanC4(true), WantsExtraSpace(false), Unsellable(false), ClickRepairable(true),
      CanBeOccupied(false), CanOccupyFire(false), MaxNumberOccupants(0), ShowOccupantPips(true),
      QueueingCell(TypesMakePoint(0, 0)), NumberImpassableRows(-1), Radar(false), SpySat(false), ChargeAnim(false), IsAnimDelayedFire(false),
      SiloDamage(false), UnitRepair(false), UnitReload(false), Bunker(false), Cloning(false),
      Grinding(false), UnitAbsorb(false), InfantryAbsorb(false), SecretLab(false), DoubleThick(false),
      Flat(false), DockUnload(false), Recoilless(false), HasStupidGuardMode(true),
      BridgeRepairHut(false), Gate(false), SAM(false), ConstructionYard(false), NukeSilo(false),
      Refinery(false), Weeder(false), WeaponsFactory(false), LaserFencePost(false), LaserFence(false),
      FirestormWall(false), Hospital(false), Armory(false), EMPulseCannon(false), TickTank(false),
      TurretAnimIsVoxel(false), BarrelAnimIsVoxel(false), CloakGenerator(false), SensorArray(false),
      ICBMLauncher(false), Artillary(false), Helipad(false), OrePurifier(false), FactoryPlant(false),
      InfantryCostBonus(1.0f), UnitsCostBonus(1.0f), AircraftCostBonus(1.0f), BuildingsCostBonus(1.0f),
      DefensesCostBonus(1.0f), GDIBarracks(false), NODBarracks(false), YuriBarracks(false),
      ChargedAnimTime(999.0f), DelayedFireDelay(0), SuperWeapon(-1), SuperWeapon2(-1), GateStages(9),
      PowersUpToLevel(-1), DamagedDoor(false), InvisibleInGame(false), TerrainPalette(false),
      PlaceAnywhere(false), ExtraDamageStage(true), AIBuildThis(false), IsBaseDefense(false),
      CloakRadiusInCells(20), ConcentricRadialIndicator(false), PsychicDetectionRadius(0),
      BarrelStartPitch(0x40), DemandLoad(false), DemandLoadBuildup(false), FreeBuildup(false),
      IsThreatRatingNode(false), PrimaryFireDualOffset(false), ProtectWithWall(false),
      CanHideThings(true), CrateBeneath(false), LeaveRubble(false), CrateBeneathIsMoney(false),
      NumberOfDocks(1), DockingOffsets(1, 0)
{
    AbstractClass::vf_rtti_5();
    TypesAddItemEarlyOut(DAT_00A83C68, this);
    ArrayIndex = TypesFindIndex(DAT_00A83C68, this);
    BuildingAnimFrame[0].Frame = 0;
    BuildingAnimFrame[0].Count = 1;
    BuildingAnimFrame[0].Rate = 0;
    BuildingAnimFrame[1].Frame = 0;
    BuildingAnimFrame[1].Count = 1;
    BuildingAnimFrame[1].Rate = 0;
    BuildingAnimFrame[2].Frame = 0;
    BuildingAnimFrame[2].Count = 1;
    BuildingAnimFrame[2].Rate = 0;
    BuildingAnimFrame[4].Frame = 0;
    BuildingAnimFrame[4].Count = 1;
    BuildingAnimFrame[4].Rate = 0;
    BuildingAnimFrame[5].Frame = 0;
    BuildingAnimFrame[5].Count = 1;
    BuildingAnimFrame[5].Rate = 0;
    int i;
    for (i = 0; i < 21; ++i) {
        BuildingAnimStruct& anim = BuildingAnim[i];
        memset(anim.Anim, 0, sizeof(anim.Anim));
        memset(anim.Damaged, 0, sizeof(anim.Damaged));
        memset(anim.Garrisoned, 0, sizeof(anim.Garrisoned));
        anim.X = 0;
        anim.Y = 0;
        anim.ZAdjust = 0;
        anim.YSort = 0;
        anim.Powered = true;
        anim.PoweredLight = false;
        anim.PoweredEffect = false;
        anim.PoweredSpecial = false;
    }
    BuildupFile[0] = 0;
    PowersUpBuilding[0] = 0;
    TheaterSpecificID[0] = 0;
    VoxelBarrelFile[0] = 0;
    Trainable = false;
    DeployingAnimLoaded = false;
    UnderDoorAnimLoaded = false;
    RubbleLoaded = false;
    RoofDeployingAnimLoaded = false;
    UnderRoofDoorAnimLoaded = false;
    for (i = 0; i < 10; ++i) {
        MuzzleFlash[i] = TypesMakePoint(TypesZeroCoord.X, TypesZeroCoord.Y);
    }
    for (i = 0; i < 8; ++i) {
        DamageFireOffset[i] = TypesMakePoint(TypesZeroCoord.X, TypesZeroCoord.Y);
    }
    for (i = 0; i < 8; ++i) {
        RemoveOccupy[i] = TypesMakePoint(0xFFFF, 0xFFFF);
        AddOccupy[i] = TypesMakePoint(0xFFFF, 0xFFFF);
    }
    ImmuneToPsionics = true;
    ImmuneToPsionicWeapons = true;
    ImmuneToPoison = false;
    Parasiteable = false;
    Organic = false;
    ConsideredAircraft = false;
    Bunkerable = false;
    TPoint3D<int>* dock = DockingOffsets.Items;
    dock->X = 0;
    dock->Y = 0;
    dock->Z = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E520
BuildingTypeClass::BuildingTypeClass(const AbstractNoInit& noInit)
    : TechnoTypeClass(noInit), Buildup(0)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E580
// SYNTHETIC: GAMEMD 0x465DC0 -- the scalar deleting destructor expands this body.
BuildingTypeClass::~BuildingTypeClass()
{
    if (BuildupLoaded && Buildup != 0) {
        FUN_007C8B3D(Buildup);
        Buildup = 0;
        BuildupLoaded = false;
    }
    if (BibShapeLoaded && BibShape != 0) {
        FUN_007C8B3D(BibShape);
        BibShape = 0;
        BibShapeLoaded = false;
    }
    if (DeployingAnimLoaded && DeployingAnim != 0) {
        FUN_007C8B3D(DeployingAnim);
        DeployingAnim = 0;
        DeployingAnimLoaded = false;
    }
    if (UnderDoorAnimLoaded && UnderDoorAnim != 0) {
        FUN_007C8B3D(UnderDoorAnim);
        UnderDoorAnim = 0;
        UnderDoorAnimLoaded = false;
    }
    if (RubbleLoaded && Rubble != 0) {
        FUN_007C8B3D(Rubble);
        Rubble = 0;
        RubbleLoaded = false;
    }
    if (RoofDeployingAnimLoaded && RoofDeployingAnim != 0) {
        FUN_007C8B3D(RoofDeployingAnim);
        RoofDeployingAnim = 0;
        RoofDeployingAnimLoaded = false;
    }
    if (UnderRoofDoorAnimLoaded && UnderRoofDoorAnim != 0) {
        FUN_007C8B3D(UnderRoofDoorAnim);
        UnderRoofDoorAnim = 0;
        UnderRoofDoorAnimLoaded = false;
    }
    AnnounceExpiredPointer(1);
    DAT_00A83C68.RemoveItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E760
int FUN_0045E760(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x64, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E7B0
int FUN_0045E7B0(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x24, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E800
bool BuildingTypeClass::vf_32(const CellStruct* cell, HouseClass* owner)
{
    BuildingClass* building = new BuildingClass(this, owner);
    if (building) {
        CoordStruct coord;
        coord.X = cell->X * 256 + 128;
        coord.Y = cell->Y * 256 + 128;
        coord.Z = 0;
        return building->vf_54(coord, 0);
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E880
ObjectClass* BuildingTypeClass::vf_35(HouseClass* owner)
{
    return new BuildingClass(this, owner);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E8F0
//
// Load the image once and rebias every non-zero pixel by 0x41, in place. The
// global is both the "already loaded" flag and the result, so a second call does
// nothing.
//
// Zero pixels are left alone rather than being biased to a negative value — that
// is what makes 0 the transparent index and everything else an offset into a
// palette that starts at 'A'.
//
// PARTIAL (95.3%, 41/43) — identical multiset. One register delta remains: the
// inner load and store swap the SIB base and index roles (`[EDX+ECX]` against
// `[ECX+EDX]`) — the cheap addressing class in section 4.8. The global-store
// ordering delta recorded earlier no longer shows in the current build.
//
// Eleven further spellings were measured this pass and every one holds at
// 86.0% or drops. For the global store: the surface bound to a local with the
// global assigned from it and the load call made through the local; the same
// with the call made through the global; the store folded into an inline
// `Store(p)` helper whose result is the call's receiver; the scratch buffer
// bound to a `void*` local first; the load call lifted into an inline helper
// taking the surface as `Image_0045E8F0* const&` (the lever that resolved
// 0x40A260); and a volatile-qualified store of the global (81.4%). For the SIB
// roles: the reversed subscript `x[row]`, the pointer form `*(row + x)`, an
// unsigned loop index (81.4%), and the row rebound to a `char* const line`
// inside the loop. The rebias walk lifted into its own inline function scores
// 81.4%, so the two loops are one function in retail.
//
// The cursor and the row counter are separate locals copied from the pixel
// pointer and the height, and that is load-bearing rather than style. Retail
// copies both (`MOV EDX,EAX; MOV EDI,ECX` at 0x45E94C) because the originals stay
// live; walking the returned pointer directly and counting down the height
// in place removes both copies and scores 16.3%. Two extra locals, seventy
// points.
void FUN_0045E8F0()
{
    char scratch[0x10];

    if (DAT_0089DDBC != 0) {
        return;
    }

    DAT_0089DDBC = (Image_0045E8F0*)FUN_005B40B0(DAT_008193F4, 0);
    DAT_0089DDBC->FUN_0069E7E0(scratch, 0);
    char* pixels = DAT_0089DDBC->FUN_0069E740(0);

    int width = DAT_0089DDBC->Width;
    int height = DAT_0089DDBC->Height;
    if (height <= 0) {
        return;
    }

    char* row = pixels;
    int rows = height;
    do {
        for (int x = 0; x < width; x++) {
            if (row[x] != 0) {
                row[x] = row[x] - 0x41;
            }
        }
        row += width;
        rows--;
    } while (rows != 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The rate local is declared before the frame count is read, which keeps the shape pointer out of EAX.
// FUNCTION: GAMEMD 0x45E970
void __fastcall FUN_0045E970(int theater)
{
    FUN_0045E8F0();
    DAT_0089DDC4 = FUN_005B40B0("POWEROFF.SHP", 0);
    DAT_0089DDC8 = FUN_005B40B0("WRENCH.SHP", 0);
    int radius = 0;
    int i;
    for (i = 0; i < DAT_00A83C78; i++) {
        BuildingTypeClass* type = (BuildingTypeClass*)DAT_00A83C6C[i];
        signed char r = type->CloakRadiusInCells;
        if (radius <= r) {
            radius = r;
        }
        if (type->Theater != 0) {
            char path[0x200];
            if (type->DemandLoad == 0) {
                _makepath(path, 0, 0, type->ImageFile, DAT_007E1B78[theater].Extension);
                type->Image = FUN_005B40B0(path, 0);
            } else if (type->Image != 0) {
                FUN_007C8B3D(type->Image);
                type->Image = 0;
                type->ImageAllocated = 0;
            }
            if (type->DemandLoadBuildup == 0) {
                _makepath(path, 0, 0, type->BuildupFile, DAT_007E1B78[theater].Extension);
                type->Buildup = (SHPStruct*)FUN_005B40B0(path, 0);
            } else if (type->Buildup != 0) {
                FUN_007C8B3D(type->Buildup);
                type->Buildup = 0;
                type->BuildupLoaded = 0;
            }
            if (type->Buildup != 0) {
                int rate = 1;
                int frames = ((Shp_004309D0*)type->Buildup)->Frames;
                if (frames != 0) {
                    rate = 0x4B / frames;
                }
                type->BuildingAnimFrame[0].Frame = 0;
                type->BuildingAnimFrame[0].Count = frames;
                type->BuildingAnimFrame[0].Rate = rate;
            }
        } else if (type->NewTheater != 0) {
            if (type->DemandLoad != 0 && type->Image != 0) {
                FUN_007C8B3D(type->Image);
                type->Image = 0;
                type->ImageAllocated = 0;
            }
            if (type->DemandLoadBuildup != 0 && type->Buildup != 0) {
                FUN_007C8B3D(type->Buildup);
                type->Buildup = 0;
                type->BuildupLoaded = 0;
            }
            type->StampTheater(theater);
        }
    }
    if (radius != 0) {
        if (DAT_0089DDC0 != 0) {
            delete DAT_0089DDC0;
        }
        DAT_0089DDC0 = new DibSurface(radius + 16, radius + 16, 1, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45EBD0
CoordStruct BuildingTypeClass::vf_30()
{
    int width;
    int height;
    Obj_0069E430* shape = static_cast<Obj_0069E430*>(vf_39());
    if (shape) {
        RectangleStruct rect = shape->FUN_0069E7E0(0);
        width = rect.Width;
        height = rect.Height;
    } else {
        width = 0;
        height = 0;
    }
    CoordStruct coord;
    coord.X = width;
    coord.Y = width;
    coord.Z = height;
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45EC20
// The function-local static (guard bit 0 of 0x89C890, cell at 0x89C8E8) is built through a temporary;
// its destructor stub is the bare RET at 0x45EC80 (compiler-generated atexit entry).
CellStruct* BuildingTypeClass::vf_36(int arg)
{
    static TypesStaticCell list = TypesMakeStaticCell(0x7FFF, 0x7FFF);
    CellStruct* data = FoundationData;
    if (data == 0)
        data = &list;
    return data;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45EC80
// Empty function.
void __cdecl FUN_0045EC80()
{
}

#include "_layout/rules_class.h"
#include "_layout/aircraft_type_class.h"
#include "_layout/unit_type_class.h"

// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern RulesClass* DAT_008871E0;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45ECE0
int BuildingTypeClass::vf_29()
{
    int pips = FoundationWidth[Foundation] * 60 / 8;
    switch (PipScale) {
    case 2:
        if (Weeder) {
            int limit = DAT_008871E0->WeedCapacity;
            if (limit < 0)
                return 0;
            if (limit > pips)
                return pips;
            return limit;
        } else {
            int limit = Storage;
            if (limit < 0)
                return 0;
            if (limit > pips)
                return pips;
            return limit;
        }
    case 4:
        return pips;
    }
    return TechnoTypeClass::vf_29();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45ED50
//
// Start from the base budget, and when this object is the one the host's pair
// points at — and the host is not in the suppressed state — take off half the
// two measurements. Whatever the trailing object measures comes off as well,
// and that result is clamped at zero; the early exit is not clamped.
//
// PARTIAL (56.6%, 30/53). Everything up to and including the pair adjustment is
// byte-exact, including the callee-saved naming (budget in ESI, the pair entry
// in EDI). The whole residual is the trailing object: retail parks it in EBX —
// reusing the register that held `this`, which dies at that load — and pays a
// `MOV ECX,EBX` before the slot call, where VC6 loads it straight into ECX and
// skips the copy. Everything after is the same instruction stream renamed.
//
// The ESI/EDI half was fixed by phrasing: subtracting into a fresh local
// (`int r = budget - ...`) rather than back into `budget` lowers the budget
// variable's use count, and VC6 hands ESI to the lighter of the two. Written as
// `budget -= ...; return budget > 0 ? budget : 0` the names come out swapped
// (47.2%).
//
// The EBX half is not source-selectable so far. Rejected, all 56.6% or worse:
// a `this`-walking local reassigned to the trailing object; a `for`/`while`
// whose induction variable starts at `this` and whose body always returns; a
// reference instead of a pointer; re-reading `this->At_EA0` twice and letting
// CSE pick the register; a static inline wrapper around the slot call; a
// genuine `virtual` at slot 43 instead of the member-pointer idiom; declaring
// the locals `register`; and the flag sweep /G3 /G5 /G6 /GB /Gr /Gd /Zp1 /Oa
// /Ow /Gf /Ob0 /Ob2 /Ox (all identical). /O1 /Os and dropping /Oy change the
// whole function and score 0%.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides, none sunk), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
int BuildingTypeClass::vf_43()
{
    int budget = TechnoTypeClass::vf_43();
    RulesClass* host = DAT_008871E0;
    const AircraftTypeClass** pair = host->PadAircraft.Items;
    AircraftTypeClass* first = const_cast<AircraftTypeClass*>(pair[0]);

    if (this == *first->Dock.Items && host->SeparateAircraft == 0) {
        AircraftTypeClass* second = const_cast<AircraftTypeClass*>(pair[1]);

        budget += -((second->vf_43()
                     + first->vf_43()) / 2);
    }

    UnitTypeClass* trailing = FreeUnit;
    if (trailing != 0) {
        int result = budget - trailing->vf_43();
        return result > 0 ? result : 0;
    }

    return budget;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// CAPPED at 20.3% (12 of 59 instructions by position; the instruction sequence has the same shape). Observed
// delta: register assignment only. Retail holds `this` in EBX, the argument in EBP, the running cost in ESI and
// the first PadAircraft type in EDI and evaluates the second type's cost first, spilling it to [esp+0x14]; this
// build holds the argument in EBX, `this` in EDI/EBP and calls the first type first. Forms tried: seven
// (cached rules pointer or not, second-first and first-first call order, an explicit temporary for each cost,
// early-return and fall-through tails, `freeUnit` loaded early or late).
// FUNCTION: GAMEMD 0x45EDD0
int BuildingTypeClass::vf_33(HouseClass* house)
{
    int cost = TechnoTypeClass::vf_33(house);
    RulesClass* host = DAT_008871E0;
    const AircraftTypeClass** padAircraft = host->PadAircraft.Items;
    AircraftTypeClass* first = const_cast<AircraftTypeClass*>(padAircraft[0]);
    if (this == *first->Dock.Items && host->SeparateAircraft == 0) {
        int a = const_cast<AircraftTypeClass*>(padAircraft[1])->vf_33(house);
        int b = first->vf_33(house);
        cost += (a + b) / 2;
    }
    UnitTypeClass* freeUnit = FreeUnit;
    if (freeUnit) {
        cost += freeUnit->vf_33(house);
        return cost <= 0 ? 0 : cost;
    }
    return cost;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45F040
void* BuildingTypeClass::vf_39()
{
    if (Image == 0 && DemandLoad) {
        const char* theater = TheaterSpecificID;
        if (theater[0]) {
            TypesFileView file(theater);
            file.Open(0);
            Image = file.ReadShape();
            if (Image) {
                ImageAllocated = true;
            } else {
                char name[260];
                strncpy(name, theater, 0x13);
                TypesStampGenericTheater(name);
                TypesFileView file2(name);
                Image = file2.ReadShape();
                if (Image)
                    ImageAllocated = true;
            }
        }
        return Image;
    }
    return Image;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45F160
//
// Same skeleton as 0x45F1D0 and the same trailing-block layout - retail's `JNZ`
// jumps forward to the cached case - but both successful paths answer true and
// the value written is a constant rather than the measurement. Written out
// longhand rather than shared with the sibling, per the family rule.
bool Obj_0045F1D0::FUN_0045F160(Shape_0045F1D0** shape, int* bias)
{
    if (Enabled && shape != 0) {
        Shape_0045F1D0* cached = Cached;

        if (cached == 0) {
            Shape_0045F1D0* fresh = vt_09C();

            *shape = fresh;

            if (fresh != 0) {
                if (fresh->Height / 2 > 3) {
                    *bias = 3;

                    return true;
                }
            }
        } else {
            *shape = cached;
            *bias  = 0;

            return true;
        }
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45F1D0
bool Obj_0045F1D0::FUN_0045F1D0(Shape_0045F1D0** shape, int* half)
{
    if (Enabled && shape != 0) {
        Shape_0045F1D0* cached = Cached;

        // The cached path is the *trailing* block: retail's `JNZ` at 0x45F1EB
        // jumps forward to it, so the fresh lookup is the fall-through and the
        // guard is written as `cached == 0`. The other way round scores 21.6%.
        if (cached == 0) {
            Shape_0045F1D0* fresh = vt_09C();

            *shape = fresh;

            if (fresh != 0) {
                int height = fresh->Height / 2;

                if (height > 3) {
                    *half = height + 3;

                    return true;
                }
            }
        } else {
            *shape = cached;
            *half  = cached->Height / 2;
        }
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45FE50
bool BuildingTypeClass::vf_25(CCINIClass* ini)
{
    int i;
    CoordStruct coordDefault;
    char animName[0x80];
    Point2D pointDefault;
    Point2D pointDefault2;
    char name[0x80];
    char frameText[0x40];
    char frameDefault[0x40];
    char dockKey[0x20];
    char yKey[0x40];
    char sortKey[0x40];
    char animKey[0x40];
    char damagedKey[0x40];
    char zKey[0x40];
    char xKey[0x40];

    ini->Reset();
    if (TechnoTypeClass::vf_25(ini)) {
        BuildCat = ini->FUN_00475060(ID, "BuildCat", BuildCat);
        AntiInfantryValue = ini->ReadInteger(ID, "AntiInfantryValue", AntiInfantryValue);
        AntiArmorValue = ini->ReadInteger(ID, "AntiArmorValue", AntiArmorValue);
        AntiAirValue = ini->ReadInteger(ID, "AntiAirValue", AntiAirValue);
        HasSpotlight = ini->ReadBool(ID, "HasSpotlight", HasSpotlight);
        HalfDamageSmokeLocation1 = ini->ReadCoord(ID, "HalfDamageSmokeLocation1", HalfDamageSmokeLocation1);
        HalfDamageSmokeLocation2 = ini->ReadCoord(ID, "HalfDamageSmokeLocation2", HalfDamageSmokeLocation2);
        Radar = ini->ReadBool(ID, "Radar", Radar);
        SpySat = ini->ReadBool(ID, "SpySat", SpySat);
        SpeedType = ini->ReadBool(ID, "WaterBound", SpeedType == 5) ? 5 : -1;
        Adjacent = ini->ReadInteger(ID, "Adjacent", Adjacent);
        Capturable = ini->ReadBool(ID, "Capturable", Capturable);
        Powered = ini->ReadBool(ID, "Powered", Powered);
        PoweredSpecial = ini->ReadBool(ID, "PoweredSpecial", PoweredSpecial);
        Overpowerable = ini->ReadBool(ID, "Overpowerable", Overpowerable);
        Spyable = ini->ReadBool(ID, "Spyable", Spyable);
        CanC4 = ini->ReadBool(ID, "CanC4", CanC4);
        WantsExtraSpace = ini->ReadBool(ID, "WantsExtraSpace", WantsExtraSpace);
        Bib = ini->ReadBool(ID, "Bib", Bib);
        Unsellable = ini->ReadBool(ID, "Unsellable", Unsellable);
        ClickRepairable = ini->ReadBool(ID, "ClickRepairable", ClickRepairable);
        CanBeOccupied = ini->ReadBool(ID, "CanBeOccupied", CanBeOccupied);
        CanOccupyFire = ini->ReadBool(ID, "CanOccupyFire", CanOccupyFire);
        ShowOccupantPips = ini->ReadBool(ID, "ShowOccupantPips", ShowOccupantPips);
        MaxNumberOccupants = ini->ReadInteger(ID, "MaxNumberOccupants", MaxNumberOccupants);
        NumberImpassableRows = ini->ReadInteger(ID, "NumberImpassableRows", NumberImpassableRows);
        ProduceCashStartup = ini->ReadInteger(ID, "ProduceCashStartup", ProduceCashStartup);
        ProduceCashAmount = ini->ReadInteger(ID, "ProduceCashAmount", ProduceCashAmount);
        ProduceCashDelay = ini->ReadInteger(ID, "ProduceCashDelay", ProduceCashDelay);
        InfantryGainSelfHeal = ini->ReadInteger(ID, "InfantryGainSelfHeal", InfantryGainSelfHeal);
        UnitsGainSelfHeal = ini->ReadInteger(ID, "UnitsGainSelfHeal", UnitsGainSelfHeal);
        RefinerySmokeFrames = ini->ReadInteger(ID, "RefinerySmokeFrames", RefinerySmokeFrames);
        BaseNormal = ini->ReadBool(ID, "BaseNormal", BaseNormal);
        EligibileForAllyBuilding = ini->ReadBool(ID, "EligibileForAllyBuilding", EligibileForAllyBuilding);
        EligibleForDelayKill = ini->ReadBool(ID, "EligibleForDelayKill", EligibleForDelayKill);
        NeedsEngineer = ini->ReadBool(ID, "NeedsEngineer", NeedsEngineer);
        CaptureEvaEvent = ini->FUN_00474FA0(ID, "CaptureEvaEvent", CaptureEvaEvent);
        ProtectWithWall = ini->ReadBool(ID, "ProtectWithWall", ProtectWithWall);
        for (i = 0; i < MaxNumberOccupants; ++i) {
            char number[0x10];
            strcpy(animName, "MuzzleFlash");
            itoa(i, number, 10);
            strcat(animName, number);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            MuzzleFlash[i] = DAT_00887180.ReadPoint(ImageFile, animName, pointDefault);
            if (MuzzleFlash[i].X == 0xFFFF && MuzzleFlash[i].Y == 0xFFFF) {
                MuzzleFlash[i].X = 0;
                MuzzleFlash[i].Y = 0;
            }
        }
        for (i = 0; i < 8; ++i) {
            char number[0x10];
            strcpy(animName, "DamageFireOffset");
            itoa(i, number, 10);
            strcat(animName, number);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            DamageFireOffset[i] = DAT_00887180.ReadPoint(ImageFile, animName, pointDefault);
            if (DamageFireOffset[i].X == 0xFFFF && DamageFireOffset[i].Y == 0xFFFF) {
                DamageFireOffset[i].X = TypesZeroCoord.X;
                DamageFireOffset[i].Y = TypesZeroCoord.Y;
                break;
            }
        }
        Wall = ini->ReadBool(ID, "Wall", Wall);
        Weeder = ini->ReadBool(ID, "Weeder", Weeder);
        Helipad = ini->ReadBool(ID, "Helipad", Helipad);
        OrePurifier = ini->ReadBool(ID, "OrePurifier", OrePurifier);
        FactoryPlant = ini->ReadBool(ID, "FactoryPlant", FactoryPlant);
        Factory = ini->FUN_00474FF0(ID, "Factory", Factory);
        {
            UnitTypeClass* old = FreeUnit;
            FreeUnit = ini->ReadString(ID, "FreeUnit", TypesEmptyText, name, 0x80) ? TypesFindUnitType(name) : old;
        }
        HoverPad = ini->ReadBool(ID, "HoverPad", HoverPad);
        IsTemple = ini->ReadBool(ID, "IsTemple", IsTemple);
        IsPlug = ini->ReadBool(ID, "IsPlug", IsPlug);
        {
            InfantryTypeClass* old = SecretInfantry;
            SecretInfantry = ini->ReadString(ID, "SecretInfantry", TypesEmptyText, name, 0x80) ? TypesFindInfantryType(name) : old;
        }
        {
            UnitTypeClass* old = SecretUnit;
            SecretUnit = ini->ReadString(ID, "SecretUnit", TypesEmptyText, name, 0x80) ? TypesFindUnitType(name) : old;
        }
        {
            BuildingTypeClass* old = SecretBuilding;
            SecretBuilding = ini->ReadString(ID, "SecretBuilding", TypesEmptyText, name, 0x80) ? TypesFindBuildingType(name, &DAT_00A83C68) : old;
        }
        InfantryCostBonus = (float)ini->ReadDouble(ID, "InfantryCostBonus", InfantryCostBonus);
        UnitsCostBonus = (float)ini->ReadDouble(ID, "UnitsCostBonus", UnitsCostBonus);
        AircraftCostBonus = (float)ini->ReadDouble(ID, "AircraftCostBonus", AircraftCostBonus);
        BuildingsCostBonus = (float)ini->ReadDouble(ID, "BuildingsCostBonus", BuildingsCostBonus);
        DefensesCostBonus = (float)ini->ReadDouble(ID, "DefensesCostBonus", DefensesCostBonus);
        TogglePower = ini->ReadBool(ID, "TogglePower", TogglePower);
        {
            int sound = BuildupSound;
            if (ini->ReadString(ID, "BuildupSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = BuildupSound;
            }
            BuildupSound = sound;
        }
        {
            int sound = PackupSound;
            if (ini->ReadString(ID, "PackupSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = PackupSound;
            }
            PackupSound = sound;
        }
        {
            int sound = CreateUnitSound;
            if (ini->ReadString(ID, "CreateUnitSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = CreateUnitSound;
            }
            CreateUnitSound = sound;
        }
        {
            int sound = UnitExitSound;
            if (ini->ReadString(ID, "UnitExitSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = UnitExitSound;
            }
            UnitExitSound = sound;
        }
        {
            int sound = UnitEnterSound;
            if (ini->ReadString(ID, "UnitEnterSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = UnitEnterSound;
            }
            UnitEnterSound = sound;
        }
        {
            int sound = WorkingSound;
            if (ini->ReadString(ID, "WorkingSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = WorkingSound;
            }
            WorkingSound = sound;
        }
        {
            int sound = NotWorkingSound;
            if (ini->ReadString(ID, "NotWorkingSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = NotWorkingSound;
            }
            NotWorkingSound = sound;
        }
        UnitRepair = ini->ReadBool(ID, "UnitRepair", UnitRepair);
        UnitReload = ini->ReadBool(ID, "UnitReload", UnitReload);
        Bunker = ini->ReadBool(ID, "Bunker", Bunker);
        Cloning = ini->ReadBool(ID, "Cloning", Cloning);
        Grinding = ini->ReadBool(ID, "Grinding", Grinding);
        UnitAbsorb = ini->ReadBool(ID, "UnitAbsorb", UnitAbsorb);
        InfantryAbsorb = ini->ReadBool(ID, "InfantryAbsorb", InfantryAbsorb);
        SecretLab = ini->ReadBool(ID, "SecretLab", SecretLab);
        DockUnload = ini->ReadBool(ID, "DockUnload", DockUnload);
        Gate = ini->ReadBool(ID, "Gate", Gate);
        SAM = ini->ReadBool(ID, "SAM", SAM);
        ConstructionYard = ini->ReadBool(ID, "ConstructionYard", ConstructionYard);
        NukeSilo = ini->ReadBool(ID, "NukeSilo", NukeSilo);
        Refinery = ini->ReadBool(ID, "Refinery", Refinery);
        WeaponsFactory = ini->ReadBool(ID, "WeaponsFactory", WeaponsFactory);
        LaserFencePost = ini->ReadBool(ID, "LaserFencePost", LaserFencePost);
        LaserFence = ini->ReadBool(ID, "LaserFence", LaserFence);
        FirestormWall = ini->ReadBool(ID, "FirestormWall", FirestormWall);
        Hospital = ini->ReadBool(ID, "Hospital", Hospital);
        Armory = ini->ReadBool(ID, "Armory", Armory);
        GDIBarracks = ini->ReadBool(ID, "GDIBarracks", GDIBarracks);
        NODBarracks = ini->ReadBool(ID, "NODBarracks", NODBarracks);
        YuriBarracks = ini->ReadBool(ID, "YuriBarracks", YuriBarracks);
        EMPulseCannon = ini->ReadBool(ID, "EMPulseCannon", EMPulseCannon);
        TickTank = ini->ReadBool(ID, "TickTank", TickTank);
        ChargedAnimTime = (float)ini->ReadDouble(ID, "ChargedAnimTime", ChargedAnimTime);
        SuperWeapon = ini->FUN_00474F50(ID, "SuperWeapon", SuperWeapon);
        SuperWeapon2 = ini->FUN_00474F50(ID, "SuperWeapon2", SuperWeapon2);
        CloakGenerator = ini->ReadBool(ID, "CloakGenerator", CloakGenerator);
        SensorArray = ini->ReadBool(ID, "SensorArray", SensorArray);
        CloakRadiusInCells = (unsigned char)ini->ReadInteger(ID, "CloakRadiusInCells", (signed char)CloakRadiusInCells);
        PsychicDetectionRadius = ini->ReadInteger(ID, "PsychicDetectionRadius", PsychicDetectionRadius);
        BarrelStartPitch = ini->ReadInteger(ID, "BarrelStartPitch", BarrelStartPitch >> 5) << 5;
        DeployFacing = ini->ReadInteger(ID, "DeployFacing", DeployFacing >> 5) << 5;
        LightVisibility = ini->ReadInteger(ID, "LightVisibility", LightVisibility);
        LightIntensity = (int)(ini->ReadDouble(ID, "LightIntensity", (double)(LightIntensity / 1000)) * 1000.0 + 0.1);
        LightRedTint = (int)(ini->ReadDouble(ID, "LightRedTint", (double)(LightRedTint / 1000)) * 1000.0 + 0.1);
        LightGreenTint = (int)(ini->ReadDouble(ID, "LightGreenTint", (double)(LightGreenTint / 1000)) * 1000.0 + 0.1);
        LightBlueTint = (int)(ini->ReadDouble(ID, "LightBlueTint", (double)(LightBlueTint / 1000)) * 1000.0 + 0.1);
        GateCloseDelay = ini->ReadDouble(ID, "GateCloseDelay", GateCloseDelay);
        InvisibleInGame = ini->ReadBool(ID, "InvisibleInGame", InvisibleInGame);
        {
            ini->ReadString(ID, "PowersUpBuilding", TypesEmptyText, animName, 0x18);
            if (strlen(animName))
                strcpy(PowersUpBuilding, animName);
        }
        PowersUpToLevel = ini->ReadInteger(ID, "PowersUpToLevel", PowersUpToLevel);
        BridgeRepairHut = ini->ReadBool(ID, "BridgeRepairHut", BridgeRepairHut);
        HasStupidGuardMode = ini->ReadBool(ID, "HasStupidGuardMode", HasStupidGuardMode);
        CrateBeneath = ini->ReadBool(ID, "CrateBeneath", CrateBeneath);
        CrateBeneathIsMoney = ini->ReadBool(ID, "CrateBeneathIsMoney", CrateBeneathIsMoney);
        LeaveRubble = ini->ReadBool(ID, "LeaveRubble", LeaveRubble);
        PlaceAnywhere = ini->ReadBool(ID, "PlaceAnywhere", PlaceAnywhere);
        ICBMLauncher = ini->ReadBool(ID, "ICBMLauncher", ICBMLauncher);
        Artillary = ini->ReadBool(ID, "Artillary", Artillary);
        {
            coordDefault = TargetCoordOffset;
            TargetCoordOffset = ini->ReadCoord(ID, "TargetCoordOffset", coordDefault);
        }
        {
            coordDefault = ExitCoord;
            ExitCoord = ini->ReadCoord(ID, "ExitCoord", coordDefault);
        }
        AIBuildThis = ini->ReadBool(ID, "AIBuildThis", AIBuildThis);
        IsBaseDefense = ini->ReadBool(ID, "IsBaseDefense", IsBaseDefense);
        IsThreatRatingNode = ini->ReadBool(ID, "IsThreatRatingNode", IsThreatRatingNode);
        ConcentricRadialIndicator = ini->ReadBool(ID, "ConcentricRadialIndicator", ConcentricRadialIndicator);
        RotCount = Turret ? 0x20 : 1;
        {
            int power = PowerBonus > 0 ? PowerBonus : -PowerDrain;
            power = ini->ReadInteger(ID, "Power", power);
            PowerBonus = power;
            if (power < 0) {
                PowerDrain = -power;
                PowerBonus = 0;
            } else {
                PowerDrain = 0;
            }
        }
        {
            int power = ExtraPowerBonus > 0 ? ExtraPowerBonus : -ExtraPowerDrain;
            power = ini->ReadInteger(ID, "ExtraPower", power);
            ExtraPowerBonus = power;
            if (power < 0) {
                ExtraPowerDrain = -power;
                ExtraPowerBonus = 0;
            }
        }
        Height = DAT_00887180.ReadInteger(ImageFile, "Height", Height);
        OccupyHeight = DAT_00887180.ReadInteger(ImageFile, "OccupyHeight", Height);
        Recoilless = DAT_00887180.ReadBool(ImageFile, "Recoilless", Recoilless);
        DoubleThick = DAT_00887180.ReadBool(ImageFile, "DoubleThick", DoubleThick);
        Flat = DAT_00887180.ReadBool(ImageFile, "Flat", Flat);
        SiloDamage = DAT_00887180.ReadBool(ImageFile, "SiloDamage", SiloDamage);
        ChargeAnim = DAT_00887180.ReadBool(ImageFile, "ChargeAnim", ChargeAnim);
        IsAnimDelayedFire = DAT_00887180.ReadBool(ImageFile, "IsAnimDelayedFire", IsAnimDelayedFire);
        DelayedFireDelay = DAT_00887180.ReadInteger(ImageFile, "DelayedFireDelay", DelayedFireDelay);
        {
            OverlayTypeClass* old = ToOverlay;
            ToOverlay = DAT_00887180.ReadString(ImageFile, "ToOverlay", TypesEmptyText, name, 0x80) ? TypesFindOverlay(name) : old;
        }
        Foundation = DAT_00887180.ReadFoundation(ImageFile, "Foundation", Foundation);
        {
            int foundation = DAT_00887180.ReadFoundation(ID, "Foundation", Foundation);
            if (foundation)
                Foundation = foundation;
        }
        MidPoint = DAT_00887180.ReadInteger(ImageFile, "MidPoint", MidPoint);
        DoorStages = DAT_00887180.ReadInteger(ImageFile, "DoorStages", DoorStages);
        DamagedDoor = DAT_00887180.ReadBool(ImageFile, "DamagedDoor", DamagedDoor);
        TerrainPalette = DAT_00887180.ReadBool(ImageFile, "TerrainPalette", TerrainPalette);
        GateStages = DAT_00887180.ReadInteger(ImageFile, "GateStages", GateStages);
        PrimaryFirePixelOffset = DAT_00887180.ReadPoint(ImageFile, "PrimaryFirePixelOffset", PrimaryFirePixelOffset);
        SecondaryFirePixelOffset = DAT_00887180.ReadPoint(ImageFile, "SecondaryFirePixelOffset", SecondaryFirePixelOffset);
        PrimaryFireDualOffset = DAT_00887180.ReadBool(ImageFile, "PrimaryFireDualOffset", PrimaryFireDualOffset);
        ExtraDamageStage = DAT_00887180.ReadBool(ImageFile, "ExtraDamageStage", ExtraDamageStage);
        SpecialZOverlayZAdjust = DAT_00887180.ReadInteger(ImageFile, "SpecialZOverlayZAdjust", SpecialZOverlayZAdjust);
        NormalZAdjust = DAT_00887180.ReadInteger(ImageFile, "NormalZAdjust", NormalZAdjust);
        ZShapePointMove = DAT_00887180.ReadPoint(ImageFile, "ZShapePointMove", ZShapePointMove);
        ExtraLight = (short)DAT_00887180.ReadInteger(ImageFile, "ExtraLight", (short)ExtraLight);
        CanHideThings = DAT_00887180.ReadBool(ID, "CanHideThings", CanHideThings);
        for (i = 1; i <= 8; ++i) {
            wsprintfA(animName, "RemoveOccupy%d", i);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            RemoveOccupy[i - 1] = DAT_00887180.ReadPoint(ImageFile, animName, pointDefault);
            wsprintfA(animName, "AddOccupy%d", i);
            pointDefault2 = TypesMakePoint(0xFFFF, 0xFFFF);
            AddOccupy[i - 1] = DAT_00887180.ReadPoint(ImageFile, animName, pointDefault2);
        }
        {
            pointDefault = TypesMakePoint(0, 0);
            QueueingCell = DAT_00887180.ReadPoint(ImageFile, "QueueingCell", pointDefault);
        }
        FoundationData = TypesFoundationCells[Foundation];
        FoundationOutside = TypesFoundationOutsideCells[Foundation];
        {
            DAT_00887180.ReadString(ImageFile, "Buildup", TypesEmptyText, animName, 0x10);
            if (strlen(animName))
                strcpy(BuildupFile, animName);
        }
        StampTheater(DAT_00A8B230->unknown_1258);
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[1].Frame, BuildingAnimFrame[1].Count, BuildingAnimFrame[1].Rate);
            if (DAT_00887180.ReadString(ImageFile, "AnimIdle", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[1].Frame, &BuildingAnimFrame[1].Count, &BuildingAnimFrame[1].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[2].Frame, BuildingAnimFrame[2].Count, BuildingAnimFrame[2].Rate);
            if (DAT_00887180.ReadString(ImageFile, "AnimActive", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[2].Frame, &BuildingAnimFrame[2].Count, &BuildingAnimFrame[2].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[4].Frame, BuildingAnimFrame[4].Count, BuildingAnimFrame[4].Rate);
            if (DAT_00887180.ReadString(ImageFile, "AnimAux1", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[4].Frame, &BuildingAnimFrame[4].Count, &BuildingAnimFrame[4].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[5].Frame, BuildingAnimFrame[5].Count, BuildingAnimFrame[5].Rate);
            if (DAT_00887180.ReadString(ImageFile, "AnimAux2", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[5].Frame, &BuildingAnimFrame[5].Count, &BuildingAnimFrame[5].Rate);
        }
        TYPES_READ_ANIM(BuildingAnim[3], "ActiveAnim")
        TYPES_READ_ANIM(BuildingAnim[4], "ActiveAnimTwo")
        TYPES_READ_ANIM(BuildingAnim[5], "ActiveAnimThree")
        TYPES_READ_ANIM(BuildingAnim[6], "ActiveAnimFour")
        TYPES_READ_ANIM_QUIRK(BuildingAnim[14], "SuperAnim", BuildingAnim[6].X, BuildingAnim[6].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[15], "SuperAnimTwo", BuildingAnim[4].X, BuildingAnim[4].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[16], "SuperAnimThree", BuildingAnim[5].X, BuildingAnim[5].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[17], "SuperAnimFour", BuildingAnim[5].X, BuildingAnim[5].Y)
        TYPES_READ_ANIM(BuildingAnim[10], "SpecialAnim")
        TYPES_READ_ANIM(BuildingAnim[11], "SpecialAnimTwo")
        TYPES_READ_ANIM(BuildingAnim[12], "SpecialAnimThree")
        TYPES_READ_ANIM(BuildingAnim[13], "SpecialAnimFour")
        TYPES_READ_ANIM(BuildingAnim[19], "LowPower")
        TYPES_READ_ANIM(BuildingAnim[20], "SuperLowPower")
        TYPES_READ_ANIM_NOBOOLS(BuildingAnim[8], "ProductionAnim")
        TYPES_READ_ANIM(BuildingAnim[18], "IdleAnim")
        TYPES_READ_ANIM_NOBOOLS(BuildingAnim[7], "PreProductionAnim")
        TYPES_READ_ANIM_NOBOOLS_RULES(BuildingAnim[9], "TurretAnim")
        TurretAnimIsVoxel = ini->ReadBool(ID, "TurretAnimIsVoxel", TurretAnimIsVoxel);
        BarrelAnimIsVoxel = ini->ReadBool(ID, "BarrelAnimIsVoxel", BarrelAnimIsVoxel);
        ini->ReadString(ID, "VoxelBarrelFile", VoxelBarrelFile, VoxelBarrelFile, 0x10);
        {
            coordDefault = VoxelBarrelOffsetToPitchPivotPoint;
            VoxelBarrelOffsetToPitchPivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToPitchPivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToRotatePivotPoint;
            VoxelBarrelOffsetToRotatePivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToRotatePivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToBuildingPivotPoint;
            VoxelBarrelOffsetToBuildingPivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToBuildingPivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToBarrelEnd;
            VoxelBarrelOffsetToBarrelEnd = ini->ReadCoord(ID, "VoxelBarrelOffsetToBarrelEnd", coordDefault);
        }
        Upgrades = ini->ReadInteger(ID, "Upgrades", Upgrades);
        if (Upgrades > 0) {
            for (i = 1; i - 1 < Upgrades; ++i) {
                BuildingAnimStruct& slot = BuildingAnim[i - 1];
                sprintf(animKey, "PowerUp%01dAnim", i);
                sprintf(damagedKey, "PowerUp%01dDamagedAnim", i);
                sprintf(xKey, "PowerUp%01dLocXX", i);
                sprintf(yKey, "PowerUp%01dLocYY", i);
                sprintf(zKey, "PowerUp%01dLocZZ", i);
                sprintf(sortKey, "PowerUp%01dYSort", i);
                DAT_00887180.ReadString(ImageFile, animKey, TypesEmptyText, animName, 0x10);
                if (strlen(animName))
                    strcpy(slot.Anim, animName);
                DAT_00887180.ReadString(ImageFile, damagedKey, TypesEmptyText, animName, 0x10);
                if (strlen(animName))
                    strcpy(slot.Damaged, animName);
                slot.X = DAT_00887180.ReadInteger(ImageFile, xKey, slot.X);
                slot.Y = DAT_00887180.ReadInteger(ImageFile, yKey, slot.Y);
                slot.ZAdjust = DAT_00887180.ReadInteger(ImageFile, zKey, slot.ZAdjust);
                slot.YSort = DAT_00887180.ReadInteger(ImageFile, sortKey, slot.YSort);
            }
        }
        {
            int oldDocks = NumberOfDocks;
            NumberOfDocks = ini->ReadInteger(ID, "NumberOfDocks", oldDocks);
            if (NumberOfDocks > DockingOffsets.Capacity) {
                DockingOffsets.SetCapacity(NumberOfDocks, 0);
                for (i = oldDocks; i < NumberOfDocks; ++i) {
                    TPoint3D<int> zero;
                    zero.X = 0;
                    zero.Y = 0;
                    zero.Z = 0;
                    DockingOffsets.Items[i] = zero;
                }
            }
            for (i = 0; i < NumberOfDocks; ++i) {
                sprintf(dockKey, "DockingOffset%d", i);
                coordDefault = *(CoordStruct*)&DockingOffsets.Items[i];
                CoordStruct result = DAT_00887180.ReadCoord(ImageFile, dockKey, coordDefault);
                *(CoordStruct*)&DockingOffsets.Items[i] = result;
            }
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x464A70
CoordStruct BuildingTypeClass::vf_27(const CoordStruct& in)
{
    CoordStruct coord = in;
    coord.Z = TypesMap.GetFloorHeight(&coord);
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x464AC0
bool BuildingTypeClass::vf_42(CellStruct* arg1, HouseClass* arg2)
{
    if (PlaceAnywhere)
        return true;
    return TechnoTypeClass::vf_42(arg1, arg2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x464AF0
CoordStruct BuildingTypeClass::vf_31()
{
    CoordStruct coord;
    coord.X = FoundationWidth[Foundation] << 8;
    coord.Y = FoundationHeight[Foundation] << 8;
    coord.Z = Height * TypesLevelHeight;
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x464B30
void BuildingTypeClass::vf_13(Obj_004A1D30* crc)
{
    TechnoTypeClass::vf_13(crc);
    crc->FUN_004A1D90(GateCloseDelay);
    crc->FUN_004A1D50(LightVisibility);
    crc->FUN_004A1D50(LightIntensity);
    crc->FUN_004A1D50(LightRedTint);
    crc->FUN_004A1D50(LightGreenTint);
    crc->FUN_004A1D50(LightBlueTint);
    crc->FUN_004A1DB0(BuildupFile);
    crc->FUN_004A1DB0(PowersUpBuilding);
    crc->FUN_004A1D50(Adjacent);
    crc->FUN_004A1D50(Factory);
    crc->FUN_004A1D50(PowerBonus);
    crc->FUN_004A1D50(PowerDrain);
    crc->FUN_004A1D50(ExtraPowerBonus);
    crc->FUN_004A1D50(ExtraPowerDrain);
    crc->FUN_004A1D50(Foundation);
    crc->FUN_004A1D50(Height);
    crc->FUN_004A1D50(OccupyHeight);
    crc->FUN_004A1D50(MidPoint);
    crc->FUN_004A1D50(DoorStages);
    crc->FUN_004A1DE0(BuildingAnimFrame, sizeof(BuildingAnimFrame));
    crc->FUN_004A1DE0(BuildingAnim, sizeof(BuildingAnim));
    crc->FUN_004A1D50(Upgrades);
    crc->FUN_004A1D50(SpecialZOverlayZAdjust);
    crc->FUN_004A1CA0(HoverPad);
    crc->FUN_004A1CA0(IsPlug);
    crc->FUN_004A1CA0(IsTemple);
    crc->FUN_004A1CA0(HasSpotlight);
    crc->FUN_004A1CA0(BaseNormal);
    crc->FUN_004A1CA0(EligibileForAllyBuilding);
    crc->FUN_004A1CA0(NeedsEngineer);
    crc->FUN_004A1CA0(Bib);
    crc->FUN_004A1CA0(Wall);
    crc->FUN_004A1CA0(Capturable);
    crc->FUN_004A1CA0(Powered);
    crc->FUN_004A1CA0(Unsellable);
    crc->FUN_004A1CA0(Radar);
    crc->FUN_004A1CA0(SpySat);
    crc->FUN_004A1CA0(ChargeAnim);
    crc->FUN_004A1CA0(IsAnimDelayedFire);
    crc->FUN_004A1D50(DelayedFireDelay);
    crc->FUN_004A1CA0(SiloDamage);
    crc->FUN_004A1CA0(UnitRepair);
    crc->FUN_004A1CA0(UnitReload);
    crc->FUN_004A1CA0(Cloning);
    crc->FUN_004A1CA0(Grinding);
    crc->FUN_004A1CA0(UnitAbsorb);
    crc->FUN_004A1CA0(InfantryAbsorb);
    crc->FUN_004A1CA0(SecretLab);
    crc->FUN_004A1CA0(Flat);
    crc->FUN_004A1CA0(DockUnload);
    crc->FUN_004A1CA0(Recoilless);
    crc->FUN_004A1CA0(BridgeRepairHut);
    crc->FUN_004A1CA0(Gate);
    crc->FUN_004A1CA0(SAM);
    crc->FUN_004A1CA0(ConstructionYard);
    crc->FUN_004A1CA0(NukeSilo);
    crc->FUN_004A1CA0(Refinery);
    crc->FUN_004A1CA0(WeaponsFactory);
    crc->FUN_004A1CA0(LaserFencePost);
    crc->FUN_004A1CA0(LaserFence);
    crc->FUN_004A1CA0(FirestormWall);
    crc->FUN_004A1CA0(Helipad);
    crc->FUN_004A1CA0(OrePurifier);
    crc->FUN_004A1CA0(ExtraDamageStage);
    crc->FUN_004A1CA0(Hospital);
    crc->FUN_004A1CA0(Armory);
    crc->FUN_004A1D50(GateStages);
    crc->FUN_004A1D50(PowersUpToLevel);
    crc->FUN_004A1CA0(DamagedDoor);
    crc->FUN_004A1CA0(InvisibleInGame);
    crc->FUN_004A1CA0(TerrainPalette);
    crc->FUN_004A1CA0(TurretAnimIsVoxel);
    crc->FUN_004A1CA0(BarrelAnimIsVoxel);
    crc->FUN_004A1DB0(VoxelBarrelFile);
    crc->FUN_004A1D90(unknown_1728);
    crc->FUN_004A1DE0(&VoxelBarrelOffsetToPitchPivotPoint, sizeof(CoordStruct));
    crc->FUN_004A1DE0(&VoxelBarrelOffsetToRotatePivotPoint, sizeof(CoordStruct));
    crc->FUN_004A1DE0(&VoxelBarrelOffsetToBuildingPivotPoint, sizeof(CoordStruct));
    crc->FUN_004A1DE0(&VoxelBarrelOffsetToBarrelEnd, sizeof(CoordStruct));
    crc->FUN_004A1CA0(CrateBeneath);
    crc->FUN_004A1CA0(LeaveRubble);
    crc->FUN_004A1CA0(CrateBeneathIsMoney);
    crc->FUN_004A1D50(NumberOfDocks);
    crc->FUN_004A1D50(BarrelStartPitch);
    crc->FUN_004A1CA0(ConcentricRadialIndicator);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// CAPPED at 94.6% aligned-instruction match (192 of 203 retail instructions). Observed delta: only stack
// slots. Retail keeps the element count in the dead pStm argument slot and the loop index and the no-init
// temporary in the dead `this` slot; this build puts the count in the `this` slot and the index in the pStm slot,
// so six [esp+N] operands differ and the two-instruction foundation table address (`lea edx,[eax+0x89C900]`)
// is written with a relocation. Forms tried: count and index declared in different orders and at function
// scope; an initialised count; a named no-init tag; an extra stream alias; the count and loop in a nested block
// (kept, 94.6% against 89.7% without).
// FUNCTION: GAMEMD 0x465010
HRESULT __stdcall BuildingTypeClass::Load(IStream* pStm)
{
    if (FreeBuildup && Buildup) {
        gg_free(Buildup);
        Buildup = 0;
        BuildupLoaded = false;
    }
    if (BibShapeLoaded && BibShape) {
        gg_free(BibShape);
        BibShape = 0;
        BibShapeLoaded = false;
    }
    if (DeployingAnimLoaded && DeployingAnim) {
        gg_free(DeployingAnim);
        DeployingAnim = 0;
        DeployingAnimLoaded = false;
    }
    if (UnderDoorAnimLoaded && UnderDoorAnim) {
        gg_free(UnderDoorAnim);
        UnderDoorAnim = 0;
        UnderDoorAnimLoaded = false;
    }
    if (RubbleLoaded && Rubble) {
        gg_free(Rubble);
        Rubble = 0;
        RubbleLoaded = false;
    }
    if (RoofDeployingAnimLoaded && RoofDeployingAnim) {
        gg_free(RoofDeployingAnim);
        RoofDeployingAnim = 0;
        RoofDeployingAnimLoaded = false;
    }
    if (UnderRoofDoorAnimLoaded && UnderRoofDoorAnim) {
        gg_free(UnderRoofDoorAnim);
        UnderRoofDoorAnim = 0;
        UnderRoofDoorAnimLoaded = false;
    }

    HRESULT hr = TechnoTypeClass::Load(pStm);
    if (hr < 0)
        return hr;

    new (this) BuildingTypeClass(AbstractNoInit());

    {
    int count;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;

    new (&DockingOffsets) VectorClass<TPoint3D<int> >;
    DockingOffsets.SetCapacity(count, 0);
    for (int i = 0; i < count; ++i) {
        TPoint3D<int> coord;
        coord.X = 0;
        coord.Y = 0;
        coord.Z = 0;
        hr = pStm->Read(&coord, sizeof(coord), 0);
        if (hr < 0)
            return hr;
        DockingOffsets.Items[i] = coord;
    }
    }

    LoadFixup();
    FUN_005F9070();
    FoundationData = TypesFoundationCells[Foundation];
    FoundationOutside = TypesFoundationOutsideCells[Foundation];
    ToTile = 0;
    DAT_00B0C110.SwizzleManagerClass::vf_4(&ToOverlay);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FreeUnit);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&SecretInfantry);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&SecretUnit);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&SecretBuilding);
    LoadFixup();
    Buildup = 0;
    BuildupLoaded = false;
    BibShape = 0;
    BibShapeLoaded = false;
    DeployingAnim = 0;
    DeployingAnimLoaded = false;
    UnderDoorAnim = 0;
    UnderDoorAnimLoaded = false;
    Rubble = 0;
    RubbleLoaded = false;
    RoofDeployingAnim = 0;
    RoofDeployingAnimLoaded = false;
    UnderRoofDoorAnim = 0;
    UnderRoofDoorAnimLoaded = false;
    StampTheater(DAT_00A8B230->unknown_1258);
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465300
HRESULT __stdcall BuildingTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = TechnoTypeClass::Save(pStm, fClearDirty);
    if (hr < 0)
        return hr;

    int count = DockingOffsets.Capacity;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (int i = 0; i < count; ++i) {
        hr = pStm->Write(&DockingOffsets.Items[i], sizeof(TPoint3D<int>), 0);
        if (hr < 0)
            return hr;
    }
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465380
HRESULT __stdcall BuildingTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_BuildingType;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4653C0
char* FUN_004653C0(const char* name)
{
    if (FUN_007C8D20(STR_00817474, name) != 0
        && FUN_007C8D20(STR_00817694, name) != 0) {

        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x24, name) == 0) {
                return DAT_00A83C6C[i];
            }
        }

        void* item = FUN_007C8E17(0x1798);

        if (item != 0) {
            return ((Item*)item)->FUN_0045DD90(name);
        }
    }

    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// PARTIAL (97.6%, 80/82): identical multiset. The one remaining delta is the register of the vtable load in
// the inlined `delete` of the old surface (retail EAX, here EDX); a local for the old pointer and a base-typed
// global both leave it unchanged.
// FUNCTION: GAMEMD 0x465450
void FUN_00465450()
{
    int radius = 0;
    int i;
    for (i = 0; i < DAT_00A83C78; i++) {
        signed char r = ((BuildingTypeClass*)DAT_00A83C6C[i])->CloakRadiusInCells;
        if (radius <= r) {
            radius = r;
        }
    }
    if (radius != 0) {
        if (DAT_0089DDC0 != 0) {
            delete DAT_0089DDC0;
        }
        DAT_0089DDC0 = new DibSurface(radius + 16, radius + 16, 1, 0);
    }

    for (i = 0; i < DAT_00A83C78; i++) {
        BuildingTypeClass* type = (BuildingTypeClass*)DAT_00A83C6C[i];
        char buffer[0x3C];
        buffer[0] = 0;
        DAT_00887048->ReadString(type->ID, "ToTile", 0, buffer, 0x3C);
        int tile = IsometricTileTypeClass::FUN_00544CE0(buffer);
        if (tile >= 0 && tile < IsometricTileTypeClass_Array.Count) {
            type->ToTile = IsometricTileTypeClass_Array.Items[tile];
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465910
bool BuildingTypeClass::vf_40()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465920
bool BuildingTypeClass::vf_41()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465960
void* BuildingTypeClass::vf_48()
{
    if (Buildup == 0 && DemandLoadBuildup) {
        if (strlen(BuildupFile)) {
            char path[260];
            _makepath(path, 0, 0, BuildupFile, TypesShpExtension);
            TypesStampTheater(path, DAT_00A8B230->unknown_1258);
            TypesFileView file(path);
            void* shape = file.ReadShape();
            if (shape == 0) {
                TypesStampGenericTheater(path);
                TypesFileView file2(path);
                shape = file2.ReadShape();
            }
            Buildup = (SHPStruct*)shape;
            if (shape) {
                BuildupLoaded = true;
                int rate = 1;
                int frames = ((short*)shape)[3] / 2;
                if (Gate)
                    frames = GateStages + 1;
                if (frames > 0)
                    rate = (int)(DAT_008871E0->BuildupTime * 900.0 / frames);
                BuildingAnimFrame[0].Frame = 0;
                BuildingAnimFrame[0].Count = frames;
                BuildingAnimFrame[0].Rate = rate;
            }
        }
        return Buildup;
    }
    return Buildup;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465B30
void Owned_465B30::FUN_00465B30()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465B70
void Owned_465B70::FUN_00465B70()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465BB0
void Owned_465BB0::FUN_00465BB0()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465BF0
void Owned_465BF0::FUN_00465BF0()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465C30
void Owned_465C30::FUN_00465C30()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465C70
void Owned_465C70::FUN_00465C70()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465D30
// `XOR AL,AL` rather than `XOR EAX,EAX` — only the low byte is set, so the
// return type is bool, not int.
bool __cdecl FUN_00465D30()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465D70
int Obj_00465D00::FUN_00465D70() const
{
    return unknown_EDC;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465D90
int BuildingTypeClass::vf_11()
{
    return 7;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465DA0
int BuildingTypeClass::vf_12()
{
    return 0x1798;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465DB0
int BuildingTypeClass::vf_16()
{
    return ArrayIndex;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x465DC0 -- compiler-generated scalar deleting destructor.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00465E10
// VectorClass<TPoint3D<int>>::operator==
// FUNCTION: GAMEMD 0x00465E70
// VectorClass<TPoint3D<int>>::SetCapacity
// FUNCTION: GAMEMD 0x00465F80
// VectorClass<TPoint3D<int>>::FindItemIndex
// FUNCTION: GAMEMD 0x00465FD0
// VectorClass<TPoint3D<int>>::Slot5
// FUNCTION: GAMEMD 0x00465DE0
// VectorClass<TPoint3D<int>>::Slot6

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465F50
void FUN_00465F50(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x466080
void* BufferHolderDtor::FUN_00466080(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4638;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E4530
extern const double DAT_007E4530 = 60.0;
// GLOBAL: GAMEMD 0x81834C
extern const char TypesShpExtension[] = ".SHP";
// END defined globals
