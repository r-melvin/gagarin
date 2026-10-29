// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below; the
//   per-object drain is the body of 0x401FC0 expanded inline.
//
// Ordered ascending by retail address.

#include "drain_and_unlink_methods.h"
#include "small_misc3_methods.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);
void FUN_00407510(void* self);

// Object whose +0xC list holds Obj_00401FC0 entries.
struct Mgr_00401B00
{
    char     _pad000[0x4];     // +0x0000
    void*    At_04;            // +0x0004
    void*    At_08;            // +0x0008
    ListNode List_0C;          // +0x000C

    void FUN_00401B00();
    int FUN_00401EF0();
};
GG_STATIC_ASSERT(offsetof(Mgr_00401B00, At_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Mgr_00401B00, At_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Mgr_00401B00, List_0C) == 0xC);

// Entry of the +0xC list: the +0xC field is the "still in use" word read by 0x401EF0.
struct Ent_00401B00
{
    char          _pad000[0x4];     // +0x0000
    void*         Link;             // +0x0004
    char          _pad008[0x4];     // +0x0008
    int           InUse;            // +0x000C
    char          _pad010[0xC];     // +0x0010
    char          At_1C[0x8];       // +0x001C
    char          At_24[0x18];      // +0x0024
    Ctx_00401FC0* Ctx;              // +0x003C
};
GG_STATIC_ASSERT(offsetof(Ent_00401B00, InUse) == 0xC);
GG_STATIC_ASSERT(offsetof(Ent_00401B00, At_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Ent_00401B00, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Ent_00401B00, Ctx) == 0x3C);

// FUNCTION: GAMEMD 0x401B00
//
// Drain every entry off the +0xC list, each one unlinked, its node list
// returned to the context's free list and its +0x1C part torn down, then
// release the two owned blocks and the object itself.
void Mgr_00401B00::FUN_00401B00()
{
    Ent_00401B00* ent;
    while ((ent = (Ent_00401B00*)FUN_00407470(&List_0C)) != 0) {
        if (ent->Link != ent) {
            FUN_00407450(ent);
        }
        Node_00401FC0* node;
        while ((node = FUN_00407470(ent->At_24)) != 0) {
            FUN_00407450(node);
            FUN_00408600(node);
            FUN_00407530(ent->Ctx->NodeList, node);
        }
        FUN_00408530(ent->At_1C);
        FUN_00407530(ent->Ctx->ObjList, ent);
    }
    if (At_04) {
        FUN_00407510(At_04);
    }
    if (At_08) {
        FUN_00407510(At_08);
    }
    FUN_007C8B3D(this);
}

// FUNCTION: GAMEMD 0x401EF0
//
// Find the first entry on the +0xC list that is not in use and release it the
// same way as above; returns whether one was found.
//
// PARTIAL: 94.3% (50/53). The only delta is the epilogue order: retail loads the
// result (`MOV EAX,1`) ahead of the three pops, cl pops ESI and EBX first. Tried
// a named result local, the loop spelled with a leading null test, and a
// separate node temporary; none moves it.
int Mgr_00401B00::FUN_00401EF0()
{
    Ent_00401B00* ent = (Ent_00401B00*)FUN_00407480(&List_0C);
    for (;;) {
        if (!ent) {
            return 0;
        }
        if (ent->InUse == 0) {
            break;
        }
        ent = (Ent_00401B00*)FUN_00407480((ListNode*)ent);
    }
    if (ent->Link != ent) {
        FUN_00407450(ent);
    }
    Node_00401FC0* node = FUN_00407470(ent->At_24);
    while (node) {
        FUN_00407450(node);
        FUN_00408600(node);
        FUN_00407530(ent->Ctx->NodeList, node);
        node = FUN_00407470(ent->At_24);
    }
    FUN_00408530(ent->At_1C);
    FUN_00407530(ent->Ctx->ObjList, ent);
    return 1;
}
