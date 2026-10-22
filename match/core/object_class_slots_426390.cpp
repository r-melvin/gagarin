// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// ObjectClass bodies for primary-table (0x7EF060) slots emitted together at
// 0x426390..0x426522. Slot numbers come from the RTTI-located table; names are
// placeholders (object_class.h). 0x4263C0 returns the retail wide string
// L"No name" at 0x8182E0.
#include "../_layout/object_class.h"

// FUNCTION: GAMEMD 0x426390
bool ObjectClass::vf_25()
{
    return false;
}

// FUNCTION: GAMEMD 0x4263A0
int ObjectClass::vf_26(int a1, int a2)
{
    return 0;
}

// FUNCTION: GAMEMD 0x4263B0
bool ObjectClass::vf_32()
{
    return false;
}

// FUNCTION: GAMEMD 0x4263C0
const wchar_t* ObjectClass::vf_36()
{
    return L"No name";
}

// FUNCTION: GAMEMD 0x4263D0
// PARTIAL 42.9%: retail keeps the return pointer in ESI and returns it with
// MOV EAX,ESI; cl reloads it from the stack. Tried copy-then-add, member-wise
// copy and a brace-initialised local.
CoordStruct ObjectClass::vf_44(int a1, int a2, int a3, int a4)
{
    CoordStruct coord = vf_18();
    CoordStruct result;
    result.X = coord.X;
    result.Y = coord.Y;
    result.Z = coord.Z + 50;
    return result;
}

// FUNCTION: GAMEMD 0x426410
bool ObjectClass::vf_48()
{
    return true;
}

// FUNCTION: GAMEMD 0x426420
bool ObjectClass::vf_49()
{
    return false;
}

// FUNCTION: GAMEMD 0x426430
bool ObjectClass::vf_50(int a1)
{
    return false;
}

// FUNCTION: GAMEMD 0x426440
void ObjectClass::vf_67(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x426450
void ObjectClass::vf_68(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x426460
void ObjectClass::vf_85(int a1, int a2, int a3)
{
}

// FUNCTION: GAMEMD 0x426470
void ObjectClass::vf_86()
{
}

// FUNCTION: GAMEMD 0x426480
void ObjectClass::vf_87(int a1)
{
}

// FUNCTION: GAMEMD 0x426490
bool ObjectClass::vf_88()
{
    return false;
}

// FUNCTION: GAMEMD 0x4264A0
void ObjectClass::vf_92()
{
}

// FUNCTION: GAMEMD 0x4264B0
void ObjectClass::vf_99(int a1)
{
}

// FUNCTION: GAMEMD 0x4264C0
int ObjectClass::vf_107(int a1, int a2, int a3, int a4, int a5)
{
    return 0;
}

// FUNCTION: GAMEMD 0x4264D0
int ObjectClass::vf_108(int a1, int a2, int a3, int a4, int a5)
{
    return 0;
}

// FUNCTION: GAMEMD 0x4264E0
bool ObjectClass::vf_117()
{
    return false;
}

// FUNCTION: GAMEMD 0x4264F0
bool ObjectClass::vf_118()
{
    return false;
}

// FUNCTION: GAMEMD 0x426500
bool ObjectClass::vf_119()
{
    return false;
}

// FUNCTION: GAMEMD 0x426510
bool ObjectClass::vf_120()
{
    return true;
}

// FUNCTION: GAMEMD 0x426520
int ObjectClass::vf_121()
{
    return 0;
}
