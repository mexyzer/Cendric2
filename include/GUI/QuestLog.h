#pragma once

#include "global.h"
#include "CharacterCore.h"
#include "InputController.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Structs/QuestData.h"
#include "GUI/QuestDescriptionWindow.h"
#include "GUI/Button.h"
#include "GUI/TabBar.h"
#include "GUI/SlicedSprite.h"
#include "Enums/EnumNames.h"

class QuestDescriptionWindow;
class ScrollBar;
class ScrollHelper;

// a quest entry in the quest log
class QuestEntry final : public GameObject {
public:
	QuestEntry(const std::string& questID, bool isMainQuest);

	void render(sf::RenderTarget& renderTarget) override;
	void update(const sf::Time& frameTime) override;
	GameObjectType getConfiguredType() const override;
	void setPosition(const sf::Vector2f& pos) override;
	void onLeftJustPressed() override;
	void onMouseOver() override;
	void select();
	void deselect();
	bool isClicked();
	bool isSelected() const;
	const std::string& getQuestID() const;

private:
	bool m_isSelected = false;
	bool m_isClicked = false;
	bool m_isMouseover = false;
	bool m_isMainQuest;
	BitmapText m_name;

	std::string m_questID;
};

// the quest log, as displayed in a level or a map
// it takes its information directly from the character core
class QuestLog final {
public:
	QuestLog(CharacterCore* core);
	~QuestLog();

	void show();
	void hide();

	bool isVisible() const;

	void render(sf::RenderTarget& target);
	void update(const sf::Time& frameTime);

	// reloads the quests, depending on the core
	void reload();

public:
	static const int MAX_ENTRY_LENGTH_CHARACTERS;

	static const float TOP;
	static const float LEFT;
	static const float WIDTH;

private:
	CharacterCore* m_core;

	bool m_isVisible = false;

	void init();
	void clearAllEntries();
	void calculateEntryPositions();

	Window* m_window;
	
	BitmapText m_title;
	BitmapText m_emptyText;

	TabBar* m_tabBar;

	SlicedSprite m_scrollWindow;
	ScrollBar* m_scrollBar = nullptr;
	ScrollHelper *m_scrollHelper = nullptr;

	std::vector<QuestEntry> m_startedQuests;
	std::vector<QuestEntry> m_completedQuests;
	std::vector<QuestEntry> m_failedQuests;

	QuestState m_currentTab;
	QuestEntry* m_selectedEntry = nullptr;
	std::string m_selectedQuestID = "";

	void selectTab(QuestState state);
	void selectEntry(QuestEntry* selectedEntry);

	QuestDescriptionWindow* m_descriptionWindow = nullptr;
	void showDescription(const std::string& questID);
	void hideDescription();

	std::map<QuestState, std::vector<QuestEntry>*> m_stateMap;

	static const int ENTRY_COUNT;
	static const float MAX_ENTRY_LENGTH;

	static const float WINDOW_MARGIN;

	static const sf::Vector2f BUTTON_SIZE;

	static const float SCROLL_WINDOW_LEFT;
	static const float SCROLL_WINDOW_TOP;
	static const float SCROLL_WINDOW_WIDTH;
	static const float SCROLL_WINDOW_HEIGHT;
};