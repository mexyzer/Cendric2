#include "Spells/DivineShieldSpell.h"
#include "GameObjectComponents/LightComponent.h"
#include "Screens/LevelScreen.h"

DivineShieldSpell::DivineShieldSpell(const AttributeData& additionalResistance) : Spell() {
	m_additionalResistance = additionalResistance;
}

void DivineShieldSpell::load(const SpellData& bean, LevelMovableGameObject* mob, const sf::Vector2f& target) {
	setSpriteOffset(sf::Vector2f(-12.f, -12.f));
	const sf::Texture* tex = g_resourceManager->getTexture(bean.spritesheetPath);

	Animation* spellAnimation = new Animation();
	spellAnimation->setSpriteSheet(tex);

	for (int i = 0; i < 8; i++) {
		spellAnimation->addFrame(sf::IntRect(i * 120, 0, 120, 120));
	}

	for (int i = 7; i > -1; i--) {
		spellAnimation->addFrame(sf::IntRect(i * 120, 0, 120, 120));
	}

	addAnimation(GameObjectState::Idle, spellAnimation);

	// initial values
	setCurrentAnimation(getAnimation(GameObjectState::Idle), false);
	playCurrentAnimation(true);

	Spell::load(bean, mob, target);
	m_mob->addAttributes(m_data.duration, m_additionalResistance);
	m_mob->addHeal(getHeal(), false, isCritical());

	LightData lightData(sf::Vector2f(getBoundingBox()->width * 0.5f, getBoundingBox()->height * 0.5f), sf::Vector2f(100.f, 150.f), 0.2f);
	addComponent(new LightComponent(lightData, this));
}

void DivineShieldSpell::update(const sf::Time& frameTime) {
	sf::Vector2f nextPosition;
	calculatePositionAccordingToMob(nextPosition, m_mob);
	setPosition(nextPosition);

	MovableGameObject::update(frameTime);
	updateTime(m_data.activeDuration, frameTime);

	if (m_data.activeDuration.asMilliseconds() <= 0) {
		setDisposed();
	}
}

bool DivineShieldSpell::getConfiguredRotateSprite() const {
	return false;
}

void DivineShieldSpell::execOnHit(LevelMovableGameObject* target) {
	// nop
}

void DivineShieldSpell::setDisposed() {
	Spell::setDisposed();
	if (m_mob->getConfiguredType() == GameObjectType::_LevelMainCharacter) {
		dynamic_cast<LevelScreen*>(m_screen)->removeTypedBuffs(SpellID::DivineShield);
	}
}