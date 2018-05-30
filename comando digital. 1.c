
/*******************************************************************************
*              Sistema de navega��o para rob�s aut�nomos
*
*                             Meca TCC 2012
*
* Comando Didital:   Novenbro de 2012                               Raul S F
********************************************************************************
*/

#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_B4,bits=8)
#include <lcd.c>
#use fast_io(a)
#use standard_io(b)
#use standard_io(c)
#use fast_io(d)
//#use fast_io(b)

int codico,c_codico,c_timer0,c_timer1,start;


#priority CCP1,TIMER1,TIMER0


#int_ccp1 
void Sinal(void){

   output_high(pin_c1);
   disable_interrupts(INT_CCP1);
   c_codico=0;
//    delay_us(10);
//    set_timer1(200);
   output_low(pin_c1); 
    setup_timer_2(T2_DIV_BY_16,16,16);
   enable_interrupts(INT_TIMER2);
   start=1;
   
}

#int_TIMER1
void  TIMER1_isr(void){
static int t_codico;

} 

#int_TIMER2
void  TIMER2_isr(void){
static int t_codico;
   
 
  if(start==3){
   disable_interrupts(INT_TIMER2);
   enable_interrupts(INT_CCP1);
  }
  
if(start==2){
   output_high(pin_c3);
   setup_timer_2(T2_DIV_BY_16,32,16);
   
   if(input(PIN_C2)==0){
   bit_set(t_codico,c_codico);
   }
   c_codico++;
   output_low(pin_c3);
 if(c_codico==8){
   c_timer1++;
   if(t_codico>8)codico=t_codico;
   c_codico=0;
   t_codico=0; 
   start=3;  
   }  
   }
   if(start==1){
   setup_timer_2(T2_DIV_BY_16,224,6);
   start=2;   
  }

}  

void main(void){
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_2(T2_DIV_BY_16,16,16);
   setup_ccp1(CCP_CAPTURE_FE);    
   enable_interrupts(INT_CCP1);
 
//   setup_adc_ports(AN0_AN1_AN3);
//   setup_adc(ADC_CLOCK_DIV_16);
//   setup_timer_0 (RTCC_DIV_32|RTCC_INTERNAL );
//   enable_interrupts(INT_TIMER0);
   disable_interrupts(INT_TIMER1);
   disable_interrupts(INT_TIMER2);
   ext_int_edge( H_TO_L );  
//   setup_comparator(NC_NC_NC_NC);
//   setup_vref(FALSE);
   lcd_init(); 
   set_tris_c(0b11111100);
   set_tris_b(0b00011111); 
   set_tris_a(0b00001011);
   output_high(pin_b0);
   output_high(pin_b1);
   output_high(pin_b2);
   output_high(pin_b3);
   output_high(pin_b4);
//   printf(lcd_putc,"Meca TCC 2012\nv. comando 16"); 
// printf("\fvers�o comando 11"); 
   delay_ms(000);//300
   output_low(pin_b0);
   output_low(pin_b1);
   output_low(pin_b2);
   output_low(pin_b3);
   output_low(pin_b4);
   enable_interrupts(GLOBAL);
   while(true){ 
     printf(lcd_putc,"\fTimer 0:\%u",c_timer0);
   printf(lcd_putc,"\nTimer 1:\%u",codico);
    delay_ms(100);
       ext_int_edge( L_TO_H ); 
   }  
}

