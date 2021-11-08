#ifndef X86_H
#define X86_H

#define V20 	88
#define V30 	86 

#define PIN_CLK   29
#define PIN_RESET 27
#define PIN_ALE   26
#define PIN_IO_M  10
#define PIN_DTR   11
#define PIN_BHE   6

#define PIN_INTR  28
#define PIN_INTA  31

#define AD0   25
#define AD1   24
#define AD2   23
#define AD3   22
#define AD4   21
#define AD5   30
#define AD6   14
#define AD7   13

#define A8    12
#define A9    3
#define A10   2
#define A11   0
#define A12   7
#define A13   9
#define A14   8
#define A15   15

#define A16   16
#define A17   1
#define A18   4 
#define A19   5

#include <wiringPi.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <fstream> 

using namespace std;

static bool Stop_Flag;


void Reset();	
void Start(int Processor);
void Load_Bios(string Bios_file);
//Memory
void Write_Memory_Array(unsigned long long int Address, char code_for_8088[], int Length);
void Read_Memory_Array(unsigned long long int Address, char* char_Array, int Length);
void Write_Memory_Byte(unsigned long long int Address, char byte_for_8088);
char Read_Memory_Byte(unsigned long long int Address);		
void Write_Memory_Word(unsigned long long int Address, unsigned short int word_for_8088);
//IO

void Write_IO_Byte(unsigned long long int Address, char byte_for_8088);
char Read_IO_Byte(unsigned long long int Address);
void Write_IO_Word(unsigned long long int Address, unsigned short int word_for_8088);

//INT

void IRQ0();
void IRQ1();
#endif
