#include "SoundManager.hpp"

float SoundManager::volume{ 100.0f };
sf::Vector2f* SoundManager::listenerCenter;
std::array<sf::Sound*, 20> SoundManager::sounds;

void SoundManager::update() {
	for (unsigned int i{ 0 }; i < sounds.size(); i++) {
		if (sounds.at(i) != NULL) {
			if (sounds.at(i)->getStatus() == sf::SoundSource::Status::Stopped) {
				sounds.at(i)->~Sound();
				free(sounds.at(i));
				sounds.at(i) = NULL;
			}
		}
	}
};

void SoundManager::playSound( const std::pair<SoundOrigin, SoundReason>& _pair, const float& _volumeByDistanceToPlayer ) {
	if (_pair.first != SoundOrigin::None) {
		bool freeSpotFound{ false };
		for (unsigned int i{ 0 }; i < sounds.size() && !freeSpotFound; i++) {
			if (sounds.at(i) == NULL) {
				sounds.at(i) = new sf::Sound;
				if (Atlas::bufferedSounds.at(_pair).size() > 1) {
					sounds.at(i)->setBuffer(Atlas::bufferedSounds.at(_pair).at(randomIntFromZeroTo((unsigned int)(Atlas::bufferedSounds.at(_pair).size() - 1))));
				} else {
					sounds.at(i)->setBuffer(Atlas::bufferedSounds.at(_pair).at(0));
				}
				float instanceVolume{ SoundManager::volume - ( 80.f * ( _volumeByDistanceToPlayer / 900.0f ) ) };
				if (instanceVolume < SoundManager::volume * 0.04f) {
					instanceVolume = SoundManager::volume * 0.04f;
				}
				sounds.at(i)->setVolume( instanceVolume );
				sounds.at(i)->play();
				freeSpotFound = true;
			}
		}
	}
};

void SoundManager::playSound( const std::pair<SoundOrigin, SoundReason>& _pair, const sf::Vector2f& _position ) {
    playSound( _pair, calculateDistance( *listenerCenter, _position ) );
};

void SoundManager::pauseSounds() {
	for (unsigned int i{ 0 }; i < sounds.size(); i++) {
		if (sounds.at(i) != NULL) {
			if (sounds.at(i)->Playing) {
				sounds.at(i)->pause();
			}
		}
	}
}

void SoundManager::unpauseSounds() {
	for (unsigned int i{ 0 }; i < sounds.size(); i++) {
		if (sounds.at(i) != NULL) {
			if (sounds.at(i)->Paused) {
				sounds.at(i)->play();
			}
		}
	}
};

void SoundManager::setVolume( const float& _volume ) {
	SoundManager::volume = _volume;
};
