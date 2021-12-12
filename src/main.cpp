#include <Arduino.h>


#define timeout_on 1000 * 60 * 5 	// 5 минут реле включено
#define timeout_off 1000 * 60 * 10	// 10 минут реле выключено
#define RELAY_PIN 0 				// пин, управляющий реле (в релейном модуле с ESP-01 это пин 0)

unsigned long previousMillis = 0;
bool isTurnedOn;

void setup()
{
	Serial.begin(9600);
	pinMode(RELAY_PIN, OUTPUT);

	isTurnedOn = false;
	digitalWrite(RELAY_PIN, LOW);
	previousMillis = millis();
}

void loop()
{
	unsigned long currentMillis = millis();

	if (isTurnedOn)
	{
		if (currentMillis - previousMillis >= timeout_on)
		{
			previousMillis = currentMillis;
			digitalWrite(RELAY_PIN, LOW);
			Serial.write("On");
			isTurnedOn = false;
		}
	}
	else
	{
		if (currentMillis - previousMillis >= timeout_off)
		{
			previousMillis = currentMillis;
			digitalWrite(RELAY_PIN, HIGH);
			Serial.write("Off");
			isTurnedOn = true;
		}
	}
}