#ifndef __DISPLAY__
#define __DISPLAY__

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

class Display {
  public:
	Display()
	  : line1("")
	  , line2("") {
		display = new Adafruit_SSD1306(128, 32, &Wire);
	}

	void begin() {
		display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
		display->setTextSize(1);
		display->setTextColor(WHITE);
		display->invertDisplay(true);
	}

	Display& update() {
		display->clearDisplay();
		display->setCursor(5, 5);
		display->println(line1);
		display->setCursor(5, display->height() / 2 + 5);
		display->println(line2);
		display->display();
        return *this;
	}

	Display& clearln1() {
		line1 = "";
		return *this;
	}

	template<class T>
	Display& println1(T line) {
		line1 += String(line);
		return *this;
	}

	Display& clearln2() {
		line2 = "";
		return *this;
	}

	template<class T>
	Display& println2(T line) {
		line2 += String(line);
		return *this;
	}

  private:
	String line1;
	String line2;

	Adafruit_SSD1306* display;
};

#endif
