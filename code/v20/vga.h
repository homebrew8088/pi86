#ifndef VGA_H
#define VGA_H

#include "x86.h"
#include "SDL.h"
#include "font.h"
#include <thread>

using namespace std;

void Mode_0_40x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position);
void Mode_2_80x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position);
void Text_Mode_40x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position);
void Text_Mode_80x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position);
void Graphics_Mode_320_200_Palette_0(SDL_Renderer *Renderer, char* Video_Memory);
void Graphics_Mode_320_200_Palette_1(SDL_Renderer *Renderer, char* Video_Memory);


#endif
