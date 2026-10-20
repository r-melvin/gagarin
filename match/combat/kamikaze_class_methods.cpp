// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp Kamikaze.h / ArrayClasses.h / Timer.h
//   (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x54E6F0  Kamikaze::Clear  (__thiscall)
//   FUNCTION: GAMEMD 0x54E750  Kamikaze::Save   (__thiscall)
//   LIBRARY:  GAMEMD 0x7C8B3D  GameDelete (operator delete / free; excluded)

#include "kamikaze_class_methods.h"

// FUNCTION: GAMEMD 0x54E6F0  (__thiscall)
// Free every node back-to-front, drop the vector's storage but keep its
// capacity, then re-arm the update timer for the current frame (TimeLeft = 1).
//
// raw_match: 100.0% (0 real diffs). diff_retail: 94.4% — the only residual is a
// consistent ESI<->EDI swap of the two long-lived enregistered values: retail
// (build 8447) gives ESI to the higher-weight loop counter `i` (this->EDI), our
// our compiler gives ESI to `this` (i->EDI). Every instruction is
// structurally identical; 16 lines are register-renamed and the 2 prologue
// "diff" lines are just the resulting `push edi`/`mov <r>,ecx` ordering. This is
// the documented unexplained-codegen register-allocation delta — phrasing-invariant
// (verified across cap-hoist / self-pointer / split-decl rewrites), so it will
// reach byte-exact under the genuine build-8447 compiler.
//
// Lift pass (2026-09-18): diff_retail reports 55.6% (20/36) with an IDENTICAL
// mnemonic multiset - "scheduling/register naming only". The swap is downstream
// of the prologue: retail pushes EBX, ESI and EDI all in the prologue and then
// takes `this` into EDI, so ESI falls to the lighter value (the loop counter,
// later reused for `&Nodes`); cl 8804 defers `PUSH EDI` to the register's first
// use, which makes `this` the first-defined value and hands it ESI. The same
// deferred-push shape shows up at 0x403530, 0x41C250 and 0x447AC0 in this pass,
// so it is one 8447-vs-8804 prologue class rather than a local phrasing miss.
void Kamikaze::Clear()
{
    for (int i = Nodes.Count - 1; i >= 0; --i)
        GameDelete(Nodes.Items[i]);

    int cap = Nodes.Capacity;
    Nodes.Clear();
    Nodes.SetCapacity(cap, 0);

    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = 1;
    this->UpdateTimer = timer;
}

// FUNCTION: GAMEMD 0x54E750  (__thiscall)
// Serialise the node vector: first the node count, then each 8-byte node.
// Returns the last IStream::Write HRESULT (kept in EAX); a failed write breaks
// out early and is returned verbatim.
HRESULT Kamikaze::Save(IStream* pStm)
{
    int count = Nodes.Count;
    HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr >= 0)
    {
        for (int i = 0; i < count; ++i)
        {
            hr = pStm->Write(Nodes.Items[i], 8, 0);
            if (hr < 0)
                break;
        }
    }
    return hr;
}
