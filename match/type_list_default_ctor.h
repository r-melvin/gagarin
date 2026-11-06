// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Body of TypeList<T>::TypeList(), kept out of type_list.h so that a TU decides by including this header whether the
// compiler can see it. vector_class_operations.h includes it, so the body is visible in 402 of the TUs (every TU
// that reaches that header, directly or through _layout/*.h), and the constructor is inlined there. Retail expands
// it inline in the ScenarioClass and TiberiumClass constructors and in 0x665650, and calls the out-of-line
// instantiations (0x512960, 0x5AC400, 0x67A390, 0x67A470, 0x67A4F0, 0x67A600, 0x67A740, 0x67A820, 0x67A8B0,
// 0x717AF0) from TechnoTypeClass::Load (0x7162F0), HouseTypeClass::Load (0x512290), the RulesClass no-init
// constructor (0x664D20) and the unmatched 0x5981F0, 0x672AE0, 0x675210, 0x75E0C0, 0x721E80 and 0x772CD0. Of the
// matched or partial callers, trivial_tu238_methods.cpp (0x7162F0) is the TU that gets the call form from the body
// being invisible; 0x664D20 calls eleven lists and expands one inside a single function (an inline-budget effect).
#ifndef GG_MATCH_CORE_TYPE_LIST_DEFAULT_CTOR_H
#define GG_MATCH_CORE_TYPE_LIST_DEFAULT_CTOR_H
#include "type_list.h"
template<class T> TypeList<T>::TypeList() : DynamicVectorClass<T>() {}
#endif
