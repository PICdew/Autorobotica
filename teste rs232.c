#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_C7,bits=8)
#include <lcd.c>
#use standard_io(c)
#use standard_io(a)
#use fast_io(b)
int motor,habilita,sentido,velocidade,passo,rampa;
EnviaComando();


void EnviaComando( int t_motor,int1 t_habilita, int t_sentido, int t_velocidade,
long int t_passo,int t_rampa){
long cmd[7];

cmd[0]='C';
cmd[1]=1;
cmd[2]=t_habilita;
cmd[3]=t_sentido;
cmd[4]=t_velocidade;
cmd[5]=t_passo;
cmd[6]=t_rampa;

printf("%c%c%c%c%c%c%c\r\n"cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6]); 


}




void main(void){
 lcd_init();  
 set_tris_b(0b1100000000); 
    while(true){ 
    
  output_high(pin_a0);
   motor=0;
   habilita=1;
   sentido=1;
   velocidade=5;
   passo=10000;
   rampa=0;
      EnviaComando(motor,habilita,sentido,velocidade,passo,rampa);
       printf(lcd_putc,"\fenviando:%u\nhabi%u\nfre%u"motor,habilita,sentido); 
   delay_ms (200);
   output_low(pin_a0);
    delay_ms (200);
  
   }
 
 
}        
   

