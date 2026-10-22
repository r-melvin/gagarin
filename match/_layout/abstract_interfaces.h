// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The three game interfaces AbstractClass derives besides IPersistStream.
//   Names and class-keys come from the retail RTTI TypeDescriptors
//   (".?AUIRTTITypeInfo@@" struct, ".?AVINoticeSink@@" / ".?AVINoticeSource@@"
//   classes); the hierarchy descriptors give IRTTITypeInfo one base (IUnknown)
//   and the notice interfaces none. Method names are placeholders.
#ifndef GG_MATCH_LAYOUT_ABSTRACT_INTERFACES_H
#define GG_MATCH_LAYOUT_ABSTRACT_INTERFACES_H

#include <objidl.h>   // IUnknown, IPersistStream, IStream (VC98 SDK, LIBRARY)
#include "../_rt/gg_static_assert.h"

// IRTTITypeInfo: IUnknown plus three __stdcall slots (AbstractClass's table
// 0x7E1F34). No table of its own is ever stored, so it is novtable like the
// SDK's MIDL interfaces.
struct __declspec(novtable) IRTTITypeInfo : public IUnknown
{
    virtual int __stdcall vf_rtti_3() = 0;    // 3
    virtual int __stdcall vf_rtti_4() = 0;    // 4
    virtual void __stdcall vf_rtti_5() = 0;   // 5
};
GG_STATIC_ASSERT(sizeof(IRTTITypeInfo) == 4);

#ifndef GG_MATCH_LAYOUT_INOTICESINK_DEFINED
#define GG_MATCH_LAYOUT_INOTICESINK_DEFINED
// VTABLE: GAMEMD 0x7E1FBC (1 slot, _purecall). Slot 0 overrides return false
// with RET 8 (0x410580).
class INoticeSink
{
public:
    virtual bool Notice(int id, int arg) = 0;            // 0
};
GG_STATIC_ASSERT(sizeof(INoticeSink) == 4);
#endif

// VTABLE: GAMEMD 0x7E1FB4 (1 slot, _purecall). Slot 0 overrides are a bare
// RET 4 (0x410590).
class INoticeSource
{
public:
    virtual void vf_0(int arg) = 0;                      // 0
};
GG_STATIC_ASSERT(sizeof(INoticeSource) == 4);

#endif  // GG_MATCH_LAYOUT_ABSTRACT_INTERFACES_H
