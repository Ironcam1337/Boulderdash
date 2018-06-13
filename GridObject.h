#pragma once

#include "GameObject.h"

// Forward Declaration
class Grid;

// GridObject class
// A GameObject that can be arranged in a grid
// Each grid slot can only have one GridObject in it at
// a time.
// You could expand this to create "Cell" style GridObjects
// that could have vectors of GameObjects in each one!
class GridObject : public GameObject
{

public:

	enum Type { PLAYER, DIAMOND, BOULDER, DIRT, EXIT };

	GridObject(Type _type) : m_type(_type) { }

	// GridObject Functions
	virtual void SetGrid(Grid* _grid) { m_grid = _grid; }
	virtual void SetGridCoords(int _x, int _y) { m_gridX = _x; m_gridY = _y; }

	// Grid Types set by child classes
	void SetType(Type _newType) { m_type = _newType; }
	Type GetType() { return m_type; }

	void ClearReceivedInput() { m_receivedInput = false; }
	bool HasRececeivedInput() { return m_receivedInput; }
	bool HasKilledPlayer = false;
	bool ReachedNextLevel = false;

protected:

	bool m_receivedInput;
	Grid* m_grid;
	int m_gridX;
	int m_gridY;
	Type m_type;
	
};