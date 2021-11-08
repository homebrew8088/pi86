////////////////////////////
//System Timer INT 0X08
///////////////////////////
#include "timer.h"

void System_Timer()
{
   while(Stop_Flag != true)
   {
      usleep(54926); 
      IRQ0();
   }
}
void Start_System_Timer()
{
   thread system_timer(System_Timer);
   system_timer.detach();
}
