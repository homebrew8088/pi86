//Compiler
//g++ pi86.cpp x86.cpp vga.cpp font.h timer.cpp drives.cpp keycodes.h -o pi86 `sdl2-config --cflags --libs` -pthread -lwiringPi

#include "SDL.h"
#include <stdio.h>
#include <fstream> 
#include <unistd.h>
#include <thread>
#include "x86.h"
#include "font.h"
#include "vga.h"
#include "timer.h"
#include "drives.h"
#include "keycodes.h"


using namespace std;
	
void keyboard();
void Up_Date_Screen(SDL_Window *Window, SDL_Renderer *Renderer);

int main(int argc, char* argv[]) {
	
	SDL_Window *window;                    // Declare a pointer
	SDL_Renderer *renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
        "x86",     		             // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        720,                               // width, in pixels
        400,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
	);
    
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//this makes it full screen 
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//The bios file to load	
	Load_Bios("bios.bin");
	
	
	///////////////////////////////////////////////////////////////////
	//Change this Start(V30); 8086 or Start(V20); 8088 to set the processor
	///////////////////////////////////////////////////////////////////
	Start(V20);		
	

	
	//Drive images a: and C:			
	Start_Drives("floppy.img", "hdd.img");
	//Starts the system timer, IRQ0 / INT 0x08
	Start_System_Timer();
	
	thread keyboard_loop(keyboard);			//Start Keyboard 
	thread screen_loop(Up_Date_Screen, window, renderer);		//Start screen

	while (Stop_Flag != true)   
	{
		usleep(50);                                   		//Give the 8088 time to run
		if(Read_IO_Byte(0xF0FF) == 0X00)            		//Check for stop command
		{  
			Stop_Flag = true; 
			break;                              	//If stop = 0x00 then stop threads
		}
	}

	keyboard_loop.join();  
	screen_loop.join();                         
	//this is for returning from full screen
	//SDL_SetWindowFullscreen(window, 0);
 
	// Close and destroy the window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Clean up
	SDL_Quit();
	return 0;
}


void Up_Date_Screen(SDL_Window *Window, SDL_Renderer *Renderer)
{
	char Vblank[0x4000];
	char Video_Memory_40x25[2000];
	char Video_Memory_80x25[4000];
	char Video_Memory_320x200[0x4000];
	char Cursor_Position[2];            //Array to store cursor position 
	while(Stop_Flag != true)
	{
		
		while(Stop_Flag != true & Read_Memory_Byte(0x00449) == 0x00 | Stop_Flag != true & Read_Memory_Byte(0x00449) == 0x01)
		{
			Read_Memory_Array(0xB8000, Video_Memory_40x25, 2000); 
			Read_Memory_Array(0x00450, Cursor_Position, 2);
			Mode_0_40x25(Renderer, Video_Memory_40x25, Cursor_Position);
			//SDL_Delay(10); 
		}
		
		while(Stop_Flag != true & Read_Memory_Byte(0x00449) == 0x02 | Stop_Flag != true & Read_Memory_Byte(0x00449) == 0x03)
		{
			Read_Memory_Array(0xB8000, Video_Memory_80x25, 4000); 
			Read_Memory_Array(0x00450, Cursor_Position, 2);
			Mode_2_80x25(Renderer, Video_Memory_80x25, Cursor_Position);
			//SDL_Delay(10); 
		}

		while(Stop_Flag != true & Read_Memory_Byte(0x00449)  == 0x04 & Read_Memory_Byte(0x00466)  == 0x00)
		{
			Read_Memory_Array(0xB8000, Video_Memory_320x200, 0x4000); 
			Graphics_Mode_320_200_Palette_0(Renderer, Video_Memory_320x200);
			//SDL_Delay(10); 
		}
		
		while(Stop_Flag != true & Read_Memory_Byte(0x00449)  == 0x04 & Read_Memory_Byte(0x00466)  == 0x01)
		{
			Read_Memory_Array(0xB8000, Video_Memory_320x200, 0x4000); 
			Graphics_Mode_320_200_Palette_1(Renderer, Video_Memory_320x200);
			//SDL_Delay(10); 
		}
	}
	
}

void Insert_Key(char character_code, char scan_code) //Interrupt_9
{
	char Key_Buffer_Tail =  Read_Memory_Byte(0x041C);               	//Read the position of the keyboard buffer tail pointer   
	Write_Memory_Byte(0x400 + Key_Buffer_Tail, character_code); 	//Write Character code at the keyboard buffer tail pointer
	Write_Memory_Byte(0x401 + Key_Buffer_Tail, scan_code);      	//Write scan code at the keyboard buffer tail pointer 
	Key_Buffer_Tail = Key_Buffer_Tail + 2;                         		//Add 2 to the keyboard buffer tail pointer    
	if(Key_Buffer_Tail >=  Read_Memory_Byte(0x0482))                	//Check to see if the keyboard buffer tail pointer is at the end of the buffer
	{
		Key_Buffer_Tail = Read_Memory_Byte(0x0480);
	}
	Write_Memory_Byte(0x041C, Key_Buffer_Tail);                    	//Write the new keyboard buffer tail pointer 	
}
void keyboard()
{	SDL_Event e;

	while(Stop_Flag != true)
	{
		if (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_QUIT) 
			{
				Stop_Flag = true;     
				break;
			}
			if(e.type == SDL_KEYDOWN)
	 		{
				switch (e.key.keysym.mod)
				{
				//KMOD_NONE
				case 0x0000:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_NUM
				case 0x1000:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_LSHIFT
				case 0x0001:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_RSHIFT
				case 0x0002:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_LSHIFT + KMOD_NUM
				case 0x1001:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_RSHIFT + KMOD_NUM
				case 0x1002:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_LSHIFT + KMOD_RSHIFT
				case 0x0003:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_LSHIFT + KMOD_RSHIFT + KMOD_NUM
				case 0x1003:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS 
				case 0x2000:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS + KMOD_LSHIFT
				case 0x2001:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS + KMOD_RSHIFT
				case 0x2002:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS + KMOD_LSHIFT + KMOD_RSHIFT
				case 0x2003:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS + KMOD_NUM
				case 0x3000:
					Insert_Key(character_codes_uppercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS + KMOD_LSHIFT + KMOD_NUM
				case 0x3001:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS + KMOD_RSHIFT + KMOD_NUM
				case 0x3002:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_CAPS + KMOD_LSHIFT + KMOD_RSHIFT + KMOD_NUM
				case 0x3003:
					Insert_Key(character_codes_lowercase[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);
					break;
				//KMOD_LCTRL
				case 0x0040:
					if(e.key.keysym.scancode == 0x2A)
					{
						Reset();
					}
					Insert_Key(character_codes_ctrl[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);	
					break;
				//KMOD_RCTRL
				case 0x0080:
					Insert_Key(character_codes_ctrl[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);	
					break;
				//KMOD_LALT
				case 0x0100:
					if(e.key.keysym.scancode == 0x2A)
					{
						Write_Memory_Byte(0x00449, 0x02);
					}
					Insert_Key(character_codes_ctrl[e.key.keysym.scancode], scan_codes[e.key.keysym.scancode]);	
					break;
				//KMOD_RALT
				case 0x0200:
					break;
				default:
					break;
				}


				Write_IO_Byte(0x0060, scan_codes[e.key.keysym.scancode]);

				IRQ1();

			} 
		}
	}
}
/*		X86 keyboard flag
 
  		|7|6|5|4|3|2|1|0|  40:17  Keyboard Flags Byte 0
		 | | | | | | | `---- right shift key depressed
		 | | | | | | `----- left shift key depressed
		 | | | | | `------ CTRL key depressed
		 | | | | `------- ALT key depressed
		 | | | `-------- scroll-lock is active
		 | | `--------- num-lock is active
		 | `---------- caps-lock is active
		 `----------- insert is active

		|7|6|5|4|3|2|1|0|  40:18  Keyboard Flags Byte 1
		 | | | | | | | `---- left CTRL key depressed
		 | | | | | | `----- left ALT key depressed
		 | | | | | `------ system key depressed and held
		 | | | | `------- suspend key has been toggled
		 | | | `-------- scroll lock key is depressed
		 | | `--------- num-lock key is depressed
		 | `---------- caps-lock key is depressed
		 `----------- insert key is depressed */
/*
    KMOD_NONE = 0x0000,
    KMOD_LSHIFT = 0x0001,
    KMOD_RSHIFT = 0x0002,
    KMOD_LCTRL = 0x0040,
    KMOD_RCTRL = 0x0080,
    KMOD_LALT = 0x0100,
    KMOD_RALT = 0x0200,
    KMOD_LGUI = 0x0400,
    KMOD_RGUI = 0x0800,
    KMOD_NUM = 0x1000,
    KMOD_CAPS = 0x2000,
    KMOD_MODE = 0x4000,
    KMOD_RESERVED = 0x8000
*/

