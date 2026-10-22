// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//   The retail assert path string names this unit WDTProps.cpp. /Ob2 lets the
//   out-of-line destructor 0x76BED0 also expand inside the deleting wrapper
//   0x76C030, as retail does.
#include "world_domination_tour.h"

using WorldDominationTour::CampaignProperties;

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- __fastcall string-table lookup.
wchar_t* __fastcall StringTable_LoadString(const char* label, int* out,
                                           const char* file, int line);
// GLOBAL: GAMEMD 0x889F64 -- the shared empty default string.
extern const char STR_00889F64[];

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

// FUNCTION: GAMEMD 0x76BFA0
int CampaignProperties::FUN_0076BFA0() const
{
    if (State.Pointer != 0) {
        return State->unknown_18;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x76BFC0
int CampaignProperties::FUN_0076BFC0() const
{
    if (State.Pointer != 0) {
        return State->unknown_14;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x76BFE0
int CampaignProperties::FUN_0076BFE0() const
{
    if (State.Pointer != 0) {
        return State->unknown_24 - 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x76BFF0
Member_7B46F0 CampaignProperties::FUN_0076BFF0() const
{
    return Member_7B46F0(State.Pointer != 0 ? State->unknown_10 : STR_00889F64);
}

// FUNCTION: GAMEMD 0x76C030
void* CampaignProperties::DeletingDtor(unsigned int flags)
{
    this->~CampaignProperties();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
