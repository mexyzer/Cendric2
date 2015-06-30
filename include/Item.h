#pragma once

#include "global.h"

#include "Structs/ItemBean.h"

// An item in cendrics / a npcs / a mobs inventory
class Item 
{
public:
	Item(ItemBean& bean);

	const std::string& getDescription() const;
	const std::string& getName() const;
	ItemID getID() const;
	ItemType getType() const;
	LevelEquipmentID getLevelEquipmentID() const;
	const sf::Vector2i& getIconTextureLocation() const;
	const AttributeBean& getAttributes() const;
	// the items gold value
	int getValue() const;

private:
	ItemBean m_bean;
};