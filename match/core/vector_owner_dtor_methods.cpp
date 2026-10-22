// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//   Bytes matched against retail gamemd.exe v1.001 at 0x43A600.
//
// Flags: without /GX. Under /GX the destructor gets an exception frame to
// destroy the vector member if the body throws, and retail has none (0.0%).

#include "vector_owner_dtor_methods.h"

// FUNCTION: GAMEMD 0x43A600
// Delete every neuron and clear its slot, then clear the vector through its
// virtual Clear (+0x0C). The count is read once, before the loop. The member
// destructor that follows is the inline ~VectorClass: reseat the
// VectorClass<NeuronClass*> vtable and free the buffer only if it is owned.
BrainClass::~BrainClass()
{
    int count = Neurons.Count();
    for (int i = 0; i < count; i++) {
        delete Neurons.Items[i];
        Neurons.Items[i] = 0;
    }
    Neurons.Clear();
}
