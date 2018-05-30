/*******************************************************************************
*              Sistema de navegaï¿½ï¿½o para robï¿½s autï¿½nomos
*                            Controle remoto
*                             AutoRobotica
*
* Controle Remoto 6.2:   Julho de 2014                                Raul S F
********************************************************************************
********************************************************************************
* Historico
* Revisao 32:31/10/2013;controle de potï¿½cia por PWM
* Revisao 5:31/10/2013;envio da potencia
* Revisao 51:02/11/2013;adiï¿½ï¿½o de um bit a transmiï¿½ï¿½o 
* Revisao 52:09/11/2013; bitstop
* Revisao 53:15/11/2013; acrescimo de botoe leds e relocaï¿½ï¿½o
* Revisao 53:15/11/2013; alteração dos codigos
********************************************************************************
*/

#include <16F628.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,put
#use delay(clock=10000000)
//#use fast_io(a)
//#use fast_io(b)

int portadora=11,pausa=50,um,codico=0,start,controle,dury=0,frequencia=10,
t_frequencia=0,potencia=0,modo=0,pisca=0,seguir=0,ciclo=33;
long int cont,soma,c_led=0;


#int_TIMER0

void  TIMER0_isr(void){
static int c_codico,c_controle,c_potencia,bitstop=0;
   
   if(start==5){
   output_low(pin_b6);
   bitstop--;
   um=1;
   if(bitstop==0)start=6;
   }
   
   if(start==4){      
   um=1;
   start=5;
   }
   
   if(start==3){
   c_potencia--;
   output_high(pin_b6);
   um=0;
   if(bit_test(potencia,c_potencia)){
   output_low(pin_b6); 
   um=1;
   }
      else{
   um=0;
   output_high(pin_b6);
   }
   if(c_potencia==0)start=4;
  }
   
   if(start==2){
    c_codico--;
   output_high(pin_b6);
   um=0;
  if(bit_test(codico,c_codico)){
  output_low(pin_b6); 
  um=1;
  }   
   else{
   um=0;
   output_high(pin_b6);
   }
   if(c_codico==0)start=3;
  }

  if(start==1){
   c_controle--;
   setup_timer_0( RTCC_INTERNAL|RTCC_DIV_32);
   output_high(pin_b6);
   um=0;
  if(bit_test(controle,c_controle)){
  output_low(pin_b6); 
  um=1;
  }
   
   else{
   output_high(pin_b6);
   um=0; 
   }         
    if(c_controle==0){
    start=2;
    
    }
  }
   if(start==0){
   output_low(pin_b6); 
   um=1;
   setup_timer_0( RTCC_INTERNAL|RTCC_DIV_64);
    set_timer0(120);
   start=1;   
   c_controle=8;//comprimentos em bits
   c_codico=6; //comprimentos em bits
   c_potencia=6;//comprimentos em bits
   bitstop=2;//comprimentos em bits

   if(potencia<8){
//   dury=dury+3;//inclemento de potência
   potencia=potencia+1;
   ciclo=ciclo+1;//43
   }
   if(potencia>7){
   potencia=potencia+1;
   ciclo=65;
   output_low(pin_b7);
   }
  if(potencia==10){
   dury=1;//inclemento de potência
   potencia=1;
   ciclo=33;
   }
//    setup_timer_2(T2_DIV_BY_1,(65-potencia),1);//65
  }
  
   if(start==6){
   disable_interrupts(INT_TIMER0);
   output_high(pin_b6);
   um=0;
   set_timer1(0);
   pausa=0;
   start=0;         
   } 
   if(start>0) set_timer0(120);
   setup_timer_2(T2_DIV_BY_1,(ciclo),1);
     if(um==1){setup_ccp1(CCP_PWM);
      set_pwm1_duty(ciclo/2);
    }
      else{
      setup_ccp1(CCP_OFF);
      output_low(pin_b3);
      }
} 

#int_TIMER1
void  TIMER1_isr(void){
if(t_frequencia==0){
   output_low(pin_b7);
   t_frequencia=frequencia;
  }
  else t_frequencia--;
  
   if(t_frequencia<=dury){
     output_high(pin_b7);
  }
}

//tempo gasto no atraso 7/1000000=2us
//portadora 1/(38000000*2)=13-2us
//40/1000000=2us

void main(){
   port_b_pullups(TRUE);
   setup_timer_0( RTCC_INTERNAL|RTCC_DIV_32);//setup_wdt(WDT_18MS);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_2(T2_DIV_BY_16,255,16);//65
  // enable_interrupts(INT_TIMER2);
   disable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
  //enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_TIMER0);
    set_tris_a(0b00000000);
    set_tris_b(0b00111111);
   output_high(pin_b6);
   output_high(pin_b7);
    output_high(pin_a0);
    delay_ms(100);
    output_high(pin_a1);
    delay_ms(100);
    output_high(pin_a2);
    output_low(pin_a0);
    delay_ms(100);
    output_high(pin_a3);
    output_low(pin_a1);
    delay_ms(100);
    output_high(pin_a4);
    output_low(pin_a2);
    delay_ms(100);        
    output_low(pin_a3);
    delay_ms(100);  
    output_low(pin_a4);
    delay_ms(100); 
    output_high(pin_a0);
    
    output_low(pin_b7);
    
    controle=10;//codigo do controle remoto:1
//    controle=20;//codigo do controle remoto:2
//    controle=30;//codigo do controle remoto:3
//    controle=40;//codigo do controle remoto:4
codico=controle;
 while(true){
  
   if(codico==(controle+8)){//Pisca LED seguir
       if(c_led==100){
       pisca=!pisca;
       c_led=0;
       }
       else c_led++;    
    if(pisca==1) output_high(pin_a2);
    if(pisca==0) output_low(pin_a2);
   }
   
   soma++;//tempo para zerar comando
   if((soma==3800)&&(codico!=(controle+8))){//controle+8 comando follow
   codico=controle;;
   soma=0;
   }
   
 if(pausa==(10+(controle*3))){//100 repetiï¿½ao
   start=0;
   enable_interrupts(INT_TIMER0);
   um=1;
   pausa=0;
 }
/*       while(um==1){
     
      output_low(pin_b6);
      delay_cycles( 8 );
      delay_us(portadora);
//     output_high(pin_b6);//desabilita 30kH
      delay_us(portadora);
       
      }
*/
 if(input(pin_b0)==0){//ON/MODO/STOP
    codico=30;
  if(modo==1){
    output_high(pin_a0);
    output_low(pin_a1);
    output_low(pin_a2);
    output_low(pin_a3);
    output_low(pin_a4); 
    codico=50;//STOP
    modo=2;
    delay_ms(80);
    } 
  if(modo==0){
    output_low(pin_a0);
    output_high(pin_a1);
    output_high(pin_a2);
    output_high(pin_a3);
    output_high(pin_a4);  
    modo=1;
    codico=50;//STOP
    delay_ms(80);   
    }
   if(modo==2){
   modo=0;
   delay_ms(80);
   }
       
    cont=0;
      while(input(pin_b0)==0){//Off
      cont++;
      delay_ms(10);
      if(cont>100){
      output_low(pin_a0);
      cont=0;
         output_low(pin_a0);
         output_low(pin_a1);
         output_low(pin_a2);
         output_low(pin_a3);
         output_low(pin_a4);
         output_low(pin_b5);
         output_low(pin_b6);
         output_low(pin_b7);
         enable_interrupts(INT_EXT);;
         ext_int_edge(H_TO_L);
         delay_ms(100);
         sleep();
         delay_ms(300);
         reset_cpu();
      }
      }
     cont=0; 
  }
   if(input(pin_b2)==0){
    if(modo==0){
   output_high(pin_a1);
   output_low(pin_a2);
   output_low(pin_a3);
   output_low(pin_a4);;
   codico=31;//ir para 1
    }
     if(modo==1){
   output_high(pin_a1);
   output_low(pin_a2);
   output_low(pin_a3);
   output_low(pin_a4);;
   codico=(controle+5);//codigo de comando
    }
   } 
/*   if(input(pin_b7)==0){
   if(modo==0){
   output_low(pin_a1);
   output_high(pin_a2);
   output_low(pin_a3);
   output_low(pin_a4);
    codico=32;//ir para 2
    }
   if(modo==1){
   output_low(pin_a1);
   output_high(pin_a2);
   output_low(pin_a3);
   output_low(pin_a4);
    codico=(controle+6);//codigo de comando
    }  
   }
 */   
   if(input(pin_b4)==0){
    if(modo==0){
   output_low(pin_a1);
   output_low(pin_a2);
   output_high(pin_a3);
   output_low(pin_a4);
    codico=33;//ir para 3
     }
   if(modo==1){
   output_low(pin_a1);
   output_low(pin_a2);
   output_high(pin_a3);
   output_low(pin_a4);
   codico=(controle+7);//codigo de comando 
    }
   } 
      if(input(pin_b5)==0){//CALL/FOLLOW
    if(modo==0){
   output_high(pin_a1);
   output_low(pin_a2);
   output_low(pin_a3);
   output_high(pin_a4);
    codico=(30+(controle/10));//CALL
     }
   if(modo==1){
   output_low(pin_a1);
   output_high(pin_a2);
   output_low(pin_a3);
   output_low(pin_a4);
   codico=(controle+8);//FOLLOW
    } }
   pausa++;   
   delay_ms(1);
   
    if(input(pin_b1)==0){//CALL/FOLLOW
      if(seguir==1){
      output_low(pin_a1);
      output_high(pin_a2);
      output_low(pin_a3);
      output_low(pin_a4);
      codico=(controle+8);//FOLLOW
      }
      if(seguir==0){
       output_high(pin_a0);
       output_low(pin_a1);
       output_low(pin_a2);
       output_low(pin_a3);
       output_low(pin_a4); 
       codico=50;//STOP
      }
    delay_ms(300);
    seguir=!seguir;
    }


 } 
}
