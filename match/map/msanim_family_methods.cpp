// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes compared against the user's retail gamemd.exe v1.001 across
//   0x5CD320..0x5CEDC6. The class identities come from the image's own runtime
//   type information (see the header). Six of the entry points
//   below carry no name in the analysis database and were
//   found by sweeping the range as raw bytes for the 0x90 alignment pads that
//   separate functions; those are scored with scripts/vc6/raw_match.py, which
//   does not need the analysis to know the address.
//
// Percentages in the attempt notes below are historical; current partial
// scores are recorded in scripts/data/match_manifest.json.
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5CD320  MSVQAnim::IsFinished
//   FUNCTION: GAMEMD 0x5CD330  MSBitPrintAnim::Construct
//   FUNCTION: GAMEMD 0x5CD3A0  MSBitPrintAnim::~MSBitPrintAnim (out of line)
//   FUNCTION: GAMEMD 0x5CD3C0  MSBitPrintAnim::SetStarted
//   FUNCTION: GAMEMD 0x5CD3D0  MSBitPrintAnim::GetRect
//   FUNCTION: GAMEMD 0x5CD400  MSBitPrintAnim::IsFinished
//   FUNCTION: GAMEMD 0x5CD410  MSBitPrintAnim::Update
//   FUNCTION: GAMEMD 0x5CD4D0  MSBitPrintAnim::Draw
//   FUNCTION: GAMEMD 0x5CD570  MSPrintAnim::Construct      (PARTIAL; see manifest)
//   FUNCTION: GAMEMD 0x5CD690  MSPrintAnim::Layout
//   FUNCTION: GAMEMD 0x5CDB90  MSCountPages                (PARTIAL, 94.7%)
//   FUNCTION: GAMEMD 0x5CDC50  MSPrintAnim::Update         (PARTIAL, 99.1%)
//   FUNCTION: GAMEMD 0x5CDEE0  MSPrintAnim::Draw
//   FUNCTION: GAMEMD 0x5CE2B0  MSPrintAnim::GetRect
//   FUNCTION: GAMEMD 0x5CE2E0  MSPrintAnim::SetActive
//   FUNCTION: GAMEMD 0x5CE300  MSPrintAnim::IsFinished
//   FUNCTION: GAMEMD 0x5CE330  MSPrintAnim::MeasureWidth
//   FUNCTION: GAMEMD 0x5CE3A0  MSPrintAnim::DrawLines
//   FUNCTION: GAMEMD 0x5CE4A0  MSPCXAnim::ConstructCentred
//   FUNCTION: GAMEMD 0x5CE640  MSPCXAnim::ConstructAt
//   FUNCTION: GAMEMD 0x5CE7B0  MSPCXAnim::~MSPCXAnim (out of line)
//   FUNCTION: GAMEMD 0x5CE7D0  MSPCXAnim::Update
//   FUNCTION: GAMEMD 0x5CE8C0  MSPCXAnim::Draw             (PARTIAL, 35.1%)
//   FUNCTION: GAMEMD 0x5CEA40  MSPCXAnim::Attach
//   FUNCTION: GAMEMD 0x5CEA80  MSPCXAnim::GetRect
//   FUNCTION: GAMEMD 0x5CEAB0  MSPCXAnim::IsFinished
//   FUNCTION: GAMEMD 0x5CEAC0  MSAnim::SetEnabled
//   FUNCTION: GAMEMD 0x5CEAD0  MSAnim::PauseTimer
//   FUNCTION: GAMEMD 0x5CEB20  MSAnim::ResumeTimer
//   FUNCTION: GAMEMD 0x5CEB40  MSAnim::IsFinished
//   FUNCTION: GAMEMD 0x5CEB50  MSAnim::Attach
//   FUNCTION: GAMEMD 0x5CEB60  MSAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CEB80  MSShapeAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CEBD0  MSFadeAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CEC20  MSOverlayAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CEC70  MSBinkAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CECB0  MSVQAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CED10  MSBitPrintAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CED40  MSPrintAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CED70  MSPCXAnim::DeletingDtor
//   FUNCTION: GAMEMD 0x5CEDB0  MSAnimResetCounters
//   VTABLE:   GAMEMD 0x7EE8E8  MSAnim        (9 slots)
//   VTABLE:   GAMEMD 0x7EE910  MSShapeAnim
//   VTABLE:   GAMEMD 0x7EE938  MSFadeAnim
//   VTABLE:   GAMEMD 0x7EE960  MSOverlayAnim
//   VTABLE:   GAMEMD 0x7EE988  MSBinkAnim
//   VTABLE:   GAMEMD 0x7EE9B0  MSVQAnim
//   VTABLE:   GAMEMD 0x7EE9D8  MSBitPrintAnim
//   VTABLE:   GAMEMD 0x7EEA00  MSPrintAnim
//   VTABLE:   GAMEMD 0x7EEA2C  MSPCXAnim
//   GLOBAL:   GAMEMD 0xABFBB0  the four map-stage counters
//   GLOBAL:   GAMEMD 0x887310  the screen surface
//   VTABLE:   GAMEMD 0x7E16B0  CCFileClass  (the stack file object)
//   VTABLE:   GAMEMD 0x7E1668  CDFileClass  (its base)
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete (CRT; excluded from the match)
//
// ENTRY-POINT CORRECTIONS the raw sweep's implied lengths get wrong. A pool
// address's length is an upper bound on the first body there, never its length:
//   0x5CDEE0 is 0x1E0, not 0x3C4. The body ends at 0x5CE0BD and an unrelated
//     class's function begins at 0x5CE0C0 (it reads members at +0x50, +0x54 and
//     +0x5C that no class in this file has) and runs to 0x5CE2A4.
//   0x5CD850 is 0x335 exactly, one body.
//
// PARTIAL — 0x5CD570 MSPrintAnim::Construct, 93.8%. Retail's centring block
// starts the running width at zero and subtracts the font lead at the end
// (0x5CD611..0x5CD66F: the lead and the accumulator sit in the dead a8 and
// centred argument slots); the margin argument only seeds Interval. The earlier
// source seeded the width with the lead and subtracted the margin, which was
// wrong as well as worse (45.8%). The remaining delta is the two timer stores,
// which retail places above the string constructor's argument setup; that is
// accepted rather than forced with a receiver alias.
//
// HISTORICAL ATTEMPTS — 0x5CD570 MSPrintAnim::Construct, old oracle
// reported 90.6% (87/96 instructions,
// multiset identical). Two residuals. cl keeps the address of the clock member
// in a callee-saved register across the whole body and writes the re-stamped
// clock through it, where retail addresses the member directly; and retail
// spills a second dead zero into the ninth argument's home slot beside the
// centring accumulator, which shifts every stack displacement in the centring
// block by four. Measured: the timer written as three field copies out of a
// named temporary (49.0 -- the copy blocks cl's elimination of the temporary's
// own stores), as a read of the temporary's never-written clock word (71.9),
// and as the whole-struct assignment `Timer = MSTimer(duration)` that this file
// now uses (90.6); the clock store spelled through the member's `Value` rather
// than the struct, and a named local for the interval, each changed nothing.
//
// BODY-EXACT — 0x5CDB90 MSCountPages and 0x5CDC50 MSPrintAnim::Update. Both
// were register-assignment residuals: the three locals of each loop take their
// registers in declaration order, and the first indexed read pushes whichever
// is zero. MSCountPages declares i, pages, used; Update's measuring block
// declares lead, j, width.
//
// PARTIAL — 0x5CE8C0 MSPCXAnim::Draw, 35.1%. The intersection expands inline
// here (the out-of-line 0x421B60 the other two callers use is not called), so
// its result is a named-return-value cl keeps in registers: retail stores only
// the X and Y of it and leaves the width and height in EAX and ECX, then passes
// the same sixteen-byte slot to the image's frame query. Reproducing the
// two-store form needs the result in a local whose address never escapes, which
// forces a third rectangle into the frame (0x3C against retail's 0x2C) because
// cl will not merge that local with the one whose address is taken -- the same
// merge it performs happily in ConstructCentred four functions later. Measured:
// one rectangle used for both (12.2, four stores and the four return blocks
// merged), the result scoped and a second rectangle after it (32.8), the same
// with the frame rectangle in its own block (35.1), the zero rectangle hoisted
// to the caller (24.4), an out-pointer form writing X and Y per return path
// (9.2), and four-int locals in place of the rectangle copy (5.3). /Op, /Ob1
// and /Ox leave it at 35.1. The residual is one register-allocation choice --
// retail names the caller's rectangle EDI and the copy's height EBX, cl the
// reverse, which costs one `MOV` and shifts every later displacement -- plus
// the unmerged sixteen bytes.
//
// MSBitPrintAnim construction uses direct timer stores. Redundant receiver
// aliases used only to force scheduling have been removed.

#include "msanim_family_methods.h"
#include "../_layout/memory_buffer.h"

MSAnimCounters MSAnimCounts;
MSPrintSurface* MSSurfaceGlobal;
MSTextEngine*   MSEngineGlobal;
MSSurface*      MSScreenSurface;
char VT_007E16B0;
char VT_007E1668;

// FUNCTION: GAMEMD 0x5CD320
// Slot 7 for the VQA animation: a cached flag, the same one-byte load the PCX
// animation's slot 7 performs out of its own member.
bool MSVQAnim::IsFinished()
{
    return Finished;
}

// FUNCTION: GAMEMD 0x5CD330
// Build a bit-printed line: the base takes the rectangle's two leading
// numbers, the text is built from the caller's pointer, and then the whole
// rectangle is copied in. Retail schedules the derived vtable seat into the
// middle of that copy, which is cl's own placement of the seat every derived
// constructor performs after its base returns.
MSBitPrintAnim* MSBitPrintAnim::Construct(const wchar_t* text,
                                          const MSRect* rect, bool centred)
{
    int x = rect->X;
    int y = rect->Y;

    Field04 = x;
    Field08 = y;
    Enabled = true;
    Timer.StartTime = Timer.Clock.GetTime();
    Timer.Remaining = 0;
    SeatBaseVptr();
    Text.Construct(text);
    Bounds = *rect;
    Started = false;
    SeatOwnVptr();
    Centred = centred;
    return this;
}

// FUNCTION: GAMEMD 0x5CD3A0
// The out-of-line copy of the destructor. Both vtable seats survive here
// because the string release between them can observe the first, which is the
// same reason the inlined copy at 0x5CED10 keeps only one.
void __fastcall MSBitPrintAnim_Destroy(MSBitPrintAnim* self)
{
    self->MSBitPrintAnim::~MSBitPrintAnim();
}

// FUNCTION: GAMEMD 0x5CD3C0
// Mark the line started. Unlike MSPrintAnim::SetActive this one stores
// unconditionally — retail has no compare here.
void MSBitPrintAnim::SetStarted(bool on)
{
    Started = on;
}

// FUNCTION: GAMEMD 0x5CD3D0
// Slot 6: the 16-byte copy out of the rectangle at +0x20.
MSRect MSBitPrintAnim::GetRect()
{
    return Bounds;
}

// FUNCTION: GAMEMD 0x5CD400
// Slot 7: the started flag doubles as the finished one for a bit-printed line.
bool MSBitPrintAnim::IsFinished()
{
    return Started;
}

// FUNCTION: GAMEMD 0x5CD410
// Slot 4 for a bit-printed line: clip the surface to the line's own box, send
// the text through the engine, and hand the box back to the caller. The
// clipping rectangle is the box in corner form -- left, top, right, bottom --
// which is why the two trailing numbers are one short of the far edge.
bool MSBitPrintAnim::Update(int context, MSRect* out)
{
    if (MSEngineGlobal != 0 && MSSurfaceGlobal != 0) {
        MSRect clip;

        clip.X = Bounds.X;
        clip.Y = Bounds.Y;
        clip.Width = Bounds.X + Bounds.Width - 1;
        clip.Height = Bounds.Y + Bounds.Height - 1;
        MSSurfaceGlobal->SetClip(&clip);

        // The flag is converted in its own statement, not inside the
        // argument list: as an argument expression cl interleaves the
        // conversion with the pushes and rotates the whole block's registers
        // (44.6 and 61.4 percent on the two bodies that make this call); as a
        // named local the three member loads group ahead of the pushes exactly
        // as retail has them, and both bodies land on 100.
        int centred = Centred != 0;

        MSEngineGlobal->Print(MSSurfaceGlobal, context, Text.Peek(),
                              Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height,
                              centred, 0, 0);
    }

    *out = Bounds;
    return !Started;
}

// FUNCTION: GAMEMD 0x5CD4D0
// Slot 5 for a bit-printed line: the same send as slot 4, but clipped to the
// rectangle the caller names rather than always to the line's own box. A null
// rectangle means the line's own, which is the whole of retail's one-armed
// `JNE` over the `LEA`.
void MSBitPrintAnim::Draw(int context, MSRect* area)
{
    if (MSEngineGlobal != 0 && MSSurfaceGlobal != 0) {
        MSRect* box = area;

        if (box == 0) {
            box = &Bounds;
        }

        MSRect clip;

        clip.X = box->X;
        clip.Y = box->Y;
        clip.Width = box->X + box->Width - 1;
        clip.Height = box->Y + box->Height - 1;
        MSSurfaceGlobal->SetClip(&clip);

        int centred = Centred != 0;

        MSEngineGlobal->Print(MSSurfaceGlobal, context, Text.Peek(),
                              Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height,
                              centred, 0, 0);
    }
}

// FUNCTION: GAMEMD 0x5CD570
// Complete retail span: 0x115 bytes, including RET immediate at 0x5CD682.
// Build a printed page. The base takes the caller's two leading numbers and
// the text is built from the caller's pointer, exactly as the bit-printed
// line's constructor does; then the page's own members are seated, the timer
// is re-stamped from a temporary carrying its interval, and the page is laid
// out inside the caller's rectangle. A centred page finally measures its first
// line and banks half the slack as its pen offset.
MSPrintAnim* MSPrintAnim::Construct(const wchar_t* text, int x, int y,
                                    MSFont* font, const MSRect* rect,
                                    int duration, int margin, bool a8,
                                    bool centred)
{
    Init(x, y);
    SeatBaseVptr();
    Text.Construct(text);

    int interval = duration;

    Interval = margin;
    Field30 = a8;
    Field20 = 0;
    CharPos = interval;
    LineCount = 0;
    Font = font;
    Active = false;
    Centred = centred;
    CentreOffset = 0;
    SeatOwnVptr();

    // The timer temporary: retail builds a twelve-byte  and
    // struct-assigns it in, and cl kills the temporary's own stamp and interval
    // stores against the copy that immediately reads them back. What survives
    // is one read of the clock word the temporary never wrote, carried out of
    // the dead stack slot -- the same shape recorded at 0x6B7BB0. Written here
    // as that surviving read so the frame and the three stores come out as
    // retail has them.
    Timer = MSTimer(interval);

    Layout(rect);

    if (centred) {
        int lead = Font->Lead;
        int i = 0;
        int width = 0;

        while (Text.CharAt(i) != 0) {
            if (Text.CharAt(i) == 10) {
                break;
            }

            width += Font->CharWidth(Text.CharAt(i));
            ++i;
        }

        CentreOffset = (Bounds.Width - width - lead) / 2;
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CD690
// Lay the page out inside the caller's rectangle: measure the text, centre the
// pen horizontally in the slack and vertically in whatever the line height does
// not divide, move the measured box to the pen, and clip the box to the
// caller's rectangle. A caller's rectangle with no width or no height skips all
// of that and simply parks the box at the pen.
void MSPrintAnim::Layout(const MSRect* area)
{
    if (area->Width > 0 && area->Height > 0) {
        Font->Measure(Text.Peek(), &Bounds);

        Field04 += (area->Width - Bounds.Width) / 2;

        // Retail divides once and multiplies back rather than taking the
        // remainder the division already left in EDX: an IDIV against a held
        // register, then IMUL by that same register and a subtraction, at
        // 0x5CD6EB..0x5CD6FA. A modulo on the same two operands divides
        // straight out of memory and emits neither the multiply nor the
        // subtraction.
        int lineHeight = Font->LineHeight;
        int lines = area->Height / lineHeight;

        Field08 += (area->Height - lines * lineHeight) / 2;
        Bounds.X += Field04;
        Bounds.Y += Field08;

        Bounds = MSRectIntersect(&Bounds, *area);

        Field04 += Font->Lead / 2;
    } else {
        Font->Measure(Text.Peek(), &Bounds);

        Bounds.X = Field04;
        Bounds.Y = Field08;
    }
}

// FUNCTION: GAMEMD 0x5CDB90
// Count the page breaks one run of text needs at a given font and height, and
// put a form feed in front of each one. The inner walk is a rotated
// `while (ch && ch != newline)`: the terminator test is peeled to the top, the
// newline test heads the body, and the terminator test closes it.
int __fastcall MSCountPages(WideStringClass* text, MSFont* font, int limit)
{
    if (!text->Equals(0)) {
        if (font != 0) {
            if (limit >= font->LineHeight) {
                int i = 0;
                int pages = 0;
                int used = 0;

                while (text->CharAt(i) != 0) {
                    while (text->CharAt(i) != 0 && text->CharAt(i) != 10) {
                        ++i;
                    }

                    if (text->CharAt(i) != 10) {
                        used += font->LineHeight;

                        if (used >= limit) {
                            used = 0;
                            ++pages;
                            text->Insert(0xC, i);
                        }

                        ++i;
                    }
                }

                return pages;
            }
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x5CDC50
// Slot 4 for a printed page: step it on by one character. Nothing happens
// until the interval has run out; then the timer is re-stamped, the page's
// background is restored when it owns one, and the pen walks from the line
// start up to the current character position, laying each one out and printing
// it. A centred line measures itself once, on the first character of the line,
// and banks half its slack as the pen offset. Running off the bottom of the
// box advances the line start past the next newline and stops the walk.
bool MSPrintAnim::Update(int context, MSRect* out)
{
    out->X = 0;
    out->Y = 0;
    out->Width = 0;
    out->Height = 0;

    if (TimeLeft() != 0) {
        return false;
    }

    if (Enabled != true) {
        return false;
    }

    Timer = MSTimer(Interval);

    if (CharPos > Text.Length()) {
        if (LineCount > 2) {
            return !Active;
        }
    }

    if (Field30 == true) {
        ((MSBlitSurface*)context)->Blit(&Bounds, MSScreenSurface, &Bounds,
                                        0, 1);
    }

    int penX = Field04;
    bool centred = Centred;
    int penY = Field08;
    unsigned int i = Field20;

    while (i <= CharPos) {
        wchar_t ch = Text.At(i);

        if (ch == 0) {
            ++LineCount;
            break;
        }

        if (centred) {
            WideStringClass line;

            line.CopyFrom(&Text);
            line.Slice(0, i);

            // The lead is read before the two counters are zeroed. Declared
            // the other way round the whole block loses a point: the two
            // counters are both zero when the first indexed read is made, so
            // cl pushes whichever of them it zeroed first, and only one of the
            // three orders puts retail's register there.
            int lead = Font->Lead;
            int j = 0;
            int width = 0;

            while (line.CharAt(j) != 0) {
                if (line.CharAt(j) == 10) {
                    break;
                }

                width += Font->CharWidth(line.CharAt(j));
                ++j;
            }

            CentreOffset = (Bounds.Width - width - lead) / 2;
            penX += CentreOffset;
            centred = false;
            line.Release();
        }

        if (ch == 10) {
            penX = Field04;
            centred = Centred;

            int lineHeight = Font->LineHeight;

            penY += lineHeight;

            if (lineHeight - Field08 + penY > Bounds.Height) {
                unsigned int k = Field20;

                while (Text.CharAt(k) != 0 && Text.CharAt(k) != 10) {
                    ++k;
                }

                if (Text.CharAt(k) == 10) {
                    ++k;
                }

                Field20 = k;
                break;
            }
        } else {
            unsigned int mode;

            if (Field30) {
                mode = CharPos - i;

                if (mode >= 2) {
                    mode = 2;
                }
            } else {
                mode = 2;
            }

            Font->PrintRun((MSSurface*)context, ch, penX, penY, mode, 1);
            penX += Font->CharWidth(ch);
        }

        ++i;
    }

    *out = Bounds;
    ++CharPos;
    return false;
}

// FUNCTION: GAMEMD 0x5CDEE0
// Slot 5 for a printed page: redraw every character revealed so far. A named
// clipping rectangle is intersected against the page's box first, exactly as
// slot 6's helper does; the walk then stops at whichever of the reveal
// position and the text length comes first, and each centred line measures
// itself once before its first character goes out.
//
// The sweep's implied length for this entry (0x3C4) runs past its end: the
// body finishes at 0x5CE0BD and a separate function of another class begins at
// 0x5CE0C0, so the real length is 0x1E0.
void MSPrintAnim::Draw(int context, MSRect* clip)
{
    if (clip != 0) {
        MSRect out;
        MSRect shown = *MSRectIntersectOut(&out, clip, &Bounds, 0, 0);

        if (shown.Width <= 0 || shown.Height <= 0) {
            return;
        }
    }

    int penX = Field04;
    bool centred = Centred;
    int penY = Field08;
    unsigned int limit;

    if (CharPos < Text.Length()) {
        limit = CharPos;
    } else {
        limit = Text.Length();
    }

    for (unsigned int i = Field20; i < limit; ++i) {
        if (Text.CharAt(i) == 10) {
            penX = Field04;
            centred = Centred;

            int lineHeight = Font->LineHeight;

            penY += lineHeight;

            if (lineHeight + penY >= ((MSSurface*)context)->Limit()) {
                return;
            }
        } else {
            if (centred) {
                WideStringClass line;

                line.CopyFrom(&Text);
                line.Slice(0, i);

                int lead = Font->Lead;
                int width = 0;
                int j = 0;

                while (line.CharAt(j) != 0) {
                    if (line.CharAt(j) == 10) {
                        break;
                    }

                    width += Font->CharWidth(line.CharAt(j));
                    ++j;
                }

                CentreOffset = (Bounds.Width - width - lead) / 2;
                penX += CentreOffset;
                centred = false;
                line.Release();
            }

            Font->PrintRun((MSSurface*)context, Text.CharAt(i), penX, penY,
                           2, 1);
            penX += Font->CharWidth(Text.CharAt(i));
        }
    }
}

// FUNCTION: GAMEMD 0x5CE2B0
// Hand back the rectangle the printed text occupies. The whole body is a
// 16-byte copy out of the member at +0x38; retail's `ADD ECX,0x38` is the
// member's address folded into the receiver register before the copy.
MSRect MSPrintAnim::GetRect()
{
    return Bounds;
}

// FUNCTION: GAMEMD 0x5CE2E0
// Turn the printer on or off. The guard is retail's, not an optimisation: the
// store happens only when the flag actually changes.
void MSPrintAnim::SetActive(bool on)
{
    if (on != Active) {
        Active = on;
    }
}

// FUNCTION: GAMEMD 0x5CE300
// The printer has finished when it is running at all, has walked past the end
// of its text, and has held the completed page for more than two ticks. Both
// comparisons are unsigned in retail (JBE twice), which is what pins CharPos
// and LineCount as unsigned rather than signed counters.
int MSPrintAnim::IsFinished()
{
    if (Active) {
        if (CharPos > Text.Length()) {
            if (LineCount > 2) {
                return 1;
            }
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x5CE330
// Add up the widths of one line's characters. The line ends at the string's
// terminator or at the first newline, and the walk re-reads the character at
// the index each time rather than holding it — retail calls the indexed
// reader three times per turn, once for the newline test, once for the width
// and once for the loop condition.
int MSPrintAnim::MeasureWidth(WideStringClass* text)
{
    int i = 0;
    int width = 0;

    while (text->CharAt(i) != 0) {
        if (text->CharAt(i) == 10) {
            break;
        }

        width += Font->CharWidth(text->CharAt(i));
        ++i;
    }

    return width;
}

// FUNCTION: GAMEMD 0x5CE3A0
// Draw the page onto the caller's surface, one character at a time. A named
// clipping rectangle is intersected against the page's own box first and
// nothing is drawn unless the overlap has both a width and a height; a
// newline moves the pen down one line height and stops the page at the
// surface's last printable row.
void MSPrintAnim::DrawLines(MSSurface* surface, MSRect* clip)
{
    if (clip != 0) {
        MSRect out;
        MSRect shown = *MSRectIntersectOut(&out, clip, &Bounds, 0, 0);

        if (shown.Width <= 0 || shown.Height <= 0) {
            return;
        }
    }

    int y = Field08;
    int x = Field04;
    unsigned int count = Field20;

    for (unsigned int i = 0; i < count; ++i) {
        if (Text.CharAt(i) == 10) {
            int lineHeight = Font->LineHeight;

            x = Field04;
            y += lineHeight;

            if (lineHeight + y >= surface->Limit()) {
                return;
            }
        } else {
            Font->PrintRun(surface, Text.CharAt(i), x, y, 2, 1);
            x += Font->CharWidth(Text.CharAt(i));
        }
    }
}

// FUNCTION: GAMEMD 0x5CE4A0
// Build a PCX animation centred on the screen. The base starts at the origin
// with its flag clear, the derived members are seated, and only then is the
// animation enabled; the picture is looked up as "<stem>.PCX" through a stack
// file object which is torn down inline on both exits of the name test.
MSPCXAnim* MSPCXAnim::ConstructCentred(MSStringClass* name,
                                       MSAnimVector* owner, bool flag)
{
    InitEmpty();
    SeatBaseVptr();

    Surface = MSScreenSurface;
    Owner = owner;
    Image = 0;
    Field28 = flag;
    Finished = false;
    MSRect* box = &Bounds;

    box->X = 0;
    box->Y = 0;
    box->Width = 0;
    box->Height = 0;
    SeatOwnVptr();
    Enabled = true;

    if (name->At(0)) {
        MSStringClass stem;
        stem.Init();
        name->Split(0, ".", &stem);

        MSStringClass full;

        MSFileClass file;
        file.Construct(stem.Concat(&full, ".PCX"));
        full.Destruct();

        if (file.Exists(0)) {
            Image = (MSDeletable*)MSReadPCXFile(&file, 0, 0, 0);

            if (Image != 0) {
                {
                    MSRect frame;
                    Bounds = *((MSImageSurface*)Image)->GetRect(&frame);
                }

                MSRect screen;
                MSRect sw = *Surface->GetRect(&screen);

                Bounds.X += (sw.Width - Bounds.Width) / 2;
                Bounds.Y += (sw.Height - Bounds.Height) / 2;
            }
        }

        file.Vtbl    = &VT_007E16B0;
        file.Reset64 = 0;
        ((MemoryBuffer*)file.Sub58)->Clear();
        file.Vtbl    = &VT_007E1668;
        FUN_00431B80(&file);

        stem.Destruct();
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CE640
// The same build-up placed at the caller's point rather than centred. The
// trailing surface query is retail's and its result is dropped on the floor.
MSPCXAnim* MSPCXAnim::ConstructAt(MSStringClass* name, MSAnimVector* owner,
                                  const MSPoint* where, bool flag)
{
    InitEmpty();
    SeatBaseVptr();

    Surface = MSScreenSurface;
    Owner = owner;
    Image = 0;
    Field28 = flag;
    Finished = false;
    MSRect* box = &Bounds;

    box->X = 0;
    box->Y = 0;
    box->Width = 0;
    box->Height = 0;
    SeatOwnVptr();
    Enabled = true;

    if (name->At(0)) {
        MSStringClass stem;
        stem.Init();
        name->Split(0, ".", &stem);

        MSStringClass full;

        MSFileClass file;
        file.Construct(stem.Concat(&full, ".PCX"));
        full.Destruct();

        if (file.Exists(0)) {
            Image = (MSDeletable*)MSReadPCXFile(&file, 0, 0, 0);

            if (Image != 0) {
                MSRect frame;
                *box = *((MSImageSurface*)Image)->GetRect(&frame);
                box->X = where->X;
                Bounds.Y = where->Y;
                Surface->GetRect(&frame);
            }
        }

        file.Vtbl    = &VT_007E16B0;
        file.Reset64 = 0;
        ((MemoryBuffer*)file.Sub58)->Clear();
        file.Vtbl    = &VT_007E1668;
        FUN_00431B80(&file);

        stem.Destruct();
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CE7B0
void __fastcall MSPCXAnim_Destroy(MSPCXAnim* self)
{
    self->MSPCXAnim::~MSPCXAnim();
}

// FUNCTION: GAMEMD 0x5CE7D0
// Slot 4 for the PCX animation, and the one body in the family that redraws
// its neighbours: blit this animation's own frame, draw itself, then walk the
// sibling list and hand each one the rectangle this animation just occupied,
// skipping its own entry. The index of that entry comes from the list's own
// lookup, which takes its argument by reference — the temporary holding
// `this` is what retail parks in the incoming parameter's dead stack slot.
bool MSPCXAnim::Update(int context, MSRect* out)
{
    if (!Finished) {
        if (Enabled) {
            if (Image != 0) {
                MSRect area;

                Surface->Blit(&Bounds, Image, Image->GetFrame(&area, 0, 1));
                Draw(context, 0);

                // One fused copy, not two: writing the member into the local
                // and the local out gives retail's four loads followed by
                // interleaved stores, where copying the member twice emits two
                // separate load/store runs and five extra moves (34.0 percent).
                MSRect mine = Bounds;

                *out = mine;

                int skip = Owner->IndexOf(this);

                for (int i = 0; i < Owner->Count; ++i) {
                    if (i != skip) {
                        Owner->Vector[i]->Draw(context, &mine);
                    }
                }
            }

            Finished = true;
        }
    }

    return Finished && !Field28;
}

// FUNCTION: GAMEMD 0x5CE8C0
// Slot 5 for the PCX animation: blit the image's current frame onto the
// caller's surface. When the caller names a clipping rectangle the animation's
// own box is intersected against it first and nothing goes out unless the
// overlap has both a width and a height; a null rectangle draws unclipped and
// leaves the frame rectangle to the image itself.
void MSPCXAnim::Draw(int context, MSRect* area)
{
    if (Image != 0 && !Finished && Enabled) {
        if (area != 0) {
            MSRect clip = MSRectIntersect(&Bounds, *area);

            if (clip.Width <= 0 || clip.Height <= 0) {
                return;
            }
        }

        {
            MSRect frame;

            ((MSSurface*)context)->Blit(&Bounds, Image,
                                        Image->GetFrame(&frame, 0, 1));
        }
    }
}

// FUNCTION: GAMEMD 0x5CEA40
// Slot 8 for the PCX animation, the one class in the family that uses the
// hook: blit the image's current frame into the animation's own rectangle on
// the surface it was given. The hook's argument is never read — retail's
// `RET 4` pops it and nothing else touches it.
void MSPCXAnim::Attach(void* target)
{
    if (Image != 0 && Enabled) {
        MSRect area;

        Surface->Blit(&Bounds, Image, Image->GetFrame(&area, 0, 1));
    }
}

// FUNCTION: GAMEMD 0x5CEA80
// Slot 6 for the PCX animation: the same 16-byte copy as the printer's, out of
// the bounds member at +0x2C.
MSRect MSPCXAnim::GetRect()
{
    return Bounds;
}

// FUNCTION: GAMEMD 0x5CEAB0
// Slot 7: the PCX animation caches its own finished flag rather than deriving
// one, so the body is a single byte load.
bool MSPCXAnim::IsFinished()
{
    return Finished;
}

// FUNCTION: GAMEMD 0x5CEAC0
// Slot 1, shared by all nine classes: enable or disable the animation.
void MSAnim::SetEnabled(bool on)
{
    Enabled = on;
}

// The time still on the clock. Zero once the interval has run out; the whole
// interval when the timer is already paused, since a paused timer stamps its
// start as -1 and keeps its remainder in +0x18.
__forceinline int MSAnim::TimeLeft()
{
    int remain = Timer.Remaining;

    // Retail compares StartTime against -1 again here even when the caller
    // has just done so (PauseTimer). An ordinary signed test lets cl fold the
    // repeated compare; that difference is accepted rather than steered.
    if (Timer.StartTime != -1) {
        int elapsed = Timer.Clock.GetTime() - Timer.StartTime;

        if (elapsed < remain) {
            remain -= elapsed;
        } else {
            remain = 0;
        }
    }

    return remain;
}

// FUNCTION: GAMEMD 0x5CEAD0
// Slot 2: freeze the animation's clock, banking whatever is left of the
// current interval. Retail tests StartTime twice — once here and once inside
// the timer's ordinary inline reader (MSTimer::TimeLeft); the forced-inline
// MSAnim::TimeLeft lets cl fold the second test.
void MSAnim::PauseTimer()
{
    if (Timer.StartTime != -1) {
        Timer.Remaining = Timer.TimeLeft();
        Timer.StartTime = -1;
    }
}

// FUNCTION: GAMEMD 0x5CEB20
// Slot 3: restart the clock, but only from a genuinely paused state.
void MSAnim::ResumeTimer()
{
    if (Timer.StartTime == -1) {
        Timer.StartTime = Timer.Clock.GetTime();
    }
}

// FUNCTION: GAMEMD 0x5CEB40
// Slot 7 of the base: an animation with no completion notion never finishes.
bool MSAnim::IsFinished()
{
    return false;
}

// FUNCTION: GAMEMD 0x5CEB50
// Slot 8 of the base: an empty hook. The argument is popped by the callee and
// never read, which is the whole of retail's `RET 4`.
void MSAnim::Attach(void* target)
{
}

// FUNCTION: GAMEMD 0x5CEB60
// Slot 0 of the base. The destructor body is nothing but the vptr seat every
// destructor of a polymorphic class performs, so the thunk is the seat, the
// conditional free and the returned receiver.
void* MSAnim::DeletingDtor(unsigned int f)
{
    SeatBaseVptr();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CEB80
void* MSShapeAnim::DeletingDtor(unsigned int f)
{
    this->MSShapeAnim::~MSShapeAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CEBD0
// MSFadeAnim adds nothing, so its destructor reduces to MSShapeAnim's: its own
// vptr seat is a dead store cl kills against the base's, and the three bodies
// come out byte-identical, which is what the binary shows.
void* MSFadeAnim::DeletingDtor(unsigned int f)
{
    this->MSFadeAnim::~MSFadeAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CEC20
void* MSOverlayAnim::DeletingDtor(unsigned int f)
{
    this->MSOverlayAnim::~MSOverlayAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CEC70
void* MSBinkAnim::DeletingDtor(unsigned int f)
{
    this->MSBinkAnim::~MSBinkAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CECB0
void* MSVQAnim::DeletingDtor(unsigned int f)
{
    this->MSVQAnim::~MSVQAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CED10
// The bit-printed animation's only member with a destructor is its wide
// string, whose destructor retail calls out of line.
void* MSBitPrintAnim::DeletingDtor(unsigned int f)
{
    this->MSBitPrintAnim::~MSBitPrintAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CED40
void* MSPrintAnim::DeletingDtor(unsigned int f)
{
    this->MSPrintAnim::~MSPrintAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CED70
void* MSPCXAnim::DeletingDtor(unsigned int f)
{
    this->MSPCXAnim::~MSPCXAnim();

    if (f & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x5CEDB0
// Clear the four adjacent map-stage counters. Retail materialises the zero in
// a register once and stores it four times, which is what four assignments of
// the same constant to adjacent globals produce.
void MSAnimResetCounters()
{
    MSAnimCounts.Field00 = 0;
    MSAnimCounts.Field04 = 0;
    MSAnimCounts.Field08 = 0;
    MSAnimCounts.Field0C = 0;
}
