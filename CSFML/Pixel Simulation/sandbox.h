#pragma once
#include <stdbool.h>
#include "SFML/Graphics.h"
#include "vertices.h"
#include "pixels.h"


bool isEmpty(int x, int y);

bool inBounds(int x, int y);

sfVertex* getQuad(int x, int y);

void setPixelColor(int x, int y, sfColor col);

void swap(int x1, int y1, int x2, int y2);

float delta_time;
void updateDT(float dt);

void init();
void initVertices();

//Reset the grid
void reset();

//Update of the whole simulation
void update();

//Updates
float updateVelocity(int x, int y);
void update_sand(int x, int y);
void update_water(int x, int y);

//Drawing
void addPixel(int x, int y);
void drawCircle(int x, int y, int radius);
void draw(sfRenderWindow* window);
void fillScreenSelected();