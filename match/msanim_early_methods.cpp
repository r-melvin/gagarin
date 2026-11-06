// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against the user's retail gamemd.exe v1.001 across
//   0x5CB6C0..0x5CCE82, the earlier half of the map-stage animation family
//   whose later half lives in msanim_family_methods.cpp (types from its header).
// Address index: 0x5CB790 0x5CB880 0x5CBB80 0x5CBCB0 0x5CC110 0x5CC330 0x5CC550 0x5CC6C0 0x5CC760 0x5CC820 0x5CC850
//   0x5CC880 0x5CCA10 0x5CCA20 0x5CCC30 0x5CCE40 0x5CCE90 0x5CEC70 0x5CECB0

#include "msanim_family_methods.h"
#include "_layout/memory_buffer.h"
#include "shared_constants_globals.h"

// GLOBAL: GAMEMD 0x88730C -- the blitter the shape animations redraw through.
extern MSBlitSurface* DAT_0088730C;

static inline bool MSRectEqual(const RectangleStruct& a, const RectangleStruct& b)
{
    return a.X == b.X && a.Y == b.Y && a.Width == b.Width
        && a.Height == b.Height;
}

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- shape draw, __fastcall: surface in ECX, convert in EDX, fourteen
// stack words (the last two are a point passed by value).
void FUN_004AED70(MSSurface* surface, int convert, MSShapeFile* shape, int frame, MSPoint* position,
                  RectangleStruct* clip, unsigned int flags, int a6, int a7, int a8, int zAdjust,
                  int a10, int a11, int a12, MSPoint offset);

// GLOBAL: GAMEMD 0x830078 -- the four draw-flag words the fade stages index (0x406, 0x404, 0x402, 0x400).
extern unsigned int DAT_00830078[4];

// GLOBAL: GAMEMD 0x8A00A4 / 0x8A00A8 -- display mode width and height.
extern int DAT_008A00A4;
extern int DAT_008A00A8;

// FUNCTION: GAMEMD 0x5CB790
// Jump to a frame. When the rectangle moves, the screen is redrawn over the
// old position; the frame is then clamped to the last one in the file.
void MSShapeAnim::SetFrame(unsigned int frame)
{
    RectangleStruct old;
    old = GetRect();
    Frame = frame;

    if (!MSRectEqual(old, GetRect())) {
        DAT_0088730C->Blit(&old, MSScreenSurface, &old, 0, 1);
    }

    if (Frame >= (unsigned int)Buffer->Frames) {
        Frame = Buffer->Frames - 1;
    }
}

// FUNCTION: GAMEMD 0x5CB840
// Store the +0x2C index, clamped below the shape's frame count.
void MSShapeAnim::FUN_005CB840(unsigned int value)
{
    Field2C = value;
    int limit = Buffer->Frames;
    if (value >= (unsigned int)limit)
        Field2C = limit - 1;
}

// FUNCTION: GAMEMD 0x5CB860
// Store the last-frame index, clamped below the shape's frame count.
void MSShapeAnim::FUN_005CB860(unsigned int value)
{
    LastFrame = value;
    int limit = Buffer->Frames;
    if (value >= (unsigned int)limit)
        LastFrame = limit - 1;
}

// FUNCTION: GAMEMD 0x5CB880
// PARTIAL: 94.1% -- the same instructions as retail; the merged-box path stores its four words in a different
// order (retail loads the spilled width into ESI before the first store) and the final copy of the old box
// reuses two registers where retail holds four.
// Slot 4: once the interval has run out, redraw the screen over the current frame, step to the next one
// (wrapping to +0x2C or stopping at the last) and draw it. The rectangle handed back is the union of the old
// and the new frame's boxes; when the animation has finished it is the old box alone.
bool MSShapeAnim::Update(MouseSurfaceView* context, RectangleStruct* out)
{
    if (Enabled == true && Timer.TimeLeft() == 0) {
        Timer = MSTimer(Field24);

        RectangleStruct old;
        {
            RectangleStruct tmp;
            old = *Buffer->GetFrameRect(&tmp, Frame);
        }
        old.X += Field04;
        old.Y += Field08;

        if (Flags & 0x200) {
            old.X += -(Buffer->Width / 2);
            old.Y += -(Buffer->Height / 2);
        }

        ((MSBlitSurface*)context)->Blit(&old, MSScreenSurface, &old, 0, 1);

        ++Frame;
        if (Frame > (unsigned int)LastFrame) {
            if (!Field34) {
                *out = old;
                return true;
            }
            Frame = Field2C;
        }

        {
            MSPoint none = { 0, 0 };
            RectangleStruct clip;
            MSPoint position;
            position.X = Field04;
            position.Y = Field08;
            FUN_004AED70((MSSurface*)context, Field20, Buffer, Frame, &position,
                         ((MSSurface*)context)->GetRect(&clip), Flags | 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, none);
        }

        {
            RectangleStruct tmp;
            *out = *Buffer->GetFrameRect(&tmp, Frame);
        }
        out->X += Field04;
        out->Y += Field08;

        if (Flags & 0x200) {
            out->X += -(Buffer->Width / 2);
            out->Y += -(Buffer->Height / 2);
        }

        if (out->Width > 0 && out->Height > 0) {
            if (old.Width > 0 && old.Height > 0) {
                RectangleStruct merged = *out;

                if (merged.X > old.X) {
                    merged.Width += merged.X - old.X;
                    merged.X = old.X;
                }
                if (merged.Y > old.Y) {
                    merged.Height += merged.Y - old.Y;
                    merged.Y = old.Y;
                }
                if (merged.X + merged.Width < old.X + old.Width) {
                    merged.Width = old.Width - merged.X + old.X + 1;
                }
                if (merged.Y + merged.Height < old.Y + old.Height) {
                    merged.Height = old.Height - merged.Y + old.Y + 1;
                }

                out->X = merged.X;
                out->Y = merged.Y;
                out->Width = merged.Width;
                out->Height = merged.Height;
            } else {
                RectangleStruct same = *out;
                *out = same;
            }
        } else {
            *out = old;
        }

        return false;
    }

    out->X = 0;
    out->Y = 0;
    out->Width = 0;
    out->Height = 0;
    return false;
}

// FUNCTION: GAMEMD 0x5CBB80
// Slot 5: draw the current frame. A clipping rectangle first has to overlap the frame's box.
void MSShapeAnim::Draw(MouseSurfaceView* context, RectangleStruct* area)
{
    RectangleStruct r;
    r.X = 0;
    r.Y = 0;
    r.Width = 0;
    r.Height = 0;

    if (area != 0) {
        RectangleStruct tmp;
        r = *Buffer->GetFrameRect(&tmp, Frame);
        r.X += Field04;
        r.Y += Field08;

        if (Flags & 0x200) {
            r.X += -(Buffer->Width / 2);
            r.Y += -(Buffer->Height / 2);
        }

        r = *MSRectIntersectOut(&tmp, area, &r, 0, 0);
        if (r.Width <= 0 || r.Height <= 0) {
            return;
        }
    }

    if (Enabled) {
        MSPoint none = { 0, 0 };
        RectangleStruct clip;
        MSPoint position;
        position.X = Field04;
        position.Y = Field08;
        FUN_004AED70((MSSurface*)context, Field20, Buffer, Frame, &position,
                     ((MSSurface*)context)->GetRect(&clip), Flags | 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, none);
    }
}

// FUNCTION: GAMEMD 0x5CBCB0
// PARTIAL: 83.3% -- the same instructions as retail; cl orders the four frame-rectangle
// loads differently (retail loads X, then the Y offset, then Y, W, H, then the X offset).
// The rectangle of the current frame, moved to where the animation sits and,
// when the centring flag is set, pulled back by half the shape's size.
RectangleStruct MSShapeAnim::GetRect()
{
    RectangleStruct tmp;
    RectangleStruct* frame = Buffer->GetFrameRect(&tmp, Frame);

    RectangleStruct r;
    r.X = frame->X;
    r.Y = frame->Y;
    r.Width = frame->Width;
    r.Height = frame->Height;
    r.Y += Field08;
    r.X += Field04;

    if (Flags & 0x200) {
        r.X -= Buffer->Width / 2;
        r.Y -= Buffer->Height / 2;
    }

    return r;
}

// FUNCTION: GAMEMD 0x5CC110
// Slot 5 of the fade animation: the same clipped draw, with the draw flags taken from the stage table (the last
// entry for any stage past the table).
void MSFadeAnim::Draw(MouseSurfaceView* context, RectangleStruct* area)
{
    RectangleStruct r;
    r.X = 0;
    r.Y = 0;
    r.Width = 0;
    r.Height = 0;

    if (area != 0) {
        RectangleStruct tmp;
        r = *Buffer->GetFrameRect(&tmp, Frame);
        r.X += Field04;
        r.Y += Field08;

        if (Flags & 0x200) {
            r.X += -(Buffer->Width / 2);
            r.Y += -(Buffer->Height / 2);
        }

        r = *MSRectIntersectOut(&tmp, area, &r, 0, 0);
        if (r.Width <= 0 || r.Height <= 0) {
            return;
        }
    }

    {
        unsigned int flags;
        if (unknown_40 < 4) {
            flags = DAT_00830078[unknown_40] | Flags;
        } else {
            flags = Flags | DAT_00830078[3];
        }

        MSPoint none = { 0, 0 };
        RectangleStruct clip;
        MSPoint position;
        position.X = Field04;
        position.Y = Field08;
        FUN_004AED70((MSSurface*)context, Field20, Buffer, Frame, &position,
                     ((MSSurface*)context)->GetRect(&clip), flags, 0, 0, 0, 0x3E8, 0, 0, 0, none);
    }
}

// FUNCTION: GAMEMD 0x5CC330
// Slot 4 of the overlay: once the interval has run out and the fade has not finished, redraw the screen over the
// frame, draw it with the current stage's flags, redraw the sibling animations over it and step the stage. The
// fade's last stage draws once more with the plain draw flags; the animation reports itself done when its
// +0x48 byte is clear.
bool MSOverlayAnim::Update(MouseSurfaceView* context, RectangleStruct* out)
{
    if (Enabled == true && Timer.TimeLeft() == 0) {
        Timer = MSTimer(Field24);

        if (unknown_40 >= 4) {
            return false;
        }

        {
            RectangleStruct tmp;
            *out = *Buffer->GetFrameRect(&tmp, Frame);
        }
        out->X += Field04;
        out->Y += Field08;

        if (Flags & 0x200) {
            out->X += -(Buffer->Width / 2);
            out->Y += -(Buffer->Height / 2);
        }

        ((MSBlitSurface*)context)->Blit(out, MSScreenSurface, out, 0, 1);

        unsigned int stage = unknown_40 < 3 ? unknown_40 : 3;

        {
            MSPoint none = { 0, 0 };
            RectangleStruct clip;
            MSPoint position;
            position.X = Field04;
            position.Y = Field08;
            FUN_004AED70((MSSurface*)context, Field20, Buffer, Frame, &position,
                         ((MSSurface*)context)->GetRect(&clip), DAT_00830078[stage] | Flags,
                         0, 0, 0, 0x3E8, 0, 0, 0, none);
        }

        if (unknown_44 != 0) {
            int skip = unknown_44->IndexOf(this);

            for (int i = 0; i < unknown_44->Count; ++i) {
                if (i != skip) {
                    unknown_44->Vector[i]->Draw(context, out);
                }
            }
        }

        ++unknown_40;
        if (unknown_40 >= 4) {
            MSPoint zero = { 0, 0 };
            RectangleStruct lastClip;
            MSPoint last;
            last.X = Field04;
            last.Y = Field08;
            FUN_004AED70(MSScreenSurface, Field20, Buffer, Frame, &last,
                         ((MSSurface*)context)->GetRect(&lastClip), Flags | 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, zero);
        }

        return unknown_48 == 0;
    }

    out->X = 0;
    out->Y = 0;
    out->Width = 0;
    out->Height = 0;
    return false;
}

// FUNCTION: GAMEMD 0x5CC550
// Slot 5 of the overlay: the clipped draw, with the flags of the current stage (never past the third entry).
void MSOverlayAnim::Draw(MouseSurfaceView* context, RectangleStruct* area)
{
    RectangleStruct r;
    r.X = 0;
    r.Y = 0;
    r.Width = 0;
    r.Height = 0;

    if (Enabled) {
        {
            RectangleStruct tmp;
            r = *Buffer->GetFrameRect(&tmp, Frame);
            r.X += Field04;
            r.Y += Field08;

            if (Flags & 0x200) {
                r.X += -(Buffer->Width / 2);
                r.Y += -(Buffer->Height / 2);
            }

            if (area != 0) {
                r = *MSRectIntersectOut(&tmp, area, &r, 0, 0);
                if (r.Width <= 0 || r.Height <= 0) {
                    return;
                }
            }
        }

        {
            unsigned int stage = unknown_40 < 3 ? unknown_40 : 3;

            MSPoint none = { 0, 0 };
            RectangleStruct clip;
            MSPoint position;
            position.X = Field04;
            position.Y = Field08;
            FUN_004AED70((MSSurface*)context, Field20, Buffer, Frame, &position,
                         ((MSSurface*)context)->GetRect(&clip), DAT_00830078[stage] | Flags,
                         0, 0, 0, 0x3E8, 0, 0, 0, none);
        }
    }
}

// FUNCTION: GAMEMD 0x5CC6C0
// Slot 8 of the overlay: draw the current stage straight onto the screen surface.
void MSOverlayAnim::Attach(void* target)
{
    unsigned int stage = unknown_40 < 3 ? unknown_40 : 3;

    if (Enabled) {
        MSPoint none = { 0, 0 };
        RectangleStruct clip;
        MSPoint position;
        position.X = Field04;
        position.Y = Field08;
        FUN_004AED70(MSScreenSurface, Field20, Buffer, Frame, &position,
                     MSScreenSurface->GetRect(&clip), DAT_00830078[stage] | Flags,
                     0, 0, 0, 0x3E8, 0, 0, 0, none);
    }
}

// FUNCTION: GAMEMD 0x5CC760
// Remember the caller's numbers and box; when the file name is not empty, open it as a Bink player and
// move it to the argument box's corner.
MSBinkAnim::MSBinkAnim(Wstring* name, int flags, int field34, const RectangleStruct* rect, bool field38)
    : MSAnim(rect->X, rect->Y), Player(0), Field20(flags), Bounds(*rect), Field34(field34), Field38(field38)
{
    if ((unsigned int)name->Length() > 0) {
        Player = new MSBinkPlayer(name->FUN_007B5440(), flags);
        Player->Move(rect->X, rect->Y);
    }
}

// FUNCTION: GAMEMD 0x5CC820
// The Bink animation's destructor, out of line (the scalar deleting destructor expands it inline).
MSBinkAnim::~MSBinkAnim()
{
    delete Player;
}

// FUNCTION: GAMEMD 0x5CC850
// Slot 6: the box the player was opened in.
RectangleStruct MSBinkAnim::GetRect()
{
    return Bounds;
}

// FUNCTION: GAMEMD 0x5CC880
// Slot 7: true when there is no player, or the player reports it has finished.
bool MSBinkAnim::vf_7()
{
    return Player == 0 || Player->IsDone();
}

// FUNCTION: GAMEMD 0x5CCA10
// Slot 8: an empty hook.
void MSBinkAnim::Attach(void* target)
{
}

// FUNCTION: GAMEMD 0x5CCA20
// The same build with the movie's source box taken from the caller; the destination box is still centred on the
// caller's surface, at the display mode's size.
MSVQAnim::MSVQAnim(MSStringClass* name, MSSurface* surface, MSAnimVector* field24, const RectangleStruct* source,
                   bool field2c)
    : Player(0), Surface(surface), Field24(field24), Movie(0), Field2C(field2c), Finished(false)
{
    if (name->FUN_007B47F0(0) && surface != 0) {
        MSBounds none2;
        MSBounds none1;
        Player = FUN_005BFAA0(name->FUN_007B5440(), surface, none1, none2, (int)(DAT_00A8EB98 * 255.0), 0);

        if (Player != 0) {
            int height = DAT_008A00A8;
            int width = DAT_008A00A4;
            int y = (surface->Limit() - DAT_008A00A8) / 2;
            int x = (surface->Slot31() - DAT_008A00A4) / 2;
            RectangleStruct dest = { x, y, width, height };
            Player->Dest = dest;
            Player->Source = *source;
        }

        MSStringClass stem;
        stem.Init();
        name->Split(0, ".", &stem);

        MSFileClass file;
        {
            MSStringClass full;
            file.Construct(stem.Concat(&full, ".PCX"));
            full.Destruct();
        }

        if (file.Exists(0)) {
            Movie = (MSDeletable*)MSReadPCXFile(&file, 0, 0, 0);
        }

        file.Vtbl    = &VT_007E16B0;
        file.Reset64 = 0;
        ((MemoryBuffer*)file.Sub58)->Clear();
        file.Vtbl    = &DAT_007E1668;
        FUN_00431B80(&file);

        stem.Destruct();
    }
}

// FUNCTION: GAMEMD 0x5CCC30
// Build a VQA animation. When there is a name and a surface, the movie is opened with an empty clip pair and
// the volume scale, its destination box is centred (640x400) on the caller's surface and its source box on
// the screen surface; the backdrop is then looked up as "<stem>.PCX" through a stack file object which is
// torn down inline.
MSVQAnim::MSVQAnim(MSStringClass* name, MSSurface* surface, MSAnimVector* field24, bool field2c)
    : Player(0), Surface(surface), Field24(field24), Movie(0), Field2C(field2c), Finished(false)
{
    if (name->FUN_007B47F0(0) && surface != 0) {
        MSBounds none2;
        MSBounds none1;
        Player = FUN_005BFAA0(name->FUN_007B5440(), surface, none1, none2, (int)(DAT_00A8EB98 * 255.0), 0);

        if (Player != 0) {
            int y = (surface->Limit() - 400) / 2;
            int x = (surface->Slot31() - 640) / 2;
            RectangleStruct dest = { x, y, 640, 400 };
            Player->Dest = dest;

            y = (DAT_0088730C->Slot32() - 400) / 2;
            x = (DAT_0088730C->Slot31() - 640) / 2;
            RectangleStruct source = { x, y, 640, 400 };
            Player->Source = source;
        }

        MSStringClass stem;
        stem.Init();
        name->Split(0, ".", &stem);

        MSStringClass full;

        MSFileClass file;
        file.Construct(stem.Concat(&full, ".PCX"));
        full.Destruct();

        if (file.Exists(0)) {
            Movie = (MSDeletable*)MSReadPCXFile(&file, 0, 0, 0);
        }

        file.Vtbl    = &VT_007E16B0;
        file.Reset64 = 0;
        ((MemoryBuffer*)file.Sub58)->Clear();
        file.Vtbl    = &DAT_007E1668;
        FUN_00431B80(&file);

        stem.Destruct();
    }
}

// FUNCTION: GAMEMD 0x5CCE40
// The VQA animation's destructor, out of line: the movie goes through its own slot-zero deleting
// destructor, then the player is stopped and deleted. The compiler emits its scalar deleting destructor
// 0x5CECB0 beside the constructor above.
MSVQAnim::~MSVQAnim()
{
    if (Movie != 0) {
        Movie->DeletingDtor(1);
    }

    if (Player != 0) {
        Player->Stop();
        delete Player;
    }
}

// FUNCTION: GAMEMD 0x5CCE90
// Slot 4: step the movie. With a player, a new frame is drawn and handed back as the changed box (the siblings
// redraw over it), and the end of the movie paints the backdrop once more; without one the backdrop is painted
// once and the animation finishes. It is done when it has finished and is not held open.
bool MSVQAnim::Update(MouseSurfaceView* context, RectangleStruct* out)
{
    if (Player != 0) {
        bool ended = false;

        if (!Finished) {
            if (FUN_005C0080(Player, &ended) == true) {
                Draw(context, 0);
                *out = Player->Source;

                int skip = Field24->IndexOf(this);

                for (int i = 0; i < Field24->Count; ++i) {
                    if (i != skip) {
                        Field24->Vector[i]->Draw(context, &Player->Source);
                    }
                }
            }

            if (ended == true) {
                if (Movie != 0) {
                    RectangleStruct frame;

                    ((MSBlitSurface*)Surface)->Blit(&Player->Dest, (MSSurface*)Movie,
                                                    ((MSImageSurface*)Movie)->GetRect(&frame), 0, 1);
                    Draw(context, 0);
                    *out = Player->Source;

                    int skip = Field24->IndexOf(this);

                    for (int i = 0; i < Field24->Count; ++i) {
                        if (i != skip) {
                            Field24->Vector[i]->Draw(context, &Player->Source);
                        }
                    }
                }
            }

            if (ended) {
                Finished = ended;
            }
        }
    } else {
        if (!Finished && Movie != 0) {
            RectangleStruct tmp;
            RectangleStruct area = *((MSImageSurface*)Movie)->GetRect(&tmp);

            ((MSBlitSurface*)Surface)->Blit(&area, (MSSurface*)Movie, &area, 0, 1);
            Draw(context, 0);
            *out = area;

            int skip = Field24->IndexOf(this);

            for (int i = 0; i < Field24->Count; ++i) {
                if (i != skip) {
                    Field24->Vector[i]->Draw(context, &area);
                }
            }
        }

        Finished = true;
    }

    return Finished && !Field2C;
}

// Compiler-generated scalar deleting destructor of MSBinkAnim (destructor and base destructor expanded inline).
// SYNTHETIC: GAMEMD 0x5CEC70 -- MSBinkAnim::`scalar deleting destructor'

// Compiler-generated scalar deleting destructor of MSVQAnim, emitted with the vtable 0x7EE9B0 by the constructor.
// SYNTHETIC: GAMEMD 0x5CECB0 -- MSVQAnim::`scalar deleting destructor'

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8EB98
float DAT_00A8EB98;
// END defined globals
