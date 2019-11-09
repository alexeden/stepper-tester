#include "Controls.cc"
#include "Display.cc"
#include <Adafruit_MotorShield.h>
#include <Arduino.h>
#include <SPI.h>
#include <Streaming.h>

Adafruit_MotorShield motor_shield = Adafruit_MotorShield();
Adafruit_StepperMotor* stepper	  = motor_shield.getStepper(200, 2);
Controls controls				  = Controls();
Display display					  = Display();

/**
 * Declarations
 */
void joystick_callback(int8_t x, int8_t y);
void button_callback(FJBUTTON* buttons, uint8_t count);

void setup() {
	display.begin();
	controls.begin().register_button_callback(button_callback).register_joystick_callback(joystick_callback);
    stepper->setSpeed(30);
}

uint32_t last_loop = micros();

void loop() {
    auto delta = micros() - last_loop;
    last_loop = micros();
	controls.update();
    display.clearln2().println2(delta);
	display.update();
}

void left_button_pressed() {
    display.clearln2().println2("Backward 200 steps").update();
    stepper->step(200, BACKWARD);
}

void right_button_pressed() {
    display.clearln2().println2("Forward 200 steps").update();
    stepper->step(200, FORWARD);
}

void up_button_pressed() {
}

void down_button_pressed() {
}

void select_button_pressed() {
}

void joystick_callback(int8_t x, int8_t y) {
	display.clearln1().println1(x).println1(", ").println1(y);
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
