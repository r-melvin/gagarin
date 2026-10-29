// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x412870 and 0x4128F0.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
//
// The aircraft tracker object at 0x887888: 0x190 bucket vectors (0x18 bytes each,
// DynamicVectorClass<TechnoClass*> by RTTI of vtable 0x7E17AC) followed by the
// current-cell vector at 0x889E08. One object, so one initialiser and one atexit
// registration. The bucket loop calls the VectorClass base constructor (0x40BD00)
// per element while the trailing member has it inlined: the compiler's own
// inlining split for a member array against a single member. The destructor body
// is the tracker's Clear (0x413800) -- every vector emptied and its capacity
// re-reserved -- followed by the implicit member destruction (current vector,
// then the buckets backwards).
#include "vector_class_operations.h"

class TechnoClass;

struct TrackerStorage_00887888
{
    DynamicVectorClass<TechnoClass*> TrackerVectors[0x190];  // +0x0000 0x887888
    DynamicVectorClass<TechnoClass*> CurrentVector;          // +0x2580 0x889E08

    ~TrackerStorage_00887888()
    {
        DynamicVectorClass<TechnoClass*>* v = TrackerVectors;
        int i = 0x190;
        do {
            int cap = v->Capacity;
            v->Clear();
            v->SetCapacity(cap, 0);
            ++v;
        } while (--i != 0);

        int cap = CurrentVector.Capacity;
        CurrentVector.Clear();
        CurrentVector.SetCapacity(cap, 0);
    }
};
GG_STATIC_ASSERT(offsetof(TrackerStorage_00887888, CurrentVector) == 0x2580);
GG_STATIC_ASSERT(sizeof(TrackerStorage_00887888) == 0x2598);

// SYNTHETIC: GAMEMD 0x412870 -- initialiser: constructs DAT_00887888, registers 0x4128F0.
// SYNTHETIC: GAMEMD 0x4128F0 -- atexit cleanup: destroys DAT_00887888.
// GLOBAL: GAMEMD 0x887888
TrackerStorage_00887888 DAT_00887888;
