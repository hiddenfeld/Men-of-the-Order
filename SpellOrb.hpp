#pragma once
#include <math.h>
#include "SFML/Graphics.hpp"
#include "I_Unit.hpp"

struct SpellOrb {

	sf::Vector2f position;
	sf::Vector2f movement;
	I_Unit* target;
	bool spent{false};
	float timeToLive;

	SpellOrb(const sf::Vector2f&, const sf::Vector2f&, const float&);
	SpellOrb(const sf::Vector2f&, const sf::Vector2f&, const float&, I_Unit*);

	void update(const float&);
	void moveAlongMovementVector(const float&);
	void accelerateTowardsTarget(const float&);
};