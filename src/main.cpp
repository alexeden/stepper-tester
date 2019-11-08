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
String display_line_1 = "";
String display_line_2 = "";

/**
 * Declarations
 */
void update_display();

void joystickCallback(int8_t x, int8_t y) {
    display_line_1 = String(x) + ", " + String(y);
}

void buttonCallback(FJBUTTON* buttons, uint8_t count) {
    display_line_2 = "";

    for(int i = 0; i < count; i++) {
        if (buttons[i].pressed) {
            display_line_2 += (String(buttons[i].pinId) + " ");
        }
    }

    if (display_line_2 == "") {
        display_line_2 = "No buttons pressed";
    }
}


void setup() {
	display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display->setTextSize(1);
	display->setTextColor(WHITE);
    display->invertDisplay(true);
    joy.begin();
    joy.registerJoystickCallback(joystickCallback);
    joy.registerButtonCallback(buttonCallback);
}

void loop() {
    joy.update();
    update_display();
    // delay(10);
}

void update_display() {
	display->clearDisplay();
    display->setCursor(5, 5);
    display->println(display_line_1);
    display->setCursor(5, display->height() / 2 + 5);
    display->println(display_line_2);
    display->display();
}
