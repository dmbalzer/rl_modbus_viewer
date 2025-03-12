#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "structs.h"

bool quit = false;

Image* images = NULL;

int main(void)
{
	InitWindow(960,640,"Raylib Modbus Viewer");
	SetTargetFPS(30);

	while ( !quit ) {
		if ( WindowShouldClose() ) quit = true;
		BeginDrawing();
		ClearBackground(DARKGRAY);
		
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
