#pragma once
#include "SFML/Graphics.h"

#define RAND_MAX 0x7fff

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define PIXEL_SIZE 2

#define W_WIDTH  WINDOW_WIDTH / PIXEL_SIZE
#define W_HEIGHT  WINDOW_HEIGHT / PIXEL_SIZE

#define AIR_COLOR sfColor_fromRGB(72,72,72)
#define SAND_COLOR sfColor_fromRGB(227, 197, 107)
#define WATER_COLOR sfColor_fromRGB(96, 168, 219)
#define WOOD_COLOR sfColor_fromRGB(97, 50, 8);

//Pixel types
typedef enum Pixel { AIR, SAND, WATER, WOOD,NR_ELEMENTS } Pixel;
Pixel pixel_type;

sfColor COLOR_MAP[NR_ELEMENTS];

static void initColors() {
	COLOR_MAP[AIR] = AIR_COLOR;
	COLOR_MAP[SAND] = SAND_COLOR;
	COLOR_MAP[WATER] = WATER_COLOR;
	COLOR_MAP[WOOD] = WOOD_COLOR;
}

static const float gravity = 10.f;

static double clamp(double d, double min, double max) {
	const double t = d < min ? min : d;
	return t > max ? max : t;
}

static const float randomBetween(float from, float to)
{
	float diff = to - from;
	return (((float)rand() / RAND_MAX) * diff) + from;
}