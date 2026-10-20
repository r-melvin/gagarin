// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp TechnoClass.h (consult-only). Each function is
//   ordered ascending by retail address.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x70F7E0  TechnoClass::TargetingTimerFinished (__thiscall)
//   FUNCTION: GAMEMD 0x70F820  TechnoClass::GetOriginalOwner       (__thiscall)
//   FUNCTION: GAMEMD 0x734270  TechnoClass::ClearSidebarTabObject  (__thiscall)

#include "techno_class_owner_methods.h"

// Sidebar "tab object" globals @ 0x00B0FE5C / 0x00B0FE60. Declared-only so cl
// emits reloc-normalised absolute stores/compares.
extern TechnoClass* SidebarTabObjectA;   // 0x00B0FE5C
extern TechnoClass* SidebarTabObjectB;   // 0x00B0FE60

// FUNCTION: GAMEMD 0x70F7E0  (__thiscall)
// Inlines CDTimerClass::GetTimeLeft on TargetingTimer and reports whether it has
// expired. StartTime == -1 means "not running" -> the stored TimeLeft is the
// remaining value verbatim; otherwise subtract the elapsed frames, clamping the
// remainder at 0. The countdown is finished when the remainder is 0.
//
// STATUS: bool-delta. The two countdown paths and all control flow are
// byte-exact, and the StartTime==-1 / clamped-to-0 tail reproduces retail's
// long-form bool materialisation `xor ecx,ecx; test eax,eax; setz cl; mov al,cl`
// EXACTLY. The remaining-frames return is `(TimeLeft - elapsed) == 0`: retail
// (SP5/build-8447) emits the same long-form setz on the live subtraction result,
// but our compiler applies its flag-live zero-test peephole and
// emits the lean `neg eax; sbb eax,eax; inc eax` (5 bytes vs 9) for that one
// tail, whose shorter length cascades the trailing offsets. Confirmed
// phrasing-invariant across `==0`, `!(...)`, `t-=e;return t==0`, and a bound bool
// local. Isolated to the setcc tail — the documented unexplained-codegen delta.
//
// The branch-vs-expression lever that fixed 0x53C450 does not apply here, and it
// is worth saying why: there, retail wanted the *short* `TEST AL,AL; SETE AL` and
// writing the negation as a branch produced it. Here retail wants the *long*
// four-instruction materialisation on a value whose flags are already live from
// the `SUB`, and writing this tail as a branch (`if (t) return false; return
// true;`) removes our NEG/SBB/INC but drops all four of retail's instructions
// instead of matching them — three short rather than a three-for-three swap. The
// expression form is closer, so it stays.
//
// Lift pass (2026-09-18), two more rejected:
//   * same-width union alias on the subtraction result
//     (`union { int S; unsigned U; } r; r.S = timeLeft - elapsed;
//     return r.U == 0;`) - cl folds the alias away, still 35.0% with an
//     identical stream.
//   * the whole countdown moved into a genuine in-class inline
//     `CDTimerClass::GetTimeLeft()` with three early returns and
//     `return TargetingTimer.GetTimeLeft() == 0;` at the call site. This DOES
//     produce the long-form bool materialisation on every path (the banked
//     "early return inside an inlined helper duplicates the caller's
//     continuation" rule), but it duplicates it THREE times where retail
//     shares one tail between the StartTime==-1 path and the clamped path,
//     and it sinks the TimeLeft load into the branches: 8.7%.
// Retail's split is one long-form tail per *value source*: the load/zero pair
// share one, the live SUB gets its own. cl 8804 only withholds its
// flags-live peephole when the value did not arrive from an arithmetic op in
// the same block, and no spelling reached that.
bool TechnoClass::TargetingTimerFinished() const
{
    int timeLeft = this->TargetingTimer.TimeLeft;
    if (this->TargetingTimer.StartTime != -1) {
        int elapsed = CurrentFrame - this->TargetingTimer.StartTime;
        if (elapsed < timeLeft)
            return (timeLeft - elapsed) == 0;
        timeLeft = 0;
    }
    return timeLeft == 0;
}

// FUNCTION: GAMEMD 0x70F820  (__thiscall)
// The house that originally owned this object. When mind-controlled, the
// controlling unit's CaptureManager remembers the original owner; when held by
// a house's mind-control, OriginallyOwnedByHouse holds it; otherwise the live
// Owner is the original owner.
HouseClass* TechnoClass::GetOriginalOwner() const
{
    if (this->MindControlledBy != NULL)
        return this->MindControlledBy->CaptureManager->GetOriginalOwner(
            const_cast<TechnoClass*>(this));
    if (this->MindControlledByHouse != NULL)
        return this->OriginallyOwnedByHouse;
    return this->Owner;
}

// FUNCTION: GAMEMD 0x734270  (__thiscall)
// Removes this object from the two sidebar tab-object slots. A null this clears
// both slots; otherwise only the slot(s) that point at this object are cleared.
void TechnoClass::ClearSidebarTabObject()
{
    if (this == NULL) {
        SidebarTabObjectA = NULL;
        SidebarTabObjectB = NULL;
        return;
    }
    if (this == SidebarTabObjectA) {
        SidebarTabObjectA = NULL;
        return;
    }
    if (this == SidebarTabObjectB) {
        SidebarTabObjectB = NULL;
        return;
    }
}
