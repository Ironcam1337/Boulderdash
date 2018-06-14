#pragma once

#include "GridSprite.h"

// Player class
// A GridSprite which the player can move around as
class Player : public GridSprite
{
public:

	// Constructor
	Player(sf::Texture& _texture);

	// Game Object Functions
	bool input(const sf::Event& _event) override;

private:


};