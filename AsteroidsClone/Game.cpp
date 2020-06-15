#include "pch.h"
#include "Game.h"


#include <iostream>
#include <memory>


#include "GameManager.h"
#include "InterfaceManager.h"
#include "ThreatSpawner.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
}

void Game::Cleanup( )
{
}

void Game::Update(const float elapsedSec )
{
	GameManager::GetInstance().Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	GameManager::GetInstance().Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (e.keysym.scancode == SDL_SCANCODE_I)
	{
		std::cout << "Welcome to Asteroids! Before you start playing, let's go over the controls and a couple really handy tricks!" << std::endl << std::endl << std::endl;
		std::cout << "The objective of the game is to acquire as much score as possible while not getting hit by asteroids or enemy projectiles." << std::endl << std::endl;
		std::cout << "First off, the controls: the rotation of the spaceship is controlled with the left and right arrow keys." << std::endl;
		std::cout << "Acceleration and deceleration is controlled by pressing the up and down arrow keys." << std::endl << std::endl << std::endl;
		std::cout << "The objective of the game and the simple controls might give you the impression that this will be a cake walk, but because" << std::endl;
		std::cout << "the simple controls might fool you, I'll give you a couple tips and insights: " << std::endl;
		std::cout << "	- You can have 4 shots on the screen at any one time.  This is useful for when you are blasting rocks at close range." << std::endl;
		std::cout << "	  You can pretty much drill them to dust." << std::endl;
		std::cout << "	- Your shots 'wrap around' the screen. This means any shot that goes past the edge of the screen will reappear on the" << std::endl;
		std::cout << "	  opposite side traveling the same direction. Enemies also have 'wrap around' shots." << std::endl;
		std::cout << "	- You will be rewarded with 1 extra life every time you gain 10.000 points in score." << std::endl;
	}
	
	ObjectManager::GetInstance().GetPlayer().ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	ObjectManager::GetInstance().GetPlayer().ProcessKeyUpEvent(e);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	ObjectManager::GetInstance().GetPlayer().ProcessMouseMotionEvent(e);
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	if (GameManager::GetInstance().GetGameState() == Playing)
	{
		ObjectManager::GetInstance().GetPlayer().ProcessMouseDownEvent(e);
	}
	else
	{
		InterfaceManager::GetInstance().ProcessMouseClickEvent(Vector2D<float>(static_cast<float>(e.x), static_cast<float>(800 - e.y)));
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	ObjectManager::GetInstance().GetPlayer().ProcessMouseUpEvent(e);
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
