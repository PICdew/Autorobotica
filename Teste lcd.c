#include <16f877a.h>
#use delay(clock=2000000)
#fuses hs
#include <lcd.c>

int x;

long rise,fall,pulse_width;

#int_ccp2
void isr()
{
   rise = CCP_1;
   fall = CCP_2;

   pulse_width = fall - rise;     // CCP_1 is the time the pulse went high
} 

void main()
{
   setup_ccp1(CCP_CAPTURE_RE);    // Configure CCP1 to capture rise
   setup_ccp2(CCP_CAPTURE_FE);    // Configure CCP2 to capture fall
   setup_timer_1(T1_INTERNAL);    // Start timer 1

   enable_interrupts(INT_CCP2);   // Setup interrupt on falling edge
   enable_interrupts(GLOBAL);
lcd_init();

   while(true)
   {
    delay_ms(500);
   
   printf(lcd_putc,"\fsubida:%lu\ndecida:%lu",rise,fall);
  
   }
}
