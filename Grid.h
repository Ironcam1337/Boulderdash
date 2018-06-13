#pragma once

#include "GameObject.h"

// Forward Declarations
class GridObject;

// Grid Class
// Inherits from GameObject so we can use polymorphic calls to
// GameObject general functions
// Holds a 2 dimmensional array of GridObjects and passes GameObject
// calls down to those child objects.
class Grid : public GameObject
{

public:

	// Constructor and Destructor
	Grid(const int _GRID_SIZE_X, 
		const int _GRID_SIZE_Y,
		const float _CELL_WIDTH,
		const float _CELL_HEIGHT);
	~Grid();

	// Game Object Functions
	bool input(const sf::Event& _event) override;
	void update(const float& _dtAsSeconds) override;
	void draw(sf::RenderWindow& _renderWindow) override;

	// Grid Functions
	GridObject* GetObject(int _x, int _y);
	void SetObject(int _x, int _y, 
		GridObject* _object, 
		bool _deleteExisting = false);
	void MoveObject(int _xOrigin, int _yOrigin,
		int _xNew, int _yNew,
		bool _deleteExisting = true);
	sf::Vector2f GetPosition() { return m_GridPosition; }
	void SetPosition(sf::Vector2f _newPos) { m_GridPosition = _newPos; }

	// Const grid data members can be public
	const int GRID_SIZE_X;
	const int GRID_SIZE_Y;
	const float CELL_WIDTH;
	const float CELL_HEIGHT;

	bool PlayerStillInGrid = true;
	bool ReachedNextLevel = false;
	int diamondsOnScreen;

private:

	// 2 Dimmensional array to pointers to GridObjects
	GridObject*** m_GridArray;
	sf::Vector2f m_GridPosition;
};