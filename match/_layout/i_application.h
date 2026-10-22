// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Interface stub for the RTTI base IApplication (TypeDescriptor .?AUIApplication@@). It has no vtable of
//   its own in the image, so only what RTTI and the deriving vtables attest is declared:
//   its own bases (IUnknown); its slot count is not attested (it is the primary base of every deriving class here).
#ifndef GG_MATCH_LAYOUT_I_APPLICATION_H
#define GG_MATCH_LAYOUT_I_APPLICATION_H

#include <unknwn.h>

struct __declspec(novtable) IApplication : public IUnknown
{
};

#endif  // GG_MATCH_LAYOUT_I_APPLICATION_H
