// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// ordered ascending
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.

#include "deleting_dtor_sweep.h"
#include "../platform/pk_blow_pipes.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

// FUNCTION: GAMEMD 0x477750
void* Obj_477750::FUN_477750(unsigned int flags)
{
    ((Pipe*)this)->Pipe::~Pipe();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x48BB00
void* Obj_48BB00::FUN_48BB00(unsigned int flags)
{
    FUN_0048B1F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x4A59A0
void* Obj_4A59A0::FUN_4A59A0(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4AEBB0
void* Obj_4AEBB0::FUN_4AEBB0(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4AEBF0
void* Obj_4AEBF0::FUN_4AEBF0(unsigned int flags)
{
    FUN_005652C0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4B57D0   EditClass::`scalar deleting destructor'
void* EditClass::ScalarDeletingDestructor(unsigned int flags)
{
    FUN_004C30B0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4D2910
void* Obj_4D2910::FUN_4D2910(unsigned int flags)
{
    FUN_004D1650(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4E0170
void* FootClass_4E0170::FUN_4E0170(unsigned int flags)
{
    FUN_004D3590(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4E1AD0
void* Obj_4E1AD0::FUN_4E1AD0(unsigned int flags)
{
    FUN_005565A0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4E30D0
void* Obj_4E30D0::FUN_4E30D0(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4E30F0
void* Obj_4E30F0::FUN_4E30F0(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x558180
void* Obj_558180::FUN_558180(unsigned int flags)
{
    FUN_006B1D00(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x588BF0
void* Obj_588BF0::FUN_588BF0(unsigned int flags)
{
    FUN_005652C0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x5B4610
void* Obj_5B4610::FUN_5B4610(unsigned int flags)
{
    static_cast<BlockCipherView*>(static_cast<void*>(this))->~BlockCipherView();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x5C10D0
void* Obj_5C10D0::FUN_5C10D0(unsigned int flags)
{
    FUN_005D8C80(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x5D3450
void* Obj_5D3450::FUN_5D3450(unsigned int flags)
{
    FUN_005D2E30(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x624480
void* Obj_624480::FUN_624480(unsigned int flags)
{
    FUN_007B6760(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x65BED0
void* Obj_65BED0::FUN_65BED0(unsigned int flags)
{
    FUN_0065B2F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x6B1390
void* Obj_6B1390::FUN_6B1390(unsigned int flags)
{
    FUN_006AF4A0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x7106E0
void* Obj_7106E0::FUN_7106E0(unsigned int flags)
{
    FUN_006F4500(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7179A0
void* Obj_7179A0::FUN_7179A0(unsigned int flags)
{
    FUN_00711AE0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x720210
void* Obj_720210::FUN_720210(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x723710
void* Obj_723710::FUN_723710(unsigned int flags)
{
    FUN_00721880(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x724C10
void* Obj_724C10::FUN_724C10(unsigned int flags)
{
    FUN_007240B0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x727CD0
void* Obj_727CD0::FUN_727CD0(unsigned int flags)
{
    FUN_00726E00(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x72A210
void* Obj_72A210::FUN_72A210(unsigned int flags)
{
    FUN_0055A6F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x72A670
void* Obj_72A670::FUN_72A670(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x74AB50
void* Obj_74AB50::FUN_74AB50(unsigned int flags)
{
    FUN_007499F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x74F340
void* Obj_74F340::FUN_74F340(unsigned int flags)
{
    FUN_0074C9F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x766A60
void* Obj_766A60::FUN_766A60(unsigned int flags)
{
    FUN_00767300(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x769C00
void* Obj_769C00::FUN_769C00(unsigned int flags)
{
    FUN_007680C0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x76B6F0
void* Obj_76B6F0::FUN_76B6F0(unsigned int flags)
{
    FUN_0076AFC0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x7B1790
void* Obj_7B1790::FUN_7B1790(unsigned int flags)
{
    ((WinsockInterfaceClass*)this)->WinsockInterfaceClass::~WinsockInterfaceClass();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

