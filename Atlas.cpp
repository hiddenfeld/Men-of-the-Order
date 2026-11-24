#include "Atlas.hpp"

bool Atlas::loaded{false};
std::map<SpriteName, IntRect> Atlas::spriteBounds;
std::map<std::pair<SoundOrigin, SoundReason>, std::vector<sf::SoundBuffer>> Atlas::bufferedSounds;

void Atlas::load() {
	if (loaded) {
		return;
	}
	loaded = true;
	spriteBounds.insert({SpriteName::Bush			   , {0, 0,  270,  290}});
	spriteBounds.insert({SpriteName::DirtRoadInTheWoods, {0, 0, 1175, 1689}});
	spriteBounds.insert({SpriteName::Goblin			   , {0, 0,  160,  220}});
	spriteBounds.insert({SpriteName::Knight            , {0, 0,  260,  295}});
	spriteBounds.insert({SpriteName::Log			   , {0, 0,  360,  180}});
	spriteBounds.insert({SpriteName::Squire            , {0, 0,  260,  295}});
	spriteBounds.insert({SpriteName::Tree              , {0, 0,  476,  449}});

	std::vector<sf::SoundBuffer> localSounds;
	sf::SoundBuffer buffer;
	buffer.loadFromFile("sounds/humanHurt1.ogg");
	localSounds.push_back(buffer);
	buffer.loadFromFile("sounds/humanHurt2.ogg");
	localSounds.push_back(buffer);
	buffer.loadFromFile("sounds/humanHurt3.ogg");
	localSounds.push_back(buffer);
	bufferedSounds.insert({{SoundOrigin::Knight, SoundReason::Hurt		}, localSounds});
	localSounds.clear();
	buffer.loadFromFile("sounds/metalHit1.ogg");
	localSounds.push_back(buffer);
	buffer.loadFromFile("sounds/metalHit2.ogg");
	localSounds.push_back(buffer);
	buffer.loadFromFile("sounds/metalHit3.ogg");
	localSounds.push_back(buffer);
	bufferedSounds.insert({{SoundOrigin::Knight, SoundReason::Block		}, localSounds});
};