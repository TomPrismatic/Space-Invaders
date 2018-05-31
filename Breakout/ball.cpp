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

// This Includes
#include "Ball.h"

// Static Variables

// Static Function Prototypes

// Implementation

Ball::Ball()
: m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
{

}

Ball::~Ball()
{

}

bool
Ball::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY)
{
    VALIDATE(Entity::Initialise(IDB_BALLSPRITE, IDB_BALLMASK));
    
    xPosition = _fPosX;
    m_fY = _fPosY;

    m_fVelocityX = _fVelocityX;
    m_fVelocityY = _fVelocityY;

    return (true);
}

void
Ball::Draw()
{
    Entity::Draw();
}

void
Ball::Process(float _fDeltaTick)
{
    xPosition += m_fVelocityX * _fDeltaTick;
    m_fY += m_fVelocityY * _fDeltaTick;

    Entity::Process(_fDeltaTick);
}

float 
Ball::GetVelocityX() const
{
    return (m_fVelocityX);
}

float 
Ball::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
Ball::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}

void 
Ball::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}

float 
Ball::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
