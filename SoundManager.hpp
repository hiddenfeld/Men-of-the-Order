#pragma once
#include <SFML/Audio.hpp>
#include <array>
#include "Atlas.hpp"
#include "Pythagoras.cpp"
#include "RandomIntFromZeroTo.cpp"
#include "SoundOrigin.hpp"
#include "SoundReason.hpp"

struct SoundManager {
    static sf::Vector2f* listenerCenter;
	static std::array<sf::Sound*, 20> sounds;

	static void update();
	static void playSound( const std::pair<SoundOrigin, SoundReason>&, const float& );
	static void playSound( const std::pair<SoundOrigin, SoundReason>&, const sf::Vector2f& );
	static void pauseSounds();
	static void unpauseSounds();
	static void setVolume( const float& );

private:
	static float volume;
};
