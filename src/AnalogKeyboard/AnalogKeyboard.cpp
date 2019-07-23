#include "AnalogKeyboard.h"

AnalogKeyboard::AnalogKeyboard(uint8_t p_pin) : _analogPin(p_pin) {
	pinMode(_analogPin, INPUT);
}

bool AnalogKeyboard::upIsPressed() {
	return _buttonPressed == KEYBOARD_UP;
}

bool AnalogKeyboard::downIsPressed() {
	return _buttonPressed == KEYBOARD_DOWN;
}

bool AnalogKeyboard::menuIsPressed() {
	return _buttonPressed == KEYBOARD_MENU;
}

bool AnalogKeyboard::backIsPressed() {
	return _buttonPressed == KEYBOARD_BACK;
}

void AnalogKeyboard::setDebounceTime(uint16_t p_time) {
	_debounceTime = p_time;
}
void AnalogKeyboard::run() {
	unsigned long millisec = millis();
	uint16_t reading = analogRead(_analogPin);
	keyboardKey keyReading = KEYBOARD_NONE;

	// transform reading in button type
	if (reading > 1000) { // usually 1023
		keyReading = KEYBOARD_UP;
	} else if (reading > 750 && reading < 830) { // usually 791
		keyReading = KEYBOARD_DOWN;
	} else if (reading > 500 && reading < 600) { // usually 561
		keyReading = KEYBOARD_MENU;
	} else if (reading > 280 && reading < 380) { // usually 333
		keyReading = KEYBOARD_BACK;
	}

	// handle _buttonPressed
	_buttonPressed = KEYBOARD_NONE;

	if (keyReading != _lastState) {
		_timeNow = millisec;
	}

	if (keyReading == KEYBOARD_UP && (millisec - _timeNow) > _debounceTime) {
		if (!_ignoreReadingUp) {
			_buttonPressed = KEYBOARD_UP;
			_ignoreReadingUp = true;
		}
	} else {
		_ignoreReadingUp = false;
	}
	if (keyReading == KEYBOARD_DOWN && (millisec - _timeNow) > _debounceTime) {
		if (!_ignoreReadingDown) {
			_buttonPressed = KEYBOARD_DOWN;
			_ignoreReadingDown = true;
		}
	} else {
		_ignoreReadingDown = false;
	}
	if (keyReading == KEYBOARD_MENU && (millisec - _timeNow) > _debounceTime) {
		if (!_ignoreReadingMenu) {
			_buttonPressed = KEYBOARD_MENU;
			_ignoreReadingMenu = true;
		}
	} else {
		_ignoreReadingMenu = false;
	}
	if (keyReading == KEYBOARD_BACK && (millisec - _timeNow) > _debounceTime) {
		if (!_ignoreReadingBack) {
			_buttonPressed = KEYBOARD_BACK;
			_ignoreReadingBack = true;
		}
	} else {
		_ignoreReadingBack = false;
	}

	_lastState = keyReading;
}