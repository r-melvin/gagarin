// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   VoxelAnimTypeClass registry lookup, read off retail gamemd.exe v1.001 (vtable 0x7F6548).
//   Address index: 0x74BB20 registry lookup.

#include "../_layout/voxel_anim_type_class.h"
#include "../core/vector_class_operations.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);


// FUNCTION: GAMEMD 0x74BB20
// Finds the type named `id` (case-insensitive) in the given registry, or allocates a new one. The
// reserved names "<none>" and "none" give null. The registry arrives in EDX.
VoxelAnimTypeClass* __fastcall FUN_0074BB20(const char* id, DynamicVectorClass<VoxelAnimTypeClass*>* registry)
{
    if (_stricmp("<none>", id) != 0 && _stricmp("none", id) != 0) {
        for (int i = 0; i < registry->Count; ++i) {
            if (_stricmp(registry->Items[i]->ID, id) == 0) {
                return registry->Items[i];
            }
        }
        return new VoxelAnimTypeClass(id);
    }
    return 0;
}
