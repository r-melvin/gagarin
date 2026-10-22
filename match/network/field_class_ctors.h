// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Every offset below was read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI, from the five constructors at 0x4CB5E0,
//   0x4CB700, 0x4CB760, 0x4CB7C0 and 0x4CB830:
//     * `PUSH 4; PUSH id; PUSH this; CALL 0x7C91D0` — the ID buffer is the
//       object itself, so `ID` is at +0x00 and is 4 bytes wide.
//     * `MOV word ptr [EBX+0x4],<const>` — DataType at +0x04, 2 bytes.
//     * `MOV word ptr [EBX+0x6],<const>` / `MOV word ptr [EBX+6],AX` —
//       Size at +0x06, 2 bytes.
//     * `XOR ECX,ECX; MOV CX,word ptr [EBX+0x6]` and `AND EAX,0xFFFF` —
//       both 16-bit members are read *zero*-extended, so both are unsigned.
//     * `MOV dword ptr [EBX+0x8],EAX` — Data at +0x08 (the operator-new
//       result).
//     * `MOV dword ptr [EBX+0xC],0x0` — Next at +0x0C.
//   sizeof is 0x10: the destructor at 0x4CB890 frees `[ESI+0x8]` and the list
//   walk never reaches past +0x0C.
//
//   The four later additions re-confirm the same offsets independently:
//   0x4CB580 (`MOV EAX,0x1; MOV word ptr [EBX+0x4],AX; MOV word ptr
//   [EBX+0x6],AX` — DataType and Size both 1 for the `char` overload, which is
//   why cl shares one register instead of storing two immediates), 0x4CB640
//   and 0x4CB6A0 (`MOV word ptr [EBX+0x4],0x3` / `0x4` with
//   `MOV word ptr [EBX+0x6],0x2`), and the destructor at 0x4CB890
//   (`MOV EAX,dword ptr [ESI+0x8]; PUSH EAX; CALL; ADD ESP,0x4;
//   MOV dword ptr [ESI+0x8],0x0`).
//
//   The class name is the retail RTTI name. The type-tag constants are the
//   immediates each constructor stores, named by value. The overload set is
//   the one the retail constructors require: each one's parameter width and
//   signedness is read off its own stores and extensions.
//
// FieldClass — one tagged, length-prefixed field inside a network PacketClass.
// The data payload is always a fresh heap copy owned by the field.
#ifndef GG_MATCH_NETWORK_FIELD_CLASS_CTORS_H
#define GG_MATCH_NETWORK_FIELD_CLASS_CTORS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Field payload type tags. The constants are the immediates stored into
// DataType by the constructors; each name carries its value in hex.
#define FIELD_TYPE_01            1
#define FIELD_TYPE_02   2
#define FIELD_TYPE_03           3
#define FIELD_TYPE_04  4
#define FIELD_TYPE_05            5
#define FIELD_TYPE_06   6
#define FIELD_TYPE_07          7
#define FIELD_TYPE_14           20

class FieldClass
{
public:
    // Declared ascending by retail address.
    FieldClass(char* id, char data);                // GAMEMD 0x4CB580
    FieldClass(char* id, unsigned char data);       // GAMEMD 0x4CB5E0
    FieldClass(char* id, short data);               // GAMEMD 0x4CB640
    FieldClass(char* id, unsigned short data);      // GAMEMD 0x4CB6A0
    FieldClass(char* id, long data);                // GAMEMD 0x4CB700
    FieldClass(char* id, unsigned long data);       // GAMEMD 0x4CB760
    FieldClass(char* id, char* data);               // GAMEMD 0x4CB7C0
    FieldClass(char* id, void* data, int length);   // GAMEMD 0x4CB830
    ~FieldClass();                                  // GAMEMD 0x4CB890

    char           ID[4];      // +0x00
    unsigned short DataType;   // +0x04
    unsigned short Size;       // +0x06
    void*          Data;       // +0x08
    FieldClass*    Next;       // +0x0C
};

GG_STATIC_ASSERT(offsetof(FieldClass, ID)       == 0x00 &&
                 offsetof(FieldClass, DataType) == 0x04 &&
                 offsetof(FieldClass, Size)     == 0x06 &&
                 offsetof(FieldClass, Data)     == 0x08 &&
                 offsetof(FieldClass, Next)     == 0x0C);
GG_STATIC_ASSERT(sizeof(FieldClass) == 0x10);

#endif  // GG_MATCH_NETWORK_FIELD_CLASS_CTORS_H
