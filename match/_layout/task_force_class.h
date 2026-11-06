// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail vtable 0x7F4680 (primary; +4 0x7F4664, +8 0x7F465C, +0xC 0x7F4654) names
//   .?AVTaskForceClass@@ in its locator. Slot 12 (0x6E87E0) returns the object size 0xD4;
//   the INI reader 0x6E8420 fills up to six {count, type} entries from +0xA4 and counts
//   them at +0x9C; the loader 0x6E86A0 swizzles the six type pointers (+0xA8, step 8).
#ifndef GG_MATCH_LAYOUT_TASK_FORCE_CLASS_H
#define GG_MATCH_LAYOUT_TASK_FORCE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "obj_004c4f90.h"

class TechnoTypeClass;
class CCINIClass;
struct TaskForceTypeView;

// The {amount, type} entry; its text form is the retail Obj_004C4F90 (see obj_004c4f90.h).
typedef Obj_004C4F90 TaskForceEntry;

class TaskForceClass : public AbstractTypeClass
{
public:
    // The stream loader's in-place construction.
    // FUNCTION: GAMEMD 0x6E7E80
    // The class factory's construction (TClassFactory<TaskForceClass>): the same constructor with a default argument.
    TaskForceClass(const char* id = 0);
    // FUNCTION: GAMEMD 0x6E8000
    // Copies the type identity and the used entries.
    TaskForceClass(const TaskForceClass& other);
    TaskForceClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}
    // FUNCTION: GAMEMD 0x6E87F0 (scalar deleting form; destructor expanded in place)
    virtual ~TaskForceClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6E86A0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6
    virtual int vf_11();                                                  // 11  0x6E87D0
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x6E8420
    virtual bool vf_26(CCINIClass* ini);                                  // 26  0x6E8510
    virtual int vf_12();                                                  // 12  0x6E87E0

    // FUNCTION: GAMEMD 0x6E80F0
    // Copy the source's entries into this one and return this by value (the copy is built in the caller's slot).
    TaskForceClass FUN_006E80F0(TaskForceClass* source);
    // FUNCTION: GAMEMD 0x6E8160
    int FUN_006E8160() const;
    // FUNCTION: GAMEMD 0x6E8780
    int FUN_006E8780() const;

    int            ArrayIndex;      // +0x98
    int            EntryCount;      // +0x9C
    int            unknown_A0;      // +0xA0
    TaskForceEntry Entries[6];      // +0xA4
};

GG_STATIC_ASSERT(offsetof(TaskForceClass, ArrayIndex) == 0x98);
GG_STATIC_ASSERT(offsetof(TaskForceClass, EntryCount) == 0x9C);
GG_STATIC_ASSERT(offsetof(TaskForceClass, Entries) == 0xA4);
GG_STATIC_ASSERT(sizeof(TaskForceClass) == 0xD4);

#endif
