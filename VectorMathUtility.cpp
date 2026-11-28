#pragma once
#include "SFML/Graphics.hpp"
#include <math.h>

inline float calculateVectorLength(const float& _x, const float& _y) {
	return (float)std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
};

inline float calculateVectorLength(const sf::Vector2f& _vector) {
	return (float)std::sqrt(std::pow(_vector.x, 2) + std::pow(_vector.y, 2));
};

inline sf::Vector2f normalizeVector(const float& _x, const float& _y) {
	float length{calculateVectorLength(_x, _y)};
	return {_x / length, _y / length};
};

inline sf::Vector2f normalizeVector(const sf::Vector2f& _vector) {
	float length{calculateVectorLength(_vector)};
	return {_vector.x / length, _vector.y / length};
};

inline sf::Vector2f lengthenVector(const float& _x, const float& _y, const float& _length) {
	return {_x * _length, _y * _length};
};

inline sf::Vector2f lengthenVector(const sf::Vector2f& _vector, const float& _length) {
	return {_vector.x * _length, _vector.y * _length};
};