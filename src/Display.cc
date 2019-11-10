#ifndef __DISPLAY__
#define __DISPLAY__

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

class Display {
  public:
	Display()
	  : line1("")
	  , line2("")
	  , line3("") {
		display = new Adafruit_SSD1306(128, 32, &Wire);
	}

	void begin() {
		display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
		display->setTextSize(1);
		display->setTextColor(WHITE);
	}

	Display& invert(bool invert) {
		display->invertDisplay(invert);
        return *this;
    }

	Display& update() {
		display->clearDisplay();
		display->setCursor(0, 0);
		display->println(line1);
		display->setCursor(0, display->height() / 3);
		display->println(line2);
		display->setCursor(0, 2 * display->height() / 3);
		display->println(line3);
		display->display();
        return *this;
	}

	Display& clear() {
        clearln1();
        clearln2();
        clearln3();
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

	Display& clearln3() {
		line3 = "";
		return *this;
	}

	template<class T>
	Display& println3(T line) {
		line3 += String(line);
		return *this;
	}

  private:
	String line1;
	String line2;
	String line3;

	Adafruit_SSD1306* display;
};

#endif
