#pragma once

#include "GridSprite.h"

// Player class
// A GridSprite which can move around
class Player : public GridSprite
{
public:

	// Constructor
	Player(sf::Texture& _texture);

	// Game Object Functions
	bool input(const sf::Event& _event) override;

	//
	//void SetIsDead(bool isDead) { m_isDead = isDead; }
	//bool GetIsDead() { return m_isDead; }
	//


private:


};