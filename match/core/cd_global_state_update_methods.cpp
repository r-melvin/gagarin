// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 0x47AAC0 clears the search-path list at 0x89E410 and tail-jumps to the
// independently callable 0x47AB10 path helper. 0x47AD50 allocates and appends
// an 8-byte search-path node. 0x47ADA0 stores an ECX dword in 0x89E414 and
// shifts the prior value to 0x89E418; 0x47AB10 reads the low byte of 0x89E414
// as an index. Names and original owners remain unknown.
#include "../_rt/gg_static_assert.h"
#include "../_layout/cd_search_path.h"

// FUNCTION: GAMEMD 0x0047AB10 (decl; reloc; ECX path/EAX result ABI view; original return type unknown)
int __fastcall FUN_0047AB10(char* basePath);

// GLOBAL: GAMEMD 0x0089E41C (writable path buffer; capacity not established)
extern char DAT_0089E41C[];

// LIBRARY: GAMEMD 0x007C93E8 (caller cleanup)
extern "C" void __cdecl FUN_007C93E8(void* block);
// LIBRARY: GAMEMD 0x007C8B3D (caller cleanup)
extern "C" void __cdecl FUN_007C8B3D(void* block);
// FUNCTION: GAMEMD 0x007D5408 (decl; reloc; caller-cleanup duplicate helper)
extern "C" char* __cdecl FUN_007D5408(char* text);
// LIBRARY: GAMEMD 0x007C8E17 (caller cleanup; operator new)
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

GG_STATIC_ASSERT(sizeof(unsigned int) == 4);

// GLOBAL: GAMEMD 0x0089E414
extern unsigned int DAT_0089E414;
// GLOBAL: GAMEMD 0x0089E418
extern unsigned int DAT_0089E418;
GG_STATIC_ASSERT(sizeof(DAT_0089E414) == 4);
GG_STATIC_ASSERT(sizeof(DAT_0089E418) == 4);

// FUNCTION: GAMEMD 0x0047AAC0 (0x43-byte wrapper; tail jump to 0x47AB10)
int __cdecl FUN_0047AAC0(void)
{
    SearchPath_0047AE10* node = DAT_0089E410;
    while (node != 0) {
        SearchPath_0047AE10* next = node->Next;
        if (node->Path != 0) {
            FUN_007C93E8((void*)node->Path);
        }
        FUN_007C8B3D(node);
        node = next;
    }
    DAT_0089E410 = 0;
    return FUN_0047AB10(DAT_0089E41C);
}

// FUNCTION: GAMEMD 0x0047AD50 (69 bytes, entry-origin)
void __fastcall FUN_0047AD50(char* path)
{
    SearchPath_0047AE10* added =
        (SearchPath_0047AE10*)FUN_007C8E17(8);
    added->Path = FUN_007D5408(path);
    added->Next = 0;

    if (DAT_0089E410 == 0) {
        DAT_0089E410 = added;
        return;
    }

    SearchPath_0047AE10* tail = DAT_0089E410;
    while (tail->Next != 0) {
        tail = tail->Next;
    }
    tail->Next = added;
}

// FUNCTION: GAMEMD 0x0047ADA0 (17 bytes, entry-origin, RET)
void __fastcall FUN_0047ADA0(unsigned int value)
{
    unsigned int previous = DAT_0089E414;
    DAT_0089E414 = value;
    DAT_0089E418 = previous;
}

// FUNCTION: GAMEMD 0x0047ADC0 (66 bytes, no-argument caller view)
// Retail callers provide no arguments and ignore EAX; the original distinction
// between a global cdecl entry and another thisless no-argument convention is
// not observable from those call sites.
void __cdecl FUN_0047ADC0(void)
{
    SearchPath_0047AE10* node = DAT_0089E410;
    if (node != 0) {
        do {
            SearchPath_0047AE10* next = node->Next;
            if (node->Path != 0) {
                FUN_007C93E8((void*)node->Path);
            }
            FUN_007C8B3D(node);
            node = next;
        } while (node != 0);
        DAT_0089E410 = node;
        return;
    }
    DAT_0089E410 = 0;
}
