#pragma once
#include "SpellOrb.hpp"

SpellOrb::SpellOrb(
	const sf::Vector2f& _position,
	const sf::Vector2f& _movement,
	const float& _timeToLive)
	:	position(_position),
		movement(_movement),
		timeToLive(_timeToLive)
{
	target = NULL;
};

SpellOrb::SpellOrb(
	const sf::Vector2f& _position,
	const sf::Vector2f& _movement,
	const float& _timeToLive,
	I_Unit* _target)
	:	position(_position),
		movement(_movement),
		timeToLive(_timeToLive),
		target(_target)
{

};
	
void SpellOrb::update(const float& _seconds) {
	timeToLive -= _seconds;
	moveAlongMovementVector(_seconds);
	if (target != NULL)
		accelerateTowardsTarget(_seconds);
};

void SpellOrb::moveAlongMovementVector(const float& _seconds) {
	// move along the movement vector
	position.x += movement.x * _seconds;
	position.y += movement.y * _seconds;
};

void SpellOrb::accelerateTowardsTarget(const float& _seconds) {
	// accelerate towards the target,
	// accelerate more if the target is far away
	// accelerate less if the target is close
	float originX{position.x};
	float originY{position.y};
	float targetX{(float)(target->position)};
	float targetY{400.0f};
	float xDistance{std::abs(originX - targetX)};
	float yDistance{std::abs(originY - targetY)};
	float xAcceleration{(float)xDistance * _seconds};
	float yAcceleration{(float)yDistance * _seconds};
	movement.x += xAcceleration;
	movement.y += yAcceleration;
};