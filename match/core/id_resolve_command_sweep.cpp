// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The six ID-resolving commands, ordered ascending by retail address.
//
// Two phrasing points carry the whole body. The three failure exits have to be
// one shared `goto`, not three `return false` statements: written as returns cl
// duplicates the two-instruction failure tail at each site and the layout
// diverges from the first branch (14.3%). And the predicate arm has to be a
// ternary feeding one assignment rather than an if/else assigning in both arms,
// which is what keeps retail's shared `MOV ECX,ESI` ahead of the test.

#include "id_resolve_command_sweep.h"

// FUNCTION: GAMEMD 0x6E30C0
bool __fastcall IdCommandOwner::FUN_006E30C0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_0050D440(obj);
    return true;

fail:
    return false;
}

// FUNCTION: GAMEMD 0x6E3120
bool __fastcall IdCommandOwner::FUN_006E3120(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_0050D320(obj);
    return true;

fail:
    return false;
}

// FUNCTION: GAMEMD 0x6E3180
bool __fastcall IdCommandOwner::FUN_006E3180(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC6D0(obj);
    return true;

fail:
    return false;
}

// FUNCTION: GAMEMD 0x6E31E0
bool __fastcall IdCommandOwner::FUN_006E31E0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC790(obj);
    return true;

fail:
    return false;
}

// FUNCTION: GAMEMD 0x6E3240
bool __fastcall IdCommandOwner::FUN_006E3240(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC820(obj);
    return true;

fail:
    return false;
}

// FUNCTION: GAMEMD 0x6E32A0
bool __fastcall IdCommandOwner::FUN_006E32A0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC8D0(obj);
    return true;

fail:
    return false;
}

