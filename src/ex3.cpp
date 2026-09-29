


#include "Arduino.h"

#define LIGHT_SENSOR_PIN 33

const unsigned long READ_INTERVAL_MS = 300;
unsigned long lastReadTime = 0;
bool alertActive = false;

/****************************************************/
void setup(void) 
{
	Serial.begin(115200);
}


/****************************************************/
void loop(void) 
{
	unsigned long currentTime = millis();
	if (currentTime - lastReadTime >= READ_INTERVAL_MS) {
		lastReadTime = currentTime;
		int reading = analogRead(LIGHT_SENSOR_PIN);

		if (reading > 3000 && !alertActive) {
			alertActive = true;
			Serial.println("ALERT=1");
		} else if (reading < 2500 && alertActive) {
			alertActive = false;
			Serial.println("ALERT=0");
		}
	}
}
