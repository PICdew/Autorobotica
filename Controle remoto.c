#INCLUDE <16F628A.H>
#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT    
#FUSES HS                  //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#use delay(clock=4000000)
#use fast_io(a)
#use fast_io(b)

int i,p,frequencia=600,dury=9,portadora=12,pulso=10;

void main(){

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
  setup_timer_2(T2_DIV_BY_4,0,1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(512);

         set_tris_b(0b00000000); 
         set_tris_a(0b11111111);
 
   while(true){
      setup_ccp1(CCP_PWM);
      set_pwm1_duty (512); 
      output_high(pin_b2);
      delay_us(52);
      output_low(pin_b2);
      delay_us(52);
      
   }
}
