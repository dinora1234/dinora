


#include "Arduino.h"

#define BUTTON_PIN 25
#define RED_LED_PIN 26
#define GREEN_LED_PIN 27
#define YELLOW_LED_PIN 12
#define BLUE_LED_PIN 14

const uint8_t ledPins[] = {RED_LED_PIN, GREEN_LED_PIN, YELLOW_LED_PIN, BLUE_LED_PIN};
const unsigned long DEBOUNCE_INTERVAL_MS = 30;
bool lastRawButtonState = LOW;
bool stableButtonState = LOW;
unsigned long lastDebounceTime = 0;
uint8_t pressCount = 0;

/****************************************************/
void setup(void) 
{
	Serial.begin(115200);
	pinMode(BUTTON_PIN, INPUT);
	for (uint8_t i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
		pinMode(ledPins[i], OUTPUT);
		digitalWrite(ledPins[i], LOW);
	}
}


/****************************************************/
void loop(void) 
{
	bool rawButtonState = digitalRead(BUTTON_PIN);
	if (rawButtonState != lastRawButtonState) {
		lastDebounceTime = millis();
		lastRawButtonState = rawButtonState;
	}

	if (millis() - lastDebounceTime >= DEBOUNCE_INTERVAL_MS &&
		rawButtonState != stableButtonState) {
		stableButtonState = rawButtonState;

		if (stableButtonState == HIGH) {
			pressCount = (pressCount + 1) % 5;
			Serial.print("count=");
			Serial.println(pressCount);

			for (uint8_t i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
				digitalWrite(ledPins[i], i < pressCount ? HIGH : LOW);
			}
		}
	}
}
