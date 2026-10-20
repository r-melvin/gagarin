// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6FB080.

#include "techno_class_reloading_methods.h"

// FUNCTION: GAMEMD 0x6FB080
//
// (Re)arm the reload countdown when the clip is not full. An empty clip with a
// distinct EmptyReload uses that; otherwise the delay is Reload plus
// ReloadIncrement scaled by the square of how many pip-wraps are loaded (one
// when the type does not wrap).
//
// The type is fetched through the virtual before every read, as retail does,
// and the timer is rewritten as a whole-struct copy of a fresh temporary, so
// the clock slot in the middle carries an uninitialised stack dword.
//
// Two named locals are load-bearing: the type's Ammo is bound before the
// compare so the techno's Ammo is read after the call (a single expression
// hoists the member load above the call into EDI and adds a push/pop pair),
// and the increment product is bound before the sum so the add lands in the
// Reload register (`ADD EAX,EDI`) rather than the product's.
void Techno_006FB080::StartReloading()
{
    int full = (this->*this->Vtbl->GetTechnoType)()->Ammo;
    if (this->Ammo < full) {
        if (this->Ammo == 0
            && (this->*this->Vtbl->GetTechnoType)()->EmptyReload != -1) {
            this->ReloadTimer =
                CDTimer_006FB080((this->*this->Vtbl->GetTechnoType)()->EmptyReload);
            return;
        }

        int wraps;
        if ((this->*this->Vtbl->GetTechnoType)()->PipWrap == 0) {
            wraps = 1;
        } else {
            wraps = this->Ammo / (this->*this->Vtbl->GetTechnoType)()->PipWrap;
        }

        int extra = (this->*this->Vtbl->GetTechnoType)()->ReloadIncrement * wraps * wraps;
        this->ReloadTimer = CDTimer_006FB080(
            (this->*this->Vtbl->GetTechnoType)()->Reload + extra);
    }
}
