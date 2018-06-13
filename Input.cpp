#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		m_Grid.input(event);

		if (event.type == Event::KeyPressed)
		{
			// Handle quit
			if (event.key.code == Keyboard::Escape)
			{
				m_Window.close();
			}
		}
	}
}