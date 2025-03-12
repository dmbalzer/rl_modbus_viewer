#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "structs.h"

bool quit = false;

Texture* textures = NULL;

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
			arrput(textures, LoadTexture(fpl.paths[i]));
		}
	}
	UnloadDirectoryFiles(fpl);
	
	Vector2 anchor = { 0 };

	while ( !quit ) {
		if ( WindowShouldClose() ) quit = true;
		BeginDrawing();
		ClearBackground(DARKGRAY);
		
		Rectangle bounds = {
			.width = 300,
			.height = 400,
		};
	
		GuiPanel(bounds, "Textures");
		GuiPanel((Rectangle){ bounds.x+bounds.width,bounds.y,bounds.width,bounds.height }, NULL);	
		BeginScissorMode(anchor.x, anchor.y + 24, bounds.width, bounds.height - 24);
		int x = anchor.x;
		int y = anchor.y;	
		for ( int i = 0; i < arrlen(textures); i++ ) {
			DrawTexture(textures[i], x, y, WHITE);
			x += textures[i].width;
		}
		EndScissorMode();	

		EndDrawing();
	}

	for ( int i = 0; i < arrlen(textures); i++ ) {
		UnloadTexture(textures[i]);
	}
	UnloadFont(font);
	CloseWindow();
	return 0;
}
