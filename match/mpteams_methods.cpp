// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5D8D10  MPTeam::AddToList  (__thiscall)

#include <windows.h>
#include "mpteams_methods.h"

// Wide-string-or-empty accessor @0x7B7140 (__fastcall, single pointer arg in
// ECX): returns *ptr, or a static empty wide string when *ptr is null.
// Declared (no body) so the harness reloc-normalises the direct call.
extern "C" const wchar_t* MPTeam_TitleOrEmpty(wchar_t** ptr);

// FUNCTION: GAMEMD 0x5D8D10  (__thiscall)
// Add this team's title to the list/combo box (CB_ADDSTRING = 0x143), then tag
// the freshly-inserted item's data with the team Index (CB_SETITEMDATA = 0x151).
// SendMessageA is loaded once into a register and called twice (MOV EBP,[imp];
// CALL EBP x2). Returns the inserted item's index.
int MPTeam::AddToList(void* hWnd)
{
    const wchar_t* title = MPTeam_TitleOrEmpty(&this->Title);

    LRESULT (WINAPI *send)(HWND, UINT, WPARAM, LPARAM) = SendMessageA;

    WPARAM index = send((HWND)hWnd, 0x143, 0, (LPARAM)title);
    send((HWND)hWnd, 0x151, index, (LPARAM)this->Index);

    return index;
}
