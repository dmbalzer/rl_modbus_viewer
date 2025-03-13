#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "structs.h"

bool quit = false;

int main(void)
{
	InitWindow(960,640,"Raylib Modbus Viewer");
	SetTargetFPS(30);

	Font font = LoadFontEx("assets/Roboto-Regular.ttf", 18, NULL, 0);
	GuiSetFont(font);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 18);

	FilePathList fpl = LoadDirectoryFiles("./assets");
	for ( int i = 0; i < fpl.count; i++ ) {
		if ( IsFileExtension(fpl.paths[i], ".png") ) {

		} else if ( IsFileExtension(fpl.paths[i], ".gif") ) {
			/* TODO */
		}
	}
	UnloadDirectoryFiles(fpl);
	
	while ( !quit ) {
		if ( WindowShouldClose() ) quit = true;

		BeginDrawing();
		ClearBackground(DARKGRAY);

		EndDrawing();
	}

	UnloadFont(font);
	CloseWindow();
	return 0;
}
