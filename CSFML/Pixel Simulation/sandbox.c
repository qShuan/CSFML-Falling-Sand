#include "sandbox.h"
#include "hslConverter.c"


//Is it
bool isEmpty(int x, int y) {
	if (p_Grid[x][y].type == AIR) return true;
	return false;
}

//Is it
bool inBounds(int x, int y) {
	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT) return true;
	return false;
}

sfVertex* getQuad(int x, int y) {
	return sfVertexArray_getVertex(m_vertices, (x + y * W_WIDTH) * 4);
}

//Fill the screen with selected pixel type
void fillScreenSelected() {
	for (int y = 0; y < W_HEIGHT; y++) {
		for (int x = 0; x < W_WIDTH; x++) {
			p_Grid[x][y].type = pixel_type;
			p_Grid[x][y].col = pixel_current(pixel_type).col;
			setPixelColor(x, y, p_Grid[x][y].col);
		}
	}
}

void updateDT(float dt) {
	delta_time = dt;
}

//Randomize color for color layering
sfColor randomColor(sfColor color) {

	//Randomize color
	HSL hsl = rgb2hsl(color.r, color.g, color.b);

	//Randomize luminance and saturation
	hsl.l *= randomBetween(0.85f, 1.15f);
	hsl.s *= randomBetween(0.85f, 1.15f);

	//Convert back to rgb
	RGB rgb = hsl2rgb(hsl.h, hsl.s, hsl.l);

	color = sfColor_fromRGB(rgb.r, rgb.g, rgb.b);

	return color;
}

void setPixelColor(int x, int y, sfColor col) {

	sfVertex* quad = getQuad(x, y);

	quad[0].color = col;
	quad[1].color = col;
	quad[2].color = col;
	quad[3].color = col;

	p_Grid[x][y].col = col;
}

void swap(int x1, int y1, int x2, int y2) {
	pixel_t temp = p_Grid[x1][y1];
	p_Grid[x1][y1] = p_Grid[x2][y2];
	p_Grid[x2][y2] = temp;

	p_Grid[x1][y1].moved_last = true;
	p_Grid[x2][y2].moved_last = true;

	setPixelColor(x1, y1, p_Grid[x1][y1].col);
	setPixelColor(x2, y2, p_Grid[x2][y2].col);

}

void initVertices() {
	for (int y = 0; y < W_HEIGHT; y++) {
		for (int x = 0; x < W_WIDTH; x++) {
			sfVertex* quad = getQuad(x, y);

			sfVector2f first = { x * PIXEL_SIZE, y * PIXEL_SIZE };
			sfVector2f second = { x * PIXEL_SIZE + PIXEL_SIZE, y * PIXEL_SIZE };
			sfVector2f third = { x * PIXEL_SIZE + PIXEL_SIZE, y * PIXEL_SIZE + PIXEL_SIZE };
			sfVector2f fourth = { x * PIXEL_SIZE, y * PIXEL_SIZE + PIXEL_SIZE };

			quad[0].position = first;
			quad[1].position = second;
			quad[2].position = third;
			quad[3].position = fourth;

			setPixelColor(x, y, p_Grid[x][y].col);
		}
	}
}

//Init of the grid
void init() {


	for (int y = 0; y < W_HEIGHT; y++) {
		for (int x = 0; x < W_WIDTH; x++) {
			p_Grid[x][y] = pixel_empty();
			//p_Grid[x][y] = pixel_empty();
		}
	}

	initVertices();
}

void reset() {
	for (int y = 0; y < W_HEIGHT; y++) {
		for (int x = 0; x < W_WIDTH; x++) {
			p_Grid[x][y] = pixel_empty();
			//p_Grid[x][y] = pixel_empty();

			setPixelColor(x, y, p_Grid[x][y].col);
		}
	}
}

float updateVelocity(int x, int y) {
	p_Grid[x][y].velocity.y = clamp(p_Grid[x][y].velocity.y + (gravity * delta_time), -10.f, 20.f);
	p_Grid[x][y].velocity.y += gravity * delta_time;

	if (inBounds(x, y + 1) && !isEmpty(x, y + 1))
		p_Grid[x][y].velocity.y /= 1.25f;

	return p_Grid[x][y].velocity.y;
}

//Updates
void update_sand(int x, int y) {

	float v = updateVelocity(x, y);

	if (inBounds(x, y + v) && isEmpty(x, y + v)) {
		swap(x, y, x, y + v);
	}
	else if(inBounds(x, y + 1) && isEmpty(x, y + 1)) {
		swap(x, y, x, y + 1);
	}
	else if (inBounds(x, y + 1) && p_Grid[x][y + 1].type == WATER) {
		if (rand() % 30 < 5) {
			swap(x, y, x, y + 1);
		}
	}
	else if (inBounds(x - 1, y + 1) && isEmpty(x - 1, y + 1) || inBounds(x + 1, y + 1) && isEmpty(x + 1, y + 1)) {
		int r = rand() % 2;
		if (r == 1) {
			if (inBounds(x - 1, y + 1) && isEmpty(x - 1, y + 1))
				swap(x, y, x - 1, y + 1);
		}
		else
			if (inBounds(x + 1, y + 1) && isEmpty(x + 1, y + 1))
				swap(x, y, x + 1, y + 1);;
	}

}

void update_water(int x, int y) {

	float v = updateVelocity(x, y);

	if (inBounds(x, y + v) && isEmpty(x, y + v)) {
		swap(x, y, x, y + v);
	}
	else if (inBounds(x, y + 1) && isEmpty(x, y + 1)) {
		swap(x, y, x, y + 1);
	}
	else if (inBounds(x - 1, y) && isEmpty(x - 1, y) || inBounds(x + 1, y) && isEmpty(x + 1, y)) {
		int r = rand() % 2;
		if (r == 1) {
			if (inBounds(x - 1, y) && isEmpty(x - 1, y))
				swap(x, y, x - 1, y);
		}
		else
			if (inBounds(x + 1, y) && isEmpty(x + 1, y))
				swap(x, y, x + 1, y);
	}
}

void update() {
	for (int y = 0; y < W_HEIGHT; y++) {

		//Fixes rendering bias
		bool leftToRight = rand() % 2 > 0 ? true : false;

		if (leftToRight) {
			for (int x = 0; x < W_WIDTH; x++) {

				if (p_Grid[x][y].moved_last) continue;

				switch (p_Grid[x][y].type) {
				case AIR:
					continue;
					break;

				case SAND:
					update_sand(x, y);
					break;

				case WATER:
					update_water(x, y);
					break;

				case WOOD:
					continue;
					break;
				}

			}
		}
		else {
			for (int x = W_WIDTH - 1; x >= 0; x--) {

				if (p_Grid[x][y].moved_last) continue;

				switch (p_Grid[x][y].type) {
				case AIR:
					continue;
					break;

				case SAND:
					update_sand(x, y);
					break;

				case WATER:
					update_water(x, y);
					break;

				case WOOD:
					continue;
					break;
				}
			}
		}
	}

}

//Ye just spawn square on pos
void addPixel(int x, int y, sfColor color) {
	if (inBounds(x, y) && isEmpty(x, y)) {
		switch (pixel_type) {
		case SAND:
			p_Grid[x][y] = pixel_sand();

			color = randomColor(color);

			setPixelColor(x, y, color);
			break;

		case WATER:
			p_Grid[x][y] = pixel_water();
			setPixelColor(x, y, p_Grid[x][y].col);
			break;

		case WOOD:
			p_Grid[x][y] = pixel_wood();
			setPixelColor(x, y, p_Grid[x][y].col);
			break;
		}
	}
}

void drawCircle(int x, int y, int radius) {

	//Random color each time a whole circle is drawn
	sfColor color = pixel_current(pixel_type).col;

	float rSquared = radius * radius;

	for (int u = x - radius; u < x + radius + 1; u++)
		for (int v = y - radius; v < y + radius + 1; v++)
			if ((x - u) * (x - u) + (y - v) * (y - v) < rSquared)
				addPixel(u, v, color);

}

//Drawing
void draw(sfRenderWindow* window) {

	sfRenderWindow_drawVertexArray(window, m_vertices, NULL);

	for (int y = 0; y < W_HEIGHT; y++) {
		for (int x = 0; x < W_WIDTH; x++) {
			p_Grid[x][y] = p_Grid[x][y];
			p_Grid[x][y].moved_last = false;
		}
	}
}