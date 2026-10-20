// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at each address
//   below. Each of these eleven functions releases the COM interface a holder
//   keeps at offset 0, if it holds one: load the pointer, and when it is not
//   null call IUnknown::Release through vtable slot 2. All eleven are the same
//   thirteen bytes with no relocation at all — there is nothing per-instance
//   to parameterise — so the body is written once as a macro and expanded per
//   entry point. Ordered ascending by retail address.

#include "com_member_release_family_methods.h"

// FUNCTION: GAMEMD 0x004B4D50
GG_COM_MEMBER_RELEASE_BODY(004B4D50)

// FUNCTION: GAMEMD 0x004B4D60
GG_COM_MEMBER_RELEASE_BODY(004B4D60)

// FUNCTION: GAMEMD 0x004D0430
GG_COM_MEMBER_RELEASE_BODY(004D0430)

// FUNCTION: GAMEMD 0x004E02C0
GG_COM_MEMBER_RELEASE_BODY(004E02C0)

// FUNCTION: GAMEMD 0x0067FDD0
GG_COM_MEMBER_RELEASE_BODY(0067FDD0)

// FUNCTION: GAMEMD 0x0067FDE0
GG_COM_MEMBER_RELEASE_BODY(0067FDE0)

// FUNCTION: GAMEMD 0x00683050
GG_COM_MEMBER_RELEASE_BODY(00683050)

// FUNCTION: GAMEMD 0x00683060
GG_COM_MEMBER_RELEASE_BODY(00683060)

// FUNCTION: GAMEMD 0x006C61C0
GG_COM_MEMBER_RELEASE_BODY(006C61C0)

// FUNCTION: GAMEMD 0x007AC670
GG_COM_MEMBER_RELEASE_BODY(007AC670)

// FUNCTION: GAMEMD 0x007AC680
GG_COM_MEMBER_RELEASE_BODY(007AC680)
