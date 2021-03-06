#include "Spells/FearSpell.h"

FearSpell::FearSpell() : Spell() {
}

void FearSpell::load(const SpellData& bean, LevelMovableGameObject* mob, const sf::Vector2f& target) {
	setSpriteOffset(sf::Vector2f(-10.f, -10.f));
	const sf::Texture* tex = g_resourceManager->getTexture(bean.spritesheetPath);

	Animation* spellAnimation = new Animation();
	spellAnimation->setSpriteSheet(tex);
	spellAnimation->addFrame(sf::IntRect(0, 0, 30, 30));
	spellAnimation->addFrame(sf::IntRect(30, 0, 30, 30));

	addAnimation(GameObjectState::Idle, spellAnimation);

	// initial values
	setCurrentAnimation(getAnimation(GameObjectState::Idle), false);
	playCurrentAnimation(true);

	Spell::load(bean, mob, target);
}
