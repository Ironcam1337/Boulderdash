#pragma once

#include "GridObject.h"
#include <SFML/Graphics.hpp>

// GridSprite class
// A GridObject which is drawn as a sprite 
// at it's grid location.
class GridSprite : public GridObject
{
public: 

	// Constructor
	GridSprite(sf::Texture& _texture, GridObject::Type _type);

	// Game Object Functions
	void draw(sf::RenderWindow& _renderWindow) override;

	// GridObject Functions
	virtual void SetGrid(Grid* _grid) override;
	virtual void SetGridCoords(int _x, int _y) override;

private:

	void UpdateSprite();

protected:

	sf::Sprite m_sprite;


};