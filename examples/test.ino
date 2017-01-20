#include "LiquidCrystal_I2C.h"
#include "VolumeBar.hpp"
#include "math.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);
VolumeBar bar(32);

void setup() {
  	lcd.init();
  	lcd.backlight();
	bar.prepare_screen(&lcd);
}

void loop() {
	for (int i = 0; i < 64; i++) {
		bar.update(round(1.0 * i / 2));
		bar.render(&lcd);
		delay(25);
	}
	delay(5000);
}
