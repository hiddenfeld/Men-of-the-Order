#pragma once
#include "InteractibleDoodadType.hpp"
#include "ResourceType.hpp"

struct InteractibleDoodad {
	int position;
	InteractibleDoodadType interactibleDoodadType;
	ResourceType resourceType;
	int remainingHarvestAmount;

	InteractibleDoodad(const int&, const InteractibleDoodadType&, const int&);
	InteractibleDoodad(const int&, const InteractibleDoodadType&, const ResourceType&, const int&);
};