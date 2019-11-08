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


void joystickCallback(int8_t x, int8_t y) {
    println(x);
}

void buttonCallback(FJBUTTON* buttons, uint8_t count) {
    // for(int i = 0; i < count; i++)
    // {
    //     Serial.print(buttons[i].pinId);
    //     Serial.print(": ");
    //     Serial.print(buttons[i].pressed);
    //     Serial.print(" - ");
    //     Serial.print(buttons[i].hasChanged);
    //     Serial.print(" | ");
    // }

    // Serial.println("");
}


void setup() {
    // Serial.begin(115200);
    // while (!Serial);
	display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display->setTextSize(1);
	display->setTextColor(WHITE);
    joy.begin();
    joy.registerJoystickCallback(joystickCallback);
    joy.registerButtonCallback(buttonCallback);
}

auto i = 0;

void loop() {
    joy.update();
    delay(100);
}


template <class T>
T println(T value) {
	display->clearDisplay();
	display->setCursor(0, 0);
	display->println(value);
	display->display();
	return value;
}
