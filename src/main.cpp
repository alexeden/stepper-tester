#include "Controls.cc"
#include "Display.cc"
#include <AccelStepper.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Streaming.h"

#define STEPPER_EN_PIN A12
#define STEPPER_PUL_PIN A11
#define STEPPER_DIR_PIN A10
#define STEPPER_CAL_SPEED 15000
#define STEPPER_CAL_TIMEOUT 30000
#define STEPPER_CAL_RANGEOUT 200000
#define STEPPER_MAX_SPEED 200000

AccelStepper stepper    = AccelStepper(AccelStepper::DRIVER, STEPPER_PUL_PIN, STEPPER_DIR_PIN);
float stepper_accel     = 1;
Controls controls	    = Controls();
Display display		    = Display();

void disableStepper() {
	digitalWrite(STEPPER_EN_PIN, LOW);
}
void enableStepper() {
	digitalWrite(STEPPER_EN_PIN, HIGH);
}
void toggleStepper() {
    digitalWrite(STEPPER_EN_PIN, !digitalRead(STEPPER_EN_PIN));
}

/**
 * Declarations
 */
void joystick_callback(int8_t x, int8_t y);
void button_callback(FJBUTTON* buttons, uint8_t count);

void setup() {
    Serial.begin(115200);
    pinMode(STEPPER_EN_PIN, OUTPUT);
    pinMode(STEPPER_PUL_PIN, OUTPUT);
    pinMode(STEPPER_DIR_PIN, OUTPUT);
    stepper.setMaxSpeed(STEPPER_MAX_SPEED);
    stepper.setAcceleration(stepper_accel);
	display.begin();
	controls.begin().register_button_callback(button_callback).register_joystick_callback(joystick_callback);
}


void loop() {
	controls.update();
    stepper.run();

    display
        .invert(stepper.isRunning())
        .clear()
        .println1("Curr ")
        .println1(stepper.currentPosition())
        .println1(", Targ ")
        .println1(stepper.targetPosition())
        .println2(stepper.speed())
        .println2(" s/s ")
        .println2(stepper_accel)
        .println2(" s/s/s ")
        .println3(digitalRead(STEPPER_EN_PIN) ? "Enabled" : "Disabled")
        .update();
}

void left_button_pressed() {
    stepper.move(-20000);
}

void right_button_pressed() {
    stepper.move(20000);
}

void up_button_pressed() {
    stepper_accel++;
    stepper.setAcceleration(stepper_accel);
}

void down_button_pressed() {
    if (stepper_accel > 1) {
        stepper_accel--;
        stepper.setAcceleration(stepper_accel);
    }
}

void select_button_pressed() {
    toggleStepper();
}

void joystick_callback(int8_t x, int8_t y) {

    // Assume zero if within range of -5 and 5
    x = x < -5 || x > 5 ? x : 0;
    float speed = x;
    stepper.setSpeed(speed);
}

void button_callback(FJBUTTON* buttons, uint8_t count) {
	for (int i = 0; i < count; i++) {
		if (buttons[i].hasChanged && buttons[i].pressed) {
			switch (buttons[i].pinId) {
				case BUTTON_RIGHT:
					right_button_pressed();
					break;
				case BUTTON_DOWN:
					down_button_pressed();
					break;
				case BUTTON_LEFT:
					left_button_pressed();
					break;
				case BUTTON_UP:
					up_button_pressed();
					break;
				case BUTTON_SEL:
					select_button_pressed();
					break;
			}
		}
	}
}
