//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Brick.h"

// Static Variables

// Static Function Prototypes

// Implementation

Brick::Brick()
: m_bHit(false)
{

}

Brick::~Brick()
{

}

bool
Brick::Initialise()
{
    VALIDATE(Entity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

    return (true);
}

void
Brick::Draw()
{
    if (!m_bHit)
    {
        Entity::Draw();
    }
}

void
Brick::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
        Entity::Process(_fDeltaTick);
    }
}

void
Brick::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
Brick::IsHit() const
{
    return (m_bHit);
}

