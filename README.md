# pi86

This is the code for my 8088/8086 (Really V20/V30) Raspberry Pi "hat"

https://www.homebrew8088.com/home/raspberry-pi-second-project



The code is fairly simple and easy to modify. Basically the Raspberry PI toggles the Clock then reads the Control Bus and then provides the 8088 what it is requesting. It will read the ALE pin and save the address then provide the proper Memory or IO Read/Write.  

Disadvantages:  

The speed, the processor is only running at about 0.3 MHz the best I could calculate.  But on the flip side the drive read writes are very fast because the memory is virtual on raspberry pi.

Not all 8088/8086 Processors will work. The power is connected to the 3.3v pin on the PI. Most NEC V20/V30's will operate 3V - 7V so this is not problem.   



I have written a c library that helps with interfacing the 8088 PCB.  I have also begun to develop a GUI window that emulates CGA/VGA graphics 

-I tested this with a fresh install of Raspberry PI os and it ran just fine.

-To compile I had to install the SDL library.

sudo apt-get update	

sudo apt-get upgrade

sudo apt-get install gcc build-essential libsdl2-dev

-To compile the bios file install nasm 

sudo apt-get install nasm

*** This is experimental use at your own risk. 

This current build runs very stable. I have left it running for seveal hours and came back and it was still running just fine. I encourage you to download the source code to the projects and give them a try and make modification. 
