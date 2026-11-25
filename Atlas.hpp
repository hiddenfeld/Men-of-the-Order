#pragma once
#include <map>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SoundOrigin.hpp"
#include "SoundReason.hpp"
#include "SpriteName.hpp"

using sf::IntRect;

struct Atlas {
	static bool loaded;
	static std::map<SpriteName, IntRect> spriteBounds;
	static std::map<std::pair<SoundOrigin, SoundReason>, std::vector<sf::SoundBuffer>> bufferedSounds;

	static void load();
	static int calculateChanceToImprove(const int&);
};