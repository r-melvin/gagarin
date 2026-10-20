// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x49A200 and its 36
//   neighbours. Functions are ordered ascending by retail address.

#include "cached_resource_dtor_family_methods.h"

// FUNCTION: GAMEMD 0x0049A200
//
// The scalar-deleting destructor of one of these objects. It reseats the
// vtable to this class, drops the reference the object holds on its registry
// handle, clears the handle, lets the inlined empty base destructor reseat the
// vtable to the base class, and finally frees the object itself when the
// caller set the deleting bit. The rest of this file is the same body once per
// class, which is how retail lays the family out: a run of identical 0x3B-byte
// functions differing only in the two vtables they store.
void* CachedResourceOwner8::FUN_0049A200(char flags)
{
    Vptr = &VT_007E57F8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A240
//
// As above, for the class whose vtable is at 0x007E57E0.
void* CachedResourceOwner8::FUN_0049A240(char flags)
{
    Vptr = &VT_007E57E0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A280
//
// As above, for the class whose vtable is at 0x007E57C8.
void* CachedResourceOwnerC::FUN_0049A280(char flags)
{
    Vptr = &VT_007E57C8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A2C0
//
// As above, for the class whose vtable is at 0x007E57B0.
void* CachedResourceOwner8::FUN_0049A2C0(char flags)
{
    Vptr = &VT_007E57B0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A300
//
// As above, for the class whose vtable is at 0x007E5798.
void* CachedResourceOwner8::FUN_0049A300(char flags)
{
    Vptr = &VT_007E5798;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A340
//
// As above, for the class whose vtable is at 0x007E5780.
void* CachedResourceOwner8::FUN_0049A340(char flags)
{
    Vptr = &VT_007E5780;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A420
//
// As above, for the class whose vtable is at 0x007E56F0.
void* CachedResourceOwner8::FUN_0049A420(char flags)
{
    Vptr = &VT_007E56F0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A460
//
// As above, for the class whose vtable is at 0x007E56D8.
void* CachedResourceOwnerC::FUN_0049A460(char flags)
{
    Vptr = &VT_007E56D8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A4A0
//
// As above, for the class whose vtable is at 0x007E56C0.
void* CachedResourceOwner8::FUN_0049A4A0(char flags)
{
    Vptr = &VT_007E56C0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A4E0
//
// As above, for the class whose vtable is at 0x007E56A8.
void* CachedResourceOwner8::FUN_0049A4E0(char flags)
{
    Vptr = &VT_007E56A8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A520
//
// As above, for the class whose vtable is at 0x007E5690.
void* CachedResourceOwner8::FUN_0049A520(char flags)
{
    Vptr = &VT_007E5690;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A560
//
// As above, for the class whose vtable is at 0x007E5678.
void* CachedResourceOwner8::FUN_0049A560(char flags)
{
    Vptr = &VT_007E5678;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A5A0
//
// As above, for the class whose vtable is at 0x007E5660.
void* CachedResourceOwner8::FUN_0049A5A0(char flags)
{
    Vptr = &VT_007E5660;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A5E0
//
// As above, for the class whose vtable is at 0x007E5648.
void* CachedResourceOwner8::FUN_0049A5E0(char flags)
{
    Vptr = &VT_007E5648;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A620
//
// As above, for the class whose vtable is at 0x007E5630.
void* CachedResourceOwner8::FUN_0049A620(char flags)
{
    Vptr = &VT_007E5630;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A660
//
// As above, for the class whose vtable is at 0x007E5618.
void* CachedResourceOwnerC::FUN_0049A660(char flags)
{
    Vptr = &VT_007E5618;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A6A0
//
// As above, for the class whose vtable is at 0x007E5600.
void* CachedResourceOwner8::FUN_0049A6A0(char flags)
{
    Vptr = &VT_007E5600;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A6E0
//
// As above, for the class whose vtable is at 0x007E55E8.
void* CachedResourceOwner8::FUN_0049A6E0(char flags)
{
    Vptr = &VT_007E55E8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049A720
//
// As above, for the class whose vtable is at 0x007E55D0.
void* CachedResourceOwner8::FUN_0049A720(char flags)
{
    Vptr = &VT_007E55D0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AA00
//
// As above, for the class whose vtable is at 0x007E5470.
void* CachedResourceOwner8::FUN_0049AA00(char flags)
{
    Vptr = &VT_007E5470;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AA40
//
// As above, for the class whose vtable is at 0x007E5460.
void* CachedResourceOwnerC::FUN_0049AA40(char flags)
{
    Vptr = &VT_007E5460;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AA80
//
// As above, for the class whose vtable is at 0x007E5450.
void* CachedResourceOwner8::FUN_0049AA80(char flags)
{
    Vptr = &VT_007E5450;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AAC0
//
// As above, for the class whose vtable is at 0x007E5440.
void* CachedResourceOwner8::FUN_0049AAC0(char flags)
{
    Vptr = &VT_007E5440;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AB00
//
// As above, for the class whose vtable is at 0x007E5430.
void* CachedResourceOwner8::FUN_0049AB00(char flags)
{
    Vptr = &VT_007E5430;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AB40
//
// As above, for the class whose vtable is at 0x007E5420.
void* CachedResourceOwner8::FUN_0049AB40(char flags)
{
    Vptr = &VT_007E5420;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AB80
//
// As above, for the class whose vtable is at 0x007E5410.
void* CachedResourceOwnerC::FUN_0049AB80(char flags)
{
    Vptr = &VT_007E5410;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049ABC0
//
// As above, for the class whose vtable is at 0x007E5400.
void* CachedResourceOwner8::FUN_0049ABC0(char flags)
{
    Vptr = &VT_007E5400;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AC00
//
// As above, for the class whose vtable is at 0x007E53F0.
void* CachedResourceOwner8::FUN_0049AC00(char flags)
{
    Vptr = &VT_007E53F0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AC40
//
// As above, for the class whose vtable is at 0x007E53E0.
void* CachedResourceOwner8::FUN_0049AC40(char flags)
{
    Vptr = &VT_007E53E0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AC80
//
// As above, for the class whose vtable is at 0x007E53D0.
void* CachedResourceOwner8::FUN_0049AC80(char flags)
{
    Vptr = &VT_007E53D0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049ACC0
//
// As above, for the class whose vtable is at 0x007E53C0.
void* CachedResourceOwner8::FUN_0049ACC0(char flags)
{
    Vptr = &VT_007E53C0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AD00
//
// As above, for the class whose vtable is at 0x007E53B0.
void* CachedResourceOwner8::FUN_0049AD00(char flags)
{
    Vptr = &VT_007E53B0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AD40
//
// As above, for the class whose vtable is at 0x007E53A0.
void* CachedResourceOwner8::FUN_0049AD40(char flags)
{
    Vptr = &VT_007E53A0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AD80
//
// As above, for the class whose vtable is at 0x007E5390.
void* CachedResourceOwnerC::FUN_0049AD80(char flags)
{
    Vptr = &VT_007E5390;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049ADC0
//
// As above, for the class whose vtable is at 0x007E5380.
void* CachedResourceOwner8::FUN_0049ADC0(char flags)
{
    Vptr = &VT_007E5380;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AE00
//
// As above, for the class whose vtable is at 0x007E5370.
void* CachedResourceOwner8::FUN_0049AE00(char flags)
{
    Vptr = &VT_007E5370;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x0049AE40
//
// As above, for the class whose vtable is at 0x007E5360.
void* CachedResourceOwner8::FUN_0049AE40(char flags)
{
    Vptr = &VT_007E5360;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}
