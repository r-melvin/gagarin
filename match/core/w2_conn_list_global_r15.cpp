// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The owned-connection list global at 0xB052D0: a DynamicVectorClass<ConnectionListStruct*>
// (vtable 0x7F0C2C) followed by a flag byte (+0x18) and a dword (+0x1C), both cleared by the
// initialiser at 0x663800. Its exit-time stub at 0x663850 frees and removes the head element
// until the list is empty, then runs the inlined vector destructor.
#include "vector_class_operations.h"

class OwnerTalkClass {
public:
    struct ConnectionListStruct;
};

struct ConnListHolder_00B052D0 {
    DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*> List;
    bool Flag;
    int Extra;

    ConnListHolder_00B052D0() : Flag(false), Extra(0) {}
    ~ConnListHolder_00B052D0()
    {
        while (List.Count != 0) {
            delete List.Items[0];
            List.Delete(0);
        }
    }
};

// GLOBAL: GAMEMD 0xB052D0
// SYNTHETIC: GAMEMD 0x00663800 -- initialiser of DAT_00B052D0 (fused ctor + atexit)
// SYNTHETIC: GAMEMD 0x00663850 -- exit-time destructor stub of DAT_00B052D0
ConnListHolder_00B052D0 DAT_00B052D0;
