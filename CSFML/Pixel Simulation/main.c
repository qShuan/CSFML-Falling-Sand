#include <stdio.h>
#include <stdbool.h>
#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "pixels.h"
#include "vertices.h"
#include "sandbox.h"



int WinMain() {

	//Init window
	sfVideoMode mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
	sfRenderWindow* window;

	window = sfRenderWindow_create(mode, "Window", sfClose | sfTitlebar, sfContextDefault);

	sfRenderWindow_setFramerateLimit(window, 100);

	//Seed
	srand(time(NULL));

	//Init
	initColors();
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
		else if (sfKeyboard_isKeyPressed(sfKeyF)) {
			fillScreenSelected();
		}
		else if (sfKeyboard_isKeyPressed(sfKeyQ)) {
			radius--;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyE)) {
			radius++;
		}

		if (radius <= 0)
			radius = 1;

		if (sfMouse_isButtonPressed(0)) {
			sfVector2i mousePos = sfMouse_getPosition(window);
			int x = mousePos.x / PIXEL_SIZE;
			int y = mousePos.y / PIXEL_SIZE;
			drawCircle(x, y, radius);
		}

		if (sfMouse_isButtonPressed(1)) {
			sfVector2i mousePos = sfMouse_getPosition(window);
			int x = mousePos.x / PIXEL_SIZE;
			int y = mousePos.y / PIXEL_SIZE;
			
			printf("R: %d  G: %d  B: %d\n", p_Grid[x][y].col.r, p_Grid[x][y].col.g, p_Grid[x][y].col.b);
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