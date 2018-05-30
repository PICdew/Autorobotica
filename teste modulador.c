#INCLUDE <16F628A.H>
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#use delay(clock=4000000)

int i,p,frequencia=600,dury=9,portadora=12,pulso=10;

void main()
{
  
 
   while(true){
   output_high(pin_a3);
   
       if(input(pin_a2)==1){
       while(p<pulso){
   
      while(i<dury){      
      output_high(pin_b2);
      delay_us(portadora);
      output_low(pin_b2);
      delay_us(portadora);
      i++;
      }
      
    i=0;  
    output_low(pin_b2);
    delay_us(frequencia);
      pulso++;
    }
 pulso=0;
   
    }
    delay_ms(100);
    output_low(pin_a3);
    delay_ms(100);
 
 } ;
  
   
}
