#include "stdafx.h"
#include "GridSprite.h"
#include "Grid.h"

// Constructor
GridSprite::GridSprite(sf::Texture& _texture, GridObject::Type _type)
	: GridObject(_type)
{
	m_sprite.setTexture(_texture);
}

// Draw the sprite - the location should already be set
// by SetGridCoords and SetGrid
void GridSprite::draw(sf::RenderWindow& _renderWindow)
{
	_renderWindow.draw(m_sprite);
}

// Set the grid and update the sprite accordingly
void GridSprite::SetGrid(Grid* _grid)
{
	// Call parent version of this function
	GridObject::SetGrid(_grid);

	UpdateSprite();
}

// Set the coordinates and update the sprite accordingly
void GridSprite::SetGridCoords(int _x, int _y)
{
	// Call parent version of this function
	GridObject::SetGridCoords(_x, _y);

	UpdateSprite();
}

// Update the position of the sprite based on the grid
void GridSprite::UpdateSprite()
{
	float x = m_gridX * m_grid->CELL_WIDTH + m_grid->GetPosition().x;
	float y = m_gridY * m_grid->CELL_HEIGHT + m_grid->GetPosition().y;
	m_sprite.setPosition(x, y);
}