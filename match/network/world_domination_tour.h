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
class Member_7B46F0
{
public:
    Member_7B46F0(const char* text);   // 0x7B4630
    ~Member_7B46F0();
    void* Data;
};

// Out-of-line destructor 0x7B6760 (a four-byte member).
class Member_7B6760
{
public:
    Member_7B6760(const wchar_t* text);   // 0x7B66D0
    ~Member_7B6760();
    void* Data;
};

// rc_ptr_base and rc_ptr<T> are the canonical ones (rc_ptr_base.cpp has the
// out-of-line constructor, destructor and deleting destructor).
#include "wdt_rc_ptr_base.h"

class WDTTerritory;
class WDTState;

// ReferenceCounted (RTTI vtable 0x7F0954): destructor out of line at 0x65D660.
// This is the model the scalar deleting destructors of these classes need (a
// non-virtual destructor, slot 0 held by DeletingDtor); wdt_rc_ptr.h has the
// virtual-destructor model the constructed classes use.
class ReferenceCounted
{
public:
    ReferenceCounted() : RefCount(0) {}
    ~ReferenceCounted();
    virtual void* DeletingDtor(unsigned int flags);
    virtual long vf_04();   // 0x65D690 in every derived table
    virtual long vf_08();   // 0x65D670 in every derived table
    long RefCount;   // +0x04
};

GG_STATIC_ASSERT(offsetof(ReferenceCounted, RefCount) == 0x04);

namespace WorldDominationTour {

// VTABLE: GAMEMD 0x7F6FC4
// 0x10 bytes: allocated with operator new(0x10) at 0x765F69.
class Conflict : public ReferenceCounted
{
public:
    Conflict(const rc_ptr<WDTTerritory>& territory) : Territory(territory) {}
    ~Conflict() {}
    virtual void* DeletingDtor(unsigned int flags);
    bool operator==(const Conflict& other) const;   // 0x766010
    int FUN_00766060() const;
    rc_ptr<WDTTerritory> Territory;   // +0x08
};

// VTABLE: GAMEMD 0x7F70DC
class History : public ReferenceCounted
{
public:
    ~History() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTState> State;   // +0x08
};

// VTABLE: GAMEMD 0x7F7314
class State : public ReferenceCounted
{
public:
    ~State() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTState> Next;   // +0x08
};

// VTABLE: GAMEMD 0x7F7334
class Territory : public ReferenceCounted
{
public:
    ~Territory() {}
    virtual void* DeletingDtor(unsigned int flags);
    int unknown_08;            // +0x08
    Member_7B6760 Member_0C;   // +0x0C
    char unknown_10[0x10];     // +0x10
    Member_7B46F0 Member_20;   // +0x20
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
    ~GameOption() {}
    virtual void* DeletingDtor(unsigned int flags);
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
    virtual void* DeletingDtor(unsigned int flags);
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
    MapSizeGameOption(unsigned int value) { unknown_08 = value; }
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
    ~PlayerProfile() {}
    virtual void* DeletingDtor(unsigned int flags);
    int unknown_08;            // +0x08
    Member_7B46F0 Member_0C;   // +0x0C
    char unknown_10[0x2C];     // +0x10
    Member_7B6760 Member_3C;   // +0x3C
    Member_7B6760 Member_40;   // +0x40
};

GG_STATIC_ASSERT(offsetof(WorldDominationTour::Conflict, Territory) == 0x08);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::Territory, Member_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::Territory, Member_20) == 0x20);
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
    virtual void* DeletingDtor(unsigned int flags);

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
    virtual void* DeletingDtor(unsigned int flags);

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
    unsigned char unknown_2C[0x18]; // +0x2C
    void** unknown_44;           // +0x44
    unsigned char unknown_48;    // +0x48
};

GG_STATIC_ASSERT(sizeof(WDTState) == 0x4C);
GG_STATIC_ASSERT(offsetof(WDTState, unknown_44) == 0x44);

namespace WorldDominationTour {

// WorldDominationTour::CampaignProperties (RTTI vtable 0x7F7294, slot 0 = 0x76C030).
class CampaignProperties : public ReferenceCounted
{
public:
    CampaignProperties(const rc_ptr<WDTState>& state);   // 0x76BF00
    ~CampaignProperties();                               // 0x76BED0
    virtual void* DeletingDtor(unsigned int flags);      // 0x76C030

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
