#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "SFML/Graphics.h"
#include "mapsAndConstants.h"

sfColor randomizeColor(sfColor color);
sfColor tintColor(int r, int g, int b);
sfColor shadeColor(int r, int g, int b);

typedef struct pixel_t {
	Pixel type;
	sfColor col;
	sfVector2f velocity;
	bool moved_last;
}pixel_t;


//Individual pixels
static pixel_t pixel_empty() {
	pixel_t p = { 0 };
	p.type = AIR;
	p.col = COLOR_MAP[AIR];

	return p;
}

static pixel_t pixel_sand() {
	pixel_t p = { 0 };
	p.type = SAND;
	p.col = randomizeColor(COLOR_MAP[SAND]);

	return p;
}

static pixel_t pixel_water() {
	pixel_t p = { 0 };
	p.type = WATER;
	p.col = randomizeColor(COLOR_MAP[WATER]);

	return p;
}

static pixel_t pixel_wood() {
	pixel_t p = { 0 };
	p.type = WOOD;
	p.col = randomizeColor(COLOR_MAP[WOOD]);

	return p;
}

static pixel_t pixel_current(Pixel p_type) { //Make it possible to fill the screen with selected pixel - works for some reason?

	switch (p_type) {
	case AIR:
		return pixel_empty();
		break;
	case SAND:
		return pixel_sand();
		break;
	case WATER:
		return pixel_water();
		break;
	case WOOD:
		return pixel_wood();
		break;
	}
};

pixel_t p_Grid[W_WIDTH][W_HEIGHT];
//pixel_t prev_Grid[W_WIDTH][W_HEIGHT]; why does not using this in here works and in the cpp version doesn't?