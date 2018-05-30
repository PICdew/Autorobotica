#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_C7,bits=8)
#include <lcd.c>
#use standard_io(c)

int motor,motor_1,motor_2,habilita_1,habilita_2,sentido_1,sentido_2,rampa_1,rampa_2;
long velocidade_1,velocidade_2,passo_1,passo_2,rampa;
int Comando[7];
 
void RecebeComando(void){

 gets(comando); //comando é o Byte recebido pela serial 
 
      printf("\r\nrecebendo comando\r\n");
  
if (comando[0]=='C') 
{ 
printf ("comando=%x\r\n"comando[4]);

   if (comando[1]==0){
   motor_1=1;   
   printf ("motor_1=%u\r\n"motor_1);
   
   if (comando[2]==0){
   habilita_1=1;   
   }
   else{habilita_1=0;}
   printf ("habilita_1=%u\r\n",comando[2]);
   
   if (comando[3]==1){
   sentido_1=1;   
   }
   else{sentido_1=0;}
   printf ("sentido_1=%u\r\n",comando[3]);
   
 
   velocidade_1=comando[4];   
   printf ("velocidade_1=%lu\r\n",velocidade_1);
   
   passo_1=comando[5];
   printf ("passo_1=%lu\r\n",passo_1);
   
   rampa_1=comando[6];
   printf ("rampa=1%u\r\n",rampa_1);
   
   }
   
      if (comando[1]==1){
   motor_2=1;   
   printf ("motor_2=%u\r\n"motor_2);
   
   if (comando[2]==0){
   habilita_2=1;   
   }
   else{habilita_2=0;}
   printf ("habilita_2=%u\r\n",comando[2]);
   
   if (comando[3]==1){
   sentido_2=1;   
   }
   else{sentido_2=0;}
   printf ("sentido_2=%u\r\n",comando[3]);
   
 
   velocidade_2=comando[4];   
   printf ("velocidade_2=%lu\r\n",velocidade_2);
   
   passo_2=comando[5];
   printf ("passo_2=%lu\r\n",passo_2);
   
   rampa_2=comando[6];
   printf ("rampa=1%u\r\n",rampa_2);
   
   }

}
 
}  

 



void main(void)
{
  
while(true)
 
{
RecebeComando();

/*
long escravo[5],estado;

if (escravo[0]=='A') 
{ 
printf ("m%lu\r\n"escravo[1]);
printf ("recebendo\r\n");
if (escravo[1]==30) 
printf ("recebendo teste%lu\r\n"escravo[1]);

if (escravo[2]=='1') 
printf ("recebendo 1\r\n");

if (escravo[3]==1) 
printf ("recebendo motor_1\r\n");

if (escravo[4]=='3') 
printf ("recebendo 3\r\n");

switch (escravo[1]) 
{ 
case '0': {output_high(pin_B6);
printf ("0\r\n");
}
break; 
case '1': {output_low(pin_B6);
printf ("1\r\n");
}
break; 
} 
}  

delay_ms (500);
*/
}

}
   

