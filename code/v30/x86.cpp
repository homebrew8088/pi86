#include "x86.h"

unsigned char RAM[0x100000];
unsigned char IO[0x10000];
bool IRQ0_Flag = 0;
bool IRQ1_Flag = 0;
void IRQ0()
{
   IRQ0_Flag = true;
   digitalWrite (PIN_INTR, HIGH); 
}
void IRQ1()
{
   IRQ1_Flag = true;
   digitalWrite (PIN_INTR, HIGH); 
}
char Read_Interrupts()
{
   char intr = IRQ0_Flag;
   intr = intr + (IRQ1_Flag << 1);
   return intr;
}
//////////////////////////////
//System Bus
///////////////////////////////

int Read_Address()
{
   int Address;
   Address = digitalRead(AD0);
   Address = Address + (digitalRead(AD1) << 1);
   Address = Address + (digitalRead(AD2) << 2);
   Address = Address + (digitalRead(AD3) << 3);
   Address = Address + (digitalRead(AD4) << 4);
   Address = Address + (digitalRead(AD5) << 5);
   Address = Address + (digitalRead(AD6) << 6);
   Address = Address + (digitalRead(AD7) << 7);
   Address = Address + (digitalRead(A8) << 8);
   Address = Address + (digitalRead(A9) << 9);
   Address = Address + (digitalRead(A10) << 10);
   Address = Address + (digitalRead(A11) << 11);
   Address = Address + (digitalRead(A12) << 12);
   Address = Address + (digitalRead(A13) << 13);
   Address = Address + (digitalRead(A14) << 14);
   Address = Address + (digitalRead(A15) << 15);
   Address = Address + (digitalRead(A16) << 16);
   Address = Address + (digitalRead(A17) << 17);
   Address = Address + (digitalRead(A18) << 18);
   Address = Address + (digitalRead(A19) << 19);
   return Address;
}
//Reads the IO_M, RD, WR pins
char Read_Control_Bus()
{
	  char Control_Bus;
	  Control_Bus = digitalRead(PIN_DTR);
	  Control_Bus = Control_Bus + (digitalRead(PIN_IO_M) << 1);
	  Control_Bus = Control_Bus + (digitalRead(PIN_INTA) << 2);
	  return Control_Bus;
}
//Reads the selected Memory Bank, High/Low 8086 only
char Read_Memory_Bank()
{
	  char Memory_Bank;
	  Memory_Bank = digitalRead(AD0);
	  Memory_Bank = Memory_Bank + (digitalRead(PIN_BHE) << 1);
	  return Memory_Bank;
}
//Sets the Data Port direction for read and writes 
void Data_Bus_Direction_8088_IN()
{
    pinMode (AD0, INPUT);  
    pinMode (AD1, INPUT);
    pinMode (AD2, INPUT);
    pinMode (AD3, INPUT);
    pinMode (AD4, INPUT);
    pinMode (AD5, INPUT);
    pinMode (AD6, INPUT);
    pinMode (AD7, INPUT);
}
void Data_Bus_Direction_8088_OUT()
{
    pinMode (AD0, OUTPUT);  
    pinMode (AD1, OUTPUT);
    pinMode (AD2, OUTPUT);
    pinMode (AD3, OUTPUT);
    pinMode (AD4, OUTPUT);
    pinMode (AD5, OUTPUT);
    pinMode (AD6, OUTPUT);
    pinMode (AD7, OUTPUT);
}
void Data_Bus_Direction_8086_IN()
{
    pinMode (AD0, INPUT);  
    pinMode (AD1, INPUT);
    pinMode (AD2, INPUT);
    pinMode (AD3, INPUT);
    pinMode (AD4, INPUT);
    pinMode (AD5, INPUT);
    pinMode (AD6, INPUT);
    pinMode (AD7, INPUT);
    
    pinMode (A8, INPUT);  
    pinMode (A9, INPUT);
    pinMode (A10, INPUT);
    pinMode (A11, INPUT);
    pinMode (A12, INPUT);
    pinMode (A13, INPUT);
    pinMode (A14, INPUT);
    pinMode (A15, INPUT);
}
void Data_Bus_Direction_8086_OUT()
{
    pinMode (AD0, OUTPUT);  
    pinMode (AD1, OUTPUT);
    pinMode (AD2, OUTPUT);
    pinMode (AD3, OUTPUT);
    pinMode (AD4, OUTPUT);
    pinMode (AD5, OUTPUT);
    pinMode (AD6, OUTPUT);
    pinMode (AD7, OUTPUT);
   
    pinMode (A8, OUTPUT);  
    pinMode (A9, OUTPUT);
    pinMode (A10, OUTPUT);
    pinMode (A11, OUTPUT);
    pinMode (A12, OUTPUT);
    pinMode (A13, OUTPUT);
    pinMode (A14, OUTPUT);
    pinMode (A15, OUTPUT);
}

//Writes Data to Data Port 0-7
void Write_To_Data_Port_0_7(char Byte)
{
   digitalWrite (AD0, Byte & 1); 
   digitalWrite (AD1,(Byte >> 1) & 1); 
   digitalWrite (AD2, (Byte >> 2) & 1); 
   digitalWrite (AD3, (Byte >> 3) & 1); 
   digitalWrite (AD4, (Byte >> 4) & 1); 
   digitalWrite (AD5, (Byte >> 5) & 1); 
   digitalWrite (AD6, (Byte >> 6) & 1); 
   digitalWrite (AD7, (Byte >> 7) & 1); 
}
//Writes Data to Data Port 8-15 8086 only
void Write_To_Data_Port_8_15(char Byte)
{
   digitalWrite (A8, Byte & 1); 
   digitalWrite (A9,(Byte >> 1) & 1); 
   digitalWrite (A10, (Byte >> 2) & 1); 
   digitalWrite (A11, (Byte >> 3) & 1); 
   digitalWrite (A12, (Byte >> 4) & 1); 
   digitalWrite (A13, (Byte >> 5) & 1); 
   digitalWrite (A14, (Byte >> 6) & 1); 
   digitalWrite (A15, (Byte >> 7) & 1); 
}
//Reads Data to Data Port 0-7
char Read_From_Data_Port_0_7()
{
   char ret;
   ret = digitalRead(AD0);
   ret = ret + (digitalRead(AD1) << 1);
   ret = ret + (digitalRead(AD2) << 2);
   ret = ret + (digitalRead(AD3) << 3);
   ret = ret + (digitalRead(AD4) << 4);
   ret = ret + (digitalRead(AD5) << 5);
   ret = ret + (digitalRead(AD6) << 6);
   ret = ret + (digitalRead(AD7) << 7);
   return ret;
}
//Reads Data to Data Port 8-15 8086 only
char Read_From_Data_Port_8_15()
{
   char ret;
   ret = digitalRead(A8);
   ret = ret + (digitalRead(A9) << 1);
   ret = ret + (digitalRead(A10) << 2);
   ret = ret + (digitalRead(A11) << 3);
   ret = ret + (digitalRead(A12) << 4);
   ret = ret + (digitalRead(A13) << 5);
   ret = ret + (digitalRead(A14) << 6);
   ret = ret + (digitalRead(A15) << 7);
   return ret;
}
//Clicks the CLK pin 
void CLK()
{
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);

   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);
   digitalWrite (PIN_CLK, HIGH);

   digitalWrite (PIN_CLK, LOW);   
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
   digitalWrite (PIN_CLK, LOW);
}

//Sets up Raspberry PI pins in the begining 
void Setup()
{
   Stop_Flag = false;
   wiringPiSetup();

   pinMode (PIN_CLK, OUTPUT);
   pinMode (PIN_RESET, OUTPUT);
   pinMode (PIN_ALE, INPUT);
   pinMode (PIN_IO_M, INPUT);
   pinMode (PIN_DTR, INPUT);
   pinMode (PIN_BHE, INPUT);

   pinMode (PIN_INTR, OUTPUT);
   pinMode (PIN_INTA, INPUT);
   digitalWrite (PIN_INTR, LOW);
   
   pinMode (AD0, INPUT);  
   pinMode (AD1, INPUT);
   pinMode (AD2, INPUT);
   pinMode (AD3, INPUT);
   pinMode (AD4, INPUT);
   pinMode (AD5, INPUT);
   pinMode (AD6, INPUT);
   pinMode (AD7, INPUT);

   pinMode (A8, INPUT);  
   pinMode (A9, INPUT);
   pinMode (A10, INPUT);
   pinMode (A11, INPUT);
   pinMode (A12, INPUT);
   pinMode (A13, INPUT);
   pinMode (A14, INPUT);
   pinMode (A15, INPUT);

   pinMode (A16, INPUT);
   pinMode (A17, INPUT);
   pinMode (A18, INPUT);
   pinMode (A19, INPUT);
}
//System Bus decoder
void Start_System_Bus(int Processor)
{
	char Control_Bus;
	int Address;
	char Memory_IO_Bank;

	if(Processor == 88)
	{
      while(Stop_Flag != true)
      {
		CLK();
	 if(digitalRead(PIN_ALE) == 1)
	 {
	    Address = Read_Address();	   
	    CLK();
	    switch (Read_Control_Bus())
	    {
	       //Read Mem
	       case 0x04:
		  Data_Bus_Direction_8088_OUT();
		  Write_To_Data_Port_0_7(RAM[Address]);
		  CLK(); CLK();
		  Data_Bus_Direction_8088_IN();
		 break;
	       //Write Mem
	       case 0x05:
		  RAM[Address] = Read_From_Data_Port_0_7();
		  CLK(); CLK();
		  break;
	       //Read IO
	       case 0x06:
		  Data_Bus_Direction_8088_OUT();
		  Write_To_Data_Port_0_7(IO[Address]);
		  printf("Read IO %#X, ", Address);
		  printf("Data %#X \n", IO[Address]);
		  CLK(); CLK();
		  Data_Bus_Direction_8088_IN();
		  break;
	       //Write IO
	       case 0x07:
		  IO[Address] = Read_From_Data_Port_0_7();
		  printf("Write IO %#X, ", Address);
		  printf("Data %#X \n", Read_From_Data_Port_0_7());
		  CLK(); CLK();
		  break;
	       //Interrupt
	       case 0x02:
		  //Waits for second INTA bus cycle 4 CLKS 8088
		  CLK();CLK();CLK();CLK();
		  switch (Read_Interrupts())
		  {
		     case 0x01:
			Data_Bus_Direction_8088_OUT();
			Write_To_Data_Port_0_7(0x08);
			CLK(); CLK(); 
			Data_Bus_Direction_8088_IN();
			IRQ0_Flag = false;
			digitalWrite (PIN_INTR, LOW); 
			break;
		     case 0x02:
			Data_Bus_Direction_8088_OUT();
			Write_To_Data_Port_0_7(0x09);
			CLK(); CLK(); 
			Data_Bus_Direction_8088_IN();
			IRQ1_Flag = false;
			digitalWrite (PIN_INTR, LOW); 
			break;
		     case 0x03:
			Data_Bus_Direction_8088_OUT();
			Write_To_Data_Port_0_7(0x08);
			CLK(); CLK(); 		
			Data_Bus_Direction_8088_IN();
			IRQ0_Flag = false;
			break;
		     default:
			printf("Default Interrupt %#X \n", Read_Interrupts());
			break;
		  }
		 break;
	       default:
		  printf("Default \n");
		 break;
	    }
	 }     
      }
   } 
   if(Processor == 86)
   {
      while(Stop_Flag != true)
      {
	 CLK();
	 if(digitalRead(PIN_ALE) == 1)
	 {
	    Address = Read_Address();	 
	    Memory_IO_Bank = Read_Memory_Bank();  
	    CLK();
	    switch (Read_Control_Bus() + (Memory_IO_Bank << 4))
	    {
	       //Write Mem
	       case 0x07:
		  RAM[Address] = Read_From_Data_Port_0_7();
		  RAM[Address+1] = Read_From_Data_Port_8_15();
		  CLK(); CLK();
		  break;
	       case 0x17:
		  RAM[Address] = Read_From_Data_Port_8_15();
		  CLK(); CLK();
		  break;
	       case 0x27:
		  RAM[Address] = Read_From_Data_Port_0_7();
		  CLK(); CLK();
		  break;
	       //Read Mem
	       case 0x06:
		  Data_Bus_Direction_8086_OUT();
		  Write_To_Data_Port_0_7(RAM[Address]);
		  Write_To_Data_Port_8_15(RAM[Address+1]);
		  CLK(); CLK();
		  Data_Bus_Direction_8086_IN();
		 break;
	       case 0x16:
		  Data_Bus_Direction_8086_OUT();
		  Write_To_Data_Port_8_15(RAM[Address]);
		  CLK(); CLK();
		  Data_Bus_Direction_8086_IN();
		 break;
	       case 0x26:
		  Data_Bus_Direction_8086_OUT();
		  Write_To_Data_Port_0_7(RAM[Address]);
		  CLK(); CLK();
		  Data_Bus_Direction_8086_IN();
		 break;
	       //Write IO
	       case 0x05:
		  IO[Address] = Read_From_Data_Port_0_7();
		  IO[Address+1] = Read_From_Data_Port_8_15();
		  CLK(); CLK();
		  break;
	       case 0x15:
		  IO[Address] = Read_From_Data_Port_8_15();
		  CLK(); CLK();
		  break;
	       case 0x25:
		  IO[Address] = Read_From_Data_Port_0_7();
		  CLK(); CLK();
		  break;
	       //Read IO
	       case 0x04:
		  Data_Bus_Direction_8086_OUT();
		  Write_To_Data_Port_0_7(IO[Address]);
		  Write_To_Data_Port_8_15(IO[Address+1]);
		  CLK(); CLK();
		  Data_Bus_Direction_8086_IN();
		 break;
	       case 0x14:
		  Data_Bus_Direction_8086_OUT();
		  Write_To_Data_Port_8_15(IO[Address]);
		  CLK(); CLK();
		  Data_Bus_Direction_8086_IN();
		 break;
	       case 0x24:
		  Data_Bus_Direction_8086_OUT();
		  Write_To_Data_Port_0_7(IO[Address]);
		  CLK(); CLK();
		  Data_Bus_Direction_8086_IN();
		 break;
		 //Interrupt
	       case 0x00:
		  //Waits for second INTA bus cycle 7 CLKS 8086
		  CLK();CLK();
		  CLK();CLK();
		  CLK();CLK();
		  CLK();
		  switch (Read_Interrupts())
		  {
		     //System Timer
		     case 0x01:
			Data_Bus_Direction_8086_OUT();
			Write_To_Data_Port_0_7(0x08);
			CLK(); CLK(); 
			Data_Bus_Direction_8086_IN();
			IRQ0_Flag = false;
			digitalWrite (PIN_INTR, LOW); 
			break;
		     //Keyboard
		     case 0x02:
			Data_Bus_Direction_8086_OUT();
			Write_To_Data_Port_0_7(0x09);
			CLK(); CLK(); 
			Data_Bus_Direction_8086_IN();
			IRQ1_Flag = false;
			digitalWrite (PIN_INTR, LOW); 
			break;
		     //System Timer and Keyboard, System Timer is handled
		     case 0x03:
			Data_Bus_Direction_8086_OUT();
			Write_To_Data_Port_0_7(0x08);
			CLK(); CLK(); 		
			Data_Bus_Direction_8086_IN();
			IRQ0_Flag = false;
			break;
		     default:
			printf("Default Interrupt %#X \n", Read_Interrupts());
			break;
		  }
		 break;
	       default:
		  printf("Default \n");
		 break;
	    }
	 }     
      }
   } 
}
void Write_Memory_Array(unsigned long long int Address, char code_for_8088[], int Length)
{  
    for(int i = 0; i < Length; i++) 
    {
         RAM[Address] = code_for_8088[i];   
         Address++;
    } 
}
void Read_Memory_Array(unsigned long long int Address, char* char_Array, int Length)
{
   for(int i=0; i < Length; ++i)
   {
      char_Array[i] = RAM[Address];
      Address++;
   }
}
void Write_Memory_Byte(unsigned long long int Address, char byte_for_8088)
{
   RAM[Address] = byte_for_8088; 
}
char Read_Memory_Byte(unsigned long long int Address)
{
   return RAM[Address];
}

void Write_Memory_Word(unsigned long long int Address, unsigned short int word_for_8088) 
{
   RAM[Address] = word_for_8088; 
   RAM[Address + 1] = word_for_8088 >> 8; 
}

void Write_IO_Byte(unsigned long long int Address, char byte_for_8088)
{
   IO[Address] = byte_for_8088; 
}
char Read_IO_Byte(unsigned long long int Address)
{
   return IO[Address];
}
void Write_IO_Word(unsigned long long int Address, unsigned short int word_for_8088) 
{
   IO[Address] = word_for_8088; 
   IO[Address + 1] = word_for_8088 >> 8; 
}

//Resest the x86
void Reset()
{
    digitalWrite (PIN_RESET, HIGH);
    CLK(); CLK(); CLK(); CLK();
    CLK(); CLK(); CLK(); CLK();
    digitalWrite (PIN_RESET, LOW);
}
void Start(int Processor)
{
   //Sets up Ports 
   Setup();	
   //Resets the x86
   Reset();
   //Starts the x86 system bus in a thread
   thread System_Bus(Start_System_Bus, Processor);
   //Detach the thread to continue in the program
   System_Bus.detach();
}

void Load_Bios(string Bios_file)
{
	std::ifstream MemoryFile;                 //New ifstream
	MemoryFile.open(Bios_file);              //Open Rom.bin
	MemoryFile.seekg (0, ios::end);           //Find the end of the file
	int FileSize = MemoryFile.tellg();        //Get the size of the file
	MemoryFile.seekg (0, MemoryFile.beg);     //Start reading at the begining
	char Rom[FileSize];                       //New char array the size of the rom file
	MemoryFile.read(Rom, FileSize);           //Read the file
	MemoryFile.close();                       //Close the file

	//Jump code to be written to 0xFFFFF, =JMP FAR 0xF000:0X0100
	char FFFF0[] = {0XEA, 0X00, 0X01, 0X00, 0XF8, 'E', 'M', ' ', '0', '4', '/', '1', '0', '/', '2', '0'};
	Write_Memory_Array(0xFFFF0, FFFF0, sizeof(FFFF0)); //Jump Code
	Write_Memory_Array(0xF8000, Rom, sizeof(Rom));     //The Rom file
	Write_Memory_Byte(0xF80FF, 0xFF);                  //Make sure STOP byte is not zero 0x00 = Stop
	Write_Memory_Byte(0xF8000, 0xFF);                  //Make sure int13 command port is 0xFF
	Write_Memory_Byte(0xF80F0, 0x03);                  //Video mode
	
	 //Video port something...?? makes it work 
	Write_IO_Byte(0X3DA, 0xFF); 
	
}

