#pragma once

#include <SFML\Graphics.hpp>

// GameObject
// A simple class to be used with polymorphic 
// functionality in a game engine.
class GameObject
{
public:
	virtual bool input(const sf::Event& _event) { return false;  }
	virtual void update(const float& _dtAsSeconds) {}
	virtual void draw(sf::RenderWindow& _renderWindow) {}
};