#include "vga.h"

void Print_Char_18x16(SDL_Renderer *Renderer, int x, int y, unsigned char Ascii_value)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if(((font_9x16[Ascii_value][j] >> (15 - i)) & 1) == 0)
			{ 
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			}
			if(((font_9x16[Ascii_value][j] >> (15 - i)) & 1) == 1)
			{ 
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			}

			SDL_RenderDrawPoint(Renderer, x + (i * 2),  y + j);
			SDL_RenderDrawPoint(Renderer, x + (i * 2) + 1, y + j);
		}
	} 
}

void Mode_0_40x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position)
{
	int index = 0; 
	for (int j = 0; j < 25; j++)
	{
		for (int i = 0; i < 40; i++)
		{
			Print_Char_18x16(Renderer, (i * 18), (j * 16), Video_Memory[index]);
			index++;
			index++;
		}
	} 
	Print_Char_18x16(Renderer, (Cursor_Position[0] * 18), (Cursor_Position[1] * 16), 0xDB);
	SDL_RenderPresent(Renderer);	
}
void Print_Char_9x16(SDL_Renderer *Renderer, int x, int y, unsigned char Ascii_value)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if(((font_9x16[Ascii_value][j] >> (15 - i)) & 1) == 0)
			{ 
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			}
			if(((font_9x16[Ascii_value][j] >> (15 - i)) & 1) == 1)
			{ 
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			}

			SDL_RenderDrawPoint(Renderer, x + i,     y + j);
		}
	} 
}
void Mode_2_80x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position)
{
	int index = 0; 
	for (int j = 0; j < 25; j++)
	{
		for (int i = 0; i < 80; i++)
		{
			Print_Char_9x16(Renderer, (i * 9), (j * 16), Video_Memory[index]);
			index++;
			index++;
		}
	} 
	Print_Char_9x16(Renderer, (Cursor_Position[0] * 9) , (Cursor_Position[1] * 16), 0xDB);
	SDL_RenderPresent(Renderer);	
}


void print_pixs_mode4_palette_0(SDL_Renderer *Renderer, int x, int y, unsigned char Ascii_value)
{
	for (int i = 0; i < 4; i++)
	{
		if(((Ascii_value >> (i + i)) & 3) == 0)
		{ 
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		}
		if(((Ascii_value >> (i + i)) & 3) == 1)//green
		{ 
			SDL_SetRenderDrawColor(Renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		}
		if(((Ascii_value >> (i + i)) & 3) == 2)//red
		{ 
			SDL_SetRenderDrawColor(Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		}
		if(((Ascii_value >> (i + i)) & 3) == 3)//yellow
		{ 
			SDL_SetRenderDrawColor(Renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
		}
		i;
		SDL_RenderDrawPoint(Renderer, x + 8 - (i + i), y);
		SDL_RenderDrawPoint(Renderer, x + 7 - (i + i), y);
		SDL_RenderDrawPoint(Renderer, x + 8 - (i + i), y + 1);
		SDL_RenderDrawPoint(Renderer, x + 7 - (i + i), y + 1);
	}	
}

void Graphics_Mode_320_200_Palette_0(SDL_Renderer *Renderer, char* Video_Memory)
{
	SDL_RenderClear(Renderer);
			int index = 0; 				
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_0(Renderer, 40 + (i * 8), (j * 4), Video_Memory[index]);
					index++;
				}
			} 
			
			index = 0x2000;
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_0(Renderer, 40 + (i * 8), 2 + (j * 4), Video_Memory[index]);
					index++;
				}
			} 
			SDL_RenderPresent(Renderer);	
			
}
void print_pixs_mode4_palette_1(SDL_Renderer *Renderer, int x, int y, unsigned char Ascii_value)
{
	
	for (int i = 0; i < 4; i++)
	{
		if(((Ascii_value >> (i + i)) & 3) == 0)
		{ 
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		}
		if(((Ascii_value >> (i + i)) & 3) == 1)//cy
		{ 
			SDL_SetRenderDrawColor(Renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
		}
		if(((Ascii_value >> (i + i)) & 3) == 2)//mag
		{ 
			SDL_SetRenderDrawColor(Renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		}
		if(((Ascii_value >> (i + i)) & 3) == 3)//white
		{ 
			SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		}
		i;
		SDL_RenderDrawPoint(Renderer, x + 8 - (i + i), y);
		SDL_RenderDrawPoint(Renderer, x + 7 - (i + i), y);
		SDL_RenderDrawPoint(Renderer, x + 8 - (i + i), y + 1);
		SDL_RenderDrawPoint(Renderer, x + 7 - (i + i), y + 1);

	}	
}
void Graphics_Mode_320_200_Palette_1(SDL_Renderer *Renderer, char* Video_Memory)
{
	SDL_RenderClear(Renderer);
			int index = 0; 
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_1(Renderer, 40 + (i * 8), (j * 4), Video_Memory[index]);
					index++;
				}
			} 
			
			index = 0x2000;
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_1(Renderer, 40 + (i * 8), 2 + (j * 4), Video_Memory[index]);
					index++;
				}
			} 
			SDL_RenderPresent(Renderer);	
				
}
