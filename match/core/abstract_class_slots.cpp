// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// AbstractClass's own bodies for the primary table 0x7E1F50 (slots 4, 9-23)
// and the INoticeSink / INoticeSource tables 0x7E1F2C / 0x7E1F24, in retail
// address order (0x410440..0x410590). Slot numbers come from the RTTI-located
// tables; names other than IsDirty / Notice / IsOnFloor / IsInAir are
// placeholders (abstract_class.h).
#include "../_layout/object_class.h"
#include "../_layout/obj_004a1d30.h"

// GLOBAL: GAMEMD 0x887680 -- the coordinate slot 18 returns.
extern CoordStruct DAT_00887680;

// FUNCTION: GAMEMD 0x410410
// Feed UniqueID and the Dirty byte to the checksum sink.
void AbstractClass::vf_13(Obj_004A1D30* crc)
{
    crc->FUN_004A1D50(UniqueID);
    crc->FUN_004A1CA0(Dirty);
}

// FUNCTION: GAMEMD 0x410440
bool AbstractClass::vf_17()
{
    return true;
}

// FUNCTION: GAMEMD 0x410450
HRESULT __stdcall AbstractClass::IsDirty()
{
    return !Dirty;
}

// FUNCTION: GAMEMD 0x410470
void AbstractClass::vf_9()
{
}

// FUNCTION: GAMEMD 0x410480
void AbstractClass::vf_10(void* a1, bool a2)
{
}

// FUNCTION: GAMEMD 0x410490
int AbstractClass::vf_14()
{
    return -1;
}

// FUNCTION: GAMEMD 0x4104A0
int AbstractClass::vf_15()
{
    return 0;
}

// FUNCTION: GAMEMD 0x4104B0
int AbstractClass::vf_16()
{
    return 0;
}

// FUNCTION: GAMEMD 0x4104C0
CoordStruct AbstractClass::vf_18()
{
    return DAT_00887680;
}

// FUNCTION: GAMEMD 0x4104F0
CoordStruct AbstractClass::vf_19(int a1)
{
    return vf_18();
}

// FUNCTION: GAMEMD 0x410520
bool AbstractClass::IsOnFloor() const
{
    return false;
}

// FUNCTION: GAMEMD 0x410530
bool AbstractClass::IsInAir() const
{
    return false;
}

// FUNCTION: GAMEMD 0x410540
CoordStruct AbstractClass::vf_22()
{
    return vf_18();
}

// FUNCTION: GAMEMD 0x410570
void AbstractClass::vf_23()
{
}

// FUNCTION: GAMEMD 0x410580 -- INoticeSink slot 0, `this` is the +0x08 subobject.
bool AbstractClass::Notice(int id, int arg)
{
    return false;
}

// FUNCTION: GAMEMD 0x410590 -- INoticeSource slot 0, `this` is the +0x0C subobject.
void AbstractClass::vf_0(int arg)
{
}
