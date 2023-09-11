#include "pixels.h"
#include "hslConverter.c"


sfColor randomizeColor(sfColor color) { //Change it to hsl

	//Init hsl and convert values
	HSL hsl = rgb2hsl(color.r, color.g, color.b);

	//Randomize luminance and saturation
	hsl.l *= randomBetween(0.9f, 1.10f);
	hsl.s *= randomBetween(0.9f, 1.10f);

	//Convert back to rgb
	RGB rgb = hsl2rgb(hsl.h, hsl.s, hsl.l);

	//Assign values to a new color
	sfColor newCol = sfColor_fromRGB(rgb.r, rgb.g, rgb.b);
	return newCol;
}

sfColor shadeColor(int r, int g, int b) {

	sfColor shaded;

	float random = randomBetween(0.5f, 0.75f);

	shaded.r = r * (random);
	shaded.g = g * (random);
	shaded.b = b * (random);

	return sfColor_fromRGB(shaded.r, shaded.g, shaded.b);;
}

sfColor tintColor(int r, int g, int b) {

	sfColor tinted;

	float random = randomBetween(0.5f, 0.75f);

	tinted.r = r + (255 - r) * random;
	tinted.g = g + (255 - g) * random;
	tinted.b = b + (255 - b) * random;

	return sfColor_fromRGB(tinted.r, tinted.g, tinted.b);
}