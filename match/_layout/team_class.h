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
#include "frame_timer.h"

class FootClass;
class HouseClass;
class TeamTypeClass;
class TagClass;
class ScriptClass;
struct ScriptActionNode;
struct TeamMember_r14;
struct ActionArg_r14;

// VTABLE: GAMEMD 0x7F4730 TeamClass (IPersistStream primary)
// VTABLE: GAMEMD 0x7F4714 TeamClass (IRTTITypeInfo, +0x04)
// VTABLE: GAMEMD 0x7F470C TeamClass (INoticeSink, +0x08)
// VTABLE: GAMEMD 0x7F4704 TeamClass (INoticeSource, +0x0C)
class TeamClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x6E8A90 (decl; reloc) -- constructor, as the class factory calls it.
    TeamClass(int unknown_arg0 = 0, int unknown_arg1 = 0, int unknown_arg2 = 0);
    virtual ~TeamClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual void vf_10(void* target, bool removed);
    virtual int vf_11();
    virtual int vf_12();
    // FUNCTION: GAMEMD 0x6EC5A0 (declaration; checksum override)
    // Retail primary slot 13: thiscall with one pointer argument.
    virtual void vf_13(Obj_004A1D30* crc);
    // FUNCTION: GAMEMD 0x6E9140 (declaration only; body unrecovered)
    // Retail primary slot 23: void return follows the base declaration provisionally.
    virtual void vf_23();

private:
    // Inline-only no-init reconstruction used after the raw stream read.
    TeamClass(const AbstractNoInit& noInit)
        : AbstractClass(noInit), unknown_64(noInit) {}

public:
    TeamTypeClass*  Type;                // +0x24
    ScriptClass*    Target28;            // +0x28
    HouseClass*     unknown_2C;          // +0x2C
    void*           unknown_30;          // +0x30
    AbstractClass*  Member34;            // +0x34
    AbstractClass*  unknown_38;          // +0x38; 6EAEE0 writes Cell/Foot common-base pointers
    void*           unknown_3C;          // +0x3C
    void*           unknown_40;          // +0x40
    void*           unknown_44;          // +0x44
    int             unknown_48;          // +0x48, checksum6EC5EF
    int             unknown_4C;          // +0x4C, checksum6EC5FA
    char            _pad_50[4];
    FootClass*      FirstUnit;           // +0x54
    CDTimerClass    unknown_58;          // +0x58, inline countdown6EC61E
    CDTimerClass    unknown_64;          // +0x64, inline countdown6EC643
    TagClass*       unknown_70;          // +0x70
    bool            unknown_74;
    char            _pad_75[0x77 - 0x75];
    bool            Flag77;              // +0x77
    bool            Flag78;              // +0x78
    unsigned char   unknown_79;
    bool            Flag7A;              // +0x7A
    bool            Flag7B;              // +0x7B
    unsigned char   unknown_7C;
    unsigned char   unknown_7D;
    unsigned char   unknown_7E;
    bool            Flag7F;              // +0x7F
    bool            Done;                // +0x80
    char            _pad_81;
    bool            Flag82;              // +0x82
    unsigned char   unknown_83;
    bool            unknown_84;
    char            _pad_85[3];
    int             unknown_88[6];       // ctor6E8CF1/CF7 clears six DWORDs; checksum appends24 bytes

    // GAMEMD 0x6E9050 -- clears/assigns the team's mission target.
    void AssignMissionTarget(AbstractClass* pTarget);

    // GAMEMD 0x6EC3A0 -- flag every member as scan-limited.
    void ScanLimit();
    // FUNCTION: GAMEMD 0x6EAEE0 (declaration; actual provider pending).
    void FUN_006EAEE0(AbstractClass**, AbstractClass**);
    // FUNCTION: GAMEMD 0x6EDB50 (declaration; thiscall, RET 8).
    void FUN_006EDB50(ScriptActionNode*, bool);
    // FUNCTION: GAMEMD 0x6EF610 (declaration; thiscall, RET 8).
    void FUN_006EF610(ScriptActionNode* action, bool enabled);

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
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Type) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Target28) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Member34) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->FirstUnit) == 4);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_70) == 0x70);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_2C) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_30) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_38) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_3C) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_40) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_44) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_70) == 4);
GG_STATIC_ASSERT(offsetof(TeamClass, Member34) == 0x34);
GG_STATIC_ASSERT(offsetof(TeamClass, FirstUnit) == 0x54);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag77)   == 0x77);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag78)   == 0x78);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7A)   == 0x7A);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7B)   == 0x7B);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7F)   == 0x7F);
GG_STATIC_ASSERT(offsetof(TeamClass, Done)     == 0x80);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag82)    == 0x82);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_84) == 0x84);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_48) == 4);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_4C) == 4);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_58) == 0x58);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_58) == 12);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_64) == 0x64);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_64) == 12);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_79) == 0x79);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_79) == 1);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_7C) == 1);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_7D) == 0x7D);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_7D) == 1);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_7E) == 0x7E);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_7E) == 1);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_83) == 0x83);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_83) == 1);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_88) == 0x88);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_88) == 24);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Flag77) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Flag78) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Flag7A) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Flag7B) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Flag7F) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Done) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->Flag82) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_88[0]) == 4);
GG_STATIC_ASSERT(sizeof(TeamClass)             == 0xA0);
#endif

#endif // GG_MATCH_LAYOUT_TEAM_CLASS_H
