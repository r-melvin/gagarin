// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x70ECE0 (Ghidra disasm).
//   Names cross-checked against YRpp TechnoClass.h (RecoilData::Fire,
//   JMP_THIS(0x70ECE0)) — consult-only, no LICENSE; each offset reconfirmed
//   against the user's binary.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70ECE0   RecoilData::Fire   (__thiscall)
//
// Disassembly skeleton (0x70ECE0..0x70ED0B, len 0x2C):
//   PUSH ECX                ; reserve 4-byte stack slot for the cached Travel
//   MOV  EAX,[ECX]          ; travel = Turret.Travel
//   TEST EAX,EAX
//   MOV  [ESP],EAX          ; spill travel
//   JZ   end
//   MOV  EAX,[ECX+4]        ; CompressFrames
//   MOV  EDX,1
//   CMP  EAX,EDX
//   MOV  [ECX+0x18],EDX     ; State = 1
//   MOV  [ECX+0x1c],EAX     ; TravelFramesLeft = CompressFrames
//   JGE  skip               ; (CompressFrames >= 1)
//   MOV  [ECX+0x1c],EDX     ; TravelFramesLeft = 1
//  skip:
//   FILD  [ESP]             ; (float)travel
//   FIDIV [ECX+0x1c]        ;  / TravelFramesLeft  (integer divisor)
//   FSTP  [ECX+0x10]        ; TravelPerFrame = ...
//  end:
//   POP  ECX
//   RET

#include "techno_class_fire_methods.h"

// FUNCTION: GAMEMD 0x70ECE0  RecoilData::Fire  (__thiscall)
void RecoilData::Fire()
{
    int travel = this->Turret.Travel;
    if (travel != 0) {
        this->State = 1;
        this->TravelFramesLeft = this->Turret.CompressFrames;
        if (this->Turret.CompressFrames < 1) {
            this->TravelFramesLeft = 1;
        }
        this->TravelPerFrame = (float)travel / (float)this->TravelFramesLeft;
    }
}
