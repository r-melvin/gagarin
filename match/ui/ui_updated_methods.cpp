// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x623120).
//   Every global address and branch reconfirmed below from the disassembly;
//   names cross-checked against YRpp UI.h / Unsorted.h (consult-only, no LICENSE).
//
// reccmp annotation:
//   FUNCTION: GAMEMD 0x623120   UI::Updated   (static, __cdecl)
//   GLOBAL:   GAMEMD 0xA8B238   SessionGameMode  (int; ==0 or ==5 -> gate out)
//   GLOBAL:   GAMEMD 0xA8D60E   InhibitFlag      (byte; nonzero -> gate out)
//   GLOBAL:   GAMEMD 0xA8DAB4   InhibitWord      (int;  nonzero -> gate out)
//
// Disassembly of 0x623120 (len 0x42, ends at the RET @0x623161):
//   CALL 0x5D4D50               ; PreUpdate() — result ignored
//   MOV  EAX,[0xA8B238]         ; SessionGameMode
//   TEST EAX,EAX / JZ  gateout  ; == 0
//   CMP  EAX,5    / JZ  gateout  ; == 5
//   MOV  AL,[0xA8D60E] / JNZ gateout ; byte != 0
//   MOV  EAX,[0xA8DAB4]/ JNZ gateout ; int  != 0
//   CALL 0x55CBF0 / JNZ false   ; if predicate A -> return false
//   CALL 0x55D360 / JZ  false   ; if !predicate B -> return false
//   MOV  AL,1 / RET             ; return true
// gateout: CALL 0x48D080 (CallBack), fall through to
// false:   XOR AL,AL / RET      ; return false

#include "ui_updated_methods.h"

// Engine globals read by Updated (absolute dword/byte loads in the disasm).
extern int           SessionGameMode; // GAMEMD 0xA8B238 (first field of the session)
extern unsigned char InhibitFlag;     // GAMEMD 0xA8D60E
extern int           InhibitWord;     // GAMEMD 0xA8DAB4

// Helper functions called by Updated (direct CALLs; result is bool in AL where used).
void PreUpdate();   // GAMEMD 0x5D4D50  (void; return value ignored)
bool PredicateA();  // GAMEMD 0x55CBF0  (byte load -> bool)
bool PredicateB();  // GAMEMD 0x55D360  (byte load -> bool)
void CallBack();    // GAMEMD 0x48D080  (void)

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x623120  (static, __cdecl)
// ---------------------------------------------------------------------------
bool UI::Updated()
{
    PreUpdate();

    if (SessionGameMode == 0 || SessionGameMode == 5 ||
        InhibitFlag != 0 || InhibitWord != 0)
    {
        CallBack();
        return false;
    }

    if (!PredicateA() && PredicateB())
        return true;

    return false;
}
