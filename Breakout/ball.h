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

#if !defined(__BALL_H__)
#define __BALL_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class Sprite;

class Ball : public Entity
{
    // Member Functions
public:
    Ball();
    virtual ~Ball();

    virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetVelocityX(float _fX);
    void SetVelocityY(float _fY);

    float GetRadius() const;

protected:

private:
    Ball(const Ball& _kr);
    Ball& operator= (const Ball& _kr);

    // Member Variables
public:

protected:
    float m_fVelocityX;
    float m_fVelocityY;

private:

};


#endif    // __BALL_H__
