#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::draw()
{
	// Clears the screen to remove the last frame
	m_Window.clear(Color::Black);

	if (HasWon) {
		m_Window.setView(m_WinView);
		m_Window.draw(m_winSprite);
	}
	else {
		// switch to main view
		m_Window.setView(m_MainView);

		// draw the grid
		m_Grid.draw(m_Window);
	}

	// Displays the updated grid
	m_Window.display();
}