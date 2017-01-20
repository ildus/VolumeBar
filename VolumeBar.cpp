#include "VolumeBar.hpp"
#include "math.h"

static unsigned char v0[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000};
static unsigned char v1[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b11111};
static unsigned char v2[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111};
static unsigned char v3[8] = {0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b11111};
static unsigned char v4[8] = {0b00000,0b00000,0b00000,0b11111,0b11111,0b11111,0b11111};
static unsigned char v5[8] = {0b00000,0b00000,0b11111,0b11111,0b11111,0b11111,0b11111};
static unsigned char v6[8] = {0b00000,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
static unsigned char v7[8] = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};

void VolumeBar::prepare_screen(LiquidCrystal_I2C *lcd) {
	// create custom LCD characters for the volume bar
	lcd->createChar(0, v0);
	lcd->createChar(1, v1);
	lcd->createChar(2, v2);
	lcd->createChar(3, v3);
	lcd->createChar(4, v4);
	lcd->createChar(5, v5);
	lcd->createChar(6, v6);
	lcd->createChar(7, v7);
}

void VolumeBar::update(int val) {
	if ((val >= 0) && (val <= maxval)) {
		curval = val;
		snprintf(buf[0], 17, "Vol:%d  ", curval);
	}
}

void VolumeBar::render(LiquidCrystal_I2C *lcd) {
	lcd->setCursor(0, 0);
	lcd->print(buf[0]);

	int until = floor(1.0 * (screen_width - 1) / maxval  * curval);
	lcd->setCursor(0, 1);
	for (int i =  0; i < until; i++) {
		lcd->setCursor(i, 1);
		if (i <= 7) {
			lcd->write(i);
		} else {
			lcd->write(7);
			lcd->setCursor(i, 0);

			int index = i % 8 + 1;
			if (index > 7)
				index = 7;

			lcd->write(index);
		}
	}

	//clear other part
	for (int i =  until; i < (screen_width - 1); i++) {
		lcd->setCursor(i, 1);
		if (i <= 7) {
			lcd->write(' ');
		} else {
			lcd->write(' ');
			lcd->setCursor(i, 0);
			lcd->write(' ');
		}
	}
}
