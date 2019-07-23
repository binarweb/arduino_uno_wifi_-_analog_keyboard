#include "src/AnalogKeyboard/AnalogKeyboard.h"

// setari
#define KEYBOARD_ANALOG_PORT A3
#define SERIAL_BAUDRATE 115200 // fast enough

AnalogKeyboard keyboard(KEYBOARD_ANALOG_PORT);

void setup() {
	Serial.begin(SERIAL_BAUDRATE);

	// setup keyboard
	keyboard.setDebounceTime(100);

	Serial.println("!!! keyboard test");
}

void loop() {
	// uint16_t reading = analogRead(KEYBOARD_ANALOG_PORT);
	// Serial.println(reading);
	// delay(1000);

	if (keyboard.upIsPressed()) {
		Serial.println("Button UP pressed!");
	}
	if (keyboard.downIsPressed()) {
		Serial.println("Button DOWN pressed!");
	}
	if (keyboard.menuIsPressed()) {
		Serial.println("Button MENU pressed!");
	}
	if (keyboard.backIsPressed()) {
		Serial.println("Button BACK pressed!");
	}

	keyboard.run();
}