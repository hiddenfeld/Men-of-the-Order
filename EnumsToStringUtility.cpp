#pragma once

#include <iostream>
#include <string>
#include "InteractibleDoodadType.hpp"
#include "ResourceType.hpp"

inline std::string convertInteractibleDoodadTypeToString(const InteractibleDoodadType& _idt) {
	switch (_idt) {
		case InteractibleDoodadType::Bush:
			return "Bush";
		case InteractibleDoodadType::Log:
			return "Log";
		default:
			std::cout << "ERROR in EnumsToStringUtility.cpp::convertInteractibleDoodadTypeToString on line #" << __LINE__ << ". Unknown InteractibleDoodadType." << std::endl;
			break;
	}
	return "<NULL>";
};

inline std::string convertResourceTypeToString(const ResourceType& _rt) {
	switch (_rt) {
		case ResourceType::Herbs:
			return "Herbs";
		case ResourceType::Wood:
			return "Wood";
		default:
			std::cout << "ERROR in EnumsToStringUtility.cpp::convertResourceTypeToString on line #" << __LINE__ << ". Unknown ResourceType." << std::endl;
			break;
	}
	return "<NULL>";
};