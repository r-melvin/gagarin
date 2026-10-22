// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x67FDF0 and its 33 duplicates: a contiguous 0x80-strided
//   run of COM vector-save thunks that are byte-for-byte identical to one
//   another and to the already-matched Save_Sides at 0x6805F0 (which sits in
//   the same run, between 0x680570 and 0x680670). Offsets re-derived here:
//   the vector's Count at `[EDI+0x10]`, its Items at `[EDI+0x4]`; the COM
//   slots `[ECX+0x10]` (IStream::Write, four args), `[ECX]`
//   (IUnknown::QueryInterface, three args) and `[ECX+0x8]`
//   (IUnknown::Release, receiver only); the IID at 0x7F7C80 read back as
//   00000109-0000-0000-C000-000000000046 = IID_IPersistStream; and the IAT
//   slot 0x7E15F4 = OleSaveToStream. Every instance names the same IID and
//   the same import, so there is no per-instance constant at all: the
//   element type is erased by the IPersistStream indirection.
//
//   THE STAND-INS STAY, AND THIS IS WHY. The RTTI sweep names a class through
//   the complete object locator four bytes below a vtable, so a body can only
//   be bound when it either stores a vtable or occupies a slot in one. This
//   family does neither: there is no vptr store anywhere in the 127 bytes
//   (the header says so above, and it was re-checked against the binary), and
//   none of the 34 addresses appears in any of the 1214 locator-anchored
//   vtables in the image. The remaining route, the caller, is a dead end too:
//   all 34 are called from the single function 0x67D300, which is itself in
//   no vtable, and the vector it passes in EDX is a global whose type nothing
//   static records. The element type is erased at the call boundary by
//   QueryInterface and it is erased in the RTTI as well, so `Elem_<addr>`
//   stays -- a stand-in that admits ignorance rather than an invented type.
//
//   THE TEMPLATE, AND WHY THE ELEMENT TYPE IS THE ONLY PARAMETER. Thirty-four
//   byte-identical bodies with no per-instance relocation are not thirty-four
//   functions in retail's source. They are one class template's member,
//   emitted once per instantiation as its own COMDAT, over element types the
//   body never mentions -- the QueryInterface to IPersistStream erases them.
//   This header carries the template; the translation unit beside it carries
//   one explicit instantiation per retail address.
//
//   WHICH REFERENCE SHAPE APPLIES: NEITHER OF THE VTABLE ONES. This family
//   writes no vtable at all -- there is no vptr store anywhere in the 127
//   bytes -- so batch fifty-four's store-order test does not arise and no
//   traits parameter is needed. The single parameter is the erased element
//   type, keyed by the address of the instantiation it produces.
//
//   THE SPELLING IS A STATIC `__fastcall` MEMBER (batch forty-seven's `@@SI`
//   shape), not an instance method. Retail passes the *stream* in ECX and the
//   vector in EDX (`MOV EDI,EDX; MOV EBX,ECX`, then `MOV ECX,[EBX]` /
//   `PUSH EBX` / `CALL [ECX+0x10]` on EBX): the value in ECX is the argument
//   the COM calls are made on, not the receiver whose members are read, so
//   this is not an instance method of the vector. A `static __fastcall`
//   member takes its first explicit argument in ECX and its second in EDX,
//   which is exactly retail's shape.
//
//   KNOWN LIMITATION -- this file is a staging ground, not a destination. The
//   TU-partition work established that MSVC6 emits each template
//   instantiation as a COMDAT into the translation unit that instantiated it.
//   These 34 instantiations therefore belong to many different original
//   translation units, not to one. Grouping them in a single sweep
//   file is correct for matching bytes now and wrong for reproducing retail's
//   link order eventually; they will have to be redistributed to their owning
//   TUs when the partition is reconstructed.
#ifndef GG_MATCH_CORE_VECTOR_PERSIST_SAVE_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_PERSIST_SAVE_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Stream_0067FDF0;
struct Persist_0067FDF0;

// IStream::Write is slot +0x10 (three IUnknown slots, then Read at +0x0C);
// __stdcall with the receiver pushed.
typedef long (__stdcall* StreamWrite_0067FDF0)(Stream_0067FDF0*, const void*,
                                               unsigned long, unsigned long*);
#define PSAVE_WRITE(s, p, n) \
    ((*(StreamWrite_0067FDF0*)(*(char**)(s) + 0x10))(s, p, n, 0))

// IUnknown on the elements and on the IPersistStream they hand back. The
// element is reached as an opaque COM pointer -- its static type never enters
// the code, which is why the template parameter is erased.
typedef long (__stdcall* Query_0067FDF0)(void*, const void*, void**);
typedef long (__stdcall* Release_0067FDF0)(Persist_0067FDF0*);
#define PSAVE_QUERY(p, iid, ppv) \
    ((*(Query_0067FDF0*)(*(char**)(p) + 0x00))(p, iid, ppv))
#define PSAVE_RELEASE(p) \
    ((*(Release_0067FDF0*)(*(char**)(p) + 0x08))(p))

// GLOBAL: GAMEMD 0x7F7C80 -- IID_IPersistStream.
struct Guid_0067FDF0 { char Bytes[16]; };
extern const Guid_0067FDF0 IID_IPersistStream_007F7C80;

// OleSaveToStream, reached through the IAT slot at 0x7E15F4.
extern "C" __declspec(dllimport) long __stdcall
OleSaveToStream(Persist_0067FDF0* pPStm, Stream_0067FDF0* pStm);

// DynamicVectorClass<T*> head: vtable@0, Items@4, Capacity@8, Count@0x10.
//
// What the save does: serialise the vector's COM elements to an IStream. The
// element count goes out first through IStream::Write, then each element is
// asked for its IPersistStream, handed to OleSaveToStream and released. Any
// failing HRESULT ends the walk and is returned as-is; a complete walk returns
// S_OK. The count is re-read from its stack slot on every iteration because
// its address escaped into the Write call.
template<class T>
struct PersistVector
{
    void* Vtbl;               // +0x0000
    T**   Items;              // +0x0004
    int   Capacity;           // +0x0008
    int   IsAllocated;        // +0x000C
    int   Count;              // +0x0010
    int   CapacityIncrement;  // +0x0014

    static long __fastcall Save(Stream_0067FDF0* stream, PersistVector* vec);
};

template<class T>
long __fastcall PersistVector<T>::Save(Stream_0067FDF0* stream,
                                       PersistVector<T>* vec)
{
    int count = vec->Count;
    long hr = PSAVE_WRITE(stream, &count, 4);
    if (hr < 0)
        return hr;

    for (int i = 0; i < count; ++i) {
        Persist_0067FDF0* persist = 0;
        hr = PSAVE_QUERY(vec->Items[i], &IID_IPersistStream_007F7C80, (void**)&persist);
        if (hr < 0)
            return hr;
        hr = OleSaveToStream(persist, stream);
        if (hr < 0)
            return hr;
        hr = PSAVE_RELEASE(persist);
        if (hr < 0)
            return hr;
    }
    return 0;
}

#endif  // GG_MATCH_CORE_VECTOR_PERSIST_SAVE_FAMILY_METHODS_H
