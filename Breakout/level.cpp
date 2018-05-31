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
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

Level::Level()
: numberOfBricksRemaining(0)
, paddle(0)
, ball(0)
, width(0)
, height(0)
, fpsCounter(0)
{

}

Level::~Level()
{
    while (vectorOfBricks.size() > 0)
    {
        Brick* brick = vectorOfBricks[vectorOfBricks.size() - 1];

        vectorOfBricks.pop_back();

        delete brick;
    }

    delete paddle;
    paddle = 0;

    delete ball;
    ball = 0;

	delete fpsCounter;
	fpsCounter = 0;

	delete background;
	background = 0;

}

bool
Level::Initialise(int width, int height)
{
    width = width;
    height = height;

    const float xVelocity = 200.0f;
    const float yVelocity = 75.0f;

	background = new Background();
	VALIDATE(background->Initialise());
	//Set the background position to start from {0,0}
	background->SetX((float)width / 2);
	background->SetY((float)height / 2);

	ball = new Ball();
    VALIDATE(ball->Initialise(width / 2.0f, height / 2.0f, xVelocity, yVelocity));

    paddle = new Paddle();
    VALIDATE(paddle->Initialise());

    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    paddle->SetX(width / 2.0f);
    paddle->SetY(height - ( 1.5f * paddle->GetHeight()));

    const int numberOfBricks = 36;
    const int startX = 20;
    const int gapBetweenBricks = 5;

    int currentX = startX;
    int currentY = startX;

    for (int i = 0; i < numberOfBricks; ++i)
    {
        Brick* brick = new Brick();
        VALIDATE(brick->Initialise());

        brick->SetX(static_cast<float>(currentX));
        brick->SetY(static_cast<float>(currentY));

        currentX += static_cast<int>(brick->GetWidth()) + gapBetweenBricks;

        if (currentX > width)
        {
            currentX = startX;
            currentY += 20;
        }

        vectorOfBricks.push_back(brick);
    }

    SetBricksRemaining(numberOfBricks);
	fpsCounter = new FPSCounter();
	VALIDATE(fpsCounter->Initialise());

    return (true);
}

void
Level::Draw()
{
	background->Draw();
	for (unsigned int i = 0; i < vectorOfBricks.size(); ++i)
    {
        vectorOfBricks[i]->Draw();
    }

    paddle->Draw();
    ball->Draw();

    DrawScore();
	DrawFPS();
}

void
Level::Process(float _fDeltaTick)
{
	background->Process(_fDeltaTick);
	ball->Process(_fDeltaTick);
	paddle->Process(_fDeltaTick);
	ProcessBallWallCollision();
	//ProcessPaddleWallCollison();
    ProcessBallPaddleCollision();
    ProcessBallBrickCollision();

    ProcessCheckForWin();
	ProcessBallBounds();

    for (unsigned int i = 0; i < vectorOfBricks.size(); ++i)
    {
        vectorOfBricks[i]->Process(_fDeltaTick);
    }
	
   
    
	fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

Paddle* 
Level::GetPaddle() const
{
    return (paddle);
}

void 
Level::ProcessBallWallCollision()
{
    float ballX = ball->GetX();
    float ballY = ball->GetY();
    float ballW = ball->GetWidth();
    float ballH = ball->GetHeight();

    float halfBallW = ballW / 2;
	float halfBallH = ballH / 2;

    if (ballX < halfBallW) //represents the situation when the ball has hit the left wall
    {
        ball->SetVelocityX(ball->GetVelocityX() * -1); //reverse the ball's x velocity
    }
    else if (ballX > width - halfBallW) //represents the situation when the ball has hit the right wall
    {
        ball->SetVelocityX(ball->GetVelocityX() * -1); //reverse the ball's x velocity direction
    }

	if (ballY < halfBallH) //represents the situation when the ball has hit the top wall
    {
        ball->SetVelocityY(ball->GetVelocityY() * -1); //reverse the ball's y velocity
    }

#ifdef CHEAT_BOUNCE_ON_BACK_WALL
	if (ballY  > height - halfBallH)  //represents the situation when the ball has hit the bottom wall
    {
        ball->SetVelocityY(ball->GetVelocityY() * -1); //reverse the ball's y velocity
    }
#endif //CHEAT_BOUNCE_ON_BACK_WALL
}




void
Level::ProcessBallPaddleCollision()
{
    float ballRadius = ball->GetRadius();

    float ballX = ball->GetX();
    float ballY = ball->GetY(); 

    float paddleX = paddle->GetX();
    float paddleY = paddle->GetY();

    float paddleHeight = paddle->GetHeight();
    float paddleWidth = paddle->GetWidth();

    if ((ballX + ballRadius > paddleX - paddleWidth / 2) && //ball.right > paddle.left
        (ballX - ballRadius < paddleX + paddleWidth / 2) && //ball.left < paddle.right
        (ballY + ballRadius > paddleY - paddleHeight / 2) && //ball.bottom > paddle.top
        (ballY - ballRadius < paddleY + paddleHeight / 2))  //ball.top < paddle.bottom
    {
        ball->SetY((paddleY - paddleHeight / 2) - ballRadius);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
        ball->SetVelocityY(ball->GetVelocityY() * -1); //Reverse ball's Y direction
    }
}

void
Level::ProcessBallBrickCollision()
{
    for (unsigned int i = 0; i < vectorOfBricks.size(); ++i)
    {
        if (!vectorOfBricks[i]->IsHit())
        {
            float ballRadius = ball->GetRadius();

            float ballX = ball->GetX();
            float ballY = ball->GetY(); 

            float brickX = vectorOfBricks[i]->GetX();
            float brickY = vectorOfBricks[i]->GetY();

            float brickHeight = vectorOfBricks[i]->GetHeight();
            float brickWidth = vectorOfBricks[i]->GetWidth();

            if ((ballX + ballRadius > brickX - brickWidth / 2) &&
                (ballX - ballRadius < brickX + brickWidth / 2) &&
                (ballY + ballRadius > brickY - brickHeight / 2) &&
                (ballY - ballRadius < brickY + brickHeight / 2))
            {
                //Hit the front side of the brick...
                ball->SetY((brickY + brickHeight / 2.0f) + ballRadius);
                ball->SetVelocityY(ball->GetVelocityY() * -1);
                vectorOfBricks[i]->SetHit(true);

                SetBricksRemaining(GetBricksRemaining() - 1);
            }
        }
    }
}

void
Level::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < vectorOfBricks.size(); ++i)
    {
        if (!vectorOfBricks[i]->IsHit())
        {
            return;
        }
    }

    Game::GetInstance().GameOverWon();
}

void
Level::ProcessBallBounds()
{
	if (ball->GetX() < 0)
    {
        ball->SetX(0);
    }
	else if (ball->GetX() > width)
    {
        ball->SetX(static_cast<float>(width));
    }

    if (ball->GetY() < 0)
    {
        ball->SetY(0.0f);
    }
    else if (ball->GetY() > height)
    {
        Game::GetInstance().GameOverLost();
        //m_pBall->SetY(static_cast<float>(m_iHeight));
    }
}

int 
Level::GetBricksRemaining() const
{
    return (numberOfBricksRemaining);
}

void 
Level::SetBricksRemaining(int numberOfBricksRemaining)
{
    numberOfBricksRemaining = numberOfBricksRemaining;
    UpdateScoreText();
}

void
Level::DrawScore()
{
    HDC hdc = Game::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = height - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, scoreString.c_str(), static_cast<int>(scoreString.size()));
}



void 
Level::UpdateScoreText()
{
    scoreString = "Bricks Remaining: ";

    scoreString += ToString(GetBricksRemaining());
}


void 
Level::DrawFPS()
{
	HDC hdc = Game::GetInstance().GetBackBuffer()->GetBFDC(); 

	fpsCounter->DrawFPSText(hdc, width, height);

}
