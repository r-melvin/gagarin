// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// The planning-mode classes whose bodies sit in PlanMgr.cpp (the __FILE__
// string "D:\\ra2mdpost\\PlanMgr.cpp" at 0x836BD4).
//
// Class names come from the retail RTTI of the vectors that hold them:
// DynamicVectorClass<PlanningMemberClass*> (table 0x7EFEE4) and
// DynamicVectorClass<PlanningBranchClass*> (0x7EFEC4) are the two vectors a
// PlanningNodeClass constructs at +0x00 and +0x20 (0x633CC0), and the node
// destructor removes `this` from the DynamicVectorClass<PlanningNodeClass*>
// globals (0x633D30). Member and method names are placeholders.
#ifndef GG_MATCH_AI_PLANNING_MANAGER_H
#define GG_MATCH_AI_PLANNING_MANAGER_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"
#include "../network/event_class_ctors.h"
#include "../_layout/techno_class.h"
#include "../_layout/geometry2d.h"

class PlanningTokenClass;

// The object a target resolves to (TargetClass 0x6E6E20); slot 22 (+0x58)
// returns its coordinate. Only that slot is typed.
class TargetAbstract
{
public:
    virtual void vf_0(); virtual void vf_1(); virtual void vf_2(); virtual void vf_3(); virtual void vf_4();
    virtual void vf_5(); virtual void vf_6(); virtual void vf_7(); virtual void vf_8(); virtual void vf_9();
    virtual void vf_10(); virtual void vf_11(); virtual void vf_12(); virtual void vf_13(); virtual void vf_14();
    virtual void vf_15(); virtual void vf_16(); virtual void vf_17(); virtual void vf_18(); virtual void vf_19();
    virtual void vf_20(); virtual void vf_21();
    virtual CoordStruct vf_22();   // +0x58
};


// One unit on a node: allocated 0x10 bytes (0x633FA6: PUSH 0x10; CALL new).
class PlanningMemberClass
{
public:
    // FUNCTION: GAMEMD 0x633A20 (defined in planning_manager.cpp)
    PlanningMemberClass();
    void FUN_00633A40(TechnoClass* owner);
    void FUN_00633A50(EventClass* event);
    void FUN_00633A60(int branch);
    void FUN_00633A70(bool flag);
    TechnoClass* FUN_00633A80();
    EventClass* FUN_00633A90();
    int FUN_00633AA0();
    bool FUN_00633AB0();

    TechnoClass* Owner;   // +0x00
    EventClass* Event;    // +0x04
    int unknown_08;       // +0x08 index into the node's branches (-1 = none)
    bool unknown_0C;      // +0x0C
};
GG_STATIC_ASSERT(offsetof(PlanningMemberClass, Owner) == 0x00);
GG_STATIC_ASSERT(sizeof(PlanningMemberClass) == 0x10);
GG_STATIC_ASSERT(offsetof(PlanningMemberClass, Event) == 0x04);
GG_STATIC_ASSERT(offsetof(PlanningMemberClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(PlanningMemberClass, unknown_0C) == 0x0C);

// One branch: an embedded event (0x6F bytes, copied as 27 dwords, a word and
// a byte) followed by two ints.
class PlanningBranchClass
{
public:
    PlanningBranchClass();
    void FUN_00633AE0(const EventClass* event);
    void FUN_00633B00(int count);
    void FUN_00633B10(int value);
    void FUN_00633B20();
    int FUN_00633B30();
    int FUN_00633B40();
    EventClass FUN_00633B50();
    int FUN_00633B70();
    int FUN_00633B80();
    CoordStruct FUN_00633B90();
    Point2D* FUN_00633C60(Point2D* out);

    EventClass Event;     // +0x00
    int unknown_70;       // +0x70 reference count
    int unknown_74;       // +0x74 (-1 = none)
};
GG_STATIC_ASSERT(offsetof(PlanningBranchClass, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(PlanningBranchClass, unknown_74) == 0x74);
GG_STATIC_ASSERT(sizeof(PlanningBranchClass) == 0x78);

class PlanningNodeClass
{
public:
    PlanningNodeClass(int value);
    ~PlanningNodeClass();
    int FUN_00633E50();
    int FUN_00633E60();
    int FUN_00633E70(TechnoClass* techno);
    PlanningNodeClass* FUN_00633EA0(TechnoClass* techno);
    PlanningNodeClass* FUN_00633F20(TechnoClass* techno);
    void FUN_00633FA0(TechnoClass* techno, const EventClass* event);
    void FUN_006340B0(TechnoClass* techno);
    // FUNCTION: GAMEMD 0x634290 (decl; reloc)
    int FUN_00634290(TechnoClass* techno);
    TechnoClass* FUN_006342D0(int index);
    EventClass FUN_006342E0(int index);
    EventClass FUN_00634310(TechnoClass* techno);
    bool FUN_00634360(TechnoClass* techno);
    void* FUN_006343B0();
    CoordStruct FUN_006343C0();
    Point2D* FUN_00634400(Point2D* out);
    int FUN_00634470(int x, int y);
    bool FUN_00634550(int x, int y, int z);
    RectangleStruct FUN_006345A0();
    bool FUN_00634630();
    void FUN_00634680();
    PlanningMemberClass* FUN_006346B0(TechnoClass* techno);
    int FUN_00634700();
    bool FUN_00634710();
    bool FUN_00634720();
    TechnoClass* FUN_00634740(int branch);
    TechnoClass* FUN_00634770();
    // FUNCTION: GAMEMD 0x634E10 (decl; reloc)
    void FUN_00634E10(PlanningMemberClass* member);
    // FUNCTION: GAMEMD 0x635120 (decl; reloc)
    void FUN_00635120();
    // FUNCTION: GAMEMD 0x635DB0 (defined in planning_node_methods.cpp; the argument is a byte, read with
    // MOV AL,[ESP+4] / TEST AL,AL)
    void FUN_00635DB0(bool arg);

    // Methods defined in planning_node_methods.cpp (same PlanMgr.cpp block, continued).
    PlanningBranchClass* FUN_006347A0(int index);
    PlanningBranchClass* FUN_006347B0(TechnoClass* techno);
    CoordStruct FUN_00634810(int branch);
    CoordStruct FUN_00634850();
    Point2D* FUN_00634880(Point2D* out, int branch);
    Point2D* FUN_006348F0(Point2D* out);
    void FUN_00634970();
    void FUN_006349B0();
    void FUN_00635060(PlanningMemberClass* member);
    bool FUN_006351A0(TechnoClass* techno);
    void FUN_006351E0(PlanningMemberClass* member);
    void FUN_00635210();
    void FUN_006352D0();
    void FUN_00635310();
    void FUN_00635560(unsigned int color);
    // FUNCTION: GAMEMD 0x63AC70 (decl; reloc) -- ECX is the node; the body reads only the selection list.
    int FUN_0063AC70();
    RectangleStruct FUN_00635DF0();
    RectangleStruct FUN_00635E90();
    void FUN_006378B0();
    void FUN_00637D00();
    int FUN_00634CC0(TechnoClass* techno);
    void FUN_00634B20();

    // The embedded loop branch at +0x38..+0xAF: a whole PlanningBranchClass (its event at +0x38, its
    // count at +0xA8 and its -1 link at +0xAC are what the node constructor 0x633CC0 initialises as
    // unknown_38/unknown_A8/unknown_AC; 0x6349B0 indexes [+0x38 + 0x70] and copies 0x6F event bytes
    // into it, and 0x634B20 prints it as "Loop Branch"). Typed as bytes above.
    PlanningBranchClass& Loop() { return *(PlanningBranchClass*)&unknown_38; }

    // Inline member search (retail also keeps it out of line at 0x634290);
    // the index of the member `techno` owns, or -1.
    int MemberIndex(TechnoClass* techno)
    {
        int index = -1;
        for (int i = 0; i < Members.Count; i++) {
            if (Members.Items[i]->Owner == techno) {
                index = i;
                break;
            }
        }
        return index;
    }
    PlanningMemberClass* MemberOf(TechnoClass* techno)
    {
        int index = MemberIndex(techno);
        if (index == -1) {
            return 0;
        }
        return Members.Items[index];
    }

    DynamicVectorClass<PlanningMemberClass*> Members;    // +0x00
    int unknown_18;                                      // +0x18
    bool unknown_1C;                                     // +0x1C
    DynamicVectorClass<PlanningBranchClass*> Branches;   // +0x20
    bool unknown_38;                                     // +0x38
    char unknown_39[0xA8 - 0x39];                        // +0x39
    int unknown_A8;                                      // +0xA8
    int unknown_AC;                                      // +0xAC
    int unknown_B0;                                      // +0xB0
    int unknown_B4;                                      // +0xB4
};
GG_STATIC_ASSERT(offsetof(PlanningNodeClass, Members) == 0x00);
GG_STATIC_ASSERT(offsetof(PlanningNodeClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(PlanningNodeClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(PlanningNodeClass, Branches) == 0x20);
GG_STATIC_ASSERT(offsetof(PlanningNodeClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(PlanningNodeClass, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(PlanningNodeClass, unknown_B4) == 0xB4);

// The token a unit's nodes hang off.
class PlanningTokenClass
{
public:
    // FUNCTION: GAMEMD 0x635F20 (defined in planning_node_methods.cpp)
    PlanningTokenClass(TechnoClass* owner);
    // Declaration: GAMEMD 0x636590 -- hidden result pointer, packed EventClass.
    EventClass FUN_00636590();
    int FUN_00636DC0();
    void FUN_00636E00(PlanningNodeClass* node);
    PlanningNodeClass* FUN_00636E60(int index);
    PlanningNodeClass* FUN_00636EB0();
    int FUN_00636EE0(PlanningNodeClass* node);
    EventClass FUN_00636F00(int node);
    EventClass FUN_00636F60();
    PlanningNodeClass* FUN_00636F80();
    void FUN_00637040();

    // Inline node lookup with wrap-around past the end (no retail body of its
    // own; inlined into 0x633EA0 and 0x633F20; the out-of-line form is 0x636E60).
    PlanningNodeClass* NodeAt(int index)
    {
        if (Nodes.Count == 0) {
            return 0;
        }
        if (index >= Nodes.Count) {
            if (unknown_94 > 0 || unknown_94 == 0) {
                index = (index - unknown_94) % unknown_90 + unknown_94;
            } else {
                return 0;
            }
        }
        if (index < 0 || index >= Nodes.Count) {
            return 0;
        }
        return Nodes.Items[index];
    }

    // The last node, or none when empty (0x6349B0, 0x634CC0: Count - 1 < 0 gives none).
    PlanningNodeClass* LastNode()
    {
        int index = Nodes.Count - 1;
        if (index < 0) {
            return 0;
        }
        return Nodes.Items[index];
    }

    TechnoClass* Owner;                              // +0x00
    DynamicVectorClass<PlanningNodeClass*> Nodes;    // +0x04
    bool unknown_1C;                                 // +0x1C
    EventClass unknown_1D;                           // +0x1D (0x6F bytes; the constructor stores its Type = 0)
    int unknown_8C;                                  // +0x8C
    int unknown_90;                                  // +0x90
    int unknown_94;                                  // +0x94
    bool unknown_98;                                 // +0x98
    bool unknown_99;                                 // +0x99
};
GG_STATIC_ASSERT(offsetof(PlanningTokenClass, Owner) == 0x00);
GG_STATIC_ASSERT(offsetof(PlanningTokenClass, Nodes) == 0x04);
GG_STATIC_ASSERT(offsetof(PlanningTokenClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(PlanningTokenClass, unknown_1D) == 0x1D);
GG_STATIC_ASSERT(offsetof(PlanningTokenClass, unknown_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(PlanningTokenClass, unknown_94) == 0x94);
GG_STATIC_ASSERT(offsetof(PlanningTokenClass, unknown_99) == 0x99);

// The six lists with run-time constructors and guarded destructors (0x6335E0..0x633940). The guard bytes
// (0xAC4B60..0xAC4B63, shared by the last three with bits 1, 2 and 4) are what VC6 emits for static data members
// defined in this order; the owning class is not recoverable, so a placeholder holds them.
struct PlanningLists
{
    // GLOBAL: GAMEMD 0xAC4B48
    static DynamicVectorClass<EventClass*> DAT_00AC4B48;
    // GLOBAL: GAMEMD 0xAC4C98
    static DynamicVectorClass<PlanningNodeClass*> DAT_00AC4C98;
    // GLOBAL: GAMEMD 0xAC4C40
    static DynamicVectorClass<TechnoClass*> DAT_00AC4C40;
    // GLOBAL: GAMEMD 0xAC4B30
    static DynamicVectorClass<PlanningNodeClass*> DAT_00AC4B30;
    // GLOBAL: GAMEMD 0xAC4C18
    static DynamicVectorClass<PlanningNodeClass*> DAT_00AC4C18;
    // GLOBAL: GAMEMD 0xAC4C78
    static DynamicVectorClass<PlanningTokenClass*> DAT_00AC4C78;
};

#endif  // GG_MATCH_AI_PLANNING_MANAGER_H
