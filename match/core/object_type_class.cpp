// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x5004E0 (Ghidra disasm).
//   Name cross-checked against YRpp ObjectTypeClass.h (consult-only, no LICENSE;
//   convention + 0xE08 offset reconfirmed against the user's binary below).
//
// Translation unit: ObjectTypeClass::IsBuildCat5.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5004E0   ObjectTypeClass::IsBuildCat5   (static __fastcall)
//
// NOTE on the sibling method ObjectTypeClass::LoadVoxel @0x5F8110: that retail
// routine is 0xBCB (3019) bytes ending at the RET @0x5F8CDA, dominated by many
// fully-inlined std::string temporaries (CCFileClass/IndexClass ctor+dtor pairs
// at 0x4739F0/0x473C50/0x43AE50/0x431B80) and voxel/HVA loader calls. It is not
// matchable in a single pass and is deferred; not included in this TU.

#include "object_type_class.h"

// FUNCTION: GAMEMD 0x5004E0  (static __fastcall)
//
//   PUSH ESI / MOV ESI,ECX            ESI = abstractID
//   TEST EDX,EDX / JGE                idx < 0  -> return 0
//   MOV ECX,ESI / CALL 0x48DCD0       p = ObjTypeFindFromCat(abstractID, idx)
//   CMP ESI,6 JZ / CMP ESI,7 JZ       abstractID must be 6 or 7
//   (else)  XOR EAX,EAX / RET         return 0
//   MOV EAX,[EAX+0xE08] / RET         return *(int*)(p + 0xE08)
//
// abstractID is held in ESI (callee-saved) across the call so the two CMPs run
// after it; idx stays live in EDX up to the call.
int __fastcall ObjectTypeClass::IsBuildCat5(int abstractID, int idx)
{
    char* p;
    if (idx < 0)
        return 0;
    p = ObjTypeFindFromCat(abstractID, idx);
    if (abstractID != 6 && abstractID != 7)
        return 0;
    return *(int*)(p + 0xE08);
}
