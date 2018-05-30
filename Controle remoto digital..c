/*******************************************************************************
*              Sistema de navega��o para rob�s aut�nomos
*                            Controle remoto
*                             Meca TCC 2012
*
* Controle Remoto 3:   Setenbro de 2012                                Raul S F
********************************************************************************/

#include <16F628.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,put
#use delay(clock=4000000)
#use fast_io(a)
#use fast_io(b)

int frequencia=5,dury=3,portadora=65,pausa=50, c_dury;
int t_dury,c_pulso,pulso, cont,f_int,um;
int  codico=0b10101001,c_codico,start;


#int_TIMER1
void  TIMER1_isr(void){
  
} 

#int_TIMER2

void  TIMER2_isr(void){
static int c_codico;


  if(start==1){
   setup_timer_2(T2_DIV_BY_4,137,16);
   um=0;
  if(bit_test(codico,c_codico)){
  um=1;
  }
   
   else{
   um=0; 
   }   
    c_codico++;   
  }
   if(start==0){
   um=1;
   setup_timer_2(T2_DIV_BY_16,66,16);
   output_low(pin_b4);
   start=1;   
  }
  
   if(c_codico==9){
   disable_interrupts(INT_TIMER2);
   output_high(pin_b4);
   um=0;
   set_timer1(0);
   c_codico=0;
   pausa=0;
   start=0; 
   } 
  
} 

#int_EXT
void  EXT_isr(void)
{

}     
//tempo gasto no atraso 7/1000000=2us
//portadora 1/(38000000*2)=13-2us
//40/1000000=2us

void main(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32);//setup_wdt(WDT_18MS);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_2(T2_DIV_BY_16,66,16);
    enable_interrupts(INT_TIMER2);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
    set_tris_a(0b00000000);
    set_tris_b(0b11000111);
    output_high(pin_a0);
    output_high(pin_a1);
    output_high(pin_a2);
//    delay_ms(100);
    output_low(pin_a0);
    output_low(pin_a2);
    output_high(pin_b4);
    
 while(true){

 if(pausa==100){
   start=0;
   enable_interrupts(INT_TIMER2);
   um=1;
 }
       while(um==1){
     
      output_low(pin_b4);      
      delay_us(portadora);
      output_high(pin_b4);
       delay_us(portadora); 
      }

 if(input(pin_b0)==1){

    output_high(pin_a1);
    output_low(pin_a0);
    output_low(pin_a2);
    codico=0b10101010;
 /*   
      while(input(pin_b0)==1){
      cont++;      
         if(cont==30){
         cont=0;
         output_low(pin_a0);
         output_low(pin_a1);
         output_low(pin_a2);
         output_low(pin_a3);
         output_low(pin_b4);
         cont2=0;
            while(cont2<10000)cont2++;
            enable_interrupts(GLOBAL);
            sleep();            
          }
      }*/
  }
    if(input(pin_b1)==1){
    output_low(pin_b4);
    output_high(pin_a0);
    output_low(pin_a1);
    output_low(pin_a2);
    codico=0b10101110;
    }
    
    if(input(pin_b2)==1){
    output_low(pin_b4);
    output_low(pin_a0);
    output_low(pin_a1);
    output_high(pin_a2);
    codico=0b10101011;
    } 
   pausa++;   
   delay_ms(1);


 } 
}
