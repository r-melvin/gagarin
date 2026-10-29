// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The World Domination Tour reference-counted data classes.
// Class names are the retail RTTI names.
#ifndef GG_MATCH_NETWORK_WORLD_DOMINATION_TOUR_H
#define GG_MATCH_NETWORK_WORLD_DOMINATION_TOUR_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

// Out-of-line destructor 0x7B46F0 (a four-byte member: a string handle).
#include "../_layout/member_7b46f0.h"

// Out-of-line destructor 0x7B6760 (a four-byte member).
class Member_7B6760
{
public:
    Member_7B6760(const wchar_t* text);   // 0x7B66D0
    ~Member_7B6760();
    void* Data;
};

// ReferenceCounted, rc_ptr_base and rc_ptr<T> are the canonical ones in
// wdt_rc_ptr.h (rc_ptr_base.cpp has the out-of-line members).
#include "wdt_rc_ptr.h"
#include "../core/vector_class.h"

class WDTTerritory;
class WDTState;

namespace WorldDominationTour {

// VTABLE: GAMEMD 0x7F6FC4
// 0x10 bytes: allocated with operator new(0x10) at 0x765F69.
class Conflict : public ReferenceCounted
{
public:
    Conflict(const rc_ptr<WDTTerritory>& territory);   // 0x765FD0
    ~Conflict();   // 0x766030
    bool operator==(const Conflict& other) const;   // 0x766010
    int FUN_00766060() const;
    rc_ptr<WDTTerritory> Territory;   // +0x08
};

// VTABLE: GAMEMD 0x7F70DC
// Size 0x10: the factory 0x767B00 allocates 0x10 bytes.
class State;
class History : public ReferenceCounted
{
public:
    History(const rc_ptr<WDTState>& state);   // 0x767B70
    ~History();   // 0x767BF0
    rc_ptr<WorldDominationTour::State> FUN_00767BB0(int arg) const;
    int FUN_00767BD0(unsigned int index) const;
    rc_ptr<WDTState> State;   // +0x08
};
GG_STATIC_ASSERT(offsetof(History, State) == 0x08);
GG_STATIC_ASSERT(sizeof(History) == 0x10);

// VTABLE: GAMEMD 0x7F6F3C
// 0x4C bytes: operator new(0x4C) at 0x764B55 (factory 0x764B30). The
// destructor 0x764F30 releases the +0x48 string, the conflict list, then the
// history and properties handles.
class CampaignProperties;
class Campaign : public ReferenceCounted
{
public:
    Campaign(unsigned int first, const rc_ptr_base& source);   // 0x764B90
    ~Campaign();   // 0x764F30
    rc_ptr<CampaignProperties> Properties;                // +0x08
    rc_ptr<History> Hist;                                 // +0x10
    DynamicVectorClass<rc_ptr<Conflict> > Conflicts;      // +0x18
    char unknown_30[0x18];                                // +0x30
    Member_7B46F0 Member_48;                              // +0x48
};
GG_STATIC_ASSERT(offsetof(Campaign, Properties) == 0x08);
GG_STATIC_ASSERT(offsetof(Campaign, Hist) == 0x10);
GG_STATIC_ASSERT(offsetof(Campaign, Conflicts) == 0x18);
GG_STATIC_ASSERT(offsetof(Campaign, Member_48) == 0x48);
GG_STATIC_ASSERT(sizeof(Campaign) == 0x4C);

// VTABLE: GAMEMD 0x7F7314
class State : public ReferenceCounted
{
public:
    State();                                                       // 0x76F560
    State(const rc_ptr<WDTState>& state, unsigned int index);     // 0x76F5A0
    ~State();   // 0x76F650
    rc_ptr<WDTState> Next;   // +0x08
    void* unknown_10;        // +0x10 the row of Next picked by the index (0 when out of range)
};
GG_STATIC_ASSERT(sizeof(State) == 0x14);   // operator new(0x14) at 0x76F504

// VTABLE: GAMEMD 0x7F7334
class Territory : public ReferenceCounted
{
public:
    ~Territory();   // 0x76FD10
    int unknown_08;            // +0x08
    Member_7B6760 Member_0C;   // +0x0C
    char unknown_10[0x10];     // +0x10
    Member_7B46F0 Member_20;   // +0x20
    char unknown_24[0xC];      // +0x24 (operator new(0x30) at 0x76F916)

    // FUNCTION: GAMEMD 0x76F970 (decl; reloc) -- builds a territory from five values.
    Territory(int a, void* b, char* c, unsigned int* d, unsigned int* e);
};

}  // namespace WorldDominationTour

// The object the option slot-3 methods read through their rc_ptr argument
// (0x7674E0 reads +0x38, 0x767800 the bytes at +0x12/+0x13). Its RTTI class
// is not identified.
class Obj_007674E0 : public ReferenceCounted
{
public:
    char unknown_08[0x0A];          // +0x08
    unsigned char unknown_12;       // +0x12
    unsigned char unknown_13;       // +0x13
    char unknown_14[0x24];          // +0x14
    unsigned int unknown_38;        // +0x38
};

GG_STATIC_ASSERT(offsetof(Obj_007674E0, unknown_12) == 0x12);
GG_STATIC_ASSERT(offsetof(Obj_007674E0, unknown_38) == 0x38);

namespace WorldDominationTour {

// VTABLE: GAMEMD 0x7F7060
// 0x0C bytes: MapSizeGameOption, which adds no member, is allocated with
// operator new(0x0C) at 0x7676F6. Slot 3 takes the rc_ptr above (ret 4 in
// every override); slot 4's arguments are not recovered.
class GameOption : public ReferenceCounted
{
public:
    GameOption(unsigned int flags) : unknown_08(flags) {}
    virtual ~GameOption();   // 0x767300
    virtual int vf_0C(const rc_ptr<Obj_007674E0>& subject) const;
    virtual int vf_10();                                          // (signature unrecovered)
    bool FUN_00767310(const rc_ptr<Obj_007674E0>& subject) const;
    unsigned int unknown_08;   // +0x08
};

// ValueGameOption<T> (vtable 0x7F7048 for unsigned char).
template <class T>
class ValueGameOption : public GameOption
{
public:
    ValueGameOption(unsigned int flags, int when_set, Member_7B46F0 name, int when_clear)   // 0x766A10
        : GameOption(flags), unknown_0C(when_clear), unknown_10(when_set), Member_14(name)
    {
    }
    virtual int vf_0C(const rc_ptr<Obj_007674E0>& subject) const
    {
        if (FUN_00767310(subject))
            return 2;
        return unknown_0C;
    }
    int unknown_0C;            // +0x0C
    int unknown_10;            // +0x10
    Member_7B46F0 Member_14;   // +0x14
};

// VTABLE: GAMEMD 0x7F709C
// Implicit destructor: the members, then GameOption's inline one.
class FlagGameOption : public GameOption
{
public:
    FlagGameOption(unsigned int flags, Member_7B46F0 name18, int when_clear, Member_7B46F0 name14, int when_set);   // 0x767820
    virtual int vf_0C(const rc_ptr<Obj_007674E0>& subject) const;
    int unknown_0C;            // +0x0C
    int unknown_10;            // +0x10
    Member_7B46F0 Member_14;   // +0x14
    Member_7B46F0 Member_18;   // +0x18
};

// MapSizeGameOption (vtable 0x7F70B4).
class MapSizeGameOption : public GameOption
{
public:
    MapSizeGameOption(unsigned int value) : GameOption(value) {}
    virtual int vf_0C(const rc_ptr<Obj_007674E0>& subject) const;
};

}  // namespace WorldDominationTour

GG_STATIC_ASSERT(sizeof(WorldDominationTour::GameOption) == 0x0C);
GG_STATIC_ASSERT(sizeof(WorldDominationTour::MapSizeGameOption) == 0x0C);
GG_STATIC_ASSERT(sizeof(WorldDominationTour::Conflict) == 0x10);

// VTABLE: GAMEMD 0x7F74F4
class PlayerProfile : public ReferenceCounted
{
public:
    ~PlayerProfile();   // 0x77A050
    int unknown_08;            // +0x08
    Member_7B46F0 Member_0C;   // +0x0C
    char unknown_10[0x2C];     // +0x10
    Member_7B6760 Member_3C;   // +0x3C
    Member_7B6760 Member_40;   // +0x40
};

GG_STATIC_ASSERT(offsetof(WorldDominationTour::Conflict, Territory) == 0x08);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::State, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::Territory, Member_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::Territory, Member_20) == 0x20);
GG_STATIC_ASSERT(sizeof(WorldDominationTour::Territory) == 0x30);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::FlagGameOption, Member_14) == 0x14);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::FlagGameOption, Member_18) == 0x18);
GG_STATIC_ASSERT(offsetof(PlayerProfile, Member_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(PlayerProfile, Member_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(PlayerProfile, Member_40) == 0x40);

// WDTTerritory (RTTI vtable 0x7F7220). Constructor 0x76AAF0 sets every field;
// destructor 0x76AB90. Field meanings are unknown.
class WDTTerritory : public ReferenceCounted
{
public:
    WDTTerritory();
    ~WDTTerritory();

    int unknown_08;              // +0x08
    short unknown_0C;            // +0x0C
    unsigned char unknown_0E;    // +0x0E
    unsigned char unknown_0F;    // +0x0F
    short unknown_10;            // +0x10
    unsigned char unknown_12;    // +0x12
    unsigned char unknown_13;    // +0x13
    unsigned char unknown_14;    // +0x14
    unsigned char unknown_15[7]; // +0x15
    unsigned char unknown_1C;    // +0x1C
    unsigned char unknown_1D;    // +0x1D
    unsigned char unknown_1E;    // +0x1E
    struct Entry
    {
        unsigned char unknown_00;
        unsigned char unknown_01;
        unsigned char unknown_02;
    };
    Entry unknown_1F[8];         // +0x1F
    unsigned char unknown_37;    // +0x37
    int unknown_38;              // +0x38
    int unknown_3C;              // +0x3C
};

GG_STATIC_ASSERT(sizeof(WDTTerritory) == 0x40);   // operator new(0x40) at 0x76AAB4
GG_STATIC_ASSERT(offsetof(WDTTerritory, unknown_1F) == 0x1F);

// WDTState (RTTI vtable 0x7F7250): 0x4C bytes (operator new(0x4C) at
// 0x76ABA6). The three strings at +0x08..+0x10 are freed by the destructor
// 0x76AFC0; +0x2C is a DynamicVectorClass<rc_ptr<WDTTerritory>> (vtable
// 0x7F7260), kept opaque here; +0x44 is a row table of +0x24 rows.
class WDTState : public ReferenceCounted
{
public:
    WDTState();                  // 0x76ABE0
    WDTState(void* source);      // 0x76AC90
    ~WDTState();                 // 0x76AFC0

    bool FUN_0076B080() const;
    unsigned char FUN_0076B090() const;

    char* unknown_08;            // +0x08 short description label
    char* unknown_0C;            // +0x0C long description label
    char* unknown_10;            // +0x10
    unsigned char unknown_14;    // +0x14
    int unknown_18;              // +0x18
    int unknown_1C;              // +0x1C
    int unknown_20;              // +0x20
    int unknown_24;              // +0x24
    int unknown_28;              // +0x28
    DynamicVectorClass<rc_ptr<WDTTerritory> > Territories;   // +0x2C
    void** unknown_44;           // +0x44
    unsigned char unknown_48;    // +0x48
};

GG_STATIC_ASSERT(sizeof(WDTState) == 0x4C);
GG_STATIC_ASSERT(offsetof(WDTState, Territories) == 0x2C);
GG_STATIC_ASSERT(offsetof(WDTState, unknown_44) == 0x44);

namespace WorldDominationTour {

// WorldDominationTour::CampaignProperties (RTTI vtable 0x7F7294, slot 0 = 0x76C030).
class CampaignProperties : public ReferenceCounted
{
public:
    CampaignProperties(const rc_ptr<WDTState>& state);   // 0x76BF00
    ~CampaignProperties();                               // 0x76BED0

    int FUN_0076BFA0() const;
    int FUN_0076BFC0() const;
    int FUN_0076BFE0() const;
    Member_7B46F0 FUN_0076BFF0() const;

    rc_ptr<WDTState> State;      // +0x08
    Member_7B6760 Member_10;     // +0x10 short description (wide)
    Member_7B6760 Member_14;     // +0x14 long description (wide)
};

GG_STATIC_ASSERT(sizeof(CampaignProperties) == 0x18);   // operator new(0x18) at 0x76BE96
GG_STATIC_ASSERT(offsetof(CampaignProperties, Member_14) == 0x14);

}  // namespace WorldDominationTour

#endif
