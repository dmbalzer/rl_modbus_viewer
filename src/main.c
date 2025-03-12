#include <raylib.h>
#include "structs.h"

bool quit = false;

int main(void)
{
	InitWindow(960,640,"Raylib Modbus Viewer");
	SetTargetFPS(60);
	while ( !quit ) {
		if ( WindowShouldClose() ) quit = true;
		BeginDrawing();
		ClearBackground(DARKGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
