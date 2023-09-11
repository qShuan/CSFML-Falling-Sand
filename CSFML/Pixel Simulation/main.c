#include <stdio.h>
#include <stdbool.h>
#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "pixels.h"
#include "vertices.h"
#include "sandbox.h"



int main() {

	//Init window
	sfVideoMode mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Window", sfDefaultStyle, sfContextDefault);

	sfRenderWindow_setFramerateLimit(window, 100);

	//Seed
	srand(time(NULL));

	//Init
	initVertexArray();
	init();
	pixel_type = SAND;

	//Radius
	int radius = 5;

	float tickSpeed = 0.f;


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
		else if (sfKeyboard_isKeyPressed(sfKeyNum3)) {
			pixel_type = WOOD;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyR)) {
			reset();
		}

		if (sfMouse_isButtonPressed(0)) {
			sfVector2i mousePos = sfMouse_getPosition(window);
			int x = mousePos.x / PIXEL_SIZE;
			int y = mousePos.y / PIXEL_SIZE;
			drawCircle(x, y, radius);
		}

		//Timer
		float dt = sfTime_asSeconds(sfClock_restart(clock));
		tickSpeed -= dt;

		updateDT(dt);

		//Logic
		update();


		//Draw
		draw(window);

		//Diplay
		sfRenderWindow_display(window);
	}

	return 0;
}
