#include <Arduino.h>
#include <Servo.h>

Servo servoblau;
int tasterstatus_1 = 0;
int tasterstatus_2 = 0;
int tasterstatus_plus = 0;
int tasterstatus_minus = 0;
int plus = 0;

int rechts = 0;
int links = 180;

int key_1 = 11;
int key_2 = 12;
int key_plus = 4;
int key_minus = 5;

int pos = 1;

void setup() {
	pinMode(13, OUTPUT);

	pinMode(key_1, INPUT);
	pinMode(key_2, INPUT);
	pinMode(key_plus, INPUT);
	pinMode(key_minus, INPUT);
	servoblau.attach(8);
	servoblau.write(abs(links - rechts) / 2);

	digitalWrite(13, LOW);

	Serial.begin(115200);
}

void loop() {
	delay(5);
	tasterstatus_1 = digitalRead(key_1);
	tasterstatus_2 = digitalRead(key_2);
	tasterstatus_plus = digitalRead(key_plus);
	tasterstatus_minus = digitalRead(key_minus);

	if (tasterstatus_1 == HIGH) {
		delay(5);
		if (digitalRead(key_1) == HIGH) {
			digitalWrite(13, HIGH);
			pos = 1;
			servoblau.write(rechts); //Position 1 ansteuern mit dem Winkel 0°
		}
	} else {
		if (tasterstatus_2 == HIGH) {
			delay(5);
			if (digitalRead(key_2) == HIGH) {
				digitalWrite(13, LOW);
				pos = 2;
				servoblau.write(120); //Position 1 ansteuern mit dem Winkel 0°
			}
		} else {
			if (tasterstatus_plus == HIGH) {
				delay(5);
				if (digitalRead(key_plus) == HIGH) {
					if (rechts < 180 && pos == 1) {
						++rechts;
						servoblau.write(rechts); //Position 1 ansteuern mit dem Winkel 0°
					}
					if (links < 180 && pos == 2) {
						++links;
						servoblau.write(links); //Position 1 ansteuern mit dem Winkel 0°
					}
					Serial.print(servoblau.readMicroseconds());
				}
			}

			else {
				if (tasterstatus_minus == HIGH) {
					delay(5);
					if (digitalRead(key_minus) == HIGH) {
						if (rechts > 0 && pos == 1) {
							--rechts;
							servoblau.write(rechts);
						}
						if (links > 0 && pos == 2) {
							--links;
							servoblau.write(links);
						}
						Serial.println(servoblau.readMicroseconds());
					}
				}
			}
		}
	}
}
