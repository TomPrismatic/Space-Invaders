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
#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"

// This include
#include "Sprite.h"

// Static Variables
HDC Sprite::sharedSpriteDC = 0;
int Sprite::refCount = 0;

// Static Function Prototypes

// Implementation

Sprite::Sprite()
: xPosition(0)
, yPosition(0)
{
    ++refCount;
}

Sprite::~Sprite()
{
    DeleteObject(sprite);
    DeleteObject(mask);

    --refCount;

    if (refCount == 0)
    {
        DeleteDC(sharedSpriteDC);
        sharedSpriteDC =  0;
    }
}

bool
Sprite::Initialise(int spriteResourceID, int maskResourceID)
{
    HINSTANCE hInstance = Game::GetInstance().GetAppInstance();

    if (!sharedSpriteDC)
    {
        sharedSpriteDC = CreateCompatibleDC(NULL);
    }

    sprite = LoadBitmap(hInstance, MAKEINTRESOURCE(spriteResourceID));
    VALIDATE(sprite);
    mask = LoadBitmap(hInstance, MAKEINTRESOURCE(maskResourceID));
    VALIDATE(mask);

    GetObject(sprite, sizeof(BITMAP), &bitmapSprite);
    GetObject(mask, sizeof(BITMAP), &bitmapMask);

    return (true);
}

void
Sprite::Draw()
{
    int width = GetWidth();
    int height = GetHeight();

    int xSize = xPosition - (width / 2);
    int ySize = yPosition - (height / 2);

    CBackBuffer* pBackBuffer = Game::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(sharedSpriteDC, mask);

    BitBlt(pBackBuffer->GetBFDC(), xSize, ySize, width, height, sharedSpriteDC, 0, 0, SRCAND);

    SelectObject(sharedSpriteDC, sprite);

    BitBlt(pBackBuffer->GetBFDC(), xSize, ySize, width, height, sharedSpriteDC, 0, 0, SRCPAINT);

    SelectObject(sharedSpriteDC, hOldObj);
}

void
Sprite::Process(float _fDeltaTick)
{

}

int
Sprite::GetWidth() const
{
    return (bitmapSprite.bmWidth);
}

int
Sprite::GetHeight() const
{
    return (bitmapSprite.bmHeight);
}

int 
Sprite::GetX() const
{
    return (xPosition);
}

int 
Sprite::GetY() const
{
    return (yPosition);
}

void 
Sprite::SetX(int xPosition)
{
    xPosition = ;
}

void 
Sprite::SetY(int yPosition)
{
    yPosition = yPosition;
}

void 
Sprite::TranslateRelative(int xPosition, int yPosition)
{
    xPosition += xPosition;
    yPosition += yPosition;
}

void 
Sprite::TranslateAbsolute(int xPosition, int yPosition)
{
    xPosition = xPosition;
    yPosition = yPosition;
}
