// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x6EF4D0: on the team `[EBP+0x24]` (the team
//   type) and `[EBP+0x54]` (the first member); on the team type `[EAX+0xE4]`
//   (the taskforce); on the taskforce `[EAX+0x9C]` (entry count) and the
//   8-byte entries at `[EAX+EDI*8+0xA4]` (amount) / `[EAX+EDI*8+0xA8]` (type);
//   on each member the slot `[EDX+0x84]` (GetTechnoType) and the next link
//   `[EDI+0x5D8]`; on the output vector (ESI) the inlined AddItem reading
//   +0x08 / +0x0D / +0x14 / +0x10 / +0x04 and calling slot +0x08 (SetCapacity),
//   the virtual `[EAX+0x10]` (FindItemIndex, address of the item pushed) and
//   the inlined RemoveItem. Names are YRpp's; every
//   offset reconfirmed here and against match/ai/team_type_class_taskforce_
//   methods.h (TaskForce +0xE4, CountEntries +0x9C, Entries +0xA4) and
//   match/_layout/foot_class.h (NextTeamMember +0x5D8).
#ifndef GG_MATCH_AI_TEAM_CLASS_MISSING_MEMBERS_METHODS_H
#define GG_MATCH_AI_TEAM_CLASS_MISSING_MEMBERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct TechnoType_006EF4D0;

// DynamicVectorClass<TechnoTypeClass*> — the output vector. The virtuals are
// declared (no body) so cl emits the indirect vtable calls in retail slot
// order; AddItem and RemoveItem are the non-virtual members retail inlined.
class TypeVector_006EF4D0
{
public:
    virtual ~TypeVector_006EF4D0();                                          // +0x00
    virtual bool operator==(const TypeVector_006EF4D0& other) const;        // +0x04
    virtual bool SetCapacity(int capacity, TechnoType_006EF4D0** pMem);     // +0x08
    virtual void Clear();                                                    // +0x0C
    virtual int  FindItemIndex(TechnoType_006EF4D0* const& item) const;     // +0x10

    bool AddItem(TechnoType_006EF4D0* item)
    {
        if (this->Count >= this->Capacity) {
            if (!this->IsAllocated && this->Capacity != 0) {
                return false;
            }
            if (this->CapacityIncrement <= 0) {
                return false;
            }
            if (!this->SetCapacity(this->Capacity + this->CapacityIncrement, 0)) {
                return false;
            }
        }
        int index = this->Count;
        this->Count = index + 1;
        this->Items[index] = item;
        return true;
    }

    bool RemoveItem(int index)
    {
        if (index < this->Count) {
            --this->Count;
            for (int i = index; i < this->Count; ++i) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
        return false;
    }

    TechnoType_006EF4D0** Items;      // +0x04
    int   Capacity;                   // +0x08
    bool  IsInitialized;              // +0x0C
    bool  IsAllocated;                // +0x0D
    int   Count;                      // +0x10
    int   CapacityIncrement;          // +0x14
};
GG_STATIC_ASSERT(offsetof(TypeVector_006EF4D0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TypeVector_006EF4D0, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(TypeVector_006EF4D0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(TypeVector_006EF4D0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TypeVector_006EF4D0, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TypeVector_006EF4D0) == 0x18);

// One taskforce entry: 8 bytes, the type pointer second.
struct TaskForceEntry_006EF4D0
{
    int                   Amount;   // +0x0000
    TechnoType_006EF4D0*  Type;     // +0x0004
};
GG_STATIC_ASSERT(sizeof(TaskForceEntry_006EF4D0) == 8);

// TaskForceClass (partial).
struct TaskForce_006EF4D0
{
    char _pad000[0x9C];                   // +0x0000
    int  CountEntries;                    // +0x009C
    char _pad0A0[0x4];                    // +0x00A0
    TaskForceEntry_006EF4D0 Entries[6];   // +0x00A4  (type pointer at +0xA8)
};
GG_STATIC_ASSERT(offsetof(TaskForce_006EF4D0, CountEntries) == 0x9C);
GG_STATIC_ASSERT(offsetof(TaskForce_006EF4D0, Entries) == 0xA4);

// TeamTypeClass (partial).
struct TeamType_006EF4D0
{
    char _pad000[0xE4];               // +0x0000
    TaskForce_006EF4D0* TaskForce;    // +0x00E4
};
GG_STATIC_ASSERT(offsetof(TeamType_006EF4D0, TaskForce) == 0xE4);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct FootVtbl_006EF4D0;

// FootClass (partial): the team-member link and the GetTechnoType slot.
struct Foot_006EF4D0
{
    FootVtbl_006EF4D0* Vtbl;          // +0x0000
    char _pad004[0x5D4];              // +0x0004
    Foot_006EF4D0* NextTeamMember;    // +0x05D8
};
GG_STATIC_ASSERT(offsetof(Foot_006EF4D0, NextTeamMember) == 0x5D8);

typedef TechnoType_006EF4D0* (Foot_006EF4D0::*Fn84_006EF4D0)();

struct FootVtbl_006EF4D0
{
    char _pad000[0x84];               // +0x0000
    Fn84_006EF4D0 GetTechnoType;      // +0x0084
};
GG_STATIC_ASSERT(offsetof(FootVtbl_006EF4D0, GetTechnoType) == 0x84);

// TeamClass (partial).
struct Team_006EF4D0
{
    char _pad000[0x24];               // +0x0000
    TeamType_006EF4D0* Type;          // +0x0024
    char _pad028[0x2C];               // +0x0028
    Foot_006EF4D0* FirstUnit;         // +0x0054

    // FUNCTION: GAMEMD 0x6EF4D0 — TeamClass::GetTaskForceMissingMemberTypes.
    void GetTaskForceMissingMemberTypes(TypeVector_006EF4D0* out);
};
GG_STATIC_ASSERT(offsetof(Team_006EF4D0, Type) == 0x24);
GG_STATIC_ASSERT(offsetof(Team_006EF4D0, FirstUnit) == 0x54);

#endif  // GG_MATCH_AI_TEAM_CLASS_MISSING_MEMBERS_METHODS_H
