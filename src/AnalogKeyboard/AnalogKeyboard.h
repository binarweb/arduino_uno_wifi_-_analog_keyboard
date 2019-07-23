#ifndef ANALOG_KEYBOARD_H
#define ANALOG_KEYBOARD_H

#include <Arduino.h>

#define BUTTON_DEBOUNCE_TIME  300 // in milliseconds

enum keyboardKey {
	KEYBOARD_NONE,
	KEYBOARD_UP,
	KEYBOARD_DOWN,
	KEYBOARD_MENU,
	KEYBOARD_BACK
};

class AnalogKeyboard {
public:
	AnalogKeyboard(uint8_t p_pin);
	void run();
	bool upIsPressed();
	bool downIsPressed();
	bool menuIsPressed();
	bool backIsPressed();
	void setDebounceTime(uint16_t p_time);
private:
	uint8_t _analogPin;
	uint16_t _debounceTime = BUTTON_DEBOUNCE_TIME;
	keyboardKey _buttonPressed = KEYBOARD_NONE;
	keyboardKey _lastState = KEYBOARD_NONE;
	unsigned long _timeNow = 0;
	bool _ignoreReadingUp = false; // to trigger button pressed event only once (until it gets released)
	bool _ignoreReadingDown = false; // to trigger button pressed event only once (until it gets released)
	bool _ignoreReadingMenu = false; // to trigger button pressed event only once (until it gets released)
	bool _ignoreReadingBack = false; // to trigger button pressed event only once (until it gets released)
};

#endif