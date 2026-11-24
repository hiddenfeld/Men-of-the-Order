#pragma once
#include "InteractibleDoodad.hpp"

InteractibleDoodad::InteractibleDoodad(
	const int& _position,
	const InteractibleDoodadType& _interactibleDoodadType,
	const int& _remainingHarvestAmount)
	:	position(_position),
		interactibleDoodadType(_interactibleDoodadType),
		remainingHarvestAmount(_remainingHarvestAmount)
{
	switch (interactibleDoodadType) {
		case InteractibleDoodadType::Bush:
			resourceType = ResourceType::Herbs;
			break;
		default:
		case InteractibleDoodadType::Log:
			resourceType = ResourceType::Wood;
			break;
	}
};

InteractibleDoodad::InteractibleDoodad(
	const int& _position,
	const InteractibleDoodadType& _interactibleDoodadType,
	const ResourceType& _resourceType,
	const int& _remainingHarvestAmount)
	:	position(_position),
		interactibleDoodadType(_interactibleDoodadType),
		resourceType(_resourceType),
		remainingHarvestAmount(_remainingHarvestAmount)
{

};