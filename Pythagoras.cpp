#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

float inline calculateDistance( const sf::Vector2f& _one, const sf::Vector2f& _two ) {
    return (float)sqrt( pow( (double)(_one.x - _two.x), 2.0 ) + pow( (double)(_one.y - _two.y), 2.0 ) );
};

float inline calculateDistance( const float& _oneX, const float& _oneY, const float& _twoX, const float& _twoY ) {
    return (float)sqrt( pow( _oneX - _twoX, 2 ) + pow( _oneY - _twoY, 2 ) );
};

float inline calculateDistance( const sf::Vector2f& _one, const sf::Vector2i& _two ) {
    return (float)sqrt( pow( _one.x - (float)_two.x, 2 ) + pow( _one.y - (float)_two.y, 2 ) );
};

float inline calculateLength( const sf::Vector2f& _vector ) {
    return (float)sqrt( pow( _vector.x, 2 ) + pow( _vector.y, 2 ) );
};

float inline calculateLength( const float& _x, const float& _y ) {
    return (float)sqrt( pow( _x, 2 ) + pow( _y, 2 ) );
};

double inline calculateLength( const double& _x, const double& _y ) {
    return sqrt( pow( _x, 2 ) + pow( _y, 2 ) );
};
