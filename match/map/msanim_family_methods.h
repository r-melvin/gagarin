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
//   0x7EE8E8    0x8065D0    0x830088         MSAnim              (the base)
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
// the dead stack slot. Modelled here as a nested `MSTimerView`, which is what
// takes that constructor from 71.9 to 90.6 percent.
#ifndef GG_MATCH_MAP_MSANIM_FAMILY_METHODS_H
#define GG_MATCH_MAP_MSANIM_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/ms_anim.h"
#include "../core/string_class.h"

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

// The three adjacent dwords MSAnim carries at +0x10..+0x18, built as one
// temporary and struct-assigned in at 0x5CD5E9..0x5CD5FF. The constructor
// writes the stamp and the interval and leaves the clock alone, so the copy
// carries the dead slot out with it.
struct MSTimerView
{
    int          StartTime;   // +0x00
    MSClockClass Clock;       // +0x04
    int          Remaining;   // +0x08

    inline MSTimerView() {}
    inline MSTimerView(int duration)
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
GG_STATIC_ASSERT(sizeof(MSTimerView) == 0xC);

// The heap-owning wide string, the member at +0x1C of both print
// animations. Only the two entry points this file reaches are declared: the
// out-of-line destructor at 0x7B6760 (called from 0x5CED1C and 0x5CED4C) and
// the measured length at 0x7B71B0 (called from 0x5CE30D). 0x7B71B0 is
// `MOV EAX,[ECX]; TEST EAX,EAX; JNZ; RET` falling into `wcslen`, so the length
// is unsigned and the null buffer answers zero without a branch of its own.
class Obj_007B66D0;

class Obj_007B66D0_msanim_family_methods
{
public:
    wchar_t* Buffer;  // +0x00

    Obj_007B66D0_msanim_family_methods() {}
    // The from-pointer constructor, reached at 0x5CE4B9.
    // FUNCTION: GAMEMD 0x7B6720 (decl; reloc)
    Obj_007B66D0_msanim_family_methods(const wchar_t* text);
    // The same entry with the caller's string object pushed (the bit-print constructor's copy at 0x5CD367).
    // FUNCTION: GAMEMD 0x7B6720 (decl; reloc)
    Obj_007B66D0_msanim_family_methods(const Obj_007B66D0& other);

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
    MSBinkPlayer(const char* file, int flags);  // FUNCTION: GAMEMD 0x4326C0 (decl)
    ~MSBinkPlayer();                     // FUNCTION: GAMEMD 0x432700 (decl)
    void Move(int x, int y);             // FUNCTION: GAMEMD 0x432AB0 (decl)
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

    char            unknown_00[0x24];
    RectangleStruct Dest;                // +0x24 where the movie is drawn on the caller's surface
    RectangleStruct Source;              // +0x34 the matching area of the screen surface
};
GG_STATIC_ASSERT(offsetof(MSVQPlayer, Dest) == 0x24 && offsetof(MSVQPlayer, Source) == 0x34);

class MSSurface;
// FUNCTION: GAMEMD 0x5BFAA0 (decl; reloc) -- open the movie `name` on a surface; two clip rectangles by value,
// a volume and a flag follow.
MSVQPlayer* __fastcall FUN_005BFAA0(const char* name, MSSurface* surface,
                                    RectangleStruct a, RectangleStruct b, int volume, int flag);

// GLOBAL: GAMEMD 0xA8EB98 -- the movie volume scale.
extern float DAT_00A8EB98;

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
    virtual void* GetFrame(RectangleStruct* area, int a, int b);  // slot 30
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
    void Measure(const wchar_t* text, RectangleStruct* out);

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
    virtual void Blit(RectangleStruct* area, void* image, void* frame);
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
    virtual RectangleStruct* GetRect(RectangleStruct* out);   // slot 30
    virtual int  Slot31();                                // slot 31: the surface width (0x7C)
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
    virtual void Blit(RectangleStruct* area, MSSurface* source,
                      RectangleStruct* from, int a, int b);
    // Slots 3..30 are declared only to place the two queries the VQA animation's constructor makes
    // on the 0x88730C surface.
    virtual void Slot03();  virtual void Slot04();  virtual void Slot05();
    virtual void Slot06();  virtual void Slot07();  virtual void Slot08();
    virtual void Slot09();  virtual void Slot10();  virtual void Slot11();
    virtual void Slot12();  virtual void Slot13();  virtual void Slot14();
    virtual void Slot15();  virtual void Slot16();  virtual void Slot17();
    virtual void Slot18();  virtual void Slot19();  virtual void Slot20();
    virtual void Slot21();  virtual void Slot22();  virtual void Slot23();
    virtual void Slot24();  virtual void Slot25();  virtual void Slot26();
    virtual void Slot27();  virtual void Slot28();  virtual void Slot29();
    virtual void Slot30();
    virtual int  Slot31();                                // the surface width
    virtual int  Slot32();                                // the surface height
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
    virtual RectangleStruct* GetRect(RectangleStruct* out);   // slot 30
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
    const char* FUN_007B5440() const;             // FUNCTION: GAMEMD 0x7B5440 (decl; reloc)
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
RectangleStruct* MSRectIntersectOut(RectangleStruct* out, const RectangleStruct* clip,
                           const RectangleStruct* self, int* x, int* y);

inline RectangleStruct MSRectIntersect(const RectangleStruct* self, const RectangleStruct& other)
{
    RectangleStruct rect;
    ((MSRectBuild*)&rect)->Build(0, 0, 0, 0);

    RectangleStruct r = *self;

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
// The hierarchy: the print, picture and movie animations, real classes on MSAnim (match/_layout/ms_anim.h).
// Their vtables are 0x7EE988 (MSBinkAnim), 0x7EE9B0 (MSVQAnim), 0x7EE9D8 (MSBitPrintAnim), 0x7EEA00
// (MSPrintAnim) and 0x7EEA2C (MSPCXAnim); the constructors, destructors and scalar deleting destructors are
// the compiler's. ~MSAnim is expanded inline into every destructor here, as retail's are (retail compiles
// the whole run 0x5CB6C0..0x5CEDC6 as one unit), so the definition below is only an inline copy for these
// translation units; ms_anim_ctors.cpp carries the out-of-line body at 0x5CB6C0.
// ---------------------------------------------------------------------------

inline MSAnim::~MSAnim()
{
}

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

// A rectangle member that starts as the zero rectangle or as a copy of the caller's, built in the
// constructor's member-initialiser run.
struct MSBounds : public RectangleStruct
{
    MSBounds()
    {
        X = 0;
        Y = 0;
        Width = 0;
        Height = 0;
    }
    MSBounds(const RectangleStruct& rect) : RectangleStruct(rect) {}
    void operator=(const RectangleStruct& rect)
    {
        RectangleStruct::operator=(rect);
    }
};

// MSBinkAnim owns one Bink player at +0x1C and plainly deletes it.
// VTABLE: GAMEMD 0x7EE988
class MSBinkAnim : public MSAnim
{
public:
    // FUNCTION: GAMEMD 0x5CC760
    // Remember the caller's numbers and box; when the file name is not empty, open it as a Bink player and
    // move it to the box's corner.
    MSBinkAnim(Wstring* name, int flags, int field34, const RectangleStruct* rect, bool field38);

    // The player's destructor is not virtual, so the delete expands to the
    // destructor call followed by the plain free.
    virtual ~MSBinkAnim();                                 // slot 0, 0x5CEC70 (out of line 0x5CC820)
    virtual bool   Update(MouseSurfaceView* context, RectangleStruct* out);       // slot 4, 0x5CC8A0
    virtual void   Draw(MouseSurfaceView* context, RectangleStruct* area);        // slot 5, 0x5CC970
    virtual RectangleStruct GetRect();                              // slot 6, 0x5CC850
    virtual bool   vf_7();                                 // slot 7, 0x5CC880
    virtual void   Attach(void* target);                   // slot 8, 0x5CCA10

    MSBinkPlayer* Player;    // +0x1C
    int           Field20;   // +0x20 the player's flags
    RectangleStruct        Bounds;    // +0x24
    int           Field34;   // +0x34
    bool          Field38;   // +0x38
};
GG_STATIC_ASSERT(offsetof(MSBinkAnim, Player) == 0x1C
              && offsetof(MSBinkAnim, Bounds) == 0x24
              && offsetof(MSBinkAnim, Field34) == 0x34
              && offsetof(MSBinkAnim, Field38) == 0x38);

// MSVQAnim owns two things and releases the later one first: the polymorphic
// movie at +0x28 goes through its own slot-zero deleting destructor, then the
// VQA player at +0x1C is stopped and deleted.
// VTABLE: GAMEMD 0x7EE9B0
class MSVQAnim : public MSAnim
{
public:
    // Retail's own order: the movie first, through its own slot-zero deleting
    // destructor, then the player, which is stopped before it is freed. The
    // member reload between the two is cl's, not the source's -- it cannot
    // prove Stop left the member alone.
    // FUNCTION: GAMEMD 0x5CCC30
    MSVQAnim(MSStringClass* name, MSSurface* surface, int field24, bool field2c);
    virtual ~MSVQAnim();                                   // slot 0, 0x5CECB0 (out of line 0x5CCE40)
    virtual bool   Update(MouseSurfaceView* context, RectangleStruct* out);       // slot 4, 0x5CCE90
    virtual void   Draw(MouseSurfaceView* context, RectangleStruct* area);        // slot 5, 0x5CD0E0
    virtual RectangleStruct GetRect();                              // slot 6, 0x5CD290
    virtual bool   vf_7();                                 // slot 7, 0x5CD320
    virtual void   Attach(void* target);                   // slot 8, 0x5CD240

    MSVQPlayer*  Player;        // +0x1C
    MSSurface*   Surface;       // +0x20
    int          Field24;       // +0x24
    MSDeletable* Movie;         // +0x28
    bool         Field2C;       // +0x2C
    bool         Finished;      // +0x2D -- slot 7's whole body is
                                //          `MOV AL,[ECX+0x2D]; RET` at 0x5CD320
};
GG_STATIC_ASSERT(offsetof(MSVQAnim, Player) == 0x1C
              && offsetof(MSVQAnim, Surface) == 0x20
              && offsetof(MSVQAnim, Field24) == 0x24
              && offsetof(MSVQAnim, Movie) == 0x28
              && offsetof(MSVQAnim, Field2C) == 0x2C
              && offsetof(MSVQAnim, Finished) == 0x2D);

// MSBitPrintAnim holds a wide string at +0x1C whose destructor retail calls
// out of line (0x5CED1C), so the member's destructor is declared and not
// defined here.
//
//   +0x1C  Obj_007B66D0_msanim_family_methods Text     constructed at 0x5CD367, released at
//                                   0x5CD3AC and 0x5CED1C
//   +0x20  RectangleStruct Bounds            the caller's rectangle copied in whole at
//                                   0x5CD36C..0x5CD390, and copied back out by
//                                   slot 6 at 0x5CD3D0
//   +0x30  bool Started             cleared by the constructor at 0x5CD383,
//                                   read by slot 7 at 0x5CD400, written by the
//                                   setter at 0x5CD3C0
//   +0x31  bool Centred             the constructor's third argument
//   +0x34  the font, `MOV EAX,[ESI+0x34]` at 0x5CDC..; a polymorphic object
//          whose slot 1 measures a character and whose slot 4 prints a run
// VTABLE: GAMEMD 0x7EE9D8
class MSBitPrintAnim : public MSAnim
{
public:
    Obj_007B66D0_msanim_family_methods Text;     // +0x1C
    RectangleStruct          Bounds;   // +0x20
    bool            Started;  // +0x30
    bool            Centred;  // +0x31

    // FUNCTION: GAMEMD 0x5CD330
    // The base takes the rectangle's two leading numbers, the text is copied from the caller's string, and the
    // whole rectangle is copied in afterwards.
    MSBitPrintAnim(const Obj_007B66D0& text, const RectangleStruct* rect, bool centred);

    virtual ~MSBitPrintAnim();                              // slot 0, 0x5CED10 (out of line 0x5CD3A0)

    // 0x5CD410, slot 4, and 0x5CD4D0, slot 5. Both hand the animation's
    // rectangle back through an out pointer rather than by value: retail
    // writes the sixteen bytes through the SECOND stack argument and still
    // answers a byte in EAX, so neither is a hidden return buffer.
    virtual bool   Update(MouseSurfaceView* context, RectangleStruct* out);       // slot 4, 0x5CD410
    virtual void   Draw(MouseSurfaceView* context, RectangleStruct* area);        // slot 5, 0x5CD4D0
    virtual RectangleStruct GetRect();                              // slot 6, 0x5CD3D0
    virtual bool   vf_7();                                 // slot 7, 0x5CD400

    void  SetStarted(bool on);            // 0x5CD3C0
};
GG_STATIC_ASSERT(offsetof(MSBitPrintAnim, Text) == 0x1C
              && offsetof(MSBitPrintAnim, Bounds) == 0x20
              && offsetof(MSBitPrintAnim, Started) == 0x30
              && offsetof(MSBitPrintAnim, Centred) == 0x31);

// MSPrintAnim is the one class in this run whose gameplay members are visible
// from the three small slots reconstructed here.
//
//   +0x1C  Obj_007B66D0_msanim_family_methods Text     destroyed out of line at 0x5CED4C
//   +0x24  unsigned CharPos         `CMP [ESI+0x24],EAX; JBE` at 0x5CE312 --
//                                   unsigned against the string length
//   +0x28  unsigned LineCount       `CMP [ESI+0x28],2; JBE` at 0x5CE317
//   +0x38  RectangleStruct Bounds            `ADD ECX,0x38` then the 16-byte copy out
//                                   at 0x5CE2B4
//   +0x48  bool Active              `MOV DL,[ECX+0x48]` at 0x5CE2E4
// VTABLE: GAMEMD 0x7EEA00
class MSPrintAnim : public MSAnim
{
public:
    Obj_007B66D0_msanim_family_methods Text;        // +0x1C
    // The character count the layout walks (`CMP EDI,EAX` / `JB` at 0x5CE484
    // against this member, and `TEST EAX,EAX` / `JBE` at 0x5CE3FC): unsigned.
    unsigned int    Field20;     // +0x20
    unsigned int    CharPos;     // +0x24
    unsigned int    LineCount;   // +0x28
    int             Interval;    // +0x2C -- the constructor's seventh argument
    bool            Field30;     // +0x30 -- its eighth
    char            unknown_31[3];
    MSFont*         Font;        // +0x34
    RectangleStruct          Bounds;      // +0x38
    bool            Active;      // +0x48
    bool            Centred;     // +0x49 -- the constructor's ninth argument
    char            unknown_4A[2];
    int             CentreOffset;  // +0x4C

    // FUNCTION: GAMEMD 0x5CD570 -- build a printed page.
    MSPrintAnim(const wchar_t* text, int x, int y, MSFont* font, const RectangleStruct* rect, int duration, int margin,
                bool a8, bool centred);

    virtual ~MSPrintAnim() { Text.Release(); }             // slot 0, 0x5CED40 (out of line: none)

    virtual bool   Update(MouseSurfaceView* context, RectangleStruct* out);       // slot 4, 0x5CDC50 -- step the page on one character
    virtual void   Draw(MouseSurfaceView* context, RectangleStruct* clip);        // slot 5, 0x5CDEE0 -- redraw everything printed so far
    virtual RectangleStruct GetRect();                              // slot 6, 0x5CE2B0
    virtual bool   vf_7();                                 // slot 7, 0x5CE300

    // 0x5CD690 -- lay the page out inside the caller's rectangle.
    void Layout(const RectangleStruct* area);
    // 0x5CE3A0 -- draw the page, one character at a time.
    void DrawLines(MSSurface* surface, RectangleStruct* clip);
    // 0x5CE330 -- the measured width of one line of the given text, stopping
    // at the terminator or the first newline.
    int   MeasureWidth(Obj_007B66D0_msanim_family_methods* text);

    void  SetActive(bool on);             // 0x5CE2E0
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

// The two leading numbers of the caller's placement, read as a pair at
// 0x5CE74A/0x5CE74E. Modelled as its own two-int struct rather than as an
// RectangleStruct because the builder reads exactly two of the four.
struct MSPoint
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(MSPoint) == 8 && offsetof(MSPoint, Y) == 4);

// MSPCXAnim owns a polymorphic PCX image at +0x24, carries a finished flag at
// +0x29 (slot 7's whole body is `MOV AL,[ECX+0x29]; RET`) and its own bounds
// at +0x2C (`ADD ECX,0x2C` at 0x5CEA84). Its destructor exists twice in the
// image: out of line at 0x5CE7B0 and expanded again inside the deleting thunk
// at 0x5CED70.
// VTABLE: GAMEMD 0x7EEA2C
class MSPCXAnim : public MSAnim
{
public:
    MSSurface*    Surface;  // +0x1C
    MSAnimVector* Owner;    // +0x20
    MSDeletable* Image;     // +0x24
    bool         Field28;   // +0x28
    bool         Finished;  // +0x29
    char         unknown_2A[2];
    MSBounds     Bounds;    // +0x2C

    // FUNCTION: GAMEMD 0x5CE4A0 -- build a PCX animation that centres itself on the screen.
    MSPCXAnim(MSStringClass* name, MSAnimVector* owner, bool flag);
    // FUNCTION: GAMEMD 0x5CE640 -- the same, placed at the caller's point instead.
    MSPCXAnim(MSStringClass* name, MSAnimVector* owner, const MSPoint* where, bool flag);

    virtual ~MSPCXAnim();                                  // slot 0, 0x5CED70 (out of line 0x5CE7B0)

    virtual bool   Update(MouseSurfaceView* context, RectangleStruct* out);       // slot 4, 0x5CE7D0
    virtual void   Draw(MouseSurfaceView* context, RectangleStruct* area);        // slot 5, 0x5CE8C0
    virtual RectangleStruct GetRect();                              // slot 6, 0x5CEA80
    virtual bool   vf_7();                                 // slot 7, 0x5CEAB0
    virtual void   Attach(void* target);                   // slot 8, 0x5CEA40
};
GG_STATIC_ASSERT(offsetof(MSPCXAnim, Surface) == 0x1C
              && offsetof(MSPCXAnim, Owner) == 0x20
              && offsetof(MSPCXAnim, Image) == 0x24
              && offsetof(MSPCXAnim, Field28) == 0x28
              && offsetof(MSPCXAnim, Finished) == 0x29
              && offsetof(MSPCXAnim, Bounds) == 0x2C);

// 0x89C4B8 is the BitText receiver and 0x89C4D0 is its BitFont.
#include "../ui/bit_font_print_methods.h"

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

#endif  // GG_MATCH_MAP_MSANIM_FAMILY_METHODS_H
