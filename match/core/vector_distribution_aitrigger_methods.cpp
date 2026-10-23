// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI names the vector VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::
// DistributionObject<AITriggerTypeClass*>>. The distribution object is a pointer and a
// weight (8 bytes, user-declared default constructor and destructor, so the element array
// is constructed by the array-new counter loop). The constructor taking a capacity and
// optional storage is the body at 0x6F27F0.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class AITriggerTypeClass;
template<class C> struct DiscreteDistributionClass { template<class P> struct DistributionObject { P Object; int Weight; DistributionObject() : Weight(0) {} ~DistributionObject() {} DistributionObject(const DistributionObject<P>& o) : Object(o.Object), Weight(o.Weight) {} bool operator==(const DistributionObject<P>& o) const { return Object==o.Object && Weight==o.Weight; } bool operator!=(const DistributionObject<P>& o) const { return !(*this==o); } }; };

// FUNCTION: GAMEMD 0x006F27F0
// Constructor (capacity, optional storage) of the vector of AITriggerTypeClass distribution objects.
template class VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;
