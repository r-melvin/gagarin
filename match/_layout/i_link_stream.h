// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Interface stub for the RTTI base ILinkStream (TypeDescriptor .?AUILinkStream@@). It has no vtable of
//   its own in the image, so only what RTTI and the deriving vtables attest is declared:
//   its own bases (IUnknown) and 5 vtable slots at its subobject offset in a deriving class.
#ifndef GG_MATCH_LAYOUT_I_LINK_STREAM_H
#define GG_MATCH_LAYOUT_I_LINK_STREAM_H

#include <unknwn.h>

struct __declspec(novtable) ILinkStream : public IUnknown
{
    virtual void vf_3() = 0;   // 3
    virtual void vf_4() = 0;   // 4
};

#endif  // GG_MATCH_LAYOUT_I_LINK_STREAM_H
