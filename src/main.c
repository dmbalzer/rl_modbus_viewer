#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "structs.h"

bool quit = false;

Texture* textures = NULL;
Gif* gifs = NULL;

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
		} else if ( IsFileExtension(fpl.paths[i], ".gif") ) {
			Gif gif = { 0 };
			gif.image = LoadImageAnim(fpl.paths[i], &gif.qty);
			Texture texture = LoadTextureFromImage(gif.image);
			gif.texture = &texture;
			arrput(textures, texture);
			arrput(gifs, gif);
		}
	}
	UnloadDirectoryFiles(fpl);
	
	while ( !quit ) {
		if ( WindowShouldClose() ) quit = true;
		BeginDrawing();
		ClearBackground(DARKGRAY);
		int x = 0, y = 0;	
		for ( int i = 0; i < arrlen(textures); i++ ) {
			DrawTexture(textures[i], x, y, WHITE);
			x += textures[i].width;
		}

		EndDrawing();
	}

	for ( int i = 0; i < arrlen(textures); i++ ) {
		UnloadTexture(textures[i]);
	}
	UnloadFont(font);
	CloseWindow();
	return 0;
}
