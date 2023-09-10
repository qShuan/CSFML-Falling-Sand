#include <stdio.h>
#include <stdbool.h>
#include "SFML/Graphics.h"
#include "SFML/Window.h"

//Pixel types
typedef enum Pixel{AIR, SAND, WATER} Pixel;
Pixel pixel_type;

//Constants
 const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
 const int PIXEL_SIZE = 1;

 const int W_WIDTH = 800, W_HEIGHT = 600;

 sfVertexArray* m_vertices;


typedef struct pixel_t {
	int id;
	Pixel type;
	sfColor col;
	bool moved_last;
}pixel_t;

pixel_t p_Grid[800][600];
pixel_t prev_Grid[800][600];

//Pixels
pixel_t pixel_empty() {
	pixel_t p = {0};
	p.id = 0;
	p.type = AIR;
	p.col = sfColor_fromRGB(72,72,72);

	return p;
}

pixel_t pixel_sand() {
	pixel_t p = { 0 };
	p.id = 1;
	p.type = SAND;
	p.col = sfColor_fromRGB(227, 197, 107);

	return p;
}

pixel_t pixel_water() {
	pixel_t p = { 0 };
	p.id = 2;
	p.type = WATER;
	p.col = sfColor_fromRGB(96, 168, 219);

	return p;
}

//Init of vertex array
void bigInit() {
	m_vertices = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(m_vertices, sfQuads);
	sfVertexArray_resize(m_vertices, W_WIDTH * W_HEIGHT * 4);
}

//Is it
bool isEmpty(int x, int y) {
	if (prev_Grid[x][y].id == 0) return true;
	return false;
}

//Is it
bool inBounds(int x, int y) {
	if (x >= 0 && x < W_WIDTH && y > 0 && y < W_HEIGHT) return true;
	return false;
}

sfVertex* getQuad(int x, int y) {
	return sfVertexArray_getVertex(m_vertices, (x + y * W_WIDTH) * 4);
}


void setPixelColor(int x, int y, sfColor col) {

	sfVertex* quad = getQuad(x, y);

	quad[0].color = col;
	quad[1].color = col;
	quad[2].color = col;
	quad[3].color = col;

}

void swap(int x1, int y1, int x2, int y2) {
	pixel_t temp = p_Grid[x1][y1];
	p_Grid[x1][y1] = p_Grid[x2][y2];
	p_Grid[x2][y2] = temp;

	setPixelColor(x1, y1, p_Grid[x1][y1].col);
	setPixelColor(x2, y2, p_Grid[x2][y2].col);

}

//Updates
void update_sand(int x, int y) {
	if (inBounds(x, y + 1) && isEmpty(x, y + 1)) {
		swap(x, y, x, y + 1);
	}
	else if (inBounds(x, y + 1) && prev_Grid[x][y + 1].type == WATER) {
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
	if (inBounds(x, y + 1) && isEmpty(x, y + 1)) {
		swap(x, y, x, y + 1);
	}
	else if (inBounds(x - 1, y) && isEmpty(x - 1, y) || inBounds(x + 1, y) && isEmpty(x + 1, y)) {
		int r = rand() % 2;
		if (r == 1) {
			if(inBounds(x - 1, y) && isEmpty(x - 1, y))
				swap(x, y, x - 1, y);
		}
		else
			if(inBounds(x + 1, y) && isEmpty(x + 1, y))
				swap(x, y, x + 1, y);
	}
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
			prev_Grid[x][y] = pixel_empty();
		}
	}

	initVertices();
}


void reset() {
	for (int y = 0; y < W_HEIGHT; y++) {
		for (int x = 0; x < W_WIDTH; x++) {
			p_Grid[x][y] = pixel_empty();
			prev_Grid[x][y] = pixel_empty();

			setPixelColor(x, y, p_Grid[x][y].col);
		}
	}
}




void update() {
	for (int y = 0; y < W_HEIGHT; y++) {

		//Fixes rendering bias
		bool leftToRight = rand() % 2 > 0 ? true : false;

		if (leftToRight) {
			for (int x = 0; x < W_WIDTH; x++) {

				switch (prev_Grid[x][y].type) {
				case AIR:
					continue;
					break;

				case SAND:
					update_sand(x, y);
					break;

				case WATER:
					update_water(x, y);
					break;
				}
			}
		}
		else {
			for (int x = W_WIDTH - 1; x >= 0; x--) {

				switch (prev_Grid[x][y].type) {
				case AIR:
					continue;
					break;

				case SAND:
					update_sand(x, y);
					break;

				case WATER:
					update_water(x, y);
					break;
				}
			}
		}
	}

}

//Ye just spawn square on pos
void addPixel(int x, int y) {
	if (inBounds(x, y)) {
		switch (pixel_type) {
		case SAND:
			p_Grid[x][y] = pixel_sand();
			setPixelColor(x, y, p_Grid[x][y].col);
			break;

		case WATER:
			p_Grid[x][y] = pixel_water();
			setPixelColor(x, y, p_Grid[x][y].col);
			break;
		}
	}
}

void drawCircle(int x, int y, int radius) {
	float rSquared = radius * radius;

	for (int u = x - radius; u < x + radius + 1; u++)
		for (int v = y - radius; v < y + radius + 1; v++)
			if ((x - u) * (x - u) + (y - v) * (y - v) < rSquared)
				addPixel(u, v);

}

//Drawing
void draw(sfRenderWindow* window) {

	sfRenderWindow_drawVertexArray(window, m_vertices, NULL);

	for (int y = 0; y < W_HEIGHT; y++) {
		for (int x = 0; x < W_WIDTH; x++) {			
			prev_Grid[x][y] = p_Grid[x][y];
		}
	}
}

int main() {

	//Init window
	sfVideoMode mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Window", sfDefaultStyle, sfContextDefault);

	//Seed
	srand(time(NULL));

	//Init
	bigInit();
	init();
	pixel_type = SAND;

	float tickSpeed = 0.001f;

	//Clock for tick timer
	sfClock* clock;
	clock = sfClock_create();

	while (sfRenderWindow_isOpen(window)) {
		sfEvent e;
		while (sfRenderWindow_pollEvent(window, &e)) {
			if (e.type == sfEvtClosed) {
				sfRenderWindow_close(window);
			}

		}

		//Clear
		sfRenderWindow_clear(window, sfBlack);

		//Input
		if (sfKeyboard_isKeyPressed(sfKeyNum1)) {
			pixel_type = SAND;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyNum2)) {
			pixel_type = WATER;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyR)) {
			reset();
		}

		if (sfMouse_isButtonPressed(0)) {
			sfVector2i mousePos = sfMouse_getPosition(window);
			int x = mousePos.x / PIXEL_SIZE;
			int y = mousePos.y / PIXEL_SIZE;
			drawCircle(x, y, 25);
		}

		//Timer
		float dt = sfTime_asSeconds(sfClock_restart(clock));
		tickSpeed -= dt;

		//Logic
		if (tickSpeed <= 0.f) {
			update();
			tickSpeed = 0.001f;
		}


		//Draw
		draw(window);

		//Diplay
		sfRenderWindow_display(window);
	}

	return 0;
}
