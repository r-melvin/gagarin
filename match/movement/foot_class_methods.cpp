// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Bodies and
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x41C090  FootClass::vf_323 (__thiscall)
//   FUNCTION: GAMEMD 0x4D3710  FootClass::vf_337 (__thiscall)
//   FUNCTION: GAMEMD 0x4D55C0  FootClass::vf_320 (__thiscall)
//   FUNCTION: GAMEMD 0x4D55F0  FootClass::vf_319 (__thiscall)
//   FUNCTION: GAMEMD 0x4D8F40  FootClass::vf_125 (__thiscall)
//   FUNCTION: GAMEMD 0x4D9FF0  FootClass::vf_316 (__thiscall)
//   FUNCTION: GAMEMD 0x4DA1C0  FootClass::ClearNavigationList (__thiscall)
//   FUNCTION: GAMEMD 0x4DBFD0  FootClass::vf_312 (__thiscall)
//   FUNCTION: GAMEMD 0x4DC030  FootClass::vf_317 (__thiscall)
//   FUNCTION: GAMEMD 0x4DEE50  FootClass::vf_332 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF040  FootClass::vf_330 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF0D0  FootClass::AbortMotion         (__thiscall)

#include "foot_class_methods.h"
#include "loco_com.h"
#include "../_layout/techno_type_class.h"

// FUNCTION: GAMEMD 0x41C090
// Native wrapper forwards sixteen stack dwords to the existing TechnoClass
// helper, preserving the receiver in ECX.
void FootClass::vf_323(SHPStruct* a1, int a2, Point2D* a3,
                       RectangleStruct* a4, int a5, int a6, int a7, int a8,
                       int a9, int a10, int a11, int a12, int a13, int a14,
                       int a15, int a16)
{
    TechnoClass::FUN_00705E00(a1, a2, a3, a4, a5, a6, a7, a8,
                             a9, a10, a11, a12, a13, a14, a15, a16);
}

// FUNCTION: GAMEMD 0x4D3710
// Store the speed fraction clamped to [0, 1].
void FootClass::vf_337(double a1)
{
    if (a1 >= 1.0) {
        a1 = 1.0;
    } else if (a1 <= 0.0) {
        a1 = 0.0;
    }
    SpeedPercentage = a1;
}

// FUNCTION: GAMEMD 0x4D55C0
// Stop the locomotor through its checked COM pointer.
bool FootClass::vf_320()
{
    (*(ILocomotionPtr*)&Locomotor)->StopMoving();
    return false;
}

// FUNCTION: GAMEMD 0x4D55F0
// Send the locomotor to a coordinate and report whether it is now moving.
bool FootClass::vf_319(const CoordStruct& a1)
{
    LocoCoord to;
    to.X = a1.X;
    to.Y = a1.Y;
    to.Z = a1.Z;
    (*(ILocomotionPtr*)&Locomotor)->MoveTo(to);
    return (*(ILocomotionPtr*)&Locomotor)->IsMoving() != 0;
}

// FUNCTION: GAMEMD 0x4D8F40
// Remember the current destination, run the TechnoClass mission change, then
// head for the new target.
void FootClass::vf_125(int mission, AbstractClass* a2, AbstractClass* a3)
{
    LastDestination = Destination;
    TechnoClass::vf_125(mission, a2, a3);
    SetDestination(a3, true);
}

// FUNCTION: GAMEMD 0x4D9FF0
// Return the slot-41 coordinate by value.
CoordStruct FootClass::vf_316()
{
    return this->vf_41();
}

// FUNCTION: GAMEMD 0x4DA1C0  (__thiscall)
// Empty the pending movement-destination queue: tail-call NavQueue.Clear()
// (virtual slot +0x0C), forwarding `this+0x5AC` as the vector's `this`.
//   MOV EAX,[ECX+0x5AC] ; ADD ECX,0x5AC ; JMP [EAX+0x0C]
void FootClass::ClearNavigationList()
{
    ((NavVector*)&this->NavQueue)->Clear();
}

// FUNCTION: GAMEMD 0x4DBFD0
// True when unarmed, or when the type has tech level -1, deploys into a
// building, or has speed <= 13. The bool local gives native SETLE AL.
bool FootClass::vf_312()
{
    if (this->vf_254(0) == 0) {
        return true;
    }
    if (this->vf_33()->TechLevel == -1) {
        return true;
    }
    if (this->vf_33()->DeploysInto != 0) {
        return true;
    }
    bool slow = this->vf_33()->Speed <= 13;
    return slow;
}

// FUNCTION: GAMEMD 0x4DC030
void FootClass::vf_317()
{
    if (this->vf_97() == 0xF) {
        this->vf_242(0);
        this->SetDestination(0, true);
    }
}

// FUNCTION: GAMEMD 0x4DEE50
void* FootClass::vf_332(void* a1, int a2, int a3)
{
    int output = -1;
    return this->vf_331(a1, a2, a3, &output);
}

// FUNCTION: GAMEMD 0x4DF040
// Query slot 331 for each list entry and keep the closest result. An empty
// current pick, an unset distance, or a result with byte +0x3D3 set replaces it.
void* FootClass::vf_330(DynamicVectorClassLayout* a1, int a2, int a3)
{
    void* best = 0;
    int bestDistance = -1;
    for (int i = 0; i < a1->Count; i++) {
        int distance = -1;
        void* found = this->vf_331(((void**)a1->Items)[i], a2, a3, &distance);
        if (found != 0) {
            if (best == 0 || distance < bestDistance || bestDistance == -1
                || ((char*)found)[0x3D3] != 0) {
                best = found;
                bestDistance = distance;
            }
        }
    }
    return best;
}

// FUNCTION: GAMEMD 0x4DF0D0  (__thiscall)
// Abort the current motion: drop the immediate source and destination cells.
//   XOR EAX,EAX ; MOV [ECX+0x5A0],EAX ; MOV [ECX+0x5A4],EAX ; RET
void FootClass::AbortMotion()
{
    this->unknown_5A0 = 0;
    this->Destination = 0;
}
