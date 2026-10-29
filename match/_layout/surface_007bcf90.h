// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_SURFACE_007BCF90_H_H
#define GG_MATCH__LAYOUT_SURFACE_007BCF90_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "rect_007bcf90.h"

struct Surface_007BCF90 {
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02(); virtual void vf_03(); virtual void vf_04();
    virtual bool vf_05(Rect_007BCF90* area, int color);
};
#endif
