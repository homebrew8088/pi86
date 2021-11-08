#include "cga.h"

//SDL_SetWindowSize(window, 700,500);

void Print_Char_40x25(SDL_Renderer *Renderer, int x, int y, unsigned char Ascii_value)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(((_8x8char[Ascii_value][j] >> i) & 1) == 0)
			{ 
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			}
			if(((_8x8char[Ascii_value][j] >> i) & 1) == 1)
			{ 
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			}

			SDL_RenderDrawPoint(Renderer, x + (i * 2),     y + (j * 2));
			SDL_RenderDrawPoint(Renderer, x + (i * 2) + 1, y + (j * 2));
			SDL_RenderDrawPoint(Renderer, x + (i * 2),     y + (j * 2) + 1);
			SDL_RenderDrawPoint(Renderer, x + (i * 2) + 1, y + (j * 2) + 1);
		}
	} 
}

void Text_Mode_40x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position)
{
	int index = 0; 
	for (int j = 0; j < 25; j++)
	{
		for (int i = 0; i < 40; i++)
		{
			Print_Char_40x25(Renderer, 2 + (i * 16), 2 + (j * 16), Video_Memory[index]);
			index++;
			index++;
		}
	} 
	Print_Char_40x25(Renderer, (Cursor_Position[0] * 16)+2, (Cursor_Position[1] * 16) + 2, 0xDB);
	SDL_RenderPresent(Renderer);
	
}

void Print_Char_80x25(SDL_Renderer *Renderer, int x, int y, unsigned char Ascii_value)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(((_8x8char[Ascii_value][j] >> i) & 1) == 0)
			{ 
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			}
			if(((_8x8char[Ascii_value][j] >> i) & 1) == 1)
			{ 
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			}

			SDL_RenderDrawPoint(Renderer, x + i, y + (j * 2));
			SDL_RenderDrawPoint(Renderer, x + i, y + (j * 2) + 1);

		}
	} 
}

void Text_Mode_80x25(SDL_Renderer *Renderer, char* Video_Memory, char* Cursor_Position)
{
	int index = 0; 
	for (int j = 0; j < 25; j++)
	{
		for (int i = 0; i < 80; i++)
		{
			Print_Char_80x25(Renderer, 2 + (i * 8), 2 + (j * 16), Video_Memory[index]);
			index++;
			index++;
		}
	} 
	Print_Char_80x25(Renderer, (Cursor_Position[0] * 8)+2, (Cursor_Position[1] * 16) + 2, 0xDB);
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
			int index = 0; 				
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_0(Renderer, 2 + (i * 8), 2 + (j * 4), Video_Memory[index]);
					index++;
				}
			} 
			
			index = 0x2000;
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_0(Renderer, 2 + (i * 8), 4 + (j * 4), Video_Memory[index]);
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
			int index = 0; 
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_1(Renderer, 2 + (i * 8), 2 + (j * 4), Video_Memory[index]);
					index++;
				}
			} 
			
			index = 0x2000;
			for (int j = 0; j < 100; j++)
			{
				for (int i = 0; i < 80; i++)
				{
					print_pixs_mode4_palette_1(Renderer, 2 + (i * 8), 4 + (j * 4), Video_Memory[index]);
					index++;
				}
			} 
			SDL_RenderPresent(Renderer);	
				
}

