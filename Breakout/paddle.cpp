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
#include "Paddle.h"

// Static Variables

// Static Function Prototypes

// Implementation

Paddle::Paddle()
{

}

Paddle::~Paddle()
{

}

bool
Paddle::Initialise()
{
    VALIDATE(Entity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));

    return (true);
}

void
Paddle::Draw()
{
    Entity::Draw();
}

void
Paddle::Process(float _fDeltaTick)
{
    
	float fHalfPaddleW = static_cast<float>(m_pSprite->GetWidth() / 2.0);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		xPosition += 400.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		xPosition -= 400.0f * _fDeltaTick;
	}
	if (xPosition - fHalfPaddleW <= 0)
	{
		xPosition = fHalfPaddleW;
	}
	else if (xPosition + fHalfPaddleW >= 385)
	{
		xPosition = 385-fHalfPaddleW;
	}
	
	Entity::Process(_fDeltaTick);
}
