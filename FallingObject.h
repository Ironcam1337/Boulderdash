#pragma once

#include "GridSprite.h"
#include <ctime>

class FallingObject : public GridSprite {

public:

	FallingObject(sf::Texture& _texture, GridObject::Type _type) : GridSprite(_texture, _type) { srand(time(0)); }
	
	void update(const float& _dtAsSeconds) override;

	bool GetKilledPlayer() { return m_killedPlayer; }

private:

	int m_framesSinceLastUpdate = 1000;
	int m_targetFramesPerUpdate = 1000;
	bool m_isFalling = false;
	bool m_killedPlayer = false;

	bool m_leftSideClear = false;
	bool m_rightSideClear = false;
	//false = fall left, true = fall right
	bool m_chosenSide;


	bool CheckIfFalling(GridObject* targetObject);

};