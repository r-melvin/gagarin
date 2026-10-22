// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit WDTProps.cpp. The name is the source-file string at 0x848d80
//   in retail gamemd.exe v1.001, passed by the assert at 0x76bf38 inside this object's
//   code range (0x76bca0-0x76c09f). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//
//   The retail assert path string names this unit WDTProps.cpp. /Ob2 lets the
//   out-of-line destructor 0x76BED0 also expand inside the deleting wrapper
//   0x76C030, as retail does.

#include "world_domination_tour.h"

using WorldDominationTour::CampaignProperties;

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- __fastcall string-table lookup.
wchar_t* StringTable_LoadString(const char* label, int* out,
                                const char* file, int line);

// GLOBAL: GAMEMD 0x889F64 -- the shared empty default string.
extern const char STR_00889F64[];

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F7280
extern const double DAT_007F7280;
// GLOBAL: GAMEMD 0xB729B0
extern double DAT_00B729B0;
// GLOBAL: GAMEMD 0xB729E8
extern double DAT_00B729E8;
// GLOBAL: GAMEMD 0xB729F0
extern int DAT_00B729F0;
// GLOBAL: GAMEMD 0xB729F4
extern int DAT_00B729F4;
// GLOBAL: GAMEMD 0xB729F8
extern int DAT_00B729F8;
// GLOBAL: GAMEMD 0xB72A00
extern double DAT_00B72A00;

// FUNCTION: GAMEMD 0x76BCD0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076BCD0()
{
    DAT_00B72A00 = DAT_00B729B0 / DAT_007F7280;
}

// FUNCTION: GAMEMD 0x76BCF0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076BCF0()
{
    DAT_00B729E8 = DAT_007E1718 / DAT_00B72A00;
}

// FUNCTION: GAMEMD 0x76BE70
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0076BE70()
{
    DAT_00B729F8 = 0;
    DAT_00B729F0 = 0x80;
    DAT_00B729F4 = 0x80;
}

// FUNCTION: GAMEMD 0x76BE90
rc_ptr<CampaignProperties> FUN_0076BE90(const rc_ptr<WDTState>& state)
{
    return rc_ptr<CampaignProperties>(new CampaignProperties(state));
}

// FUNCTION: GAMEMD 0x76BED0
CampaignProperties::~CampaignProperties()
{
}

// FUNCTION: GAMEMD 0x76BF00
CampaignProperties::CampaignProperties(const rc_ptr<WDTState>& state)
    : State(state),
      Member_10(state.Pointer != 0
                    ? StringTable_LoadString(state->unknown_08, 0, "D:\\ra2mdpost\\WDTProps.cpp", 20)
                    : StringTable_LoadString("\"WDT:DefaultShortDescription\"", 0,
                                             "D:\\ra2mdpost\\WDTProps.cpp", 20)),
      Member_14(state.Pointer != 0
                    ? StringTable_LoadString(state->unknown_0C, 0, "D:\\ra2mdpost\\WDTProps.cpp", 21)
                    : StringTable_LoadString("\"WDT:DefaultLongDescription\"", 0,
                                             "D:\\ra2mdpost\\WDTProps.cpp", 21))
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76BFA0
int CampaignProperties::FUN_0076BFA0() const
{
    if (State.Pointer != 0) {
        return State->unknown_18;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76BFC0
int CampaignProperties::FUN_0076BFC0() const
{
    if (State.Pointer != 0) {
        return State->unknown_14;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76BFE0
int CampaignProperties::FUN_0076BFE0() const
{
    if (State.Pointer != 0) {
        return State->unknown_24 - 1;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76BFF0
Member_7B46F0 CampaignProperties::FUN_0076BFF0() const
{
    return Member_7B46F0(State.Pointer != 0 ? State->unknown_10 : STR_00889F64);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76C030
void* CampaignProperties::DeletingDtor(unsigned int flags)
{
    this->~CampaignProperties();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
