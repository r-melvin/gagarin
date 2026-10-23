// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Classes that override an AbstractClass slot with a body that only forwards to
// the base body: AircraftClass AddRef/Release (slots 1, 2: 0x410300, 0x410310)
// and the checksum slot 13 of Airstrike, DiskLaser, LightSource, RadSite and
// Temporal (0x410410). The owning class of each address is read from the
// RTTI-named vtable that holds it; each class is declared only as far as these
// virtuals (no layout is claimed).
#include "../_layout/abstract_class.h"

class AircraftClass : public AbstractClass
{
public:
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
};

class AirstrikeClass : public AbstractClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
};

class DiskLaserClass : public AbstractClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
};

class LightSourceClass : public AbstractClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
};

class RadSiteClass : public AbstractClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
};

class TemporalClass : public AbstractClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
};

// FUNCTION: GAMEMD 0x004142F0
ULONG __stdcall AircraftClass::AddRef()
{
    return AbstractClass::AddRef();
}

// FUNCTION: GAMEMD 0x00414300
ULONG __stdcall AircraftClass::Release()
{
    return AbstractClass::Release();
}

// FUNCTION: GAMEMD 0x0041D6E0
void AirstrikeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
}


// FUNCTION: GAMEMD 0x00555070
void LightSourceClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
}

// FUNCTION: GAMEMD 0x0065B3B0
void RadSiteClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
}

// FUNCTION: GAMEMD 0x0071A650
void TemporalClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
}
