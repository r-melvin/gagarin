// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x53F850 and its 26 siblings: a derived class's scalar
//   deleting destructor. It seats the class's own vtable at +0, runs the base
//   destructor with `this` still live in ECX, frees the object when the
//   caller's flag bit is set, and hands the object back. Per instance the
//   vtable and the base destructor vary; the free is 0x7C8B3D in all 27, and
//   the nine distinct base destructors are what group the family into its
//   class hierarchies.
//
//   THE STORE-ORDER CHECK (batch fifty-four) SELECTS THE 335-FAMILY SHAPE.
//   Retail's first two instructions after the prologue are
//
//       MOV [ESI],<vtable> ; CALL <base destructor>
//
//   -- the **vptr is seated first**, before anything else the object owns is
//   touched. That is the order a compiler-synthesised destructor emits and
//   the order a constructor emits; it is not the members-then-vptr order that
//   proved the 78-function family to be an ordinary member seating a vtable.
//   So the vtable here is NOT an input: it is the instantiation's own emitted
//   vtable, supplied as a relocation by the compiler, exactly as in
//   vector_dtor_family_methods.h, and no traits parameter carrying a vtable
//   address is needed or wanted.
//
//   WHAT ACTUALLY VARIES, AND WHY THERE ARE TWO PARAMETERS. Two things differ
//   between the 27 bodies: the vtable (27 distinct, one each) and the base
//   destructor called (9 distinct). The base is a real template parameter --
//   `DerivedSdd<Base>` inherits it, so the compiler emits the call to that
//   base's destructor. The vtable is not a parameter at all, but each
//   instantiation needs its own, and nine bases cannot produce 27 distinct
//   instantiations; hence a second, empty tag parameter keyed by the retail
//   address, which is what makes each instantiation -- and so each emitted
//   vtable and each COMDAT -- distinct. This is the same device the
//   335-family uses where two destructors share one retail vtable.
//
//   THE BASES ARE DECLARED, NEVER DEFINED. Each `Base_XXXXXXXX` names one
//   retail base destructor by its address. Declaring the destructor without
//   defining it makes the compiler emit a direct relocated call to it, which
//   is what retail contains; reccmp/objdiff normalise the relocation target.
//
//   FLAGS: THIS CLUSTER IS `/O2 /DNDEBUG /Gy`, WITHOUT `/GX`. Bisected, not
//   assumed. With `/GX` on, VC6 refuses to inline a derived destructor that
//   calls a base destructor and emits `??_G` as `PUSH ESI; MOV ESI,ECX; CALL
//   ??1Derived; ...` -- the vtable store moved out into a separate `??1`
//   body, 0% against retail. With `/GX` off the destructor inlines into
//   `??_G` and the 36 bytes are retail's exactly. The `// VC6FLAGS:` line in
//   the translation unit pins it so the gate compiles it the same way the
//   inner loop did.
//
//   The object free is the compiler's own `operator delete` call
//   (`??3@YAXPAX@Z`), a direct `__cdecl` call with the object pushed -- the
//   same shape as retail's `PUSH ESI; CALL 0x7C8B3D; ADD ESP,4`.
//
//   KNOWN LIMITATION -- this file is a staging ground, not a destination. The
//   TU-partition work established that MSVC6 emits each template
//   instantiation as a COMDAT into the translation unit that instantiated it.
//   These 27 instantiations therefore belong to many different original
//   translation units, not to one. Grouping them in a single sweep
//   file is correct for matching bytes now and wrong for reproducing retail's
//   link order eventually; they will have to be redistributed to their owning
//   TUs when the partition is reconstructed.
#ifndef GG_MATCH_CORE_DERIVED_SDD_FAMILY_METHODS_H
#define GG_MATCH_CORE_DERIVED_SDD_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The eight base classes. Each is RTTI-named: the derived class is the class
// of the vtable its body seats, and the base is that class's own base_chain[1]
// in the whole-image RTTI sweep -- an independent check as well as a name,
// since the classes sharing a base destructor address all agree on it. The
// destructor is declared, never defined: the call is a relocation.

// FUNCTION: GAMEMD 0x00490400 (decl; reloc) -- ConvertClass::~ConvertClass.
struct Base_ConvertClass { virtual ~Base_ConvertClass(); };

// FUNCTION: GAMEMD 0x005CB6C0 (decl; reloc) -- MSAnim::~MSAnim.
struct Base_MSAnim { virtual ~Base_MSAnim(); };

// FUNCTION: GAMEMD 0x005D5D20 (decl; reloc) -- MultiplayerGameMode::~MultiplayerGameMode.
struct Base_MultiplayerGameMode { virtual ~Base_MultiplayerGameMode(); };

// FUNCTION: GAMEMD 0x005D8C80 (decl; reloc) -- MultiplayerTeam::~MultiplayerTeam.
struct Base_MultiplayerTeam { virtual ~Base_MultiplayerTeam(); };

// FUNCTION: GAMEMD 0x00624130 (decl; reloc) -- OwnerDraw::SimpleDialogControl::~SimpleDialogControl.
struct Base_OwnerDraw_SimpleDialogControl { virtual ~Base_OwnerDraw_SimpleDialogControl(); };

// FUNCTION: GAMEMD 0x0065D460 (decl; reloc) -- rc_ptr_base::~rc_ptr_base.
struct Base_rc_ptr_base { virtual ~Base_rc_ptr_base(); };

// FUNCTION: GAMEMD 0x0065D660 (decl; reloc) -- ReferenceCounted::~ReferenceCounted.
struct Base_ReferenceCounted { virtual ~Base_ReferenceCounted(); };

// FUNCTION: GAMEMD 0x007240B0 (decl; reloc) -- ToolTipManager::~ToolTipManager.
struct Base_ToolTipManager { virtual ~Base_ToolTipManager(); };


// The derived class. It adds no members -- retail's body touches nothing but
// the vptr -- so its layout is the base's single vtable pointer. `Tag` exists
// only to make each instantiation, and so each emitted vtable, distinct.
template<class Base, class Tag>
struct DerivedSdd : Base
{
    virtual ~DerivedSdd();
};

template<class Base, class Tag>
DerivedSdd<Base, Tag>::~DerivedSdd()
{
}

// The retail vtables seated by this family. Each is the slot-0 owner of one
// of the instantiations in derived_sdd_family_methods.cpp; the compiler
// supplies the address as the instantiation's own vtable relocation, so no
// name below is referenced from the code.

// VTABLE: GAMEMD 0x007EC0CC -- IPXConnClass
extern char VT_007EC0CC;

// VTABLE: GAMEMD 0x007ED0A4 -- LightConvertClass
extern char VT_007ED0A4;

// VTABLE: GAMEMD 0x007EE184 -- MultiplayerBattle
extern char VT_007EE184;

// VTABLE: GAMEMD 0x007EE424 -- FreeForAll
extern char VT_007EE424;

// VTABLE: GAMEMD 0x007EE50C -- MultiplayerManBattle
extern char VT_007EE50C;

// VTABLE: GAMEMD 0x007EE5F4 -- Megawealth
extern char VT_007EE5F4;

// VTABLE: GAMEMD 0x007EE6FC -- MultiplayerSiege
extern char VT_007EE6FC;

// VTABLE: GAMEMD 0x007EE7E4 -- MultiplayerSiegeDefenderTeam
extern char VT_007EE7E4;

// VTABLE: GAMEMD 0x007EE7F4 -- MultiplayerSiegeAttackerTeam
extern char VT_007EE7F4;

// VTABLE: GAMEMD 0x007EE814 -- UnholyAlliance
extern char VT_007EE814;

// VTABLE: GAMEMD 0x007F3F44 -- rc_ptr<PlayerProfile>
extern char VT_007F3F44;

// VTABLE: GAMEMD 0x007F6F24 -- rc_ptr<WorldDominationTour::Campaign>
extern char VT_007F6F24;

// VTABLE: GAMEMD 0x007F6F2C -- rc_ptr<WorldDominationTour::State>
extern char VT_007F6F2C;

// VTABLE: GAMEMD 0x007F6F34 -- rc_ptr<WorldDominationTour::Conflict>
extern char VT_007F6F34;

// VTABLE: GAMEMD 0x007F6F6C -- rc_ptr<WorldDominationTour::CampaignProperties>
extern char VT_007F6F6C;

// VTABLE: GAMEMD 0x007F6F74 -- rc_ptr<WorldDominationTour::History>
extern char VT_007F6F74;

// VTABLE: GAMEMD 0x007F7014 -- rc_ptr<WorldDominationTour::FlagGameOption>
extern char VT_007F7014;

// VTABLE: GAMEMD 0x007F701C -- rc_ptr<WorldDominationTour::ValueGameOption<unsigned char>>
extern char VT_007F701C;

// VTABLE: GAMEMD 0x007F7040 -- rc_ptr<WorldDominationTour::MapSizeGameOption>
extern char VT_007F7040;

// VTABLE: GAMEMD 0x007F7060 -- WorldDominationTour::GameOption
extern char VT_007F7060;

// VTABLE: GAMEMD 0x007F70EC -- rc_ptr<WDTState>
extern char VT_007F70EC;

// VTABLE: GAMEMD 0x007F7104 -- MSFrameAnim
extern char VT_007F7104;

// VTABLE: GAMEMD 0x007F712C -- rc_ptr<WorldDominationTour::Map>
extern char VT_007F712C;

// VTABLE: GAMEMD 0x007F7220 -- WDTTerritory
extern char VT_007F7220;

// VTABLE: GAMEMD 0x007F7354 -- WorldDominationTour::Voices::Anim
extern char VT_007F7354;

// VTABLE: GAMEMD 0x007F74C4 -- CCToolTip
extern char VT_007F74C4;

// VTABLE: GAMEMD 0x007F7624 -- SimpleWonlineDialogControl
extern char VT_007F7624;


#endif  // GG_MATCH_CORE_DERIVED_SDD_FAMILY_METHODS_H
