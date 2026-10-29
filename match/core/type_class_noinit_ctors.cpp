// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: the five constructors at 0x5FE3C0, 0x644220, 0x6B5370, 0x6DD180 and 0x6E7F50 each
//   forward their NoInit argument to a base constructor and then store the four COM-interface
//   vtable pointers of the RTTI class named by the first vtable (read from the binary).
//
// Each class is declared here with only what the constructor needs (a base and a virtual
// destructor, so the compiler emits the vptr stores); the classes' real bodies are recovered in
// their own units.

#include "../_layout/object_type_class.h"
#include "../_layout/abstract_class.h"

class OverlayTypeClass : public ObjectTypeClass
{
public:
    OverlayTypeClass(const AbstractNoInit& noInit);
    virtual ~OverlayTypeClass();
};

class ParticleSystemTypeClass : public ObjectTypeClass
{
public:
    ParticleSystemTypeClass(const AbstractNoInit& noInit);
    virtual ~ParticleSystemTypeClass();
};

class SmudgeTypeClass : public ObjectTypeClass
{
public:
    SmudgeTypeClass(const AbstractNoInit& noInit);
    virtual ~SmudgeTypeClass();
};

// Views: the canonical TActionClass / TaskForceClass construct inline, so the standalone retail
// constructors are recorded on non-colliding view names.
class TActionView_006DD180 : public AbstractClass
{
public:
    TActionView_006DD180(const AbstractNoInit& noInit);
    virtual ~TActionView_006DD180();
};

class TaskForceView_006E7F50 : public AbstractTypeClass
{
public:
    TaskForceView_006E7F50(const AbstractNoInit& noInit);
    virtual ~TaskForceView_006E7F50();
};

// FUNCTION: GAMEMD 0x5FE3C0
OverlayTypeClass::OverlayTypeClass(const AbstractNoInit& noInit)
    : ObjectTypeClass(noInit)
{
}

// FUNCTION: GAMEMD 0x644220
ParticleSystemTypeClass::ParticleSystemTypeClass(const AbstractNoInit& noInit)
    : ObjectTypeClass(noInit)
{
}

// FUNCTION: GAMEMD 0x6B5370
SmudgeTypeClass::SmudgeTypeClass(const AbstractNoInit& noInit)
    : ObjectTypeClass(noInit)
{
}

// FUNCTION: GAMEMD 0x6DD180
TActionView_006DD180::TActionView_006DD180(const AbstractNoInit& noInit)
    : AbstractClass(noInit)
{
}

// FUNCTION: GAMEMD 0x6E7F50
TaskForceView_006E7F50::TaskForceView_006E7F50(const AbstractNoInit& noInit)
    : AbstractTypeClass(noInit)
{
}
