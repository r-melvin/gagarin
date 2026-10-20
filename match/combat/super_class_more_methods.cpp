// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SuperClass::ShouldFlashTab — should the sidebar tab flash for this SW?
// Offsets confirmed numerically against the retail disassembly at 0x6CE1A0.
#include "super_class_more_methods.h"

// FUNCTION: GAMEMD 0x6CE1A0  SuperClass::ShouldFlashTab (__thiscall)
//   mov al,[ecx+0x70]; test al,al; jnz false        ; IsSuspended -> false
//   mov eax,[ecx+0x28]; mov dl,[eax+0xe5]; test dl,dl; jz noDrain
//     mov edx,[ecx+0x7c]; test edx,edx; jz false; jmp frames  ; ChargeDrainState
//   noDrain: mov dl,[ecx+0x6f]; test dl,dl; jz false           ; IsReady
//   frames: mov eax,[eax+0xe8]; cmp eax,-1; jnz chk; mov al,1; ret
//   chk: test eax,eax; jz false; mov ecx,[ecx+0x74]; add ecx,eax
//        mov eax,[0xa8ed84]; cmp ecx,eax; jle false; mov al,1; ret
//   false: xor al,al; ret
bool SuperClass::ShouldFlashTab() const
{
    if (!this->IsSuspended) {
        if (this->Type->UseChargeDrain) {
            if (this->ChargeDrainState == 0)
                goto fail;
        } else if (!this->IsReady) {
            goto fail;
        }

        int frames = this->Type->FlashSidebarTabFrames;
        if (frames == -1)
            return true;
        if (frames != 0 && this->ReadyFrame + frames > CurrentFrame)
            return true;
    }
fail:
    return false;
}
