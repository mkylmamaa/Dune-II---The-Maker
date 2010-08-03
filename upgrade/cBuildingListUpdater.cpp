/*
 * cBuildingListUpgrader.cpp
 *
 *  Created on: Aug 1, 2009
 *      Author: Stefan
 */

#include "..\d2tmh.h"

cBuildingListUpdater::cBuildingListUpdater(cPlayer *thePlayer) {
	assert(thePlayer);
	player = thePlayer;
}

void cBuildingListUpdater::updateStructureCreated(int structureType) {
	cLogger::getInstance()->logCommentLine("updateStructureCreated - begin");

	// activate/deactivate any lists if needed
	cBuildingList *list = player->getSideBar()->getList(LIST_CONSTYARD);

	int house = player->getHouse();
	int techLevel = player->getTechLevel();

	assert(list);

	if (structureType == WINDTRAP) {
		list->addItemToList(new cBuildingListItem(REFINERY, structures[REFINERY], list));
		cLogger::getInstance()->logCommentLine("updateStructureCreated - added REFINARY to list");
	}

	if (structureType == REFINERY) {
		if (techLevel >= 2) {
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added LIGHTFACTORY to list");
			list->addItemToList(new cBuildingListItem(LIGHTFACTORY, structures[LIGHTFACTORY], list));

			if (house == ATREIDES ||
				house == ORDOS ||
				house == FREMEN) {
				cLogger::getInstance()->logCommentLine("updateStructureCreated - added BARRACKS to list");
				list->addItemToList(new cBuildingListItem(BARRACKS, structures[BARRACKS], list));

				if (house == ORDOS && techLevel >= 5) {
					cLogger::getInstance()->logCommentLine("updateStructureCreated - added WOR to list");
					list->addItemToList(new cBuildingListItem(WOR, structures[WOR], list));
				}

			} else if (
					house == HARKONNEN ||
					house == SARDAUKAR ||
					house == FREMEN ||
					house == MERCENARY)
				cLogger::getInstance()->logCommentLine("updateStructureCreated - added WOR to list");
				list->addItemToList(new cBuildingListItem(WOR, structures[WOR], list));
		}

		cLogger::getInstance()->logCommentLine("updateStructureCreated - added SILO to list");
		list->addItemToList(new cBuildingListItem(SILO, structures[SILO], list));
	}

	if (techLevel >= 3) {
		cLogger::getInstance()->logCommentLine("updateStructureCreated - added OUTPOST to list");
		list->addItemToList(new cBuildingListItem(RADAR, structures[RADAR], list));
	}


	if (structureType == RADAR) {
		if (techLevel >= 5) {
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added TURRET to list");
			list->addItemToList(new cBuildingListItem(TURRET, structures[TURRET], list));
		}

		if (techLevel >= 8) {
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added PALACE to list");
			list->addItemToList(new cBuildingListItem(PALACE, structures[PALACE], list));
		}
	}

	if (structureType == LIGHTFACTORY)
	{
		if (techLevel >=4) {
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added HEAVYFACTORY to list");
			list->addItemToList(new cBuildingListItem(HEAVYFACTORY, structures[HEAVYFACTORY], list));
		}

		if (techLevel >=5) {
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added HIGHTECH to list");
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added REPAIR to list");
			list->addItemToList(new cBuildingListItem(HIGHTECH, structures[HIGHTECH], list));
			list->addItemToList(new cBuildingListItem(REPAIR, structures[REPAIR], list));
		}

		if (techLevel >= 6) {
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added STARPORT to list");
			list->addItemToList(new cBuildingListItem(STARPORT, structures[STARPORT], list));
		}

	}

	// Heavyfactory
	if (structureType == HEAVYFACTORY)
	{
		if (techLevel >= 7) {
			cLogger::getInstance()->logCommentLine("updateStructureCreated - added IX to list");
			list->addItemToList(new cBuildingListItem(IX, structures[IX], list));
		}
	}


	///////////////////////////////////
	// ADJUSTMENTS TO INFANTRY LIST
	///////////////////////////////////
	list = player->getSideBar()->getList(LIST_INFANTRY);
	if (house == ORDOS) {
		if (structureType == BARRACKS) {
			list->addItemToList(new cBuildingListItem(SOLDIER, units[SOLDIER], list));
		} else if (structureType == WOR) {
			list->addItemToList(new cBuildingListItem(TROOPER, units[TROOPER], list));
		}
	}

	// do something
	cLogger::getInstance()->logCommentLine("updateStructureCreated - end");
}

// structure destroyed..
void cBuildingListUpdater::updateStructureDestroyed(int structureType) {
	cLogger::getInstance()->logCommentLine("updateStructureDestroyed - begin");

	// do something

	cLogger::getInstance()->logCommentLine("updateStructureDestroyed - end");
}


/**
 * this method will update any list given, with phase given.
 */
void cBuildingListUpdater::updateUpgradeCompleted(cBuildingList *listToUpgrade) {
	assert(listToUpgrade);
	cLogger::getInstance()->logCommentLine("updateUpgradeCompleted - begin");

	int currentLevel = listToUpgrade->getUpgradeLevel();
	int newLevel = currentLevel++;
	// up the upgrade level
	listToUpgrade->setUpgradeLevel(newLevel);

	// constyard list upgrades two times
	if (listToUpgrade->getType() == LIST_CONSTYARD) {
		switch (newLevel) {
			case 1:
				listToUpgrade->addItemToList(new cBuildingListItem(SLAB4, structures[SLAB4], listToUpgrade));
			break;
		}
	}

	cLogger::getInstance()->logCommentLine("updateUpgradeCompleted - end");
}

//void upgradeTechTree(int iPlayer, int iStructureType) {
//
//	if (iPlayer != 0) {
//		logbook("tried to update tech tree for a non-human player");
//		return;
//	}
//
//	logbook("upgrading tech tree");
//
//	int iHouse = player[iPlayer].getHouse();
//	int iMission = game.iMission; // MISSION IS OK NOW, IS CORRECTLY SET AT LOADING
//
//
//

//}