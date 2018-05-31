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

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class Brick : public Entity
{
    // Member Functions
public:
    Brick();
    virtual ~Brick();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    void SetHit(bool _b);
    bool IsHit() const;

protected:

private:
    Brick(const Brick& _kr);
    Brick& operator= (const Brick& _kr);

    // Member Variables
public:

protected:
    bool m_bHit;

private:

};


#endif    // __BRICK_H__

