#include "stdafx.h"
#include "Engine.h"
#include "GridSprite.h"
#include "Player.h"
#include "FallingObject.h"
#include "ExitObject.h"

using namespace sf;

Engine::Engine()
	: m_Grid(15,15,64.0f,64.0f) // Set your grid size here!
{
	// Get the game screen resolution
	// and creste an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Grid Based Movement Example",
		Style::Titlebar);

	// Initialise the fullscreen view
	m_MainView.reset(FloatRect(0, 0, resolution.x, resolution.y));
	m_GameOverView.reset(FloatRect(0, 0, resolution.x, resolution.y));
	m_WinView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	m_winTexture = TextureHolder::GetTexture("graphics/win.jpg");
	m_gameOverTexture = TextureHolder::GetTexture("graphics/gameover.png");

	m_winSprite.setTexture(m_winTexture);
	m_gameOverSprite.setTexture(m_gameOverTexture);

	// Set the grid position so grid is centered
	sf::Vector2f gridPosition(0,0);
	gridPosition.x = 0.5f*resolution.x -m_Grid.CELL_WIDTH  * 0.5f *(float)m_Grid.GRID_SIZE_X;
	gridPosition.y = 0.5f*resolution.y -m_Grid.CELL_HEIGHT * 0.5f *(float)m_Grid.GRID_SIZE_Y;
	m_Grid.SetPosition(gridPosition);

	// Set up the grid contents
	// NOTE: This could be done based on a file
	// similar to how Thomas Was Late levels were loaded!
	
	
	LoadLevel(m_currentLevel);
}

void Engine::run()
{
	// Timing
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		// Make a float from the delta time
		float dtAsSeconds = dt.asSeconds();

		// Call each part of the game loop in turn
		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::LoadLevel(int currentLevel) {


	switch (currentLevel) {
	case 1:
		SpawnLevel( m_levelOne);
		break;
	case 2:
		SpawnLevel(m_levelTwo);
		break;
	case 3:
		SpawnLevel(m_levelThree);
		break;

	case 4:
		SpawnLevel(m_levelFour);
		break;

	case 5:
		SpawnLevel(m_levelFive);
		break;
	
	}
	
}

void Engine::SpawnLevel(int levelToLoad[15][15]) {
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			switch (levelToLoad[x][y]) {
			case 0:

				m_Grid.SetObject(x, y, new GridSprite(TextureHolder::GetTexture("graphics/dirt.png"), GridObject::DIRT), true);
				break;
			case 1:
				m_Grid.SetObject(x, y, new FallingObject(TextureHolder::GetTexture("graphics/boulder.png"), GridObject::BOULDER), true);
				break;
			case 2:
				m_Grid.SetObject(x, y, new FallingObject(TextureHolder::GetTexture("graphics/diamond.png"), GridObject::DIAMOND), true);
				break;
			case 3:
				m_Grid.SetObject(x, y, new ExitObject(TextureHolder::GetTexture("graphics/exit_locked.png"), GridObject::EXIT), true);
				break;
			case 4:
				m_Grid.SetObject(x, y, new Player(TextureHolder::GetTexture("graphics/player_down_01.png")));

			}
		}
	}
}