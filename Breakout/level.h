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

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class Ball;
class Paddle;
class Brick;
class FPSCounter;
class Background;

class Level
{
    // Member Functions
public:
    Level();
    virtual ~Level();

    virtual bool Initialise(int width, int height);

    virtual void Draw();
    virtual void Process(float deltaTick);

    Paddle* GetPaddle() const;

    int GetBricksRemaining() const;

protected:
    void ProcessBallWallCollision();
	void ProcessPaddleWallCollison();
    void ProcessBallPaddleCollision();
    void ProcessBallBrickCollision();

    void ProcessCheckForWin();

    void ProcessBallBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

    void SetBricksRemaining(int numberOfBricksRemaining);

private:
    Level(const Level& level);
    Level& operator= (const Level& level);

    // Member Variables
public:

protected:
	Background* background;
    Ball* ball;
    Paddle* paddle;
    std::vector<Brick*> vectorOfBricks;
	FPSCounter* fpsCounter;

    int width;
    int height;

    int numberOfBricksRemaining;

    std::string scoreString;

private:

};

#endif    // __LEVEL_H__
