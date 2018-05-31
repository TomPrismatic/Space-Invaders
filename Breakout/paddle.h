//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__PADDLE_H__)
#define __PADDLE_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes
class Paddle : public Entity
{
    // Member Functions
public:
    Paddle();
    virtual ~Paddle();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float deltaTick);


protected:

private:
    Paddle(const Paddle& level);
    Paddle& operator= (const Paddle& level);

    // Member Variables
public:

protected:

private:

};

#endif    // __PADDLE_H__
