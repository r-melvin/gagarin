// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at the
//   addresses below). Names cross-checked against YRpp MixFileClass.h
//   (consult-only, no LICENSE; every offset/slot reconfirmed here).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5301A0  MixFileClass::Bootstrap  (static, returns bool/AL)
//   FUNCTION: GAMEMD 0x5B40B0  MixFileClass::Retrieve   (static __fastcall:
//                                                        ECX=name, DL=forceCache)
//
// Match (period MSVC6 cl 12.00.ours vs retail, reloc-normalised):
//   0x5301A0 Bootstrap  98.2%  (residual: 4 instrs — the ScanFile vtable load
//            uses a stack reload vs retail's ctor-return EAX reuse, and the
//            `mov al,1` success tail is scheduled after the pops not before;
//            both are register-scheduling deltas, phrasing/flag-invariant.)
//   0x5B40B0 Retrieve   89.6% (mnemonic multiset identical; residual is a pure
//            ESI/EDI naming swap: retail keeps the CRC in EDI and the fresh
//            node in ESI, cl 8804 the other way round, 15 instructions.)

#include "mix_file_class.h"
#include <stdio.h>   // sprintf
#include <string.h>  // strcpy, _strlwr, strstr

// ---- external retail callees (declared; the harness reloc-normalises calls) --
struct CRCEngine
{
    int a, b, c;
    int Compute(const char* buf, int len);   // FUN_004A1DE0 __thiscall
};

// Cached-file index node (operator new(0x10)): left/right/key(crc)/value.
// Key @+0x8, Value @+0xC confirmed from the walk: `node[2]==crc && node[3]!=0`
// (CMP [EAX+0x8] / [EDX+... ]) and key<crc => node[1] (right @+0x4) else *node
// (left @+0x0).
struct IdxNode { IdxNode* Left; IdxNode* Right; int Key; void* Value; };
GG_STATIC_ASSERT(offsetof(IdxNode, Key)   == 0x08);
GG_STATIC_ASSERT(offsetof(IdxNode, Value) == 0x0C);
GG_STATIC_ASSERT(sizeof(IdxNode) == 0x10);   // operator new(0x10)
extern IdxNode* g_FileCacheRoot;             // GLOBAL: GAMEMD 0x00ABF00C
void __fastcall IdxInsert(IdxNode* node, IdxNode** parentSlot);  // FUN_005B3FF0

// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new (__cdecl; caller pops).
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// FUNCTION: GAMEMD 0x4A3890 (decl; reloc) — CCFileClass::ReadWholeFile.
void* __fastcall MakeCachedFile(CCFile_005B40B0* f);
// The 0x24-byte object built on a forced / .SHP miss; its constructor is a
// __thiscall taking the name (`PUSH EBP; MOV ECX,EAX; CALL 0x69E430`).
struct Mix_0069E430
{
    // FUNCTION: GAMEMD 0x69E430 (decl; reloc) — constructor from a name.
    void* FUN_0069E430(char* name);
};

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5301A0   MixFileClass::Bootstrap
//
// Mount EXPANDMD99.MIX .. EXPANDMD00.MIX (any that exist) into the global Array,
// then the fixed set RA2MD / RA2 / CACHEMD / CACHE / LOCALMD / LOCAL, caching
// the CACHE* archives. Restores the file-search mode on success.
//
// PARTIAL (96.5%, 219/227; multiset differs by one MOV against one LEA), up
// from 89.4%. Two independent levers moved it:
//
//   * The scratch name buffer is `char name[64]`, not `char name[32]`, and the
//     stack probe is 0x24 bytes (`ScanFile::_body[0x20]`). Retail's frame is
//     `SUB ESP,0x68`; with the four callee-saved pushes live it addresses the
//     probe as `[ESP+0x14]` and the buffer as `[ESP+0x38]`, i.e. in-frame +0x04
//     and +0x28. That makes the probe 0x24 bytes and the buffer +0x28..+0x68,
//     exactly 0x40 — the declared sizes are recoverable arithmetic, not a
//     guess. Getting the total right fixed the frame instruction and all six
//     `ADD ESP,0x68` epilogues at once: 32 bytes scores 89.4%, 48 bytes 93.0%,
//     64 bytes 96.5% and 68 bytes 93.0%.
//   * The append is spelled as the free `DynamicVectorClass_Mix_AddItem(&v, x)`
//     rather than `v.AddItem(x)`, which is worth the inlined grow path's
//     `ADD ECX,EAX; PUSH ECX` against cl's `ADD EAX,ECX; PUSH EAX`.
//
// The eight residual instructions are two spots. Retail reuses the ScanFile
// constructor's returned `this` as the Is_Available receiver
// (`MOV EDX,[EAX]; MOV ECX,EAX`) where cl re-takes the object's address
// (`LEA ECX,[ESP+0x18]`); calling `probe.Is_Available(0)` without the FileBase
// cast drops an instruction and scores 11.9%, and modelling the constructor as
// a `this`-returning `Init` over a raw buffer adds one and scores 13.6%. And
// the success epilogue materialises `MOV AL,0x1` before the four pops where cl
// puts it between `POP EBP` and `POP EBX`; naming the result in a local ahead
// of the two trailing calls leaves it unchanged.
// ---------------------------------------------------------------------------
bool MixFileClass_Bootstrap()
{
    int saved = g_FileSearchMode;
    SetFileSearchMode(-2);

    for (int i = 99; i >= 0; --i)
    {
        char name[64];
        sprintf(name, "EXPANDMD%02d.MIX", i);

        ScanFile probe(name);
        char avail = ((FileBase*)&probe)->Is_Available(0);
        probe.Close();
        if (avail)
        {
            MixFileClass* mix = new MixFileClass(name);
            if (mix)
            {
                DynamicVectorClass_Mix_AddItem(&MixArray, mix);
                Log_4a4ac0(" %s", name);
            }
        }
    }

    // Nested success-chain: every failure falls through to the single shared
    // `return false` epilogue (matches retail's converged 0x5302E4 exit).
    g_RA2MD = new MixFileClass("RA2MD.MIX");
    if (g_RA2MD)
    {
        g_RA2 = new MixFileClass("RA2.MIX");
        if (g_RA2)
        {
            Log_4a4ac0(" CACHE.MIX");
            g_CACHEMD = new MixFileClass("CACHEMD.MIX");
            if (g_CACHEMD && MixCache("CACHEMD.MIX", 0))
            {
                Log_4a4ac0(" CACHE.MIX");
                g_CACHE = new MixFileClass("CACHE.MIX");
                if (g_CACHE && MixCache("CACHE.MIX", 0))
                {
                    Log_4a4ac0(" CACHE.MIX");
                    g_LOCALMD = new MixFileClass("LOCALMD.MIX");
                    if (g_LOCALMD)
                    {
                        g_LOCAL = new MixFileClass("LOCAL.MIX");
                        if (g_LOCAL)
                        {
                            Log_4a4ac0(" LOCAL.MIX");
                            SetFileSearchMode(saved);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5B40B0   MixFileClass::Retrieve  (__fastcall static)
//
// Look a file up by lower-cased name in the CRC-keyed file cache. On a hit,
// return the cached pointer. On a miss, probe the file; if present, insert a
// cache node and build the appropriate file object; otherwise return 0.
//
// Shape notes (each one lifted the score): the walk is a search loop with a
// found-body — the node is parked in `found` and re-tested after the loop
// (`CMP EAX,EBX; JZ miss`), a `return` inside the loop folds that test away;
// the probe is a 0x6C-byte stack CCFileClass torn down explicitly on both
// exits (this class's vtable, +0x64 reset, +0x58 sub-object release, base
// vtable, base destructor — a real destructor adds an EH frame under /GX);
// the insert slot is the root pointer itself bumped in place
// (`p = &p->Right`), which loads the root straight into EDX and gives
// `ADD EDX,4` — a separate slot local or a `?:` costs a `MOV EDX,EAX`; the
// 0x24-byte object's constructor is a __thiscall taking the name.
//
// PARTIAL (89.6%, 129/144; multiset identical). Retail keeps the CRC in EDI
// and the fresh node in ESI (the value then reuses EDI); cl 8804 names them
// the other way round. Use-weight levers tried without effect: the node
// declared ahead of the CRC, the two zero links chained, `value` zero-
// initialised, the walk and the insert each moved into a static inline
// helper (parameter copy), `const int crc`, the ctor-null arm as if/else, and
// a second `int key = crc;` copy taken at the insert so the walk and the
// insert read different names (no change). Filed as the ESI/EDI tie-break
// class (cf. 0x74E930).
// ---------------------------------------------------------------------------
void* __fastcall MixFileClass_Retrieve(char* name, bool force)
{
    char buf[0x101];                 // lowercase name scratch
    strcpy(buf, name);               // intrinsic: repne scasb + rep movs
    _strlwr(buf);

    CRCEngine eng;
    eng.a = 0; eng.b = 0; eng.c = 0;
    int crc = eng.Compute(buf, strlen(buf));

    IdxNode* found = 0;
    IdxNode* node  = g_FileCacheRoot;
    while (node)
    {
        if (node->Key == crc && node->Value != 0)
        {
            found = node;
            break;
        }
        if (node->Key < crc) node = node->Right;
        else                 node = node->Left;
    }
    if (found)
        return found->Value;

    // ---- cache miss: probe the file on a stack CCFileClass ----
    CCFile_005B40B0 file;
    file.FUN_004739F0(name);
    if (!file.FUN_00473C50(0))
    {
        file.Vtbl    = &VT_007E16B0;
        file.Reset64 = 0;
        FUN_0043AE50(file.Sub58);
        file.Vtbl    = &VT_007E1668;
        FUN_00431B80(&file);
        return 0;
    }

    IdxNode* fresh = (IdxNode*)FUN_007C8E17(0x10);
    fresh->Key = crc;
    IdxNode* p = g_FileCacheRoot;
    if (p == 0)
    {
        g_FileCacheRoot = fresh;
        fresh->Left = 0;
        fresh->Right = 0;
    }
    else
    {
        if (p->Key < crc)
            p = (IdxNode*)&p->Right;
        IdxInsert(fresh, (IdxNode**)p);
    }

    void* value;
    if (!force && strstr(buf, ".SHP") == 0)
        value = MakeCachedFile(&file);
    else
    {
        Mix_0069E430* mem = (Mix_0069E430*)FUN_007C8E17(0x24);
        value = mem ? mem->FUN_0069E430(name) : 0;
    }
    fresh->Value = value;

    file.Vtbl    = &VT_007E16B0;
    file.Reset64 = 0;
    FUN_0043AE50(file.Sub58);
    file.Vtbl    = &VT_007E1668;
    FUN_00431B80(&file);
    return value;
}
