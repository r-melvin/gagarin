// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Name
//   cross-checked against YRpp Audio.h `AdjustAudioEventPanning` (consult-only,
//   no LICENSE; every offset reconfirmed against the user's binary below).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x406270  AdjustAudioEventPanning  (__fastcall)
//   LIBRARY:  GAMEMD 0x407150  AudioEvent_SetPanType0   (tail-call target, reloc)
//   LIBRARY:  GAMEMD 0x407170  AudioEvent_SetPanType3   (tail-call target, reloc)

#include "audio_pan_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x406270  (__fastcall: event=ECX, pan=EDX)
//
// Clamp the requested pan to the valid [0, 0x4000] range — values above 0x4000
// saturate to 0x4000, negative values (signed) snap to 0 — then forward the
// clamped value to whichever per-channel pan setter matches the event's
// playback type. The clamp is inlined into each branch (the retail code does
// not hoist it), and each branch tail-calls a different setter, so the whole
// thing lowers to `ADD ECX,0x108; JMP setter`.
//
// PARTIAL: retail loads the type into EAX before comparing it; the ordinary
// read lets VC6 compare the member in memory. A volatile read that forced the
// load was removed as match steering. (The positional score is 0.0% because
// the one missing instruction shifts every later one.)
// ---------------------------------------------------------------------------
void __fastcall AdjustAudioEventPanning(void* event, unsigned int pan)
{
    AudioEventTag* ev = (AudioEventTag*)event;
    int type = ev->Type;
    if (type == 3)
    {
        if (pan > 0x4000)
            pan = 0x4000;
        else if ((int)pan < 0)
            pan = 0;
        AudioEvent_SetPanType3(&ev->Channel, pan);
    }
    else
    {
        if (pan > 0x4000)
            pan = 0x4000;
        else if ((int)pan < 0)
            pan = 0;
        AudioEvent_SetPanType0(&ev->Channel, pan);
    }
}
