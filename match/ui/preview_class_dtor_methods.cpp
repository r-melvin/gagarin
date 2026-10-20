// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6406F0.

#include "preview_class_dtor_methods.h"

// FUNCTION: GAMEMD 0x6406F0
//
// PreviewClass::~PreviewClass. Releases the image surface, if any, through
// its own scalar-deleting-destructor slot (freeing the block: the pushed
// `1`), then clears the pointer. No base/member destructor call follows --
// this is the whole body.
void PreviewClass_006406F0::Dtor()
{
    if (this->ImageSurface != 0) {
        (this->ImageSurface->*this->ImageSurface->Vtbl->At_000)(1);
        this->ImageSurface = 0;
    }
}
