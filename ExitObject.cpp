#include "stdafx.h"
#include "ExitObject.h"
#include "Grid.h"
#include "TextureHolder.h"

void ExitObject::update(const float& _dtAsSeconds) {

	if (m_grid->diamondsOnScreen == 0 && m_isExitOpen == false) {
		m_sprite.setTexture(TextureHolder::GetTexture("graphics/exit_open.png"));
		m_isExitOpen = true;
	}
}