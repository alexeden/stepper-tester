#include "Controls.cc"
#include "Display.cc"
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

Adafruit_MotorShield motor_shield = Adafruit_MotorShield();
Adafruit_StepperMotor* stepper	  = motor_shield.getStepper(200, 2);
Controls controls				  = Controls();
Display display					  = Display();
uint8_t step_style_index          = 0;
uint8_t STEP_STYLES [4] = { SINGLE, DOUBLE, INTERLEAVE, MICROSTEP };


/**
 * Declarations
 */
void joystick_callback(int8_t x, int8_t y);
void button_callback(FJBUTTON* buttons, uint8_t count);

void setup() {
	display.begin();
	controls.begin().register_button_callback(button_callback).register_joystick_callback(joystick_callback);
    stepper->setSpeed(60);
    stepper->release();
}

uint32_t last_loop = micros();
String step_style_name(uint8_t i) {
    switch (i) {
        case SINGLE:
            return "SINGLE";
        case DOUBLE:
            return "DOUBLE";
        case INTERLEAVE:
            return "INTERLEAVE";
        case MICROSTEP:
            return "MICROSTEP";
    }
}

void loop() {
    // display.clearln2().println2("Backward 1000 steps").update();
    // stepper->step(500, BACKWARD, SINGLE);

    // display.clearln2().println2("Done. Wait 1 second.").update();
    // delay(1000);
    auto delta = micros() - last_loop;
    last_loop = micros();
	controls.update();
    display
        .clearln1()
        .println1(step_style_name(STEP_STYLES[step_style_index]))
        .clearln2()
        .println2(delta);
	display.update();
}

void left_button_pressed() {
    display.clearln2().println2("Backward 100 steps").update();
    stepper->step(100, BACKWARD, STEP_STYLES[step_style_index]);
    stepper->release();
}

void right_button_pressed() {
    display.clearln2().println2("Forward 100 steps").update();
    stepper->step(100, FORWARD, STEP_STYLES[step_style_index]);
    stepper->release();
}

void up_button_pressed() {
    step_style_index = step_style_index >= 3
        ? 0
        : step_style_index + 1;
}

void down_button_pressed() {
    step_style_index = step_style_index <= 0
        ? 3
        : step_style_index - 1;
}

void select_button_pressed() {
}

void joystick_callback(int8_t x, int8_t y) {
	// display.clearln1().println1(x).println1(", ").println1(y);
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
