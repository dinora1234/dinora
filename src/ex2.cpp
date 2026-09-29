


#include "Arduino.h"

#define LIGHT_SENSOR_PIN 33

const unsigned long SAMPLE_INTERVAL_MS = 1000;
const uint8_t SAMPLE_COUNT = 10;
unsigned long lastSampleTime = 0;

/****************************************************/
void setup(void) 
{
	Serial.begin(115200);
}


/****************************************************/
void loop(void) 
{
	unsigned long currentTime = millis();
	if (currentTime - lastSampleTime >= SAMPLE_INTERVAL_MS) {
		lastSampleTime = currentTime;

		int minimum = analogRead(LIGHT_SENSOR_PIN);
		int maximum = minimum;
		int total = minimum;

		for (uint8_t sampleIndex = 1; sampleIndex < SAMPLE_COUNT; sampleIndex++) {
			int reading = analogRead(LIGHT_SENSOR_PIN);
			if (reading < minimum) {
				minimum = reading;
			}
			if (reading > maximum) {
				maximum = reading;
			}
			total += reading;
		}

		Serial.print("min=");
		Serial.print(minimum);
		Serial.print(" max=");
		Serial.print(maximum);
		Serial.print(" avg=");
		Serial.println(total / SAMPLE_COUNT);
	}
}
