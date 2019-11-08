#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Streaming.h>
#include "Adafruit_seesaw.h"
#include "FeatherJoyWing.h"

Adafruit_SSD1306 *display = new Adafruit_SSD1306(128, 32, &Wire);
Adafruit_seesaw ss;
FeatherJoyWing joy(ss);

/**
 * Declarations
 */
template <class T>
T println(T str);

void setup() {
    Serial.begin(115200);
	display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display->setTextSize(1);
	display->setTextColor(WHITE);
    joy.begin();
}

void loop() {
    joy.update();
    delay(1000);
}


template <class T>
T println(T value) {
	display->clearDisplay();
	display->setCursor(0, 0);
	display->println(value);
	display->display();
	return value;
}
