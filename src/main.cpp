#include <Adafruit_GFX.h>
#include <Adafruit_MotorShield.h>
#include <Arduino.h>
#include <SPI.h>
#include <Streaming.h>
#include "Adafruit_seesaw.h"
#include "FeatherJoyWing.h"
#include "Display.cc"

Adafruit_MotorShield motor_shield = Adafruit_MotorShield();
Adafruit_StepperMotor *stepper = motor_shield.getStepper(200, 2);
Display display = Display();
Adafruit_seesaw ss;
FeatherJoyWing joy(ss);
String display_line_1 = "";
String display_line_2 = "";

/**
 * Declarations
 */
void update_display();

void joystick_callback(int8_t x, int8_t y) {
    display
        .clearln1()
        .println1(x)
        .println1(", ")
        .println1(y);
}

void button_callback(FJBUTTON* buttons, uint8_t count) {
    // display_line_2 = "";

    // for(int i = 0; i < count; i++) {
    //     if (buttons[i].pressed) {
    //         display_line_2 += (String(buttons[i].pinId) + " ");
    //     }
    // }

    // if (display_line_2 == "") {
    //     display_line_2 = "No buttons pressed";
    // }
}


void setup() {
    display.begin();
    joy.begin();
    joy.registerJoystickCallback(joystick_callback);
    joy.registerButtonCallback(button_callback);
}

void loop() {
    joy.update();
    display.update();
}
