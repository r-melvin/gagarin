// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x556520 and its 25
//   siblings.
//
//   One class template, 26 explicit instantiations. Each `template struct
//   DerivedSdd<Base_<base>, Tag_<class>>;` below makes the compiler
//   generate the scalar deleting destructor
//   `??_G?$DerivedSdd@UBase_<base>@@UTag_<class>@@@@UAEPAXI@Z`, whose 0x24
//   bytes are the retail function at the annotated address: seat this class's
//   own vtable, run the base destructor, free the object when the caller set
//   the deleting bit, and return it.
//
//   The vtable address is not written in the source at all -- retail seats the
//   vptr first, which is a synthesised destructor's order, so it is the
//   instantiation's own vtable and the linker fills the relocation in. The
//   base destructor is the first template parameter; the tag is the second,
//   and does nothing but keep the 26 instantiations distinct where only eight
//   bases exist.
//
//   BOTH PARAMETERS NOW CARRY RETAIL NAMES. The vtable each body seats was
//   re-read out of the binary as the `imm32` of the store, and all 26 carry a
//   complete object locator, so the derived class is RTTI-named and the tag
//   is named after it. The base is then that class's own base_chain[1] --
//   which is an independent check as well as a name, because six derived
//   classes share base destructor 0x5D5D20 and all six agree on
//   `MultiplayerGameMode`, eleven share 0x65D460 and all eleven agree on
//   `rc_ptr_base`, and so on for all eight bases with no disagreement.
//
//   KNOWN LIMITATION -- staging ground, not a destination: MSVC6 emits each
//   template instantiation as a COMDAT into the translation unit that
//   instantiated it, so these 26 instantiations belong to many different
//   original translation units. One sweep file is right for matching
//   bytes now and wrong for retail's eventual link order.
//
//   Instantiations are in ascending retail-address order.
//
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT

#include "derived_sdd_family_methods.h"

// FUNCTION: GAMEMD 0x00556520
// LightConvertClass -- seats its own vtable, retail 0x007ED0A4; locator 0x00805140 -> type
//   descriptor 0x00829D28 `.?AVLightConvertClass@@`. Base ConvertClass, whose destructor is 0x00490400.
struct Tag_LightConvertClass;
template struct DerivedSdd<Base_ConvertClass, Tag_LightConvertClass>;

// Remaining stand-ins have no data beyond the polymorphic prefix.
typedef DerivedSdd<Base_ConvertClass, Tag_LightConvertClass> GgDerivedSddRep;
GG_STATIC_ASSERT(sizeof(GgDerivedSddRep) == 0x4);

// FUNCTION: GAMEMD 0x005C0FE0
// MultiplayerBattle -- seats its own vtable, retail 0x007EE184; locator 0x00806088 -> type
//   descriptor 0x0082DAA8 `.?AVMultiplayerBattle@@`. Base MultiplayerGameMode, whose destructor is 0x005D5D20.
struct Tag_MultiplayerBattle;
template struct DerivedSdd<Base_MultiplayerGameMode, Tag_MultiplayerBattle>;

// FUNCTION: GAMEMD 0x005C5E40
// FreeForAll -- seats its own vtable, retail 0x007EE424; locator 0x00806358 -> type
//   descriptor 0x0082E118 `.?AVFreeForAll@@`. Base MultiplayerGameMode, whose destructor is 0x005D5D20.
struct Tag_FreeForAll;
template struct DerivedSdd<Base_MultiplayerGameMode, Tag_FreeForAll>;

// FUNCTION: GAMEMD 0x005C61A0
// MultiplayerManBattle -- seats its own vtable, retail 0x007EE50C; locator 0x008063A8 -> type
//   descriptor 0x0082E150 `.?AVMultiplayerManBattle@@`. Base MultiplayerGameMode, whose destructor is 0x005D5D20.
struct Tag_MultiplayerManBattle;
template struct DerivedSdd<Base_MultiplayerGameMode, Tag_MultiplayerManBattle>;

// FUNCTION: GAMEMD 0x005C9440
// Megawealth -- seats its own vtable, retail 0x007EE5F4; locator 0x008063F8 -> type
//   descriptor 0x0082FCE8 `.?AVMegawealth@@`. Base MultiplayerGameMode, whose destructor is 0x005D5D20.
struct Tag_Megawealth;
template struct DerivedSdd<Base_MultiplayerGameMode, Tag_Megawealth>;

// FUNCTION: GAMEMD 0x005CABD0
// MultiplayerSiege -- seats its own vtable, retail 0x007EE6FC; locator 0x00806498 -> type
//   descriptor 0x0082FEC8 `.?AVMultiplayerSiege@@`. Base MultiplayerGameMode, whose destructor is 0x005D5D20.
struct Tag_MultiplayerSiege;
template struct DerivedSdd<Base_MultiplayerGameMode, Tag_MultiplayerSiege>;

// FUNCTION: GAMEMD 0x005CAF10
// MultiplayerSiegeDefenderTeam -- seats its own vtable, retail 0x007EE7E4; locator 0x008064E8 -> type
//   descriptor 0x0082FFB8 `.?AVMultiplayerSiegeDefenderTeam@@`. Base MultiplayerTeam, whose destructor is 0x005D8C80.
struct Tag_MultiplayerSiegeDefenderTeam;
template struct DerivedSdd<Base_MultiplayerTeam, Tag_MultiplayerSiegeDefenderTeam>;

// FUNCTION: GAMEMD 0x005CAF40
// MultiplayerSiegeAttackerTeam -- seats its own vtable, retail 0x007EE7F4; locator 0x00806538 -> type
//   descriptor 0x00830018 `.?AVMultiplayerSiegeAttackerTeam@@`. Base MultiplayerTeam, whose destructor is 0x005D8C80.
struct Tag_MultiplayerSiegeAttackerTeam;
template struct DerivedSdd<Base_MultiplayerTeam, Tag_MultiplayerSiegeAttackerTeam>;

// FUNCTION: GAMEMD 0x005CB540
// UnholyAlliance -- seats its own vtable, retail 0x007EE814; locator 0x00806588 -> type
//   descriptor 0x00830058 `.?AVUnholyAlliance@@`. Base MultiplayerGameMode, whose destructor is 0x005D5D20.
struct Tag_UnholyAlliance;
template struct DerivedSdd<Base_MultiplayerGameMode, Tag_UnholyAlliance>;

// FUNCTION: GAMEMD 0x006C8840
// rc_ptr<PlayerProfile> -- seats its own vtable, retail 0x007F3F44; locator 0x0080B4C8 -> type
//   descriptor 0x00842028 `.?AV?$rc_ptr@VPlayerProfile@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_PlayerProfile;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_PlayerProfile>;

// FUNCTION: GAMEMD 0x00765710
// rc_ptr<WorldDominationTour::CampaignProperties> -- seats its own vtable, retail 0x007F6F6C; locator 0x0080D7A0 -> type
//   descriptor 0x00848120 `.?AV?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_CampaignProperties;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_CampaignProperties>;

// FUNCTION: GAMEMD 0x00765740
// rc_ptr<WorldDominationTour::History> -- seats its own vtable, retail 0x007F6F74; locator 0x0080D870 -> type
//   descriptor 0x008481B8 `.?AV?$rc_ptr@VHistory@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_History;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_History>;

// FUNCTION: GAMEMD 0x00765790
// rc_ptr<WorldDominationTour::Campaign> -- seats its own vtable, retail 0x007F6F24; locator 0x0080D648 -> type
//   descriptor 0x00847FE8 `.?AV?$rc_ptr@VCampaign@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_Campaign;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_Campaign>;

// FUNCTION: GAMEMD 0x007657C0
// rc_ptr<WorldDominationTour::State> -- seats its own vtable, retail 0x007F6F2C; locator 0x0080D7F0 -> type
//   descriptor 0x00848168 `.?AV?$rc_ptr@VState@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_State;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_State>;

// FUNCTION: GAMEMD 0x00766930
// rc_ptr<WorldDominationTour::Conflict> -- seats its own vtable, retail 0x007F6F34; locator 0x0080D700 -> type
//   descriptor 0x008480B8 `.?AV?$rc_ptr@VConflict@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_Conflict;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_Conflict>;

// FUNCTION: GAMEMD 0x00766960
// rc_ptr<WorldDominationTour::ValueGameOption<unsigned char>> -- seats its own vtable, retail 0x007F701C; locator 0x0080DA90 -> type
//   descriptor 0x008483E8 `.?AV?$rc_ptr@V?$ValueGameOption@E@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_ValueGameOption_unsigned_char;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_ValueGameOption_unsigned_char>;

// FUNCTION: GAMEMD 0x00766990
// rc_ptr<WorldDominationTour::FlagGameOption> -- seats its own vtable, retail 0x007F7014; locator 0x0080D9F0 -> type
//   descriptor 0x00848368 `.?AV?$rc_ptr@VFlagGameOption@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_FlagGameOption;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_FlagGameOption>;

// FUNCTION: GAMEMD 0x007669C0
// rc_ptr<WorldDominationTour::MapSizeGameOption> -- seats its own vtable, retail 0x007F7040; locator 0x0080DB28 -> type
//   descriptor 0x00848560 `.?AV?$rc_ptr@VMapSizeGameOption@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_MapSizeGameOption;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_MapSizeGameOption>;

// FUNCTION: GAMEMD 0x007678C0
// WorldDominationTour::GameOption -- seats its own vtable, retail 0x007F7060; locator 0x0080DB60 -> type
//   descriptor 0x008485A0 `.?AVGameOption@WorldDominationTour@@`. Base ReferenceCounted, whose destructor is 0x0065D660.
struct Tag_WorldDominationTour_GameOption;
template struct DerivedSdd<Base_ReferenceCounted, Tag_WorldDominationTour_GameOption>;

// FUNCTION: GAMEMD 0x00767C50
// rc_ptr<WDTState> -- seats its own vtable, retail 0x007F70EC; locator 0x0080DD08 -> type
//   descriptor 0x00848798 `.?AV?$rc_ptr@VWDTState@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WDTState;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WDTState>;

// FUNCTION: GAMEMD 0x00769D90
// rc_ptr<WorldDominationTour::Map> -- seats its own vtable, retail 0x007F712C; locator 0x0080DDA8 -> type
//   descriptor 0x008487E0 `.?AV?$rc_ptr@VMap@WorldDominationTour@@@@`. Base rc_ptr_base, whose destructor is 0x0065D460.
struct Tag_rc_ptr_WorldDominationTour_Map;
template struct DerivedSdd<Base_rc_ptr_base, Tag_rc_ptr_WorldDominationTour_Map>;

// FUNCTION: GAMEMD 0x0076B6C0
// WDTTerritory -- seats its own vtable, retail 0x007F7220; locator 0x0080E058 -> type
//   descriptor 0x00848BF8 `.?AVWDTTerritory@@`. Base ReferenceCounted, whose destructor is 0x0065D660.
struct Tag_WDTTerritory;
template struct DerivedSdd<Base_ReferenceCounted, Tag_WDTTerritory>;

// FUNCTION: GAMEMD 0x007784A0
// CCToolTip -- seats its own vtable, retail 0x007F74C4; locator 0x0080E560 -> type
//   descriptor 0x00849EE0 `.?AVCCToolTip@@`. Base ToolTipManager, whose destructor is 0x007240B0.
struct Tag_CCToolTip;
template struct DerivedSdd<Base_ToolTipManager, Tag_CCToolTip>;

// FUNCTION: GAMEMD 0x007A2E70
// SimpleWonlineDialogControl -- seats its own vtable, retail 0x007F7624; locator 0x0080E600 -> type
//   descriptor 0x0084A3F0 `.?AVSimpleWonlineDialogControl@@`. Base OwnerDraw::SimpleDialogControl, whose destructor is 0x00624130.
struct Tag_SimpleWonlineDialogControl;
template struct DerivedSdd<Base_OwnerDraw_SimpleDialogControl, Tag_SimpleWonlineDialogControl>;
