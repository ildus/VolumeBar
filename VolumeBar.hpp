#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H

using namespace std;

#include "LiquidCrystal_I2C.h"

class VolumeBar {
	private:
		char buf[2][17];
		const int	screen_width = 16,
					screen_height = 2; //lcd 1602

		int maxval, curval;
	public:
		VolumeBar(int max) { maxval = max; curval = 0;}

		void update(int val);
		void render(LiquidCrystal_I2C *lcd);
		void prepare_screen(LiquidCrystal_I2C *lcd);
};

#endif
