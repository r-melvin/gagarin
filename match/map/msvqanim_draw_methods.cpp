// Provenance: own-binary-via-Ghidra
//   MSVQAnim's slot-5 draw (vtable 0x7EE9B0, RTTI-named). Reuses the family
//   header read-only; the members it needs that the canonical header does not
//   declare are given TU-local views below.

#include "msanim_family_methods.h"

// The VQA player's two rectangles, read at 0x5CD119 (`ADD ESI,0x34`) and
// 0x5CD224/0x5CD22E (`LEA ESI,[EAX+0x34]`, `ADD EAX,0x24`).
struct MSVQPlayerRects
{
    char   unknown_00[0x24];
    RectangleStruct Dest;      // +0x24
    RectangleStruct Source;    // +0x34
};
GG_STATIC_ASSERT(offsetof(MSVQPlayerRects, Dest) == 0x24
              && offsetof(MSVQPlayerRects, Source) == 0x34);

// FUNCTION: GAMEMD 0x005cd0e0
// Slot 5: blit the player's current source rectangle from the screen surface
// into its destination on the caller's surface, skipped when the optional
// clip rectangle leaves nothing of the source.
void MSVQAnim::Draw(MouseSurfaceView* context, RectangleStruct* area)
{
    if (Player != 0 && !Finished) {
        if (area != 0) {
            RectangleStruct clip = MSRectIntersect(&((MSVQPlayerRects*)Player)->Source, *area);

            if (clip.Width <= 0 || clip.Height <= 0) {
                return;
            }
        }

        MSVQPlayerRects* rects = (MSVQPlayerRects*)Player;
        ((MSBlitSurface*)context)->Blit(&rects->Dest, MSScreenSurface,
                                        &rects->Source, 0, 1);
    }
}
