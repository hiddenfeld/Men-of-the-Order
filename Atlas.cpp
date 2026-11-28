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
	localSounds.clear();
	buffer.loadFromFile("sounds/heal1.ogg");
	localSounds.push_back(buffer);
	buffer.loadFromFile("sounds/heal2.ogg");
	localSounds.push_back(buffer);
	buffer.loadFromFile("sounds/heal3.ogg");
	localSounds.push_back(buffer);
	bufferedSounds.insert({{SoundOrigin::SpellOrb, SoundReason::Heal	}, localSounds});
	localSounds.clear();
	buffer.loadFromFile("sounds/spellCast1.ogg");
	localSounds.push_back(buffer);
	bufferedSounds.insert({{SoundOrigin::SpellOrb, SoundReason::Spawn	}, localSounds});
	localSounds.clear();
	buffer.loadFromFile("sounds/hitDirt1.ogg");
	localSounds.push_back(buffer);
	buffer.loadFromFile("sounds/hitDirt2.ogg");
	localSounds.push_back(buffer);
	bufferedSounds.insert({{SoundOrigin::SpellOrb, SoundReason::Hurt	}, localSounds});
};

bool Atlas::rollChanceToSucceed(const int& _chanceToSucceed) {
	if (_chanceToSucceed >= 100)
		return true;
	if (_chanceToSucceed <=   0)
		return false;
	return _chanceToSucceed >= 1 + randomIntFromZeroTo(99);
};

bool Atlas::rollChanceToImprove(const int& _chanceToSucceed) {
	if (_chanceToSucceed >= 100)
		return false;
	if (_chanceToSucceed <=   0)
		return true;
	return calculateChanceToImprove(_chanceToSucceed) >= 1 + randomIntFromZeroTo(9999);
};

/*
 Returns the chance to improve at a skill.
 
 Input parameter: const int& _chanceToSucceed
 Return value: The chance to improve as an integer * 100
			   So 100%  is returned as 10000
			   and 13% are returned as  1300
*/
int Atlas::calculateChanceToImprove(const int& _chanceToSucceed) {
	return (int)std::pow(100 - _chanceToSucceed, 2);
};