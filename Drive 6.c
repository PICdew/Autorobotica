#include <16F628a.h>
//#include <input.c>
#fuses HS,NOWDT,NOPROTECT,NOLVP,put
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_b4, rcv=PIN_b5)
#use fast_io(a)
#use fast_io(b)
//#use standard_io(b)


int comando=0;

int motor_1,motor_2,sentido_1,sentido_2,habilita,pulso;
long velocidade_1,velocidade_2,passo_1,passo_2,c_recebe,c_motor,c_pwm;

   static long int cmd;

 BYTE const posicao1[4] = {0b0101,0b1001,0b1010,0b0110};//sequencia se acionamento do motor
 int temp_velo1,velo_cont1,bobina1;
 long int s_passo1,c_passo1;

 BYTE const posicao2[4] ={0b0101,0b1001,0b1010,0b0110};//sequencia se acionamento do motor
 int temp_velo2,velo_cont2,bobina2;
 long int s_passo2,c_passo2;
 int timer;

void RecebeComando(void){

if(habilita==1){

 //comando � o Byte recebido pela serial
  
  if(bit_test(cmd,0))bit_set(comando,0);else bit_clear(comando,0);
  if(bit_test(cmd,1))bit_set(comando,1);else bit_clear(comando,1);
  
  if(bit_test(cmd,2))motor_1=1;else motor_1=0;
  if(bit_test(cmd,3))motor_2=1;else motor_2=0;
  if(bit_test(cmd,4))sentido_1=1;else sentido_1=0;
  if(bit_test(cmd,5))sentido_2=1;else sentido_2=0;
  
  if(bit_test(cmd,6))bit_set(velocidade_1,0);
  else bit_clear(velocidade_1,0);
  
  if(bit_test(cmd,7))bit_set(velocidade_1,1);
  else bit_clear(velocidade_1,1);
  
  if(bit_test(cmd,8))bit_set(velocidade_1,2);
  else bit_clear(velocidade_1,2);
 
  if(bit_test(cmd,9))bit_set(velocidade_2,0);
  else bit_clear(velocidade_2,0);
  
  if(bit_test(cmd,10))bit_set(velocidade_2,1);
  else bit_clear(velocidade_2,1);
  
  if(bit_test(cmd,11))bit_set(velocidade_2,2);
  else bit_clear(velocidade_2,2);
//}
 }
}
 

void Motor1( int t_sentido1, int velocidade1,long int passo1){

if(motor_1==1){
           
               enable_interrupts(INT_TIMER2);
               if(temp_velo1!=velocidade1){
               temp_velo1=velocidade1;
               velo_cont1=temp_velo1;
               }
                  else{
                     if(velo_cont1!=0)velo_cont1--;
                    
                       else{ 
//                           output_a(posicao1[bobina1]);//saida para o motor
                           velo_cont1=temp_velo1;
                  
                           if(t_sentido1==1){
                           bobina1++;
                           if(bobina1==4)bobina1=0;
                           }
                     
                           if(t_sentido1==0){
                           if(bobina1==0)bobina1=4;
                           bobina1--;
                           }
                          c_passo1--; 
                          
                        }
                  }
                 
            
         } 
     else {
      disable_interrupts(INT_TIMER2);
      output_a(0);
      }     
}      
      
void Motor2( int t_sentido2, int velocidade2,long int passo2){

if(motor_2==1){
               enable_interrupts(INT_TIMER2);
               if(temp_velo2!=velocidade2){
               temp_velo2=velocidade2;
               velo_cont2=temp_velo2;
               }
                  else{
                     if(velo_cont2!=0)velo_cont2--;                     
                       else{ 
//                           output_B(posicao2[bobina2]);//saida para o motor
                           velo_cont2=temp_velo2;
                  
                           if(t_sentido2==1){
                           bobina2++;
                           if(bobina2==4)bobina2=0;
                           }
                     
                           if(t_sentido2==0){
                           if(bobina2==0)bobina2=4;
                           bobina2--;
                           }
                          c_passo2--;  
                         
                        }         
                  }
                 
                   
}
else {
disable_interrupts(INT_TIMER2);
output_a(0);
}
} 

#int_TIMER2
void  TIMER2_isr(void){  
static int freq=0;
  
   if(freq==1){
   output_a(0);//saida para o motor
   output_B(0);//saida para o motor
   freq=0;
   setup_timer_2(T2_DIV_BY_4,68,16);
   }

   if(freq==0){
   output_a(posicao1[bobina1]);//saida para o motor
   output_B(posicao2[bobina2]);//saida para o motor
   freq=1;
   setup_timer_2(T2_DIV_BY_4,68,16);
   }
  }


 #int_TIMER0
void  TIMER0_isr(void){

}

void main(void) {
   setup_timer_0 (RTCC_DIV_16|RTCC_INTERNAL );
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);setup_wdt(WDT_2304MS);///
   setup_timer_2(T2_DIV_BY_4,68,16);
   enable_interrupts(INT_TIMER0);
   disable_interrupts(INT_TIMER2);
   disable_interrupts(GLOBAL);
   set_tris_a(0b00010000);
   set_tris_b(0b11110010);

printf("\r\nves�o Drive 2 \r\n"); 
//delay_ms(1900);

   while (TRUE) {   
gets(cmd);
habilita=1;

   if(input(pin_b6)==1){
   motor_1=1;
   motor_2=1;
   habilita=0;
   sentido_1=1;
   sentido_2=0;
   velocidade_1=1;
   velocidade_2=1;
   delay_ms(800);
   //printf("\r\nem teste \r\n"); 
   }
   else RecebeComando(); 
 
   if(timer<1)timer++;
   else{

  Motor1(sentido_1, velocidade_1,passo_1);
  Motor2(sentido_2, velocidade_2,passo_2);
  timer=0;
   }   
   
   }
    
 

}
