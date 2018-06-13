#pragma once

#include "GridSprite.h"

class ExitObject : public GridSprite {

public:

	ExitObject(sf::Texture& _texture, GridObject::Type _type) : GridSprite(_texture, _type) { }

	void update(const float& _dtAsSeconds) override;


private:

	bool m_isExitOpen = false;

};
