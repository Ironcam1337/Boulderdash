#include "stdafx.h"
#include "FallingObject.h"
#include "Grid.h"

void FallingObject::update(const float& _dtAsSeconds) {

	
		GridObject* targetCellObject = m_grid->GetObject(m_gridX, m_gridY + 1);
		m_isFalling = CheckIfFalling(targetCellObject);
		int randSide = rand() % 2;
		if (randSide == 0) {
			m_chosenSide = false;
		}
		else {
			m_chosenSide = true;
		}
		
			if (m_isFalling) {
				m_framesSinceLastUpdate -= _dtAsSeconds;
				if (m_framesSinceLastUpdate <= 0) {

					if (m_type == Type::BOULDER) {
					 if ((targetCellObject != nullptr) && (targetCellObject->GetType() == Type::BOULDER || targetCellObject->GetType() == Type::DIAMOND)) {
						if (m_chosenSide) {
							m_grid->MoveObject(m_gridX, m_gridY, m_gridX + 1, m_gridY + 1, true);
						}
						else {
							m_grid->MoveObject(m_gridX, m_gridY, m_gridX - 1, m_gridY + 1, true);
						}

						m_leftSideClear = false;
						m_rightSideClear = false;
					}
					 else if (targetCellObject != nullptr && targetCellObject->GetType() == Type::PLAYER) {
						 HasKilledPlayer = true;
						 m_grid->MoveObject(m_gridX, m_gridY, m_gridX, m_gridY + 1, true);
					 }
						
					else if(targetCellObject == nullptr) {
						m_grid->MoveObject(m_gridX, m_gridY, m_gridX, m_gridY + 1, true);
					}
					}
					else if (m_type == Type::DIAMOND) {
						if (targetCellObject != nullptr && targetCellObject->GetType() == Type::PLAYER) {
							HasKilledPlayer = true;
							m_grid->SetObject(m_gridX, m_gridY, nullptr, false);
						}
						else {
							m_grid->MoveObject(m_gridX, m_gridY, m_gridX, m_gridY + 1, true);
						}
					}

				m_framesSinceLastUpdate = m_targetFramesPerUpdate;
			}

		}
	
	
}

bool FallingObject::CheckIfFalling(GridObject* targetObject) {

	if (m_type == Type::BOULDER) {
		if (m_grid->GetObject(m_gridX - 1, m_gridY) == nullptr && m_grid->GetObject(m_gridX - 1, m_gridY - 1) == nullptr) {
			m_leftSideClear = true;
		}
		if (m_grid->GetObject(m_gridX + 1, m_gridY) == nullptr && m_grid->GetObject(m_gridX + 1, m_gridY - 1) == nullptr) {
			m_rightSideClear = true;
		}
		if (m_rightSideClear || m_leftSideClear) {
			return true;
		}
	}
	if (targetObject == nullptr || targetObject->GetType() == Type::PLAYER) {
		return true;
	}
	return false;
	
}