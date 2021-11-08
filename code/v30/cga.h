#ifndef CGA_H
#define CGA_H

#include "SDL.h"
#include "font.h"

using namespace std;
void Text_Mode_40x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position);
void Text_Mode_80x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position);
void Graphics_Mode_320_200_Palette_0(SDL_Renderer *Renderer, char* Video_Memory);
void Graphics_Mode_320_200_Palette_1(SDL_Renderer *Renderer, char* Video_Memory);


#endif
