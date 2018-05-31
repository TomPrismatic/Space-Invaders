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

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Local Includes

// Types

// Constants

// Prototypes
class Sprite
{
    // Member Functions
public:
    Sprite();
    ~Sprite();

    bool Initialise(int resourceID, int maskResourceID);

    void Draw();
    void Process(float deltaTick);

    int GetWidth() const;
    int GetHeight() const;

    int GetX() const;
    int GetY() const;
    void SetX(int xPosition);
    void SetY(int yPosition);

    void TranslateRelative(int xPosition, int yPosition);
    void TranslateAbsolute(int xPosition, int yPosition);

protected:


private:
    Sprite(const Sprite& sprite);
    Sprite& operator= (const Sprite& sprite);

    // Member Variables
public:

protected:
    //Center handle
    int xPosition;
    int yPosition;

    HBITMAP sprite;
    HBITMAP mask;

    BITMAP bitmapSprite;
    BITMAP bitmapMask;

    static HDC sharedSpriteDC;
    static int refCount;

private:

};

#endif    // __SPRITE_H__
