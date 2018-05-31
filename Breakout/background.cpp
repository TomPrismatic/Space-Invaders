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
#include "backbuffer.h"
#include "game.h"

// This Include
#include "background.h"

// Static Variables

// Static Function Prototypes

// Implementation

Background::Background()
{

}

Background::~Background()
{

}

bool
Background::Initialise()
{
	VALIDATE(Entity::Initialise(IDB_BACKGROUND, IDB_BACKGROUNDMASK));

	return (true);
}

void
Background::Draw()
{
	Entity::Draw();
}

void
Background::Process(float _fDeltaTick)
{
	Entity::Process(_fDeltaTick);
}
