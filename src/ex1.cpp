


#include "Arduino.h"

#define RED_LED_PIN 26
#define GREEN_LED_PIN 27
#define YELLOW_LED_PIN 12
#define BLUE_LED_PIN 14

const uint8_t ledPins[] = {RED_LED_PIN, GREEN_LED_PIN, YELLOW_LED_PIN, BLUE_LED_PIN};
const char *ledNames[] = {"RED", "GREEN", "YELLOW", "BLUE"};
const uint8_t chaseSequence[] = {0, 1, 2, 3, 2, 1};
uint8_t stepIndex = 0;

/****************************************************/
void setup(void) 
{
    Serial.begin(115200);
    for (uint8_t i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}


/****************************************************/
void loop(void) 
{
    for (uint8_t i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
        digitalWrite(ledPins[i], LOW);
    }

    uint8_t ledIndex = chaseSequence[stepIndex];
    digitalWrite(ledPins[ledIndex], HIGH);
    Serial.print("chase=");
    Serial.println(ledNames[ledIndex]);

    delay(150);
    stepIndex = (stepIndex + 1) % (sizeof(chaseSequence) / sizeof(chaseSequence[0]));
}
