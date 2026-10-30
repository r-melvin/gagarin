// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native AbstractClass constructors 0x410170 and 0x4101C0. With the four COM
// interfaces as real bases, the INoticeSink / INoticeSource implicit
// constructors store their own tables (0x7E1FBC / 0x7E1FB4) before the
// AbstractClass tables, as retail does; IPersistStream and IRTTITypeInfo are
// novtable, so they store nothing.
#include "../FUNCTION.H"

// FUNCTION: GAMEMD 0x410170
AbstractClass::AbstractClass()
    : UniqueID(-1), unknown_18(0), RefCount(0), Dirty(0)
{
    Flags.IsTechno = false;
    Flags.unknown_14_1 = false;
    Flags.IsFoot = false;
}

// FUNCTION: GAMEMD 0x4101C0
AbstractClass::AbstractClass(const AbstractNoInit&)
{
}
