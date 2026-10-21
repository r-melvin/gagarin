// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Complete retail body 0x4729C0..0x472A75 (0xB6), REA evidence
// ev_1a5aba8e115edbbdf23b9901dd549edebbe82f9b5166cd0bd9651c8e7b3e0918.
#include "../_layout/capture_manager_class.h"

extern "C" void __cdecl gg_free(void*); // LIBRARY: GAMEMD 0x7C8B3D
// Global ABI view: retail calls the fifth virtual slot (byte +0x10) through
// this vector's vtable. RTTI and constructor xrefs identify the element type;
// the method name is an ABI-view label. This is not a second native template.
class CaptureRegistryDispatchView {
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0C();
    virtual int FindItemIndex(CaptureManagerClass* const& item) const;
    virtual void Slot14();
    virtual void Slot18();
    CaptureManagerClass** Items;
    int Capacity;
    unsigned char unknown_0C;
    unsigned char IsAllocated;
    unsigned char unknown_0E;
    unsigned char unknown_0F;
    int Count;
    int CapacityIncrement;
};
// GLOBAL: GAMEMD 0x0089E0F0 — RTTI identifies DynamicVectorClass<CaptureManagerClass*>.
extern CaptureRegistryDispatchView DAT_0089E0F0;

// Slot-prefix model for the observed indirect call, not a recovered full table.
typedef int (CaptureRegistryDispatchView::*CaptureRegistryFindCall)(
    CaptureManagerClass* const&) const;
struct CaptureRegistrySlots_4729C0
{
    void* unknown_00[4];
    CaptureRegistryFindCall FindItemIndex;
};
GG_STATIC_ASSERT(sizeof(CaptureRegistryFindCall) == 4);
GG_STATIC_ASSERT(offsetof(CaptureRegistrySlots_4729C0, FindItemIndex) == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, _vtable) == 0x00);
GG_STATIC_ASSERT(offsetof(CaptureRegistryDispatchView, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(CaptureRegistryDispatchView, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(CaptureRegistryDispatchView, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(CaptureRegistryDispatchView, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(CaptureRegistryDispatchView, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(CaptureRegistryDispatchView) == 0x18);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, _vtable_IPersistStream) == 0x00);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, _vtable_IRTTITypeInfo) == 0x04);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, _vtable_INoticeSink) == 0x08);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, _vtable_INoticeSource) == 0x0C);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes) == 0x24);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Items) + 0x24 == 0x28);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Capacity) + 0x24 == 0x2C);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, unknown_0C) + 0x24 == 0x30);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, unknown_0C) + 0x25 == 0x31);

// The body has deleting-destructor behavior. Its FUN name does not establish
// a source-level destructor declaration or recovered original method name.
// FUNCTION: GAMEMD 0x4729C0
CaptureManagerClass* CaptureManagerClass::FUN_004729C0(unsigned int flags)
{
    _vtable_IPersistStream = (void*)0x7E4B40;
    _vtable_IRTTITypeInfo = (void*)0x7E4B24;
    _vtable_INoticeSink = (void*)0x7E4B1C;
    _vtable_INoticeSource = (void*)0x7E4B14;

    CaptureRegistryDispatchView* registry = &DAT_0089E0F0;
    int index = registry->FindItemIndex(this);
    if (index != -1 && index < registry->Count) {
        --registry->Count;
        for (int i = index; i < registry->Count; ++i)
            registry->Items[i] = registry->Items[i + 1];
    }

    ControlNodes._vtable = (void*)0x7E4BC4;
    if (ControlNodes.Items != 0
        && ((unsigned char*)&ControlNodes.unknown_0C)[1] != 0) {
        gg_free(ControlNodes.Items);
        ControlNodes.Items = 0;
    }
    ((unsigned char*)&ControlNodes.unknown_0C)[1] = 0;
    ControlNodes.Capacity = 0;

    ((AbstractClass*)this)->~AbstractClass();
    if (flags & 1)
        gg_free(this);
    return this;
}
