#include "stdafx.h"
#include "Engine.h"
#include <SFML\Graphics.hpp>
#include "sstream"

using namespace sf;

void Engine::update(float dtAsSeconds)
{

	// Update the grid
	m_Grid.update(dtAsSeconds);

	if (!m_Grid.PlayerStillInGrid) {
		m_Grid.PlayerStillInGrid = true;
		LoadLevel(m_currentLevel);
	}
	if (m_Grid.ReachedNextLevel) {
		m_currentLevel++;
		if(m_currentLevel < 6)
			LoadLevel(m_currentLevel);
		else
		{
			HasWon = true;
		}
		m_Grid.ReachedNextLevel = false;
	}

} // end function update()