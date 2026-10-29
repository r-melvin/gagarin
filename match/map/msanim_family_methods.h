// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Every address, member offset, vtable slot and calling convention below was
//   read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI over 0x5CD320..0x5CEDC6 and the vtable block at
//   0x7EE8E8..0x7EEA50.
//
// WHAT THIS FAMILY IS, from the binary's own runtime type information.
//
// The word four bytes below each vtable is the complete object locator; its
// +0xC is the type descriptor and the decorated name starts eight bytes into
// that. Reading the nine vtables packed between 0x7EE8E8 and 0x7EEA50 that way
// gives a single-rooted animation hierarchy used by the map-stage (campaign
// map) screen:
//
//   vtable      COL         type descriptor  name
//   0x7EE8E8    0x8065D0    0x830088         MSAnim          (the base)
//   0x7EE910    0x806620    0x8300A0         MSShapeAnim
//   0x7EE938    0x806670    (via COL)        MSFadeAnim
//   0x7EE960    0x8066C8    (via COL)        MSOverlayAnim
//   0x7EE988    0x806718    0x830100         MSBinkAnim
//   0x7EE9B0    0x806768    0x830120         MSVQAnim
//   0x7EE9D8    0x8067B8    0x830138         MSBitPrintAnim
//   0x7EEA00    0x806808    0x830158         MSPrintAnim
//   0x7EEA2C    0x806858    0x830180         MSPCXAnim
//
// The neighbouring vtables name `DynamicVectorClass<MapStage*>` (0x7EEA94) and
// `DynamicVectorClass<MSTextEntry*>` (0x7EEB34), which is what fixes "MS" as
// MapStage rather than anything to do with audio or map selection.
//
// THE BASE VTABLE, slot for slot (nine slots, 0x7EE8E8..0x7EE908 inclusive;
// 0x7EE90C is already MSShapeAnim's complete-object-locator word):
//
//   slot 0  0x5CEB60   scalar deleting destructor
//   slot 1  0x5CEAC0   SetEnabled(bool)      — not overridden by any subclass
//   slot 2  0x5CEAD0   PauseTimer()          — not overridden
//   slot 3  0x5CEB20   ResumeTimer()         — not overridden
//   slot 4  0x4C9150   Update()              — the folded `return 0` stub
//   slot 5  0x4C9150   Draw()                — same folded stub
//   slot 6  0x4C9150   GetRect()             — same folded stub
//   slot 7  0x5CEB40   vf_7()          — `XOR AL,AL; RET`
//   slot 8  0x5CEB50   Attach(void*)         — `RET 4`, an empty hook
//
// Slots 1..3 hold the same three addresses in all nine vtables, which is the
// direct evidence that they are MSAnim's own non-overridden members and that
// this translation unit owns them. Slots 4..6 of the base are all 0x4C9150,
// one `XOR EAX,EAX; RET` body the linker's identical-COMDAT folding shared out
// across the image; it is not reconstructed here.
//
// THE BASE LAYOUT (0x1C bytes), every offset from a member access:
//
//   +0x00  vptr
//   +0x04  int            0x5CE4B1 `MOV [ESI+4],EBX` with EBX zeroed
//   +0x08  int            0x5CE4B4
//   +0x0C  bool  Enabled  0x5CEAC4 `MOV [ECX+0xC],AL` (slot 1's whole body)
//   +0x10  int   StartTime  -1 means "paused"; 0x5CEAD3, 0x5CEB23
//   +0x14  clock object   `LEA ECX,[ESI+0x14]; CALL 0x6C8C40` at 0x5CEAE4
//   +0x18  int   Remaining  0x5CEADC, 0x5CEAFC
//
// The clock at +0x14 is a member object, not a pointer: retail takes its
// address with LEA and calls 0x6C8C40 (the same GetTime the game timer at
// 0xB0BD2C uses, already modelled in match/core/game_timing_methods.h).
// The three dwords at +0x10..+0x18 are one twelve-byte timer: the print
// animation's constructor builds a fresh one at 0x5CD5E9 and assigns it in
// whole, and cl's elimination of the temporary's own two stores against that
// copy is what leaves the single read of the never-written clock word out of
// the dead stack slot. Modelled here as a nested `MSTimer`, which is what
// takes that constructor from 71.9 to 90.6 percent.
#ifndef GG_MATCH_MAP_MSANIM_FAMILY_METHODS_H
#define GG_MATCH_MAP_MSANIM_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// MSVC6 has no native `wchar_t`; the CRT headers typedef it and this
// translation unit is standalone, so it declares the same typedef itself.
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

// ---------------------------------------------------------------------------
// Callees, declared only so cl emits a reloc-normalised call of the right
// shape. Addresses read from the call sites listed beside each one.
// ---------------------------------------------------------------------------

// The clock member's tick reader. FUNCTION: GAMEMD 0x6C8C40 (decl; reloc).
struct MSClockClass
{
    // The clock is one dword. Retail carries it out of an uninitialised stack
    // slot in the timer temporary at 0x5CD5EE (`MOV ECX,[ESP+0x14]` reading a
    // member the temporary's constructor never wrote), which is the same
    // three-dword timer shape seen at 0x6B7BB0.
    int Value;   // +0x00

    int GetTime();
};
GG_STATIC_ASSERT(sizeof(MSClockClass) == 4);

// The three adjacent dwords MSAnim carries at +0x10..+0x18, built as one
// temporary and struct-assigned in at 0x5CD5E9..0x5CD5FF. The constructor
// writes the stamp and the interval and leaves the clock alone, so the copy
// carries the dead slot out with it.
struct MSTimer
{
    int          StartTime;   // +0x00
    MSClockClass Clock;       // +0x04
    int          Remaining;   // +0x08

    __forceinline MSTimer() {}
    __forceinline MSTimer(int duration)
    {
        StartTime = Clock.GetTime();
        Remaining = duration;
    }

    // The time still on the clock (ordinary inline; PauseTimer's reader).
    int TimeLeft()
    {
        int left = Remaining;
        if (StartTime != -1) {
            int elapsed = Clock.GetTime() - StartTime;
            if (elapsed < left) {
                left -= elapsed;
            } else {
                left = 0;
            }
        }
        return left;
    }
};
GG_STATIC_ASSERT(sizeof(MSTimer) == 0xC);

// The heap-owning wide string, the member at +0x1C of both print
// animations. Only the two entry points this file reaches are declared: the
// out-of-line destructor at 0x7B6760 (called from 0x5CED1C and 0x5CED4C) and
// the measured length at 0x7B71B0 (called from 0x5CE30D). 0x7B71B0 is
// `MOV EAX,[ECX]; TEST EAX,EAX; JNZ; RET` falling into `wcslen`, so the length
// is unsigned and the null buffer answers zero without a branch of its own.
class Obj_007B66D0_msanim_family_methods
{
public:
    wchar_t* Buffer;  // +0x00

    // Written as a named member rather than a destructor: a member whose
    // destructor is non-trivial stops cl inlining the enclosing destructor,
    // exactly as a base's does, and the two print animations need theirs
    // inlined into their deleting thunks. Retail's call is a plain __thiscall
    // on the member's address, which this reproduces.
    void Release();                      // FUNCTION: GAMEMD 0x7B6760 (decl)
    // 0x7B7100 is `MOV EAX,[ECX]; TEST EAX,EAX; JNZ; MOV EAX,0x887734; RET` —
    // the held buffer, or one shared empty string when there is none. It takes
    // no argument and pops nothing, which is what leaves the seven arguments
    // already pushed around it on the stack at 0x5CD47A.
    const wchar_t* Peek();               // FUNCTION: GAMEMD 0x7B7100 (decl)
    unsigned int Length() const;         // FUNCTION: GAMEMD 0x7B71B0 (decl)

    // The from-pointer constructor, reached at 0x5CD367 and 0x5CE4B9. Named
    // rather than written as a constructor for the same reason Release is: a
    // member with non-trivial construction or destruction changes what cl will
    // inline around it, and retail's call is a plain __thiscall on the
    // member's address either way.
    void Construct(const wchar_t* text);  // FUNCTION: GAMEMD 0x7B6720 (decl)
    // The measured character at an index, `MOV ECX,[ECX]; ...` returning a
    // wide character in AX -- every caller in this file tests the 16-bit half
    // (`TEST AX,AX`, `CMP AX,0xA`).
    wchar_t CharAt(int index);            // FUNCTION: GAMEMD 0x7B7180 (decl)
    // 0x7B6780, the guard at 0x5CDB9D: one pushed word, a byte answer.
    bool Equals(const wchar_t* other);    // FUNCTION: GAMEMD 0x7B6780 (decl)
    // 0x7B7110, the indexed read the page update uses at 0x5CDD23: a second
    // entry point beside 0x7B7180, reached only from that one call site.
    wchar_t At(int index);                // FUNCTION: GAMEMD 0x7B7110 (decl)
    // 0x7B6720 again, this time with another string's address pushed
    // (0x5CDD48): the copy build. Declared as its own overload because the
    // argument is a string object where the other call passes a character
    // pointer; both emit the same reloc-normalised call.
    void CopyFrom(const Obj_007B66D0_msanim_family_methods* other);  // FUNCTION: GAMEMD 0x7B6720
    // 0x7B6D90, reached at 0x5CDD54 with (0, index): keep only that many
    // leading characters.
    void Slice(int start, int count);     // FUNCTION: GAMEMD 0x7B6D90 (decl)
    // 0x7B7660, reached at 0x5CDC24 with (0xC, index) — put a form feed in
    // front of the character at the index, which is how the page counter marks
    // its breaks.
    void Insert(int ch, int index);       // FUNCTION: GAMEMD 0x7B7660 (decl)
};
GG_STATIC_ASSERT(sizeof(Obj_007B66D0_msanim_family_methods) == 4
              && offsetof(Obj_007B66D0_msanim_family_methods, Buffer) == 0x00);

// The Bink playback object held by MSBinkAnim. Its destructor is an ordinary
// non-virtual one: 0x5CEC83 is `MOV ECX,EDI; CALL 0x432700` followed by the
// plain `operator delete`, which is exactly what a `delete` of a class with a
// non-virtual destructor expands to.
class MSBinkPlayer
{
public:
    ~MSBinkPlayer();                     // FUNCTION: GAMEMD 0x432700 (decl)
    bool IsDone();                       // FUNCTION: GAMEMD 0x432C50 (decl)
};

// The VQA playback object held by MSVQAnim. Retail stops it and then deletes
// it, reloading the member in between (0x5CECCE then 0x5CECD3), which is the
// ordinary shape of `p->Stop(); delete p;` on a member cl cannot prove
// unaliased across the call.
class MSVQPlayer
{
public:
    void Stop();                         // FUNCTION: GAMEMD 0x5BFF00 (decl)
    ~MSVQPlayer();                       // FUNCTION: GAMEMD 0x5C01F0 (decl)
};

// A one-slot stand-in for the polymorphic payloads MSVQAnim (+0x28) and
// MSPCXAnim (+0x24) own. Retail destroys both with `MOV EAX,[ECX]; PUSH 1;
// CALL [EAX]` — the scalar deleting destructor in slot zero reached through
// the object's own vtable. An abstract class with that one pure virtual
// reproduces the call and emits no vtable of its own, because it is never
// instantiated.
class MSDeletable
{
public:
    virtual void* DeletingDtor(unsigned int flags) = 0;  // slot 0

    // Slot 30 (`CALL [EDX+0x78]` at 0x5CEA65, 0x5CE80D and 0x5CE8F4): hand
    // back the image's current frame, filling the caller's rectangle. The
    // twenty-nine slots between are declared only to place it; none is
    // reached from this translation unit and none is defined.
    virtual void Slot01();  virtual void Slot02();  virtual void Slot03();
    virtual void Slot04();  virtual void Slot05();  virtual void Slot06();
    virtual void Slot07();  virtual void Slot08();  virtual void Slot09();
    virtual void Slot10();  virtual void Slot11();  virtual void Slot12();
    virtual void Slot13();  virtual void Slot14();  virtual void Slot15();
    virtual void Slot16();  virtual void Slot17();  virtual void Slot18();
    virtual void Slot19();  virtual void Slot20();  virtual void Slot21();
    virtual void Slot22();  virtual void Slot23();  virtual void Slot24();
    virtual void Slot25();  virtual void Slot26();  virtual void Slot27();
    virtual void Slot28();  virtual void Slot29();
    virtual void* GetFrame(struct MSRect* area, int a, int b);  // slot 30
};

// The font both print animations hold at +0x34. Two slots are reached from
// this translation unit: slot 1 measures one character (`CALL [EBP+4]` at
// 0x5CE36F and 0x5CE476) and slot 4 prints a run (`CALL [EDX+0x10]` at
// 0x5CE461); slot 32 (`CALL [EDX+0x80]` at 0x5CE42A) answers the printable
// height. The line height is a plain field at +0x08 (`MOV EAX,[ECX+8]` at
// 0x5CE417).
class MSSurface;
struct MSShapeFile;

class MSFont
{
public:
    virtual void Slot00();
    virtual int  CharWidth(wchar_t ch);          // slot 1
    virtual void Slot02();
    virtual void Slot03();
    // Slot 4, `CALL [EDX+0x10]` at 0x5CE461: six pushed words, read off the
    // push run between 0x5CE43F and 0x5CE460 — the destination surface, the
    // character, the pen position and the two mode numbers.
    virtual int  PrintRun(MSSurface* surface, wchar_t ch, int x, int y,
                          int mode, int flags);   // slot 4
    virtual void Slot05();  virtual void Slot06();  virtual void Slot07();
    virtual void Slot08();  virtual void Slot09();  virtual void Slot10();
    virtual void Slot11();  virtual void Slot12();  virtual void Slot13();
    virtual void Slot14();  virtual void Slot15();  virtual void Slot16();
    virtual void Slot17();  virtual void Slot18();  virtual void Slot19();
    virtual void Slot20();  virtual void Slot21();  virtual void Slot22();
    virtual void Slot23();  virtual void Slot24();  virtual void Slot25();
    virtual void Slot26();  virtual void Slot27();  virtual void Slot28();
    virtual void Slot29();  virtual void Slot30();  virtual void Slot31();
    virtual int  Limit();                        // slot 32

    // 0x5D30C0, reached at 0x5CD6C3 and 0x5CD82E: measure a run of text into
    // the caller's rectangle. Retail's `CALL 0x7B7100` immediately before it
    // pops nothing, so the rectangle pushed ahead of that call is still on the
    // stack and is this call's second argument.
    void Measure(const wchar_t* text, struct MSRect* out);

    // The pen's starting advance, read as a dword at 0x5CD615 and used as the
    // seed of the centring measurement.
    int  Lead;            // +0x04
    int  LineHeight;      // +0x08
    int  unknown_0C;      // +0x0C
    int  unknown_10;      // +0x10
    MSShapeFile* Glyphs;  // +0x14 the glyph shape, three frames per character

    // FUNCTION: GAMEMD 0x5D3170 -- the widest line of a text, in pixels.
    int  LineWidth(const wchar_t* text);
};
GG_STATIC_ASSERT(offsetof(MSFont, LineHeight) == 0x08);
GG_STATIC_ASSERT(offsetof(MSFont, Glyphs) == 0x14);

// The drawing surface the PCX animation holds at +0x1C. Only slot 2 is
// reached (`CALL [EDI+8]` at 0x5CEA74, 0x5CE819 and 0x5CE900): blit a frame
// into a rectangle of this surface.
class MSSurface
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Blit(struct MSRect* area, void* image, void* frame);
    // Slot 30 (`CALL [EAX+0x78]` at 0x5CE5B4 and 0x5CE75E): the surface's own
    // rectangle, filled into the caller's buffer and handed back. The same
    // displacement as the image's slot 30, but ONE pushed argument where the
    // image's animation-side overload takes three -- two different classes, one
    // slot index, read off the two call sites' push counts.
    virtual void Slot03();  virtual void Slot04();  virtual void Slot05();
    virtual void Slot06();  virtual void Slot07();  virtual void Slot08();
    virtual void Slot09();  virtual void Slot10();  virtual void Slot11();
    virtual void Slot12();  virtual void Slot13();  virtual void Slot14();
    virtual void Slot15();  virtual void Slot16();  virtual void Slot17();
    virtual void Slot18();  virtual void Slot19();  virtual void Slot20();
    virtual void Slot21();  virtual void Slot22();  virtual void Slot23();
    virtual void Slot24();  virtual void Slot25();  virtual void Slot26();
    virtual void Slot27();  virtual void Slot28();  virtual void Slot29();
    virtual struct MSRect* GetRect(struct MSRect* out);   // slot 30
    virtual void Slot31();
    // Slot 32, `CALL [EDX+0x80]` at 0x5CE42A on the caller's surface (NOT on
    // the font -- the receiver is the first parameter, reloaded from its home
    // slot two instructions earlier): the last printable line's bottom edge.
    virtual int  Limit();                                 // slot 32
};

// The caller's destination surface as the page update reaches it: the same
// slot 2 the PCX draw uses, but with five pushed words rather than three
// (0x5CDCEB..0x5CDCF3), so it is declared on its own class and the caller's
// context is cast to it.
class MSBlitSurface
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Blit(struct MSRect* area, MSSurface* source,
                      struct MSRect* from, int a, int b);
};

// GLOBAL: GAMEMD 0x887310 — the screen surface both PCX builders seat into the
// animation's +0x1C (`MOV EAX,ds:0x887310` at 0x5CE4E0 and 0x5CE680).
extern MSSurface* MSScreenSurface;

// The decoded PCX image the loader hands back. Layout-wise it is the same
// polymorphic object MSPCXAnim::Image points at; its slot 30 is declared here
// with the one-argument signature the two builders use.
class MSImageSurface
{
public:
    virtual void Slot00();  virtual void Slot01();  virtual void Slot02();
    virtual void Slot03();  virtual void Slot04();  virtual void Slot05();
    virtual void Slot06();  virtual void Slot07();  virtual void Slot08();
    virtual void Slot09();  virtual void Slot10();  virtual void Slot11();
    virtual void Slot12();  virtual void Slot13();  virtual void Slot14();
    virtual void Slot15();  virtual void Slot16();  virtual void Slot17();
    virtual void Slot18();  virtual void Slot19();  virtual void Slot20();
    virtual void Slot21();  virtual void Slot22();  virtual void Slot23();
    virtual void Slot24();  virtual void Slot25();  virtual void Slot26();
    virtual void Slot27();  virtual void Slot28();  virtual void Slot29();
    virtual struct MSRect* GetRect(struct MSRect* out);   // slot 30
};

// The heap-owning narrow string, the PCX file name's type. Written as
// named members for the same reason the wide string above is: a member with a
// real destructor changes what cl will inline around it, and retail's calls are
// plain __thiscalls on the object's address either way.
class MSStringClass
{
public:
    char* Str;   // +0x00

    void Init();                                  // FUNCTION: GAMEMD 0x7B4620
    void Destruct();                              // FUNCTION: GAMEMD 0x7B46F0
    // FUNCTION: GAMEMD 0x7B47F0 (decl; reloc) -- C-string inequality;
    // null/null is false, exactly one null is true.
    bool FUN_007B47F0(const char* text) const;
    // 0x7B5F10, reached at 0x5CE532 and 0x5CE6D2 with (0, ".", &out): the
    // index-th piece of this string once it is split on the given separators.
    void Split(int index, const char* separators, MSStringClass* out);
    // 0x7B4DA0, reached at 0x5CE545 and 0x5CE6E5: this string with the suffix
    // appended. Written with the destination as an explicit leading parameter
    // rather than as a by-value return: cl's own hidden return buffer makes the
    // result a temporary it then copies into the named local (three extra
    // instructions and four extra bytes of frame), where retail hands the
    // returned pointer straight to the file object. The two spellings push the
    // same two words in the same order.
    MSStringClass* Concat(MSStringClass* out, const char* suffix) const;
};
GG_STATIC_ASSERT(sizeof(MSStringClass) == 4);

// VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E16B0;
// VTABLE: GAMEMD 0x7E1668 — CDFileClass, the base the destructor drops to.
extern char VT_007E1668;
// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void FUN_00431B80(void* self);

// The 0x6C-byte stack file object both builders open the PCX through. Only the
// pieces these two functions touch are named; the teardown is the same inline
// five-step sequence match/ui/preview_class_pcx_methods.h records at 0x641DB0
// (0x7E16B0 at +0, +0x64 zeroed, 0x43AE50 on +0x58, 0x7E1668 at +0, 0x431B80).
struct MSFileClass
{
    char* Vtbl;                 // +0x00
    char  _pad004[0x58 - 0x04];
    char  Sub58[0x64 - 0x58];   // +0x58
    int   Reset64;              // +0x64
    char  _pad068[0x6C - 0x68];

    // FUNCTION: GAMEMD 0x473A30 (decl; reloc) — build from a name.
    MSFileClass* Construct(const MSStringClass* name);
    // FUNCTION: GAMEMD 0x473C50 (decl; reloc) — CCFileClass::Exists.
    bool Exists(int writeShared);
};
GG_STATIC_ASSERT(offsetof(MSFileClass, Sub58) == 0x58
              && offsetof(MSFileClass, Reset64) == 0x64
              && sizeof(MSFileClass) == 0x6C);

// FUNCTION: GAMEMD 0x630310 (decl; reloc) — Read_PCX_File(file, palette,
// buffer, size); the file arrives in ECX and the palette in EDX.
MSImageSurface* MSReadPCXFile(MSFileClass* file, char* palette,
                              void* buffer, long size);

// The 16-byte rectangle both GetRect overloads copy out whole.
struct MSRect
{
    int X;       // +0x00
    int Y;       // +0x04
    int Width;   // +0x08
    int Height;  // +0x0C
};
GG_STATIC_ASSERT(sizeof(MSRect) == 0x10
              && offsetof(MSRect, Y) == 0x04
              && offsetof(MSRect, Width) == 0x08
              && offsetof(MSRect, Height) == 0x0C);

// The rectangle intersection, expanded inline into the PCX draw at
// 0x5CE8C0 and into the print animation's layout at 0x5CD690. Both copies have
// the same six early exits and the same `(0,0,0,0)` local the failures hand
// back, which is what identifies it as one shared source function rather than
// two hand-written clip runs.
//
// FUNCTION: GAMEMD 0x42E410 (decl; reloc) — the four-argument constructor,
// spelled as a named member returning `this` because every other constructor
// in this file is.
struct MSRectBuild
{
    int X, Y, Width, Height;
    MSRectBuild* Build(int x, int y, int w, int h);
};
GG_STATIC_ASSERT(sizeof(MSRectBuild) == 0x10);

// FUNCTION: GAMEMD 0x421B60 (decl; reloc) — the out-of-line copy of the same
// intersection the PCX draw expands inline: the destination arrives in ECX,
// the clipping rectangle in EDX, and the rectangle being clipped plus the two
// optional origin adjustments are pushed. It hands the destination back in EAX.
MSRect* MSRectIntersectOut(MSRect* out, const MSRect* clip,
                           const MSRect* self, int* x, int* y);

__forceinline MSRect MSRectIntersect(const MSRect* self, const MSRect& other)
{
    MSRect rect;
    ((MSRectBuild*)&rect)->Build(0, 0, 0, 0);

    MSRect r = *self;

    if (other.Width <= 0 || other.Height <= 0) {
        return rect;
    }

    if (self->Width <= 0 || self->Height <= 0) {
        return rect;
    }

    if (r.X < other.X) {
        r.Width += r.X - other.X;
        r.X = other.X;
    }

    if (r.Width < 1) {
        return rect;
    }

    if (r.Y < other.Y) {
        r.Height += r.Y - other.Y;
        r.Y = other.Y;
    }

    if (r.Height < 1) {
        return rect;
    }

    if (r.X + r.Width > other.X + other.Width) {
        r.Width = other.X - r.X + other.Width;
    }

    if (r.Width < 1) {
        return rect;
    }

    if (r.Y + r.Height > other.Y + other.Height) {
        r.Height = other.Y + other.Height - r.Y;
    }

    if (r.Height < 1) {
        return rect;
    }

    return r;
}

// ---------------------------------------------------------------------------
// The hierarchy.
//
// The destructors here are NOT declared virtual and the scalar deleting
// destructors are written by hand. Retail's `??_G` bodies have the destructor
// expanded inline (the vptr seats and the member releases sit in the thunk
// itself, with no call), which is precisely what cl declines to produce from a
// compiler-generated thunk — it always calls the destructor out of line from
// one. Declaring the classes polymorphic through an unrelated virtual keeps
// the vptr seat that every destructor of a polymorphic class performs, while
// leaving the thunk to this file.
//
// Every destructor carries `throw()`: under `/GX`, the tree's flag set when
// this was written, a
// destructor that destroys a subobject otherwise acquires a full unwind frame
// retail has no trace of.
// ---------------------------------------------------------------------------

// The base-vptr seat.
//
// Retail's destructors each seat two vtable pointers: the class's own on entry
// and MSAnim's on the way out. cl will not inline a destructor whose BASE has
// a user-declared destructor -- measured in both directions, with and without
// `throw()` and with `__forceinline` on either end, it always emits an
// out-of-line call -- and it emits the base seat only when the base destructor
// IS user-declared. Those two facts cannot both be satisfied through
// inheritance.
//
// The way out is to leave MSAnim without a user destructor, so every derived
// destructor inlines and contributes its own seat, and to write the base seat
// as an explicit destructor call on a layout-compatible stand-in whose only
// member is a vptr. That expands to the one `MOV [this],<vtable>` retail has.
// The stand-in carries its own vtable symbol rather than MSAnim's, which the
// differ normalises away with every other relocation.
class MSAnimVptrSeat
{
public:
    virtual int Seat();
    __forceinline ~MSAnimVptrSeat() throw() {}
};

class MSAnim
{
public:
    // The first six slots, declared so that the two dispatches this file makes
    // through them land on the right displacement: slot 5 is reached as
    // `CALL [EDX+0x14]` at 0x5CE827, 0x5CE886 and 0x5CE95D. Slots 0..3 carry
    // placeholder names because the real bodies are the non-virtual members
    // further down -- the vtable is written by this file's VTABLE annotations,
    // not by cl. Slots 4 and 5 answer a byte and take the caller's context
    // plus an out rectangle; retail's own MSAnim entries for them are the
    // folded `return 0` at 0x4C9150, which is not reconstructed here.
    virtual void* DeletingDtorSlot(unsigned int flags);  // slot 0
    virtual void  SetEnabledSlot(bool on);               // slot 1
    virtual void  PauseTimerSlot();                      // slot 2
    virtual void  ResumeTimerSlot();                     // slot 3
    virtual bool  Update(int context, struct MSRect* out);  // slot 4
    virtual void  Draw(int context, struct MSRect* area);   // slot 5
    virtual struct MSRect GetRectSlot();                    // slot 6

    int          Field04;    // +0x04
    int          Field08;    // +0x08
    bool         Enabled;    // +0x0C
    MSTimer      Timer;      // +0x10 .. +0x18

    // The base's own field setup, expanded into every constructor in this run
    // (0x5CD338..0x5CD35C, 0x5CE4A8..0x5CE4C6, 0x5CE648..0x5CE666): take the
    // two leading numbers of the caller's rectangle, mark the animation
    // enabled, stamp the clock and start with nothing banked. Written as a
    // named forced-inline member rather than as a real constructor because
    // every constructor in this family seats its vtable pointers by hand.
    __forceinline void Init(int x, int y)
    {
        Field04 = x;
        Field08 = y;
        Enabled = true;
        Timer.StartTime = Timer.Clock.GetTime();
        Timer.Remaining = 0;
    }

    // The three non-overridden base slots, out of line in this file.
    // Seat MSAnim's vtable pointer on this object -- the tail of every
    // destructor in the family.
    __forceinline void SeatBaseVptr()
    {
        ((MSAnimVptrSeat*)this)->MSAnimVptrSeat::~MSAnimVptrSeat();
    }

    void  SetEnabled(bool on);            // 0x5CEAC0, slot 1
    void  PauseTimer();                   // 0x5CEAD0, slot 2
    void  ResumeTimer();                  // 0x5CEB20, slot 3
    bool  vf_7();                   // 0x5CEB40, slot 7
    void  Attach(void* target);           // 0x5CEB50, slot 8
    void* DeletingDtor(unsigned int f);   // 0x5CEB60, slot 0

    // The remaining time, forced inline into MSPrintAnim::Update (0x5CDC50).
    // PauseTimer uses MSTimer::TimeLeft instead.
    __forceinline int TimeLeft();
};
GG_STATIC_ASSERT(sizeof(MSAnim) == 0x1C
              && offsetof(MSAnim, Field04) == 0x04
              && offsetof(MSAnim, Field08) == 0x08
              && offsetof(MSAnim, Enabled) == 0x0C
              && offsetof(MSAnim, Timer) == 0x10);

// The list of sibling animations the PCX animation is drawn out of, held at
// its +0x20. Only slot 4 and two fields are reached: the index lookup
// (`CALL [EAX+0x10]` at 0x5CE863 and 0x5CE94A), the element array at +0x04 and
// the live count at +0x10, reloaded on every turn of both loops.
class MSAnimVector
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual int  IndexOf(MSAnim* const& item);   // slot 4

    MSAnim** Vector;       // +0x04
    int      Capacity;    // +0x08
    bool     IsValid;      // +0x0C
    bool     IsAllocated;  // +0x0D
    int      Count;  // +0x10
};
GG_STATIC_ASSERT(offsetof(MSAnimVector, Vector) == 0x04
              && offsetof(MSAnimVector, Count) == 0x10);

// MSShapeAnim owns a decoded shape buffer at +0x1C and a "we allocated it"
// flag at +0x3C; 0x5CEB83 loads the pointer, 0x5CEB90 tests the flag, and the
// release nulls both. The 0x20..0x3B gap is the shape's own bookkeeping, which
// no function in this file reads.
// The decoded shape file MSShapeAnim owns at +0x1C: a short header carrying
// the frame size and count, read at +2/+4/+6 by the animation's members.
struct MSShapeFile
{
    short Unknown0;   // +0x00
    short Width;      // +0x02
    short Height;     // +0x04
    short Frames;     // +0x06

    // FUNCTION: GAMEMD 0x69E7E0 (decl; reloc) -- the rectangle of one frame,
    // written to the caller's buffer and handed back.
    struct MSRect* GetFrameRect(struct MSRect* out, unsigned int frame);
};
GG_STATIC_ASSERT(offsetof(MSShapeFile, Width) == 2 && offsetof(MSShapeFile, Frames) == 6);

// FUNCTION: GAMEMD 0x4A3970 (decl; reloc) -- load a shape by name; the
// ownership flag arrives in EDX and is cleared before the lookup.
MSShapeFile* __fastcall MSLoadShape(const char* name, bool* owned);

class MSShapeAnim : public MSAnim
{
public:
    MSShapeFile* Buffer;     // +0x1C
    int   Field20;           // +0x20
    int   Field24;           // +0x24
    unsigned int Frame;      // +0x28 current frame
    int   Field2C;           // +0x2C
    int   LastFrame;         // +0x30 frame count minus one
    bool  Field34;           // +0x34
    char  unknown_35[3];
    unsigned int Flags;      // +0x38 (bit 9: centre on the frame)
    bool  OwnsBuffer;        // +0x3C

    // The shape animation's release: hand the decoded buffer back only when
    // this object owns it, then forget both the pointer and the flag.
    __forceinline ~MSShapeAnim() throw()
    {
        if (Buffer != 0 && OwnsBuffer) {
            ::operator delete(Buffer);
            Buffer = 0;
            OwnsBuffer = false;
        }

        SeatBaseVptr();
    }

    void* DeletingDtor(unsigned int f);   // 0x5CEB80

    // 0x5CB790 -- jump to a frame, redrawing the area it covers.
    void SetFrame(unsigned int frame);
    // 0x5CBCB0, slot 6 -- the current frame's rectangle on the screen.
    MSRect GetRectSlot();
};
GG_STATIC_ASSERT(offsetof(MSShapeAnim, Frame) == 0x28
              && offsetof(MSShapeAnim, LastFrame) == 0x30
              && offsetof(MSShapeAnim, Flags) == 0x38);
GG_STATIC_ASSERT(sizeof(MSShapeAnim) == 0x40
              && offsetof(MSShapeAnim, Buffer) == 0x1C
              && offsetof(MSShapeAnim, OwnsBuffer) == 0x3C);

// Native RTTI: Fade derives Shape and Overlay derives Fade at offset zero.
// Constructor/factory evidence proves Fade's two DWORD fields and size0x48,
// then Overlay's byte at0x48 and allocation size0x4C. Resource cleanup is
// inherited once from Shape; these added storage fields have no cleanup.
class MSFadeAnim : public MSShapeAnim
{
public:
    unsigned int unknown_40;
    unsigned int unknown_44;

    ~MSFadeAnim() throw() {}
    void* DeletingDtor(unsigned int f);   // 0x5CEBD0
};
GG_STATIC_ASSERT(sizeof(MSFadeAnim) == 0x48
              && offsetof(MSFadeAnim, unknown_40) == 0x40
              && offsetof(MSFadeAnim, unknown_44) == 0x44);

class MSOverlayAnim : public MSFadeAnim
{
public:
    unsigned char unknown_48;
    unsigned char unknown_49[3];

    ~MSOverlayAnim() throw() {}
    void* DeletingDtor(unsigned int f);   // 0x5CEC20
};
GG_STATIC_ASSERT(sizeof(MSOverlayAnim) == 0x4C
              && offsetof(MSOverlayAnim, unknown_48) == 0x48);

// MSBinkAnim owns one Bink player at +0x1C and plainly deletes it.
class MSBinkAnim : public MSAnim
{
public:
    MSBinkPlayer* Player;    // +0x1C

    // The player's destructor is not virtual, so the delete expands to the
    // destructor call followed by the plain free.
    __forceinline ~MSBinkAnim() throw() { delete Player; SeatBaseVptr(); }

    void* DeletingDtor(unsigned int f);   // 0x5CEC70
};
GG_STATIC_ASSERT(offsetof(MSBinkAnim, Player) == 0x1C);

// MSVQAnim owns two things and releases the later one first: the polymorphic
// movie at +0x28 goes through its own slot-zero deleting destructor, then the
// VQA player at +0x1C is stopped and deleted.
class MSVQAnim : public MSAnim
{
public:
    MSVQPlayer*  Player;        // +0x1C
    char         unknown_20[8]; // +0x20
    MSDeletable* Movie;         // +0x28
    char         unknown_2C[1]; // +0x2C
    bool         Finished;      // +0x2D — slot 7's whole body is
                                //          `MOV AL,[ECX+0x2D]; RET` at 0x5CD320

    // Retail's own order: the movie first, through its own slot-zero deleting
    // destructor, then the player, which is stopped before it is freed. The
    // member reload between the two is cl's, not the source's -- it cannot
    // prove Stop left the member alone.
    __forceinline ~MSVQAnim() throw()
    {
        if (Movie != 0) {
            Movie->DeletingDtor(1);
        }

        if (Player != 0) {
            Player->Stop();
            delete Player;
        }

        SeatBaseVptr();
    }

    bool  vf_7();                   // 0x5CD320, slot 7
    void* DeletingDtor(unsigned int f);   // 0x5CECB0
};
GG_STATIC_ASSERT(offsetof(MSVQAnim, Player) == 0x1C
              && offsetof(MSVQAnim, Movie) == 0x28
              && offsetof(MSVQAnim, Finished) == 0x2D);

// MSBitPrintAnim holds a wide string at +0x1C whose destructor retail calls
// out of line (0x5CED1C), so the member's destructor is declared and not
// defined here.
//
//   +0x1C  Obj_007B66D0_msanim_family_methods Text     constructed at 0x5CD367, released at
//                                   0x5CD3AC and 0x5CED1C
//   +0x20  MSRect Bounds            the caller's rectangle copied in whole at
//                                   0x5CD36C..0x5CD390, and copied back out by
//                                   slot 6 at 0x5CD3D0
//   +0x30  bool Started             cleared by the constructor at 0x5CD383,
//                                   read by slot 7 at 0x5CD400, written by the
//                                   setter at 0x5CD3C0
//   +0x31  bool Centred             the constructor's third argument
//   +0x34  the font, `MOV EAX,[ESI+0x34]` at 0x5CDC..; a polymorphic object
//          whose slot 1 measures a character and whose slot 4 prints a run
// The seat for MSBitPrintAnim's own vtable, the same layout-compatible
// stand-in trick the family's destructors use for the base seat. The
// constructor below needs both seats placed by hand, so neither comes from
// cl's automatic ones.
class MSBitPrintAnimVptrSeat
{
public:
    virtual int Seat();
    __forceinline ~MSBitPrintAnimVptrSeat() throw() {}
};

class MSBitPrintAnim : public MSAnim
{
public:
    Obj_007B66D0_msanim_family_methods Text;     // +0x1C
    MSRect          Bounds;   // +0x20
    bool            Started;  // +0x30
    bool            Centred;  // +0x31

    // The constructor at 0x5CD330. The base takes the rectangle's two leading
    // numbers, the text is built from the caller's pointer, and the whole
    // rectangle is copied in afterwards.
    // 0x5CD330. Written as a named builder rather than as a constructor: a
    // real constructor makes cl place both vtable seats itself, and it places
    // them two slots ahead of retail's (measured at 34.3 and 37.1 percent
    // across four structural spellings -- member, member-initialiser, a
    // non-polymorphic second base holding the string, and a reordered body --
    // all four of which emitted byte-identical code). Seating by hand through
    // the stand-ins puts each store where retail has it. The function returns
    // the receiver, which is what retail's `MOV EAX,ESI` before the epilogue
    // is.
    MSBitPrintAnim* Construct(const wchar_t* text, const MSRect* rect,
                              bool centred);

    // Seat MSBitPrintAnim's own vtable pointer.
    __forceinline void SeatOwnVptr()
    {
        ((MSBitPrintAnimVptrSeat*)this)
            ->MSBitPrintAnimVptrSeat::~MSBitPrintAnimVptrSeat();
    }

    __forceinline ~MSBitPrintAnim() throw() { Text.Release(); SeatBaseVptr(); }

    // 0x5CD410, slot 4, and 0x5CD4D0, slot 5. Both hand the animation's
    // rectangle back through an out pointer rather than by value: retail
    // writes the sixteen bytes through the SECOND stack argument and still
    // answers a byte in EAX, so neither is a hidden return buffer.
    bool Update(int context, MSRect* out);
    void Draw(int context, MSRect* area);

    MSRect GetRect();                     // 0x5CD3D0, slot 6
    bool  vf_7();                   // 0x5CD400, slot 7
    void  SetStarted(bool on);            // 0x5CD3C0
    void* DeletingDtor(unsigned int f);   // 0x5CED10
};
GG_STATIC_ASSERT(offsetof(MSBitPrintAnim, Text) == 0x1C
              && offsetof(MSBitPrintAnim, Bounds) == 0x20
              && offsetof(MSBitPrintAnim, Started) == 0x30
              && offsetof(MSBitPrintAnim, Centred) == 0x31);

// MSPrintAnim is the one class in this run whose gameplay members are visible
// from the three small slots reconstructed here.
//
//   +0x1C  Obj_007B66D0_msanim_family_methods Text     destroyed out of line at 0x5CED4C
//   +0x24  unsigned CharPos         `CMP [ESI+0x24],EAX; JBE` at 0x5CE312 —
//                                   unsigned against the string length
//   +0x28  unsigned LineCount       `CMP [ESI+0x28],2; JBE` at 0x5CE317
//   +0x38  MSRect Bounds            `ADD ECX,0x38` then the 16-byte copy out
//                                   at 0x5CE2B4
//   +0x48  bool Active              `MOV DL,[ECX+0x48]` at 0x5CE2E4
// The seat for MSPrintAnim's own vtable, the same stand-in the rest of the
// family uses. Its constructor at 0x5CD570 places both seats by hand.
class MSPrintAnimVptrSeat
{
public:
    virtual int Seat();
    __forceinline ~MSPrintAnimVptrSeat() throw() {}
};

class MSPrintAnim : public MSAnim
{
public:
    Obj_007B66D0_msanim_family_methods Text;        // +0x1C
    // The character count the layout walks (`CMP EDI,EAX` / `JB` at 0x5CE484
    // against this member, and `TEST EAX,EAX` / `JBE` at 0x5CE3FC): unsigned.
    unsigned int    Field20;     // +0x20
    unsigned int    CharPos;     // +0x24
    unsigned int    LineCount;   // +0x28
    int             Interval;    // +0x2C — the constructor's seventh argument
    bool            Field30;     // +0x30 — its eighth
    char            unknown_31[3];
    MSFont*         Font;        // +0x34
    MSRect          Bounds;      // +0x38
    bool            Active;      // +0x48
    bool            Centred;     // +0x49 — the constructor's ninth argument
    char            unknown_4A[2];
    int             CentreOffset;  // +0x4C

    __forceinline ~MSPrintAnim() throw() { Text.Release(); SeatBaseVptr(); }

    // Seat MSPrintAnim's own vtable pointer.
    __forceinline void SeatOwnVptr()
    {
        ((MSPrintAnimVptrSeat*)this)
            ->MSPrintAnimVptrSeat::~MSPrintAnimVptrSeat();
    }

    // 0x5CD570 — build a printed page.
    MSPrintAnim* Construct(const wchar_t* text, int x, int y, MSFont* font,
                           const MSRect* rect, int duration, int margin,
                           bool a8, bool centred);
    // 0x5CD690 — lay the page out inside the caller's rectangle.
    void Layout(const MSRect* area);
    // 0x5CE3A0 — draw the page, one character at a time.
    void DrawLines(MSSurface* surface, MSRect* clip);
    // 0x5CDC50, slot 4 — step the page on by one character.
    bool Update(int context, MSRect* out);
    // 0x5CDEE0, slot 5 — redraw everything printed so far.
    void Draw(int context, MSRect* clip);

    // 0x5CE330 — the measured width of one line of the given text, stopping
    // at the terminator or the first newline.
    int   MeasureWidth(Obj_007B66D0_msanim_family_methods* text);

    MSRect GetRect();                     // 0x5CE2B0, slot 6
    void  SetActive(bool on);             // 0x5CE2E0
    // Retail materialises a full dword on both exits (`MOV EAX,1` /
    // `XOR EAX,EAX`), where a `bool` return gives the one-byte form. This one
    // override answers an int even though the slot's other implementations
    // answer a byte.
    int   vf_7();                   // 0x5CE300, slot 7
    void* DeletingDtor(unsigned int f);   // 0x5CED40
};
GG_STATIC_ASSERT(offsetof(MSPrintAnim, Interval) == 0x2C
              && offsetof(MSPrintAnim, Field30) == 0x30
              && offsetof(MSPrintAnim, Centred) == 0x49
              && offsetof(MSPrintAnim, CentreOffset) == 0x4C
              && offsetof(MSPrintAnim, Font) == 0x34
              && offsetof(MSPrintAnim, Text) == 0x1C
              && offsetof(MSPrintAnim, CharPos) == 0x24
              && offsetof(MSPrintAnim, LineCount) == 0x28
              && offsetof(MSPrintAnim, Bounds) == 0x38
              && offsetof(MSPrintAnim, Active) == 0x48);

// MSPCXAnim owns a polymorphic PCX image at +0x24, carries a finished flag at
// +0x29 (slot 7's whole body is `MOV AL,[ECX+0x29]; RET`) and its own bounds
// at +0x2C (`ADD ECX,0x2C` at 0x5CEA84). Its destructor exists twice in the
// image: out of line at 0x5CE7B0 and expanded again inside the deleting thunk
// at 0x5CED70.
// The seat for MSPCXAnim's own vtable, the same layout-compatible stand-in the
// family's destructors use for the base seat. Both PCX builders place both
// seats by hand for the reason recorded on MSBitPrintAnim::Construct.
class MSPCXAnimVptrSeat
{
public:
    virtual int Seat();
    __forceinline ~MSPCXAnimVptrSeat() throw() {}
};

// The two leading numbers of the caller's placement, read as a pair at
// 0x5CE74A/0x5CE74E. Modelled as its own two-int struct rather than as an
// MSRect because the builder reads exactly two of the four.
struct MSPoint
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(MSPoint) == 8 && offsetof(MSPoint, Y) == 4);

class MSPCXAnim : public MSAnim
{
public:
    MSSurface*    Surface;  // +0x1C
    MSAnimVector* Owner;    // +0x20
    MSDeletable* Image;     // +0x24
    bool         Field28;   // +0x28
    bool         Finished;  // +0x29
    char         unknown_2A[2];
    MSRect       Bounds;    // +0x2C

    __forceinline ~MSPCXAnim() throw()
    {
        if (Image != 0) {
            Image->DeletingDtor(1);
        }

        SeatBaseVptr();
    }

    // Seat MSPCXAnim's own vtable pointer.
    __forceinline void SeatOwnVptr()
    {
        ((MSPCXAnimVptrSeat*)this)->MSPCXAnimVptrSeat::~MSPCXAnimVptrSeat();
    }

    // The base's field setup as both PCX builders expand it. It is NOT
    // MSAnim::Init: the two leading numbers are zero rather than the caller's,
    // and the enabled flag starts CLEAR and is raised again at the end of the
    // derived build-up (`MOV BYTE PTR [ESI+0xC],BL` at 0x5CE4B7 then
    // `MOV BYTE PTR [ESI+0xC],1` at 0x5CE50B).
    __forceinline void Inline_005CE4A0()
    {
        Field04 = 0;
        Field08 = 0;
        Enabled = false;
        Timer.StartTime = Timer.Clock.GetTime();
        Timer.Remaining = 0;
    }

    // 0x5CE4A0 — build a PCX animation that centres itself on the screen.
    MSPCXAnim* ConstructCentred(MSStringClass* name, MSAnimVector* owner,
                                bool flag);
    // 0x5CE640 — the same, placed at the caller's point instead.
    MSPCXAnim* ConstructAt(MSStringClass* name, MSAnimVector* owner,
                           const MSPoint* where, bool flag);

    bool  Update(int context, MSRect* out);  // 0x5CE7D0, slot 4
    void  Draw(int context, MSRect* area);   // 0x5CE8C0, slot 5
    MSRect GetRect();                     // 0x5CEA80, slot 6
    bool  vf_7();                   // 0x5CEAB0, slot 7
    void  Attach(void* target);           // 0x5CEA40, slot 8
    void* DeletingDtor(unsigned int f);   // 0x5CED70
};
GG_STATIC_ASSERT(offsetof(MSPCXAnim, Surface) == 0x1C
              && offsetof(MSPCXAnim, Owner) == 0x20
              && offsetof(MSPCXAnim, Image) == 0x24
              && offsetof(MSPCXAnim, Field28) == 0x28
              && offsetof(MSPCXAnim, Finished) == 0x29
              && offsetof(MSPCXAnim, Bounds) == 0x2C);

// The two map-stage printing globals, both tested for presence before any
// text goes out (0x5CD410, 0x5CD4D0). The surface takes a clipping rectangle
// directly; the engine takes the surface, the caller's context, the text and
// the rectangle in four separate numbers.

// GLOBAL: GAMEMD 0x89C4D0
class MSPrintSurface
{
public:
    int  SetClip(MSRect* area);          // FUNCTION: GAMEMD 0x433CA0 (decl)
};
extern MSPrintSurface* MSSurfaceGlobal;

// GLOBAL: GAMEMD 0x89C4B8
class MSTextEngine
{
public:
    // FUNCTION: GAMEMD 0x434CD0 (decl). Ten stack arguments plus the receiver;
    // retail cleans 0x28 on return, which is how the count is pinned.
    int Print(MSPrintSurface* surface, int context, const wchar_t* text,
              int x, int y, int width, int height, int centred, int a, int b);
};
extern MSTextEngine* MSEngineGlobal;

// GLOBAL: GAMEMD 0xABFBB0 — four adjacent dwords the map-stage screen clears
// together at 0x5CEDB0. Modelled as one struct so the four stores keep their
// retail order and the offsets carry a real assert; the addressing emits the
// base relocation with the displacement inside the relocation slot, which the
// differ normalises.
struct MSAnimCounters
{
    int Field00;  // 0xABFBB0
    int Field04;  // 0xABFBB4
    int Field08;  // 0xABFBB8
    int Field0C;  // 0xABFBBC
    MSAnimCounters() : Field00(0), Field04(0), Field08(0), Field0C(0) {}
};
GG_STATIC_ASSERT(sizeof(MSAnimCounters) == 0x10
              && offsetof(MSAnimCounters, Field0C) == 0x0C);
extern MSAnimCounters MSAnimCounts;

// FUNCTION: GAMEMD 0x5CE7B0 — the out-of-line ~MSPCXAnim.
void MSPCXAnim_Destroy(MSPCXAnim* self);

// FUNCTION: GAMEMD 0x5CD3A0 — the out-of-line ~MSBitPrintAnim.
void MSBitPrintAnim_Destroy(MSBitPrintAnim* self);

#endif  // GG_MATCH_MAP_MSANIM_FAMILY_METHODS_H
