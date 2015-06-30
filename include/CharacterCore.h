#pragma once

#include <map>

#include "global.h"
#include "ResourceManager.h"
#include "FileIO/CharacterCoreReader.h"
#include "FileIO/CharacterCoreWriter.h"
#include "Item.h"
#include "ItemFactory.h"

#include "Enums/ItemID.h"
#include "Enums/LevelEquipmentID.h"
#include "Structs/AttributeBean.h"
#include "Structs/CharacterCoreData.h"

class CharacterCore
{
public:
	CharacterCore();
	~CharacterCore();

	// returns the currently equipped item of type 'type'
	const Item& getEquippedItem(ItemType type);
	// returns the item of id "id"
	const Item& getItem(ItemID id);
	NPCState getNPCState(NPCID id);
	QuestState getQuestState(QuestID id);
	void setNPCState(NPCID id, NPCState state);
	void setQuestState(QuestID id, QuestState state);
	// loads a new game with a new core and default attributes
	void loadNew();
	// tries to create a new file with this name. if successful, returns true. if it already exists, returns false
	bool createFile(const char* fileName) const;
	// uses the character core reader to load a .sav file
	bool load(const char* fileName);
	// uses the character core writer to save a .sav file
	bool save(const char* fileName);
	// loads equipped itemvector (reload if not empty)
	void loadEquipmentItems();
	// loads itemvector (reload if not empty)
	void loadItems();
	// base attributes plus the attributes gotten by equipment
	AttributeBean* getTotalAttributes();
	// getter for items
	std::map<ItemID, int>* getItems();
	// add gold to the data
	void addGold(int gold);
	// sets health to max health
	void resetHealth();
	// save the position and map id
	void setMap(const sf::Vector2f& position, MapID map);
	// save the position and level id
	void setLevel(const sf::Vector2f& position, LevelID level);
	// getter for core part
	const CharacterCoreData& getData() const;

private:
	// clears equipped itemvector
	void clearEquippedItems();
	// clears itemvector
	void clearItems();
	// reload stats based on equipped items (called by load)
	void reloadStats();
	// adds the second bean to the first bean
	void addBean(AttributeBean& firstBean, const AttributeBean& secondBean) const;

	// base attributes plus the attributes of all currently equipped items
	AttributeBean m_totalAttributes;

	std::map<ItemID, Item> m_items;
	std::map<ItemType, Item> m_equippedItems;

	CharacterCoreData m_data;

	sf::Clock m_stopwatch; 
};