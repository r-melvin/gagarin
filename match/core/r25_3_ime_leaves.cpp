// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below (IME composition handling).
//
// Address index: 0x777E40 0x777F90

#include <windows.h>
#include <string.h>
#include <stdlib.h>

// GLOBAL: GAMEMD 0xB7355C -- the IME input context.
extern int DAT_00B7355C;

// LIBRARY: GAMEMD 0x7C8A34 (declaration) -- import thunk for ImmGetCompositionStringA.
int __stdcall FUN_007C8A34(int himc, int index, char* buffer, int size);

// LIBRARY: GAMEMD 0x7C8A2E (declaration) -- import thunk for ImmGetCandidateListA.
int __stdcall FUN_007C8A2E(int himc, int index, void* list, int size);

// FUNCTION: GAMEMD 0x777E40
// Append the selected IME candidate to dest, keeping at most size characters (terminated). As in retail,
// the candidate offset is used directly as the string pointer.
void __fastcall FUN_00777E40(int himc, int index, char* dest, size_t size)
{
    if (himc != 0) {
        int bytes = FUN_007C8A2E(himc, index, 0, 0);
        if (bytes != 0) {
            CANDIDATELIST* list = (CANDIDATELIST*)malloc(bytes);
            if (list != 0) {
                if (list->dwCount != 0 && list->dwSelection < list->dwCount) {
                    strncat(dest, (char*)list->dwOffset[list->dwSelection], size);
                    dest[size - 1] = 0;
                }
                free(list);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x777F90
// Read the IME composition string, widen it and send each character to the window as message 0x4D9.
void __fastcall FUN_00777F90(HWND window)
{
    char narrow[0x204];
    WCHAR wide[0x102];
    if (DAT_00B7355C != 0) {
        int count = FUN_007C8A34(DAT_00B7355C, 0x800, narrow, 0x200);
        if (count > 0) {
            narrow[count] = 0;
            int length = MultiByteToWideChar(0, 0, narrow, strlen(narrow), wide, 0x100);
            if (length < 0) {
                length = 0;
            }
            wide[length] = 0;
            for (int i = 0; i < length; i++) {
                SendMessageA(window, 0x4D9, wide[i], wide[i]);
            }
        }
    }
}
