#include "stdafx.h"
#include "Grid.h"
#include "GridObject.h"

// Constructor
// Called when the grid is created
Grid::Grid(const int _GRID_SIZE_X, 
	const int _GRID_SIZE_Y,
	const float _CELL_WIDTH,
	const float _CELL_HEIGHT)
	: GRID_SIZE_X (_GRID_SIZE_X)
	, GRID_SIZE_Y (_GRID_SIZE_Y)
	, CELL_WIDTH(_CELL_WIDTH)
	, CELL_HEIGHT(_CELL_HEIGHT)
{
	// Set up the grid array with empty spaces for each
	// grid object
	m_GridArray = new GridObject**[GRID_SIZE_X];
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		m_GridArray[x] = new GridObject*[GRID_SIZE_Y];
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			m_GridArray[x][y] = nullptr;
		}
	}
}

// Destructor
// Called when the grid is destroyed
Grid::~Grid()
{
	// Delete the grid array
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			delete m_GridArray[x][y];
		}
		delete[] m_GridArray[x];
	}
	delete[] m_GridArray;
}

// Input - processes events each frame sent from engine
bool Grid::input(const sf::Event& _event)
{
	// We start out assuming we have not handled input

	bool handledInput = false;

	// Clear received input flags from all grid objects
	// This is used to make sure we never give input to the same object \
	// multiple times per frame - needed if our objects move mid-frame.
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			// We check for nullptr in case there is nothing in this grid slot!
			if (m_GridArray[x][y] != nullptr)
			{
				m_GridArray[x][y]->ClearReceivedInput();
			}
		}
	}

	// Pass the Input down to the grid objects
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			// We check for nullptr in case there is nothing in this grid slot!
			// We also check that this object hasn't already received input on this frame
			// this is needed for objects that move around the grid during the input phase
			if (m_GridArray[x][y] != nullptr && !m_GridArray[x][y]->HasRececeivedInput())
			{
				// We set out handledInput to true IF we handled any input 
				// just now OR if we handled input previously.
				// NOTE: The order here is vital - if we put it in reverse order, 
				// we would not bother handling input for this grid item if we had 
				// previously handled it!
				handledInput = m_GridArray[x][y]->input(_event) || handledInput;
			}
		}
	}

	// return wether or not we handled any input to the calling code
	return handledInput;
}

// Update - processes internal logic each frame
void Grid::update(const float& _dtAsSeconds)
{
	diamondsOnScreen = 0;
	// Pass the Update down to the grid objects
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			// We check for nullptr in case there is nothing in this grid slot!
			if (m_GridArray[x][y] != nullptr)
				m_GridArray[x][y]->update(_dtAsSeconds);
			if (m_GridArray[x][y] != nullptr && m_GridArray[x][y]->HasKilledPlayer) {
				PlayerStillInGrid = false; 
			}
			if (m_GridArray[x][y] != nullptr && m_GridArray[x][y]->GetType() == GridObject::Type::DIAMOND) {
				diamondsOnScreen++;
			}
			if (m_GridArray[x][y] != nullptr && m_GridArray[x][y]->ReachedNextLevel && m_GridArray[x][y]->GetType() == GridObject::Type::EXIT) {
				ReachedNextLevel = true;
			}
			else if(m_GridArray[x][y] != nullptr){
				m_GridArray[x][y]->ReachedNextLevel = false;
			}

		}
	}

}

// Draw - draws the object to the window each frame
void Grid::draw(sf::RenderWindow& _renderWindow)
{
	// Pass the Draw down to the grid objects
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			// We check for nullptr in case there is nothing in this grid slot!
			if (m_GridArray[x][y] != nullptr)
				m_GridArray[x][y]->draw(_renderWindow);
		}
	}
}

// Find the GridObject at the specific coordinates
GridObject* Grid::GetObject(int _x, int _y)
{
	// Check that the coordinates are valid
	if (   _x >= 0 && _x < GRID_SIZE_X
		&& _y >= 0 && _y < GRID_SIZE_Y)
	{
		return m_GridArray[_x][_y];
	}
	else
	{
		// An invalid set of coordinates were supplied
		// so we just return null
		return nullptr;
	}
}

// Put the given object in the grid
void Grid::SetObject(int _x, int _y, GridObject* _object, bool _deleteExisting /*= false */)
{
	// Check that the coordinates are valid
	if (_x >= 0 && _x < GRID_SIZE_X
		&& _y >= 0 && _y < GRID_SIZE_Y)
	{
		if (m_GridArray[_x][_y] != nullptr)
		{
			// There is already something in this slot!
			// If we were told to delete it, do so
			if (_deleteExisting == true)
			{
				delete m_GridArray[_x][_y];
			}
			else
			{
				// It will still be replaced if we do
				// not delete it - but the memory will still
				// be there.
				// Use this if you have copied the pointer out already
				// and don't want to delete the actual memory

			}
		}
		m_GridArray[_x][_y] = _object;
		if (_object != nullptr)
		{
			// Important: We need to also tell this object
			// where it currently is in the grid
			// so it can draw it's sprites in the right place.
			_object->SetGrid(this);
			_object->SetGridCoords(_x, _y);
		}
	}
	else
	{
		// If the coordinates are invalid
		// do nothing
	}
}

// Move an object from one place in the grid to another
void Grid::MoveObject(int _xOrigin, int _yOrigin,
	int _xNew, int _yNew,
	bool _deleteExisting /*= true*/)
{
	// Check that the coordinates are valid
	if (_xNew >= 0 && _xNew < GRID_SIZE_X
		&& _yNew >= 0 && _yNew < GRID_SIZE_Y)
	{
		// Get the object we will be moving
		GridObject* toMove = GetObject(_xOrigin, _yOrigin);

		// Remove it from its initial slot
		SetObject(_xOrigin, _yOrigin, nullptr, false);

		// Set it in its new slot
		// By default this will delete anything in that
		// slot already
		SetObject(_xNew, _yNew, toMove, _deleteExisting);
	}
}