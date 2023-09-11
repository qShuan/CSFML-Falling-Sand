#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "SFML/Graphics.h"
#include "mapsAndConstants.h"

sfColor randomizeColor(int r, int g, int b);
sfColor tintColor(int r, int g, int b);
sfColor shadeColor(int r, int g, int b);

typedef struct pixel_t {
	int id;
	Pixel type;
	sfColor col;
	sfVector2f velocity;
	bool moved_last;
}pixel_t;

static pixel_t pixel_selected() { //Make it possible to fill the screen with selected pixel
	pixel_t p = { 0 };
	p.id = 0;
	p.type = pixel_type;
	p.col = sfColor_fromRGB(72, 72, 72);

	return p;
};

static pixel_t pixel_empty() {
	pixel_t p = { 0 };
	p.id = 0;
	p.type = AIR;
	p.col = sfColor_fromRGB(72, 72, 72);

	return p;
}

static pixel_t pixel_sand() {
	pixel_t p = { 0 };
	p.id = 1;
	p.type = SAND;
	p.col = randomizeColor(227, 197, 107);

	return p;
}

static pixel_t pixel_water() {
	pixel_t p = { 0 };
	p.id = 2;
	p.type = WATER;
	p.col = randomizeColor(96, 168, 219);

	return p;
}

static pixel_t pixel_wood() {
	pixel_t p = { 0 };
	p.id = 3;
	p.type = WOOD;
	p.col = randomizeColor(227, 197, 107);

	return p;
}

pixel_t p_Grid[W_WIDTH][W_HEIGHT];
pixel_t prev_Grid[W_WIDTH][W_HEIGHT];