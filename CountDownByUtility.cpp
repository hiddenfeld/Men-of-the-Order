#pragma once

inline void countDownBy(float& _countdownOrTimeWindow, const float& _elapsedSeconds) {
	if (_countdownOrTimeWindow > 0.0f) {
		_countdownOrTimeWindow -= _elapsedSeconds;
		if (_countdownOrTimeWindow < 0.0f)
			_countdownOrTimeWindow = 0.0f;
	}
};