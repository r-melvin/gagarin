// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x5301A0 / 0x5B40B0),
//   cross-checked against YRpp (every offset/slot reconfirmed against the user's binary here).
//
// MixFileClass — the engine's mounted .MIX archive. This TU covers the two
// static bootstrap/lookup entry points:
//   0x5301A0  MixFileClass::Bootstrap  (mount EXPANDMD##.MIX + the fixed set)
//   0x5B40B0  MixFileClass::Retrieve   (CRC-keyed cached file lookup)
#ifndef GG_MATCH_PLATFORM_MIX_FILE_CLASS_H
#define GG_MATCH_PLATFORM_MIX_FILE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct MixFileClass;

// ---------------------------------------------------------------------------
// DynamicVectorClass<MixFileClass*>  (YRpp layout/vtable order,
// reconfirmed from the inlined AddItem at 0x53020B-0x530277):
//   +0x00 vtable   +0x04 Items   +0x08 Capacity   +0x0C IsInitialized(bool)
//   +0x0D IsAllocated(bool)   +0x10 Count   +0x14 CapacityIncrement
// vtable slot 2 ([vtable+0x8]) == SetCapacity (CALL [EDX+0x8] in the grow path).
// ---------------------------------------------------------------------------
struct DynamicVectorClass_Mix
{
    virtual ~DynamicVectorClass_Mix();                                 // slot 0
    virtual bool operator==(const DynamicVectorClass_Mix& o) const;    // slot 1
    virtual bool SetCapacity(int capacity, MixFileClass** mem);        // slot 2

    MixFileClass** Items;            // +0x04
    int            Capacity;         // +0x08
    unsigned char  IsInitialized;    // +0x0C
    unsigned char  IsAllocated;      // +0x0D
    int            Count;            // +0x10
    int            CapacityIncrement;// +0x14

};

// The inlined AddItem, written as a FREE function taking the vector as its
// first pointer parameter rather than as a member. Same body; the shape is what
// decides the bytes. As a member cl accumulates the grow size into the
// capacity's register and pushes it from there (`ADD EAX,ECX; PUSH EAX`), where
// retail accumulates into the increment's register (`ADD ECX,EAX; PUSH ECX`).
// Same lever as TagClass::Destroy's append.
inline bool DynamicVectorClass_Mix_AddItem(DynamicVectorClass_Mix* v, MixFileClass* item)
{
    if (v->Count >= v->Capacity)
    {
        if ((v->IsAllocated || !v->Capacity) && v->CapacityIncrement > 0)
        {
            if (!v->SetCapacity(v->CapacityIncrement + v->Capacity, 0))
                return false;
        }
        else
        {
            return false;
        }
    }
    int i = v->Count++;
    v->Items[i] = item;
    return true;
}

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_Mix, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_Mix, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_Mix, IsInitialized)     == 0x0C);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_Mix, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_Mix, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_Mix, CapacityIncrement) == 0x14);
#endif

// ---------------------------------------------------------------------------
// A FileClass-derived scan probe (FUN_0065CA80 ctor / FUN_0065CA00 dtor;
// virtual slot 5 = Is_Available(bool)). Only the shape needed by Bootstrap.
// ---------------------------------------------------------------------------
// FileClass virtual interface (only slots 0..5 needed; slot 5 = Is_Available).
struct FileBase
{
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual void  v3();
    virtual void  v4();
    virtual char  Is_Available(int forced);// slot 5 ([vtable+0x14])
};

struct ScanFile : FileBase
{
    ScanFile(const char* name) throw();    // 0x65CA80  __thiscall ctor (returns this)
    ~ScanFile();                           // 0x65CA00  non-virtual dtor
    char _body[0x20];                      // FileClass body — 0x20, so sizeof(ScanFile)
                                           //   is 0x24. Bootstrap's frame pins it: with
                                           //   four callee-saved pushes live, retail's
                                           //   `LEA ECX,[ESP+0x14]` puts the probe at
                                           //   in-frame +0x04 and `LEA EDX,[ESP+0x38]`
                                           //   puts the name buffer at +0x28, so the
                                           //   probe spans 0x24 bytes and the buffer runs
                                           //   +0x28..+0x68, i.e. 0x40. — P2 for the rest
};

// MixFileClass minimal model. sizeof == 0x28 so `new MixFileClass(...)` emits
// operator new(0x28) exactly as retail (PUSH 0x28; CALL ??2@YAPAXI@Z). The ctor
// (FUN_005B3C20) takes (name, "") — the empty-string second arg is 0x886980.
struct MixFileClass
{
    // throw() => no /GX delete-on-ctor-throw EH frame, matching the retail
    // codegen (plain `new(0x28); if(p) ctor`, no fs:0 SEH prologue).
    MixFileClass(const char* name, const char* tag = "") throw();  // 0x5B3C20 __thiscall
    virtual ~MixFileClass();                               // Node<> dtor slot 0
    char _layout[0x24];                                    // full layout = P2
};
GG_STATIC_ASSERT(sizeof(MixFileClass) == 0x28);

// ---------------------------------------------------------------------------
// The stack CCFileClass probe used by Retrieve on a cache miss. Layout read
// off 0x5B40B0: the object sits at [ESP+0x20] and runs 0x6C bytes up to the
// name scratch; the inline teardown stores 0x7E16B0 at +0x00, zeroes +0x64,
// releases the sub-object at +0x58 through 0x43AE50, stores 0x7E1668 at
// +0x00 and calls 0x431B80 (same shape as 0x4A38D0). Torn down explicitly,
// never through a real destructor, which under /GX would add an EH frame
// retail lacks.
// ---------------------------------------------------------------------------
extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E1668;   // VTABLE: GAMEMD 0x7E1668 — CDFileClass
// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void __fastcall FUN_00431B80(void* self);

struct CCFile_005B40B0
{
    char* Vtbl;                        // +0x0000
    char  _pad004[0x58 - 0x04];
    char  Sub58[0x64 - 0x58];          // +0x0058  the released sub-object
    int   Reset64;                     // +0x0064
    char  _pad068[0x6C - 0x68];

    // FUNCTION: GAMEMD 0x4739F0 (decl; reloc) — constructor from a name.
    CCFile_005B40B0* FUN_004739F0(char* name);
    // FUNCTION: GAMEMD 0x473C50 (decl; reloc) — CCFileClass::Exists(writeShared).
    bool FUN_00473C50(int writeShared);
};
GG_STATIC_ASSERT(offsetof(CCFile_005B40B0, Sub58)   == 0x58);
GG_STATIC_ASSERT(offsetof(CCFile_005B40B0, Reset64) == 0x64);
GG_STATIC_ASSERT(sizeof(CCFile_005B40B0)            == 0x6C);

// Cache(name, mode) — FUN_005B43E0, __fastcall(const char* name, int mode),
// returns bool. Mounts a generic .MIX into the engine cache.
bool __fastcall MixCache(const char* name, int mode);

// FUN_004790B0 — __fastcall(int): push/restore the file search mode.
void __fastcall SetFileSearchMode(int mode);

// FUN_004A4AC0 — variadic cdecl progress logger (" %s", " CACHE.MIX", ...).
void Log_4a4ac0(const char* fmt, ...);

// ---------------------------------------------------------------------------
// Globals (absolute addresses reloc-normalised by the harness).
// ---------------------------------------------------------------------------
extern DynamicVectorClass_Mix MixArray;          // GLOBAL: GAMEMD 0x884D90
#include "../_layout/global_0081c1d0.h"

// Generics pointer table (each a MixFileClass*).
extern MixFileClass* g_RA2MD;     // 0x884DF8
extern MixFileClass* g_RA2;       // 0x884DFC
extern MixFileClass* g_CACHEMD;   // 0x884E48
extern MixFileClass* g_CACHE;     // 0x884E4C
extern MixFileClass* g_LOCALMD;   // 0x884E50
extern MixFileClass* g_LOCAL;     // 0x884E54

#endif  // GG_MATCH_PLATFORM_MIX_FILE_CLASS_H
