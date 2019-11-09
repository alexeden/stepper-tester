#ifndef __CONTROLS__
#define __CONTROLS__

#include "Adafruit_seesaw.h"
#include "FeatherJoyWing.h"

class Controls {
  public:
	Controls()
	  : joy(ss) {
	}

    Controls& begin() {
        joy.begin();
        return *this;
    }

    Controls& register_button_callback(featherjoywing_button_callback callback) {
        joy.registerButtonCallback(callback);
        return *this;
    }

    Controls& register_joystick_callback(featherjoywing_joystick_callback callback) {
        joy.registerJoystickCallback(callback);
        return *this;
    }

    void update() {
        joy.update();
    }

  private:
	Adafruit_seesaw ss;
	FeatherJoyWing joy;
};


#endif
