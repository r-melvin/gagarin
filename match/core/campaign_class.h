// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @0x46CC90 / @0x46CE10),
//   cross-checked against YRpp CampaignClass.h / CCINIClass.h (consult-only, no
//   LICENSE; every offset reconfirmed numerically from the disasm below).
//
// CampaignClass — a single-player campaign/battle definition. It derives from
// AbstractTypeClass (ID at +0x24) through a four-vptr COM base, so the inlined
// constructor writes four vtable pointers. Its own members, confirmed from the
// inlined constructor in CreateFromINIList:
//   +0x000 vptr        ([ESI]      = 0x7E4A28)
//   +0x004 vptr        ([ESI+0x4]  = 0x7E4A0C)
//   +0x008 vptr        ([ESI+0x8]  = 0x7E4A04)
//   +0x00C vptr        ([ESI+0xC]  = 0x7E49FC)
//   +0x098 int      idxCD       ([ESI+0x98] = -1)
//   +0x09C char     Scenario[512] ([ESI+0x9c] byte = 0; 0x9c+0x200 == 0x29c)
//   +0x29C int      FinalMovie  ([ESI+0x29c] = -1)
//   +0x2A0 wchar_t  Description[128] (wcscpy @0x2a0; 0x2a0+0x100 == 0x3a0 == new size)
#ifndef GG_MATCH_CORE_CAMPAIGN_CLASS_H
#define GG_MATCH_CORE_CAMPAIGN_CLASS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

class CCINIClass;  // INI reader; methods declared in the .cpp at their vaddrs.

struct CampaignVtbl;         // forward; completed once CampaignClass is complete

// ---------------------------------------------------------------------------
// CampaignClass  (sizeof = 0x3A0 — operator new(0x3a0) @0x46CE9C)
// ---------------------------------------------------------------------------
class CampaignClass
{
public:
    // Static helpers (free functions, __fastcall => first arg in ECX).
    // Declared ascending by retail address.
    static int  __fastcall FindIndex(const char* name);          // GAMEMD 0x46CC90
    static void __fastcall CreateFromINIList(CCINIClass* pINI);   // GAMEMD 0x46CE10

    // FUNCTION: GAMEMD 0x410800 (decl; reloc) — the AbstractTypeClass base
    // constructor, __thiscall with the identifier on the stack.
    void BaseConstruct(const char* name);

    // The constructor body, written as an explicit Construct so that the
    // allocation does NOT get VC6's /GX exception frame (see the .cpp).
    __forceinline CampaignClass* Construct(const char* name);

    // --- layout (only members the matched code touches are named) ---
    CampaignVtbl* Vptr;         // +0x00
    void*   Vptr2;              // +0x04
    void*   Vptr3;              // +0x08
    void*   Vptr4;              // +0x0C
    char    _gap_10[0x24 - 0x10];
    char    ID[0x18];           // +0x24  AbstractTypeClass identifier
    char    _gap_3C[0x98 - 0x3C];
    int     idxCD;              // +0x98
    char    Scenario[512];     // +0x9C
    int     FinalMovie;        // +0x29C
    wchar_t Description[128];  // +0x2A0
};

GG_STATIC_ASSERT(offsetof(CampaignClass, ID)          == 0x24);
GG_STATIC_ASSERT(offsetof(CampaignClass, idxCD)       == 0x98);
GG_STATIC_ASSERT(offsetof(CampaignClass, Scenario)    == 0x9C);
GG_STATIC_ASSERT(offsetof(CampaignClass, FinalMovie)  == 0x29C);
GG_STATIC_ASSERT(offsetof(CampaignClass, Description) == 0x2A0);
GG_STATIC_ASSERT(sizeof(CampaignClass) == 0x3A0);

// ReadINI lives at vtable slot +0x64 (`MOV EDX,[ESI]; PUSH pINI; MOV ECX,ESI;
// CALL dword ptr [EDX+0x64]` @0x46CF60).
typedef void (CampaignClass::*CampaignReadINI)(CCINIClass*);
struct CampaignVtbl
{
    char            _pad_00[0x64];
    CampaignReadINI At_64;      // +0x64
};

// ---------------------------------------------------------------------------
// DynamicVectorClass<CampaignClass*> — the global `CampaignClass::Array`.
// Base @0xA83CF8 (vtable). Confirmed offsets from the disasm:
//   +0x04 Items  (DAT_00A83CFC),  +0x08 Capacity (DAT_00A83D00),
//   +0x0D IsAllocated (DAT_00A83D05), +0x10 Count (DAT_00A83D08),
//   +0x14 CapacityIncrement (DAT_00A83D0C).
// SetCapacity is vtable slot +0x08 (`MOV EDX,[0xa83cf8]; PUSH 0; PUSH newcap;
// MOV ECX,0xa83cf8; CALL dword ptr [EDX+8]` @0x46CF08..0x46CF18), __thiscall,
// two stack arguments, byte result.
// ---------------------------------------------------------------------------
struct CampaignVectorVtbl;

struct CampaignVectorClass
{
    CampaignVectorVtbl* Vptr;          // +0x00
    CampaignClass** Items;             // +0x04
    int             Capacity;          // +0x08
    char            IsInitialized;     // +0x0C
    char            IsAllocated;       // +0x0D
    char            _pad_0E[2];        // +0x0E
    int             Count;             // +0x10
    int             CapacityIncrement; // +0x14

    bool AddItem(CampaignClass* item);
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(CampaignVectorClass, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(CampaignVectorClass, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(CampaignVectorClass, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(CampaignVectorClass, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(CampaignVectorClass, CapacityIncrement) == 0x14);
#endif

typedef bool (CampaignVectorClass::*CampaignVectorSetCapacity)(int, void*);
struct CampaignVectorVtbl
{
    char                      _pad_00[0x08];
    CampaignVectorSetCapacity At_08;   // +0x08
};

// GLOBAL: GAMEMD 0xA83CF8 — CampaignClass::Array.
extern CampaignVectorClass CampaignArray;

// The inlined DynamicVectorClass<T>::AddItem body (0x46CEE1..0x46CF34).
inline bool CampaignVectorClass::AddItem(CampaignClass* item)
{
    if (this->Count >= this->Capacity) {
        if (this->IsAllocated || !this->Capacity) {
            int grow = this->CapacityIncrement;
            if (grow <= 0) {
                return false;
            }
            grow += this->Capacity;
            if (!(this->*this->Vptr->At_08)(grow, 0)) {
                return false;
            }
        } else {
            return false;
        }
    }

    int index = this->Count++;
    this->Items[index] = item;
    return true;
}

#endif  // GG_MATCH_CORE_CAMPAIGN_CLASS_H
