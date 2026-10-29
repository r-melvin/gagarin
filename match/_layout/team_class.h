// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   TeamClass — an AI strike team. Constructor 0x6E8A90 (operator new size 0xA0
//   in TeamTypeClass::CreateTeam 0x6F09C0), Type @0x24 matched by the instance
//   walks of TeamTypeClass (0x6F0A70 / 0x6F1F30 / 0x6F1F70), the member offsets
//   below read by ScanLimit 0x6EC3A0. The full member set is not recovered; the
//   unnamed ranges are padding.
#ifndef GG_MATCH_LAYOUT_TEAM_CLASS_H
#define GG_MATCH_LAYOUT_TEAM_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"

class FootClass;
class HouseClass;
class TeamTypeClass;
struct TeamTarget_r14;
struct TeamMember_r14;
struct ActionArg_r14;

class TeamClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x6E8A90 (decl; reloc) -- constructor, as the class factory calls it.
    TeamClass(int unknown_arg0 = 0, int unknown_arg1 = 0, int unknown_arg2 = 0);
    virtual ~TeamClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();

    TeamTypeClass*  Type;                // +0x24
    TeamTarget_r14* Target28;            // +0x28
    char            _pad_2C[0x34 - 0x2C];
    TeamMember_r14* Member34;            // +0x34
    char            _pad_38[0x54 - 0x38];
    FootClass*      FirstUnit;           // +0x54
    char            _pad_58[0x77 - 0x58];
    bool            Flag77;              // +0x77
    bool            Flag78;              // +0x78
    char            _pad_79;
    bool            Flag7A;              // +0x7A
    bool            Flag7B;              // +0x7B
    char            _pad_7C[0x7F - 0x7C];
    bool            Flag7F;              // +0x7F
    bool            Done;                // +0x80
    char            _pad_81[0xA0 - 0x81];

    // GAMEMD 0x6E9050 -- clears/assigns the team's mission target.
    void AssignMissionTarget(AbstractClass* pTarget);

    // GAMEMD 0x6EC3A0 -- flag every member as scan-limited.
    void ScanLimit();

    // FUNCTION: GAMEMD 0x6EA870 (decl; reloc) -- TeamClass::LiberateMember.
    void LiberateMember(FootClass* foot, int idx, unsigned char count);
    // FUNCTION: GAMEMD 0x6EBAD0 (decl; reloc)
    void FUN_006EBAD0();
    // FUNCTION: GAMEMD 0x6EA080
    void FUN_006EA080();
    // FUNCTION: GAMEMD 0x6EC730
    void FUN_006EC730(int a1, bool a2);
    // FUNCTION: GAMEMD 0x6ECB50
    void FUN_006ECB50(int a1, int a2);
    // FUNCTION: GAMEMD 0x6ECF10
    void FUN_006ECF10(int a1, int a2);
    // FUNCTION: GAMEMD 0x6ECF50
    void FUN_006ECF50(ActionArg_r14* a1, int a2);
    // FUNCTION: GAMEMD 0x6EDC70
    void FUN_006EDC70(int a1, int a2);

    // FUNCTION: GAMEMD 0x6E8A90 (decl; reloc) -- the same constructor as a member returning
    // `this`, so the call is a plain `MOV ECX,EAX; CALL` after the null test, without the
    // EH frame a real `new T(...)` would register under /GX.
    TeamClass* Construct(TeamTypeClass* type, HouseClass* house, int arg);
    // GAMEMD 0x6EF5F0 -- flash the team (one stack argument).
    void Flash(int duration);
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TeamClass, Type)     == 0x24);
GG_STATIC_ASSERT(offsetof(TeamClass, Target28) == 0x28);
GG_STATIC_ASSERT(offsetof(TeamClass, Member34) == 0x34);
GG_STATIC_ASSERT(offsetof(TeamClass, FirstUnit) == 0x54);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag77)   == 0x77);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag78)   == 0x78);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7A)   == 0x7A);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7B)   == 0x7B);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7F)   == 0x7F);
GG_STATIC_ASSERT(offsetof(TeamClass, Done)     == 0x80);
GG_STATIC_ASSERT(sizeof(TeamClass)             == 0xA0);
#endif

#endif // GG_MATCH_LAYOUT_TEAM_CLASS_H
