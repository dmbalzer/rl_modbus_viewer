#ifndef STRUCTS_INCLUDED
#define STRUCTS_INCLUDED

#include <raylib.h>

typedef struct {
	int x;
	int y;
} Entity;

typedef struct {
	Image image;
	Texture* texture;
	float timer;
	float delay;
	int qty;
	int frame;
} Gif;

#endif // STRUCTS_INCLUDED
