#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "structs.h"

#define MAX_ARRAY 64
unsigned int texture_idx = 0;
Texture textures[MAX_ARRAY] = { 0 };

unsigned int gif_idx = 0;
Gif gifs[MAX_ARRAY] = { 0 };

void load_image(const char* path)
{
	if ( IsFileExtension(path, ".png") ) {
		textures[texture_idx] = LoadTexture(path);
		texture_idx++;
	} else if ( IsFileExtension(path, ".gif") ) {
		gifs[gif_idx].image = LoadImageAnim(path, &gifs[gif_idx].qty);
		gifs[gif_idx].delay = 0.1f;
		textures[texture_idx] = LoadTextureFromImage(gifs[gif_idx].image);
		gifs[gif_idx].texture = &textures[texture_idx];
		gif_idx++;
		texture_idx++;
	}
}

void anim_gifs(void)
{
	for ( int i = 0; i < MAX_ARRAY; i++ ) {
		if ( gifs[i].qty < 2 ) continue;
		gifs[i].timer += GetFrameTime();
		if ( gifs[i].timer >= gifs[i].delay ) {
			gifs[i].timer = 0;
			gifs[i].frame = ( gifs[i].frame + 1 ) % gifs[i].qty;
			unsigned int offset = gifs[i].image.width * gifs[i].image.height * gifs[i].frame * 4;
			Texture texture = *gifs[i].texture;
			UpdateTexture(texture, (unsigned char*)gifs[i].image.data + offset);
		}
	}
}

int draw_image_window(void)
{
	int result = 0;
	Rectangle bounds = (Rectangle){ 8, 8, 200, 300 };
	static Vector2 anchor = (Vector2){ 8 + 8, 8 + 24 + 8 };
	result = GuiWindowBox(bounds, "Images");

	// GuiScrollPanel(Rectangle bounds, const char *text, Rectangle content, Vector2 *scroll, Rectangle *view);
	Rectangle bounds_scroll = (Rectangle){ bounds.x, bounds.y + 24, bounds.width, bounds.height - 24 };
	int w = 0, h = 16;
	for ( int i = 0; i < MAX_ARRAY; i++ ) {
		if ( w < textures[i].width ) w = textures[i].width + 16;
		h += textures[i].height;
	}
	Rectangle bounds_content = { anchor.x, anchor.y, w, h };
	Rectangle bounds_view = { 0 };
	GuiScrollPanel(bounds_scroll, NULL, bounds_content, &anchor, &bounds_view);
	
	BeginScissorMode( bounds_view.x, bounds_view.y, bounds_view.width, bounds_view.height );
	int x = anchor.x + 8, y = anchor.y + 24 + 8;
	for ( int i = 0; i < MAX_ARRAY; i++ ) {
		DrawTexture(textures[i], x, y, WHITE);
		y += textures[i].height;
	}
	EndScissorMode();
	return result;
}

int main(void)
{
	InitWindow(960,640,"Raylib Modbus Viewer");
	SetTargetFPS(30);

	Font font = LoadFontEx("assets/Roboto-Regular.ttf", 18, NULL, 0);
	GuiSetFont(font);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 18);

	FilePathList fpl = LoadDirectoryFiles("./assets");
	for ( int i = 0; i < fpl.count; i++ ) {
		load_image(fpl.paths[i]);
	}
	UnloadDirectoryFiles(fpl);
	
	bool show_image_window = true;

	while ( !WindowShouldClose() ) {
		anim_gifs();

		BeginDrawing();
		ClearBackground(DARKGRAY);
		
		if ( show_image_window ) show_image_window = !draw_image_window();

		EndDrawing();
	}
	
	for ( int i = 0; i < MAX_ARRAY; i++ ) UnloadImage(gifs[i].image);
	for ( int i = 0; i < MAX_ARRAY; i++ ) UnloadTexture(textures[i]);
	UnloadFont(font);
	CloseWindow();
	return 0;
}
