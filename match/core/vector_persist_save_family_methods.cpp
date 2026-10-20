// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001. These 34 functions form a
//   contiguous 0x80-strided run whose 127 retail bytes are identical across
//   every member, absolute constants and import slot included, and identical
//   to the already-matched Save_Sides at 0x6805F0 in the same run.
//
//   One class template, 34 explicit instantiations. Each `template struct
//   PersistVector<Elem_XXXXXXXX>;` below makes the compiler generate
//   `?Save@?$PersistVector@UElem_XXXXXXXX@@@@SIJPAUStream_0067FDF0@@PAU1@@Z`,
//   whose 0x7F bytes are the retail function at the annotated address. The
//   element type never reaches the code -- each element is saved through
//   IPersistStream, so the only type-dependent work is erased by the
//   QueryInterface -- which is why one template body reaches 34 retail
//   bodies with no per-instance parameter beyond the type identity itself.
//
//   The element types are opaque: retail names none of them. Each is
//   declared, never defined, under the address of the save it produces.
//
//   KNOWN LIMITATION -- staging ground, not a destination: MSVC6 emits each
//   template instantiation as a COMDAT into the translation unit that
//   instantiated it, so these 34 instantiations belong to many different
//   original Westwood translation units. One sweep file is right for matching
//   bytes now and wrong for retail's eventual link order.
//
//   Instantiations are in ascending retail-address order.

#include "vector_persist_save_family_methods.h"

// FUNCTION: GAMEMD 0x0067FDF0
struct Elem_0067FDF0;
template struct PersistVector<Elem_0067FDF0>;

// Layout asserted on the first instantiation; every instantiation in this
// family has the same layout, because the only member whose type varies is a
// pointer. The assert has to follow an explicit instantiation: VC6 fails to
// re-parse the template body when offsetof is what first instantiates it, and
// it will not take a template-id as offsetof's first argument either, hence
// the typedef.
typedef PersistVector<Elem_0067FDF0> GgPersistVectorRep;
GG_STATIC_ASSERT(offsetof(GgPersistVectorRep, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgPersistVectorRep, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(GgPersistVectorRep) == 0x18);

// FUNCTION: GAMEMD 0x0067FE70
struct Elem_0067FE70;
template struct PersistVector<Elem_0067FE70>;

// FUNCTION: GAMEMD 0x0067FEF0
struct Elem_0067FEF0;
template struct PersistVector<Elem_0067FEF0>;

// FUNCTION: GAMEMD 0x0067FF70
struct Elem_0067FF70;
template struct PersistVector<Elem_0067FF70>;

// FUNCTION: GAMEMD 0x0067FFF0
struct Elem_0067FFF0;
template struct PersistVector<Elem_0067FFF0>;

// FUNCTION: GAMEMD 0x00680070
struct Elem_00680070;
template struct PersistVector<Elem_00680070>;

// FUNCTION: GAMEMD 0x006800F0
struct Elem_006800F0;
template struct PersistVector<Elem_006800F0>;

// FUNCTION: GAMEMD 0x00680170
struct Elem_00680170;
template struct PersistVector<Elem_00680170>;

// FUNCTION: GAMEMD 0x006801F0
struct Elem_006801F0;
template struct PersistVector<Elem_006801F0>;

// FUNCTION: GAMEMD 0x00680270
struct Elem_00680270;
template struct PersistVector<Elem_00680270>;

// FUNCTION: GAMEMD 0x006802F0
struct Elem_006802F0;
template struct PersistVector<Elem_006802F0>;

// FUNCTION: GAMEMD 0x00680370
struct Elem_00680370;
template struct PersistVector<Elem_00680370>;

// FUNCTION: GAMEMD 0x006803F0
struct Elem_006803F0;
template struct PersistVector<Elem_006803F0>;

// FUNCTION: GAMEMD 0x00680470
struct Elem_00680470;
template struct PersistVector<Elem_00680470>;

// FUNCTION: GAMEMD 0x006804F0
struct Elem_006804F0;
template struct PersistVector<Elem_006804F0>;

// FUNCTION: GAMEMD 0x00680570
struct Elem_00680570;
template struct PersistVector<Elem_00680570>;

// FUNCTION: GAMEMD 0x00680670
struct Elem_00680670;
template struct PersistVector<Elem_00680670>;

// FUNCTION: GAMEMD 0x006806F0
struct Elem_006806F0;
template struct PersistVector<Elem_006806F0>;

// FUNCTION: GAMEMD 0x00680770
struct Elem_00680770;
template struct PersistVector<Elem_00680770>;

// FUNCTION: GAMEMD 0x006807F0
struct Elem_006807F0;
template struct PersistVector<Elem_006807F0>;

// FUNCTION: GAMEMD 0x00680870
struct Elem_00680870;
template struct PersistVector<Elem_00680870>;

// FUNCTION: GAMEMD 0x006808F0
struct Elem_006808F0;
template struct PersistVector<Elem_006808F0>;

// FUNCTION: GAMEMD 0x00680970
struct Elem_00680970;
template struct PersistVector<Elem_00680970>;

// FUNCTION: GAMEMD 0x006809F0
struct Elem_006809F0;
template struct PersistVector<Elem_006809F0>;

// FUNCTION: GAMEMD 0x00680A70
struct Elem_00680A70;
template struct PersistVector<Elem_00680A70>;

// FUNCTION: GAMEMD 0x00680AF0
struct Elem_00680AF0;
template struct PersistVector<Elem_00680AF0>;

// FUNCTION: GAMEMD 0x00680B70
struct Elem_00680B70;
template struct PersistVector<Elem_00680B70>;

// FUNCTION: GAMEMD 0x00680BF0
struct Elem_00680BF0;
template struct PersistVector<Elem_00680BF0>;

// FUNCTION: GAMEMD 0x00680C70
struct Elem_00680C70;
template struct PersistVector<Elem_00680C70>;

// FUNCTION: GAMEMD 0x00680CF0
struct Elem_00680CF0;
template struct PersistVector<Elem_00680CF0>;

// FUNCTION: GAMEMD 0x00680D70
struct Elem_00680D70;
template struct PersistVector<Elem_00680D70>;

// FUNCTION: GAMEMD 0x00680DF0
struct Elem_00680DF0;
template struct PersistVector<Elem_00680DF0>;

// FUNCTION: GAMEMD 0x00680E70
struct Elem_00680E70;
template struct PersistVector<Elem_00680E70>;

// FUNCTION: GAMEMD 0x00680EF0
struct Elem_00680EF0;
template struct PersistVector<Elem_00680EF0>;
