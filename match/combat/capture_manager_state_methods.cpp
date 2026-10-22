// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Complete retail entry spans: 0x4722E0 (0x0C), 0x4726C0 (0x29),
// 0x4726F0 (0x2C), 0x4728E0 (0x7F), 0x472960 (0x38), and two six-byte
// entries at 0x4729A0/0x4729B0. The FUN method
// names and source grouping are unknown; Save/GetClassID follow their
// IPersistStream/IPersist vtable positions and observed operations.
// These methods use the existing receiver layout. 0x4726F0 calls the
// owner's +4 interface through slot +0x10 with COM-style stack this.
#include "../_layout/capture_manager_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../_rt/gg_istream.h"
#include "../_layout/control_node.h"

// The dword/int result is an ABI view, not a recovered original declaration.
struct CaptureOwnerSubobject_4726F0
{
    virtual int __stdcall unknown_00();
    virtual int __stdcall unknown_04();
    virtual int __stdcall unknown_08();
    virtual int __stdcall unknown_0C();
    virtual int __stdcall unknown_10();
};
struct CaptureOwnerView_4726F0
{
    char unknown_00[4];
    CaptureOwnerSubobject_4726F0 unknown_04;
};
GG_STATIC_ASSERT(offsetof(CaptureOwnerView_4726F0, unknown_04) == 0x04);

// Explicit slot-layout prefix for the observed indirect call, not a claim
// that every slot's target or the full owner interface has been recovered.
typedef int (__stdcall *CaptureOwnerCall_4726F0)(CaptureOwnerSubobject_4726F0*);
struct CaptureOwnerSlots_4726F0
{
    void* unknown_00[4];
    CaptureOwnerCall_4726F0 Slot10;
};
GG_STATIC_ASSERT(sizeof(CaptureOwnerCall_4726F0) == 4);
GG_STATIC_ASSERT(offsetof(CaptureOwnerSlots_4726F0, Slot10) == 0x10);

struct Guid_472960
{
    unsigned long unknown_00;
    unsigned long unknown_04;
    unsigned long unknown_08;
    unsigned long unknown_0C;
};
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(Guid_472960) == 0x10);

// GLOBAL: GAMEMD 0x007E9880 — first DWORD of CaptureManager's IPersist class ID.
extern "C" const unsigned long DAT_007E9880;
// GLOBAL: GAMEMD 0x007E9884 — second DWORD of the class ID.
extern "C" const unsigned long DAT_007E9884;
// GLOBAL: GAMEMD 0x007E9888 — third DWORD of the class ID.
extern "C" const unsigned long DAT_007E9888;
// GLOBAL: GAMEMD 0x007E988C — fourth DWORD of the class ID.
extern "C" const unsigned long DAT_007E988C;
// FUNCTION: GAMEMD 0x00410320 (decl; reloc)
extern "C" long __stdcall FUN_00410320(void* subject, void* stream, int clearDirty);


// FUNCTION: GAMEMD 0x4722E0
bool CaptureManagerClass::FUN_004722E0() const
{
    return MaxControlNodes == 1;
}

// FUNCTION: GAMEMD 0x4726C0
bool CaptureManagerClass::FUN_004726C0(bool* state)
{
    if (InfiniteMindControl && ControlNodes.Count > MaxControlNodes) {
        *state = OverloadPipState > 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4726F0
void CaptureManagerClass::FUN_004726F0(Obj_004A1D30* sink)
{
    AbstractClass::vf_13(sink);
    if (Owner != 0) {
        CaptureOwnerSubobject_4726F0* ownerInterface =
            &((CaptureOwnerView_4726F0*)Owner)->unknown_04;
        sink->FUN_004A1D50(ownerInterface->unknown_10());
    }
}

// FUNCTION: GAMEMD 0x4728E0 — IPersistStream::Save slot +0x18; __stdcall, RET 0xC.
long __stdcall CaptureManagerClass::Save(Gg_IStream* stream, int clearDirty)
{
    long baseResult = FUN_00410320(this, stream, clearDirty);
    if (baseResult < 0) {
        return baseResult;
    }

    int count = ControlNodes.Count;
    long result = stream->Write(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int i = 0; i < count; ++i) {
        ControlNode* node = ((ControlNode**)ControlNodes.Items)[i];
        stream->Write(&node->OriginalOwner, 4, 0);
        result = stream->Write(&node->Unit, 4, 0);
        if (result < 0) {
            return result;
        }
    }
    return baseResult;
}

// FUNCTION: GAMEMD 0x472960 — IPersist::GetClassID slot +0x0C; __stdcall, RET 8.
long __stdcall CaptureManagerClass::GetClassID(Guid_472960* outGuid)
{
    if (outGuid == 0) {
        return (long)0x80004003;
    }
    outGuid->unknown_00 = DAT_007E9880;
    outGuid->unknown_04 = DAT_007E9884;
    outGuid->unknown_08 = DAT_007E9888;
    outGuid->unknown_0C = DAT_007E988C;
    return 0;
}

// Primary table 0x7E4B40: 0x4729A0 at +0x30, 0x4729B0 at +0x2C.
// Semantic names, original return types and const qualification are unknown.
// FUNCTION: GAMEMD 0x4729A0
int CaptureManagerClass::FUN_004729A0()
{
    return 0x50;
}

// FUNCTION: GAMEMD 0x4729B0
int CaptureManagerClass::FUN_004729B0()
{
    return 0x42;
}
