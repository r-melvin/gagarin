// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x641DB0.

#include "preview_class_pcx_methods.h"
#include "../_layout/memory_buffer.h"

// FUNCTION: GAMEMD 0x641DB0
//
// Replace the preview image with a PCX file from disk. The name is opened as a
// stack file object; if it exists the old image surface is dropped, the PCX is
// decoded into a scratch surface, and — only when that surface has a nonzero
// width and height — a fresh 0x24-byte surface of the same size is allocated,
// cleared and blitted into from the scratch one, which is then destroyed.
// Every exit tears the stack file object down inline (this class's vtable, the
// +0x64 reset, the +0x58 sub-object release, the base vtable, the base
// destructor), so the teardown appears twice, once per exit.
//
// Phrasing note: the allocation is written out by hand as
// `operator new` / null test / constructor call rather than as `new T(...)`.
// A real `new` expression with a declared constructor makes VC6 emit a /GX
// exception frame (the `MOV FS:[0],...` prologue plus an unwind funclet that
// frees the block) which retail does not have — that variant scored 2.0%.
bool PreviewClass::ReadPCXPreview(const char* lpFile)
{
    File_00641DB0 file;
    file.FUN_004739F0(lpFile);

    if (file.Exists(0)) {
        if (this->ImageSurface != 0) {
            (this->ImageSurface->*this->ImageSurface->Vtbl->At_000)(1);
            this->ImageSurface = 0;
        }

        Surface_00641DB0* src = FUN_00630310(&file, 0, 0, 0);
        if (src != 0) {
            if ((src->*src->Vtbl->At_07C)() != 0) {
                if ((src->*src->Vtbl->At_080)() != 0) {
                    Surface_00641DB0* raw =
                        (Surface_00641DB0*)FUN_007C8E17(sizeof(Surface_00641DB0));
                    Surface_00641DB0* made;
                    if (raw != 0) {
                        made = raw->FUN_004BA5A0((src->*src->Vtbl->At_07C)(),
                                                 (src->*src->Vtbl->At_080)(), 1, 0);
                    } else {
                        made = 0;
                    }
                    this->ImageSurface = made;
                    (this->ImageSurface->*this->ImageSurface->Vtbl->At_018)(0);
                    (this->ImageSurface->*this->ImageSurface->Vtbl->At_004)(src, 0, 1);
                    (src->*src->Vtbl->At_000)(1);

                    file.Vtbl    = &VT_007E16B0;
                    file.Reset64 = 0;
                    ((MemoryBuffer*)file.Sub58)->Clear();
                    file.Vtbl    = &VT_007E1668;
                    FUN_00431B80(&file);
                    return true;
                }
            }
        }
    }

    file.Vtbl    = &VT_007E16B0;
    file.Reset64 = 0;
    ((MemoryBuffer*)file.Sub58)->Clear();
    file.Vtbl    = &VT_007E1668;
    FUN_00431B80(&file);
    return false;
}
