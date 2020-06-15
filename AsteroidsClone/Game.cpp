#include "pch.h"
#include "Game.h"

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
		InterfaceManager::GetInstance().ProcessMouseClickEvent(Vector2D<float>(e.x, 800 - e.y));
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
