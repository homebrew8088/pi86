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
	Start(V30);		
	

	
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
			//Ends the program when click X
			if (e.type == SDL_QUIT) 
			{
				Stop_Flag = true;     
				break;
			}
			//Process Key
			if(e.type == SDL_KEYDOWN)
	 		{
				//Convert SDL scancode to x86 scancode 
				Write_IO_Byte(0x0060, scan_codes[e.key.keysym.scancode]);
				//Trigger IRQ1
				IRQ1();
			} 
		}
	}
}

