#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_B4,bits=8)
#include <lcd.c>
#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)
//#use fast_io(b)

int f_habilita,f_destino,f_orientacao,f_frente,f_desvio,f_re,c_passo,ok;
int motor1,motor2,sentido1,sentido2,velocidade1,velocidade2,mult,soma,cont;
long int passo1,passo2;

void Frente(void){

   if(f_habilita==1){
      if((f_frente==1)&(f_desvio==1)){
      motor1=1;
      sentido1=1;  
      passo1=30;
      velocidade1=3;
      
      motor2=1;
      sentido2=1;  
      passo2=30;
      velocidade2=3;
      
      c_passo--;
      if(c_passo==0){
      ok=1;
      motor1=0;
      motor2=0;      
      }
      }
      if((f_frente==1)&(f_desvio==0)){
      motor1=1;
      sentido1=1;  
      passo1=255;
      velocidade1=2;
      
      motor2=1;
      sentido2=1;  
      passo2=255;
      velocidade2=2;
      }
      
   }
}

void EnviaComando( int t_motor1,int t_motor2, int t_sentido1, int t_sentido2, 
int t_velocidade1, int t_velocidade2,int t_passo1,int t_passo2 ){
static int cmd[9];
static int t_cmd[9];

cmd[0]='C';
cmd[1]=t_motor1;
cmd[2]=t_motor2;
cmd[3]=t_sentido1;
cmd[4]=t_sentido2;
cmd[5]=t_velocidade1;
cmd[6]=t_velocidade2;
cmd[7]=t_passo1;
cmd[8]=t_passo2;

   if((t_cmd[1]!=cmd[1])||(t_cmd[2]!=cmd[2])||(t_cmd[3]!=cmd[3])
   ||(t_cmd[4]!=cmd[4])||(t_cmd[5]!=cmd[5])||(t_cmd[6]!=cmd[6])
   ||(t_cmd[7]!=cmd[7])||(t_cmd[8]!=cmd[8])){
   t_cmd[0]=cmd[0];
   t_cmd[1]=cmd[1];
   t_cmd[2]=cmd[2];
   t_cmd[3]=cmd[3];
   t_cmd[4]=cmd[4];
   t_cmd[5]=cmd[5];
   t_cmd[6]=cmd[6];
   t_cmd[7]=cmd[7]; 
   t_cmd[8]=cmd[8]; 
   
   printf("%c%c%c%c%c%c%c%c%c\r\n"cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7],cmd[8]); 
   }
}  

#int_TIMER0
void  TIMER0_isr(void){

static int timer;

   if(timer<12)timer++;
   else{
   Frente();
   EnviaComando(motor1,motor2,sentido1,sentido2,velocidade1,velocidade2,passo1,passo2);
   printf(lcd_putc,"\fenviando:%u\nveloc.:%u\ dir%u"motor1,velocidade1,cont); 
  
   }
}   
void main(void){
// setup_adc_ports(AN0);
//   setup_adc(ADC_CLOCK_DIV_16);
   setup_timer_0 (RTCC_DIV_2|RTCC_INTERNAL );
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
//   setup_comparator(NC_NC_NC_NC);
//   setup_vref(FALSE);
   lcd_init();  
 set_tris_b(0b1100000010); 
 set_tris_a(0b0000000000);
 
 printf(lcd_putc,"\fversão teste TX 16"); 
 printf("\fversão teste TX 18"); 
 delay_ms(600);
 
    while(true){ 
    
  output_high(pin_a0);

  
    if(input(pin_b0)==1){
   motor1=1;
   sentido1=1;  
   passo1=80;
   velocidade1=4;
 
   }
   else {
   motor1=1;
   sentido1=1;  
   passo1=60;
   velocidade1=4;
   }
       delay_ms (100);
       
   if(input(pin_b1)==1){
   motor2=1;
   cont=3;
   sentido2=1;  
   passo2=50;
   velocidade2=2;
    }
    
    IF((input(pin_b0))&(input(pin_b1))==1){
    motor1=1;
   sentido1=1;  
   passo1=90;
   motor2=1;
   sentido2=0;  
   passo2=100;
 
    }
  
   
   output_low(pin_a0);
   delay_ms (100);
  
   if (cont>10)cont=0;
    
  
   }
 
 
}        
   

