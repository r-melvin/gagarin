// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   VoxelAnimTypeClass registry lookup, read off retail gamemd.exe v1.001 (vtable 0x7F6548).
//   Address index: 0x74BB20 registry lookup.

#include "../_layout/object_type_class.h"
#include "../core/vector_class_operations.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// The members the lookup touches; the allocation is 0x308 bytes.
class VoxelAnimTypeClass : public ObjectTypeClass
{
public:
    // FUNCTION: GAMEMD 0x74AD80 (decl; reloc) - the constructor taking the type's ID.
    VoxelAnimTypeClass(const char* id);
    virtual ~VoxelAnimTypeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);      // 3   0x74B7D0
    virtual HRESULT __stdcall Load(IStream* pStm);              // 5   0x74B810
    virtual int vf_11();                                        // 11  0x74B9F0
    virtual int vf_12();                                        // 12  0x74BA00
    virtual bool vf_32(const CellStruct* cell, HouseClass* house); // 32 0x74BA10
    virtual void* vf_35(void* house);                           // 35  0x74BA20
    char unknown_294[0x308 - 0x294];
};
GG_STATIC_ASSERT(sizeof(VoxelAnimTypeClass) == 0x308);

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
