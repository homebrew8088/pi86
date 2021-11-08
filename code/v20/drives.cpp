#include "drives.h"

//////////////////
//Disk Handler
///////////////////

string drive_A;    //Floppy A:  img file    
string drive_C;         //Hard Drive C:  img file 



void Get_Disk_Parameters_A()
{
   std::fstream MemoryFile;                  //This opens the drive img
   MemoryFile.open(drive_A);                 //File to open
   MemoryFile.seekg (0, MemoryFile.beg);     //Moves back to the begining
   char Floppy[0x200];                       //Char array to hold the data only reading first sector
   MemoryFile.read(Floppy, sizeof(Floppy));  //Read the file into the array
   MemoryFile.close();                       //Close the file
   
   char Media_Descriptor[0x10] = {0x04, 0, 0, 0, 0, 0, 0, 0, 0xF8, 0x02, 0, 0, 0, 0x01, 0, 0};
   //Start at port 11  
    Write_Memory_Byte(0xF800B, Media_Descriptor[Floppy[0x15] & 0x0F]);    //Media Descriptor - BL

    Write_Memory_Byte(0xF800C, Floppy[0x1A]);                             //Low byte heads per cylinder - DH -1
    Write_Memory_Byte(0xF800D, Floppy[0x1B]);                             //High byte heads per cylinder
            
    Write_Memory_Byte(0xF800E, Floppy[0x0B]);                             //Low bytes per sector - uS
    Write_Memory_Byte(0xF800F, Floppy[0x0C]);                             //High bytes per sector
   
   int Head_Per_Cylinder = (Floppy[0x1B] << 8) + Floppy[0x1A];    
   int Sector_Per_Track = (Floppy[0x19] << 8) + Floppy[0x18]; 
   int Number_Of_Sectors = (Floppy[0x14] << 8) + Floppy[0x13]; 
   
   int Number_Of_Cylinders = Number_Of_Sectors / Sector_Per_Track / Head_Per_Cylinder;
    Write_Memory_Byte(0xF8011, Number_Of_Cylinders);                      //CH
   
   Number_Of_Cylinders = (Number_Of_Cylinders >> 2) & 0xC0;
   Sector_Per_Track = Sector_Per_Track & 0X3F;                    //CL
    Write_Memory_Byte(0xF8010, Number_Of_Cylinders + Sector_Per_Track);
    Write_Memory_Byte(0xF8012, 0x00);             //Always zero for floppy
    Write_Memory_Byte(0xF8013, 0x00);             //Always zero for floppy
    Write_Memory_Byte(0xF8014, 0x00);             //Always zero for floppy
    Write_Memory_Byte(0xF8015, 0x00);             //Always zero for floppy
    Write_Memory_Byte(0xF8016, 0X01);             //Drive type
}
void Get_Disk_Parameters_C()
{
   std::fstream MemoryFile;                  //This opens the drive img
   MemoryFile.open(drive_C);                 //File to open
   MemoryFile.seekg (0, MemoryFile.beg);     //Moves back to the begining
   char drive[0x200];                       //Char array to hold the data only reading first sector
   MemoryFile.read(drive, sizeof(drive));  //Read MBR
   int Hidden_Sectors;
   //Locates boot partition
   if(drive[0x1BE] == 0x80){Hidden_Sectors = drive[0x1C6] + (drive[0x1C7] << 8) + (drive[0x1C8] << 16) + (drive[0x1C9] << 24);}
   else if(drive[0x1CE] == 0x80){Hidden_Sectors = drive[0x1D6] + (drive[0x1D7] << 8) + (drive[0x1D8] << 16) + (drive[0x1D9] << 24);}
   else if(drive[0x1DE] == 0x80){Hidden_Sectors = drive[0x1E6] + (drive[0x1E7] << 8) + (drive[0x1E8] << 16) + (drive[0x1E9] << 24);}
   else if(drive[0x1EE] == 0x80){Hidden_Sectors = drive[0x1F6] + (drive[0x1F7] << 8) + (drive[0x1F8] << 16) + (drive[0x1F9] << 24);}
   //No boot partion MBR
   else{MemoryFile.close(); Stop_Flag = true; usleep(20000); printf("No boot partion in MBR C: \n");}
   //Read volume boot record
   MemoryFile.seekg (0x200 * Hidden_Sectors, MemoryFile.beg);
   MemoryFile.read(drive, sizeof(drive));
   MemoryFile.close();                       //Close the file
   
   //char Media_Descriptor[0x10] = {0x04, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x02, 0, 0, 0, 0x01, 0, 0};
   //Start at port 11  
   //Write_Memory_Byte(0xF800B, Media_Descriptor[drive[0x15] & 0x0F]);    //Media Descriptor - BL

    Write_Memory_Byte(0xF800C, drive[0x1A]);                             //Low byte heads per cylinder - DH -1
    Write_Memory_Byte(0xF800D, drive[0x1B]);                             //High byte heads per cylinder
            
    Write_Memory_Byte(0xF800E, drive[0x0B]);                             //Low bytes per sector - uS
    Write_Memory_Byte(0xF800F, drive[0x0C]);                             //High bytes per sector
   
   int Head_Per_Cylinder = (drive[0x1B] << 8) + drive[0x1A];    
   int Sector_Per_Track = (drive[0x19] << 8) + drive[0x18]; 
   int Number_Of_Sectors = (drive[0x14] << 8) + drive[0x13]; 
   
   int Number_Of_Cylinders = Number_Of_Sectors / Sector_Per_Track / Head_Per_Cylinder;
    Write_Memory_Byte(0xF8011, Number_Of_Cylinders);                      //CH
   
   Number_Of_Cylinders = (Number_Of_Cylinders >> 2) & 0xC0;
   Sector_Per_Track = Sector_Per_Track & 0X3F;                    //CL
    Write_Memory_Byte(0xF8010, Number_Of_Cylinders + Sector_Per_Track);
   
   int Small_Sectors = (drive[0x14] << 8) + drive[0x13];
   if(Small_Sectors == 0x0000)
   {
       Write_Memory_Byte(0xF8012, drive[0x20]);   //Big sector
       Write_Memory_Byte(0xF8013, drive[0x21]);
       Write_Memory_Byte(0xF8014, drive[0x22]);
       Write_Memory_Byte(0xF8015, drive[0x23]);
   }
   else
   {
       Write_Memory_Byte(0xF8012, drive[0x13]);   //Small sector
       Write_Memory_Byte(0xF8013, drive[0x14]);
       Write_Memory_Byte(0xF8014, 0x00);
       Write_Memory_Byte(0xF8015, 0x00);
   }
    Write_Memory_Byte(0xF8016, 0X03);
}
void Int13()
{
   char Int13_Command =  Read_Memory_Byte(0xF8000);
   char Drive =  Read_Memory_Byte(0xF8006);

   if(Int13_Command != 0xFF)
   {
      if(Drive == 0x00){Get_Disk_Parameters_A();}   //File to open
      if(Drive == 0x80){Get_Disk_Parameters_C();}
      char int13_data[0X20];
       Read_Memory_Array(0xF8000, int13_data, 0X20);
      
      if(Int13_Command == 0x00)
      {
         //BIOS DOES ALL THE WORK
         //RESET DISK SYSTEM
         //NOTHING TO RESET
      }
      if(Int13_Command == 0x01)
      {
         //BIOS DOES ALL THE WORK
         //GET STATUS OF LAST OPERATION
      }  
      if(Int13_Command == 0x02) //read
      {
         int Cylinder = (int13_data[3] << 8) + int13_data[2];
         int Sector = int13_data[4];
         int Head = int13_data[5];
         int Bytes_Per_Sector = (int13_data[0x0F] << 8) + int13_data[0x0E];
         int Sector_Per_Track = (int13_data[0x10] & 0X3F) ;
         int Head_Per_Cylinder = (int13_data[0x0D] << 8) + int13_data[0x0C];
         int Number_Of_Sectors = int13_data[1];
         int LBA = (Cylinder * Head_Per_Cylinder + Head) * Sector_Per_Track + (Sector - 1);
         int Buffer_Address = (int13_data[10] << 12) + (int13_data[9] << 4) + (int13_data[8] << 8) + int13_data[7];
         
         std::fstream MemoryFile;                                    //This opens the drive img
         if(Drive == 0x00){MemoryFile.open(drive_A);}   //File to open
         if(Drive == 0x80){MemoryFile.open(drive_C);}
         MemoryFile.seekg (LBA * Bytes_Per_Sector, MemoryFile.beg);  //Set position 
         char drive[Number_Of_Sectors * Bytes_Per_Sector];          //Char array to hold the data
         MemoryFile.read(drive, sizeof(drive));                    //Read the file into the array
         MemoryFile.close();                                         //Close the file

          Write_Memory_Array(Buffer_Address, drive, sizeof(drive));
      }
      if(Int13_Command == 0x03)
      {
         int Cylinder = (int13_data[3] << 8) + int13_data[2];
         int Sector = int13_data[4];
         int Head = int13_data[5];
         int Bytes_Per_Sector = (int13_data[0x0F] << 8) + int13_data[0x0E];
         int Sector_Per_Track = (int13_data[0x10] & 0X3F) ;
         int Head_Per_Cylinder = (int13_data[0x0D] << 8) + int13_data[0x0C];
         int Number_Of_Sectors = int13_data[1];
         int LBA = (Cylinder * Head_Per_Cylinder + Head) * Sector_Per_Track + (Sector - 1);
         int Buffer_Address = (int13_data[10] << 12) + (int13_data[9] << 4) + (int13_data[8] << 8) + int13_data[7];
         char drive[Number_Of_Sectors * Bytes_Per_Sector];    //Char array to hold the data
         
          Read_Memory_Array(Buffer_Address, drive, sizeof(drive));

         std::fstream MemoryFile;                                    //This opens the drive img
         if(Drive == 0x00){MemoryFile.open(drive_A);}   //File to open
         if(Drive == 0x80){MemoryFile.open(drive_C);}
         MemoryFile.seekp (LBA * Bytes_Per_Sector, MemoryFile.beg);  //Sets position to write to           
         MemoryFile.write(drive, sizeof(drive));                   //Writes only new data
         MemoryFile.close();                                         //Close img
      }
      if(Int13_Command == 0x08)//PARAMETERS
      {
         if(int13_data[6] == 0x00){Get_Disk_Parameters_A();}   
         if(int13_data[6] == 0x80){Get_Disk_Parameters_C();}
      }  
      if(Int13_Command == 0x15)//GET DISK TYPE
      {
         if(int13_data[6] == 0x00){Get_Disk_Parameters_A();}   
         if(int13_data[6] == 0x80){Get_Disk_Parameters_C();}
      }  
       Write_Memory_Byte(0xF8000, 0xFF);  
   }

}	
void Drives()
{
   char Int13_Command; 
	while (Stop_Flag != true)   
	{
		usleep(500);
		Int13_Command =  Read_Memory_Byte(0xF8000);  	//Check for Int13 command
		if(Int13_Command != 0XFF)                       	//Check for Int13         
		{
			Int13();                                     	//Raspberry PI Int13 handler
		}  
	} 
}

void Start_Drives(string Floppy, string Hard_Drive)
{
   drive_A = Floppy;         
   drive_C = Hard_Drive;   
   thread start_drives(Drives);
   start_drives.detach();
}
