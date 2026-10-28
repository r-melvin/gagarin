// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// IPersistStream::Save overrides that only chain to a base class. Each body
// pushes its three stack arguments again and calls the base Save; the
// 29-byte form then folds every success code to S_OK (`TEST EAX,EAX; JL;
// XOR EAX,EAX`), the 23-byte form returns the base result as is.
//
// The owning class of each body is the class whose vtable slot 6 holds it in
// the retail RTTI tables; the base is the class that owns the called body
// (AbstractClass::Save 0x410320, ObjectTypeClass::Save 0x5F9950 (below),
// TechnoTypeClass::Save 0x716DC0, FootClass::Save 0x4DB690). The classes are
// declared here only as views carrying Save: intermediate bases that do not
// override it are elided, and no member is touched, so there is no layout.
// The canonical headers model the COM bases as plain vptr fields, so Save
// cannot be declared on them without a shared-header change.

#include <objidl.h>

class AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 0x410320
};

class ObjectTypeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 0x5F9950
};

class TechnoTypeClass : public ObjectTypeClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 0x716DC0
};

class FootClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 0x4DB690
};

class AircraftClass : public FootClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class AircraftTypeClass : public TechnoTypeClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class AirstrikeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class AnimTypeClass : public ObjectTypeClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class NeuronClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class BulletClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};


class DiskLaserClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class EMPulseClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class InfantryClass : public FootClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class IsometricTileClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class IsometricTileTypeClass : public ObjectTypeClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class LightSourceClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class ParasiteClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class RadSiteClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class ScriptClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class ScriptTypeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class SuperClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class SuperWeaponTypeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class Tactical : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TActionClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TagClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TagTypeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TaskForceClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TeamClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TeamTypeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TEventClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TriggerClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TriggerTypeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class TubeClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class UnitTypeClass : public TechnoTypeClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class VoxelAnimClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class VoxelAnimTypeClass : public ObjectTypeClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

// FUNCTION: GAMEMD 0x41B5C0
HRESULT __stdcall AircraftClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return FootClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x41CE90
HRESULT __stdcall AircraftTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = TechnoTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x41D780
HRESULT __stdcall AirstrikeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x428970
HRESULT __stdcall AnimTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ObjectTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x43A5B0
HRESULT __stdcall NeuronClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x46AFB0
HRESULT __stdcall BulletClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x4A7C10
HRESULT __stdcall DiskLaserClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x4C5A80
HRESULT __stdcall EMPulseClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x521B00
HRESULT __stdcall InfantryClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return FootClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x5439F0
HRESULT __stdcall IsometricTileClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x549D70
HRESULT __stdcall IsometricTileTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ObjectTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x555110
HRESULT __stdcall LightSourceClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x5F9950
HRESULT __stdcall ObjectTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6296B0
HRESULT __stdcall ParasiteClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x65B450
HRESULT __stdcall RadSiteClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x691690
HRESULT __stdcall ScriptClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x691DE0
HRESULT __stdcall ScriptTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6CDFD0
HRESULT __stdcall SuperClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6CE8D0
HRESULT __stdcall SuperWeaponTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6DBE00
HRESULT __stdcall Tactical::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E3E30
HRESULT __stdcall TActionClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E57A0
HRESULT __stdcall TagClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E6470
HRESULT __stdcall TagTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E8680
HRESULT __stdcall TaskForceClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6EC540
HRESULT __stdcall TeamClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6F1B90
HRESULT __stdcall TeamTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x71F930
HRESULT __stdcall TEventClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x7268D0
HRESULT __stdcall TriggerClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x727C80
HRESULT __stdcall TriggerTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x7281E0
HRESULT __stdcall TubeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x7480B0
HRESULT __stdcall UnitTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = TechnoTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x74AA10
HRESULT __stdcall VoxelAnimClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x74B8D0
HRESULT __stdcall VoxelAnimTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ObjectTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}
