// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   /Ob2: the scalar deleting destructor 0x4105A0 carries the destructor body
//   (the four vptr stores) inline, while 0x4101F0 also exists out of line and
//   is called by derived destructors (0x4109C0). Plain /O2 calls 0x4101F0.
// Retail 0x4101F0 reinstalls the four AbstractClass vptrs and returns. The
// interfaces have no destructors, so their tables are not restored.
#include "../FUNCTION.H"

// FUNCTION: GAMEMD 0x4101F0
AbstractClass::~AbstractClass()
{
}

// SYNTHETIC: GAMEMD 0x4105A0 -- compiler-generated scalar deleting destructor.
// SYNTHETIC: GAMEMD 0x4105E0 -- compiler-generated IRTTITypeInfo QI adjustor thunk.
// SYNTHETIC: GAMEMD 0x4105F0 -- compiler-generated IRTTITypeInfo AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x410600 -- compiler-generated IRTTITypeInfo Release adjustor thunk.
