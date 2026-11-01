// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x4CB580,
//   0x4CB5E0, 0x4CB640, 0x4CB6A0, 0x4CB700, 0x4CB760, 0x4CB7C0, 0x4CB830 and
//   0x4CB890 via the local Ghidra disassembly. Layout confirmed numerically in
//   the header. The three overloads at 0x4CB580, 0x4CB640 and 0x4CB6A0 sit in
//   address ranges the Ghidra analysis does not list as functions — each is a
//   clean 0x54-byte body behind twelve alignment NOPs — so they were recovered
//   by reading the raw bytes and decoding them, not from the function list.
//
//   The three CRT entry points the constructors reach are retail-resolved
//   addresses, not guesses: 0x7C91D0 is `strncpy` (three cdecl pushes, the
//   count immediate 4, cleanup folded into the later `ADD ESP,0x10`),
//   0x7C8E17 is operator new (one pushed byte count), 0x7C8B3D is the matching
//   operator delete (one pushed pointer, `ADD ESP,0x4`), and both `memcpy` and
//   `strlen` are expanded inline by the compiler as `REP MOVSD`/`REP MOVSB`
//   and `REPNE SCASB` respectively. They are CRT code and so are excluded
//   from the match target; only the calls into them are annotated.
//
// FieldClass constructors — one per payload type. Functions ordered ascending
// by retail address.

#include <string.h>
#include "field_class_ctors.h"

// FUNCTION: GAMEMD 0x4CB580  FieldClass::FieldClass(char*, char)
// Signed one-byte payload. DataType and Size are both the constant 1 here, so
// cl materialises 1 once in EAX and stores AX to both +0x04 and +0x06 and
// pushes the same EAX to operator new — three uses of one constant, which is
// what distinguishes this body from its unsigned twin below.
FieldClass::FieldClass(char* id, char data)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_01;
    Size = sizeof(data);
    Data = new char[Size];
    memcpy(Data, &data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB5E0  FieldClass::FieldClass(char*, unsigned char)
// One-byte payload. `Size` is the constant 1, so the `PUSH 1` for operator new
// is scheduled ahead of the two 16-bit header stores; the copy source is the
// parameter's own stack slot (`LEA ESI,[ESP+0x24]` = the incoming byte).
FieldClass::FieldClass(char* id, unsigned char data)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_02;
    Size = sizeof(data);
    Data = new char[Size];
    memcpy(Data, &data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB640  FieldClass::FieldClass(char*, short)
// Two-byte payload, DataType 3. The two header constants differ, so they are
// stored as 16-bit immediates and the `PUSH 2` for operator new is scheduled
// ahead of them exactly as in the byte overload.
FieldClass::FieldClass(char* id, short data)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_03;
    Size = sizeof(data);
    Data = new char[Size];
    memcpy(Data, &data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB6A0  FieldClass::FieldClass(char*, unsigned short)
// The unsigned twin of the previous overload; only the DataType tag differs.
FieldClass::FieldClass(char* id, unsigned short data)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_04;
    Size = sizeof(data);
    Data = new char[Size];
    memcpy(Data, &data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB700  FieldClass::FieldClass(char*, long)
// Identical shape to the byte overload with DataType 5 and Size 4.
FieldClass::FieldClass(char* id, long data)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_05;
    Size = sizeof(data);
    Data = new char[Size];
    memcpy(Data, &data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB760  FieldClass::FieldClass(char*, unsigned long)
// The unsigned twin of the previous overload; only the DataType tag differs.
FieldClass::FieldClass(char* id, unsigned long data)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_06;
    Size = sizeof(data);
    Data = new char[Size];
    memcpy(Data, &data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB7C0  FieldClass::FieldClass(char*, char*)
// The NUL is part of the payload, which is why retail's inline `strlen`
// (`OR ECX,-1; XOR EAX,EAX; REPNE SCASB; NOT ECX`) is used without the usual
// trailing decrement: `NOT ECX` already yields strlen+1, and the `+1` in the
// source cancels the intrinsic's `DEC`, leaving the bare `LEA EAX,[ECX]`.
FieldClass::FieldClass(char* id, char* data)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_07;
    Size = (unsigned short)(strlen(data) + 1);
    Data = new char[Size];
    memcpy(Data, data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB830  FieldClass::FieldClass(char*, void*, int)
// The caller-supplied length is narrowed to the 16-bit `Size` and the
// *narrowed* value is what reaches operator new — retail reuses the same EAX
// (`MOV [EBX+6],AX; AND EAX,0xFFFF; PUSH EAX`), so the allocation size is the
// one named quantity, never a second read of the parameter.
FieldClass::FieldClass(char* id, void* data, int length)
{
    strncpy(ID, id, sizeof(ID));
    DataType = FIELD_TYPE_14;
    Size = (unsigned short)length;
    Data = new char[Size];
    memcpy(Data, data, Size);
    Next = 0;
}

// FUNCTION: GAMEMD 0x4CB890  FieldClass::~FieldClass
// Releases the heap copy the constructors took and blanks the pointer. There
// is no `Next` walk here — the list that threads these fields is owned by
// PacketClass, which unlinks before destroying — and no null guard, because
// the array form of operator delete tolerates null on its own.
FieldClass::~FieldClass()
{
    delete [] (char*)Data;
    Data = 0;
}
