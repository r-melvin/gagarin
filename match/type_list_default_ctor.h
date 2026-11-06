// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Body of TypeList<T>::TypeList(), kept out of type_list.h so that a TU decides by including this header whether the
// compiler can see it. Retail expands it inline in the ScenarioClass and TiberiumClass constructors and calls the
// out-of-line instantiation (0x5AC400, 0x67A390, 0x67A470, 0x67A4F0, 0x717AF0) from TechnoTypeClass::Load (0x7162F0).
#ifndef GG_MATCH_CORE_TYPE_LIST_DEFAULT_CTOR_H
#define GG_MATCH_CORE_TYPE_LIST_DEFAULT_CTOR_H
#include "type_list.h"
template<class T> TypeList<T>::TypeList() : DynamicVectorClass<T>() {}
#endif
