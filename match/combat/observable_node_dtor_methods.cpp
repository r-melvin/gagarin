// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x632F90,
//   0x632FF0 and 0x633370. Ordered ascending by retail address.

#include "observable_node_dtor_methods.h"

// FUNCTION: GAMEMD 0x632F90
//
// Destroy a notification node and, when the caller asked for it, release the
// node itself. The vtable is reseated to the node's own before anything else
// runs, the owned payload is deleted and its pointer cleared, and the shared
// base destructor is called last. The flags byte arrives on the stack and only
// its low bit is read, which is VC6's scalar-deleting destructor convention.
BlowPipe* BlowPipe::ScalarDeletingDtor(char flags)
{
    DestructInPlace();
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x632FF0
//
// The same for the type that carries a node as a subobject at +0x14. The
// node's destructor is inlined -- retail loads the payload straight from
// [this+0x20] and then works off `LEA ESI,[this+0x14]` -- and the shared base
// destructor runs twice, once for the subobject and once for the enclosing
// object's own base.
Obj_00632FF0* Obj_00632FF0::ScalarDeletingDtor(char flags)
{
    Node.DestructInPlace();
    ((Pipe*)this)->Pipe::~Pipe();
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x633370
//
// The third instance: the same inlined-subobject shape with the other
// subobject vtable and the other shared base destructor.
Obj_00633370* Obj_00633370::ScalarDeletingDtor(char flags)
{
    Node.DestructInPlace();
    ((NodeBaseB*)this)->Destruct();
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}
