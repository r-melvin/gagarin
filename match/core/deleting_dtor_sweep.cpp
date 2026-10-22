// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// ordered ascending
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.

#include "deleting_dtor_sweep.h"
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

// FUNCTION: GAMEMD 0x487E80
void* Obj_487E80::FUN_487E80(unsigned int flags)
{
    FUN_0047BB60(this);

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

// FUNCTION: GAMEMD 0x48E660
void* Obj_48E660::FUN_48E660(unsigned int flags)
{
    FUN_004E1390(this);

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

// FUNCTION: GAMEMD 0x4B5810
void* Obj_4B5810::FUN_4B5810(unsigned int flags)
{
    FUN_004E1390(this);

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


// FUNCTION: GAMEMD 0x5172F0
void* Obj_5172F0::FUN_5172F0(unsigned int flags)
{
    FUN_0055A6F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}


// FUNCTION: GAMEMD 0x54A170
void* Obj_54A170::FUN_54A170(unsigned int flags)
{
    FUN_00544A70(this);

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
    FUN_00437FC0(this);

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

// FUNCTION: GAMEMD 0x5F6DC0
void* Obj_5F6DC0::FUN_5F6DC0(unsigned int flags)
{
    FUN_005F3B80(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5F9AE0
void* Obj_5F9AE0::FUN_5F9AE0(unsigned int flags)
{
    FUN_005F7400(this);

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

// FUNCTION: GAMEMD 0x6404B0
void* Obj_6404B0::FUN_6404B0(unsigned int flags)
{
    FUN_00652C00(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x658780
void* Obj_658780::FUN_658780(unsigned int flags)
{
    FUN_004E1390(this);

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

// FUNCTION: GAMEMD 0x6AC780
void* Obj_6AC780::FUN_6AC780(unsigned int flags)
{
    FUN_004E1390(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x6AC7A0
void* Obj_6AC7A0::FUN_6AC7A0(unsigned int flags)
{
    FUN_004E1390(this);

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

// FUNCTION: GAMEMD 0x6B8140
void* Obj_6B8140::FUN_6B8140(unsigned int flags)
{
    FUN_006B7010(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x6CE220
void* Obj_6CE220::FUN_6CE220(unsigned int flags)
{
    FUN_006CB120(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x6E64C0
void* Obj_6E64C0::FUN_6E64C0(unsigned int flags)
{
    FUN_006E5CA0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x6F0450
void* Obj_6F0450::FUN_6F0450(unsigned int flags)
{
    FUN_006E8DE0(this);

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

// FUNCTION: GAMEMD 0x746E80
void* Obj_746E80::FUN_746E80(unsigned int flags)
{
    FUN_00735780(this);

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

// FUNCTION: GAMEMD 0x76EFE0
void* Obj_76EFE0::FUN_76EFE0(unsigned int flags)
{
    FUN_0076C6E0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AD2F0
void* Obj_7AD2F0::FUN_7AD2F0(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AD310
void* Obj_7AD310::FUN_7AD310(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AD330
void* Obj_7AD330::FUN_7AD330(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AD350
void* Obj_7AD350::FUN_7AD350(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AED20
void* Obj_7AED20::FUN_7AED20(unsigned int flags)
{
    FUN_007B46F0(this);

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

// FUNCTION: GAMEMD 0x7BA3A0
void* Obj_7BA3A0::FUN_7BA3A0(unsigned int flags)
{
    FUN_007B88D0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

