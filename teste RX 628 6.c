#include <16F628.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_b4, rcv=PIN_b5)


#use fast_io(a)
#use fast_io(b)
//#use standard_io(b)

int motor_1,motor_2,sentido_1,sentido_2,habilita;
long velocidade_1,velocidade_2,passo_1,passo_2;
int Comando[9];
short f_teste;


teste();

void RecebeComando(void){
if(habilita==1){
 gets(comando); //comando é o Byte recebido pela serial 
 
      printf("\r\nrecebendo \r\n");
      
  
if (comando[0]=='C') 
{ 
printf ("comando=%c\r\n"comando[0]);

   if (comando[1]==0)
   motor_1=1;   
     
   else {motor_1=0;}   
   printf ("motor_1=%u\r\n"motor_1);
   
   if (comando[2]==1){
   motor_2=1;   
   }
   else{motor_2=0;}
   printf ("motor_2=%u\r\n",comando[2]);
   
   if (comando[3]==1){
   sentido_1=1;   
   }
   else{sentido_1=0;}
   printf ("sentido_1=%u\r\n",comando[3]);
   
   if (comando[4]==1){
   sentido_2=1;   
   }
   else{sentido_2=0;}
   printf ("sentido_2=%u\r\n",comando[4]);
   
   
   velocidade_1=comando[5];   
   printf ("velocidade_1=%u\r\n",comando[5]);
   
 
    velocidade_2=comando[6];   
    printf ("velocidade_2=%u\r\n",comando[6]);
   
   
    passo_1=comando[7];   
    printf ("passo_1=%u\r\n",comando[7]);
   
   

    passo_2=comando[8];   
    printf ("passo_2=%u\r\n",comando[8]);
   
}
} 
}

void Motor1( int t_sentido1, int velocidade1,long int passo1){

static BYTE const posicao1[5] = {0b1000,0b0001,0b0010,0b0100,0b0000};//sequencia se acionamento do motor
static int temp_velo1,velo_cont1,bobina1;
static long int s_passo1,c_passo1;

     
      if(s_passo1!=passo1){
      s_passo1=passo1;
      c_passo1=s_passo1;
      }
         else{            
            if(c_passo1!=0){
               if(temp_velo1!=velocidade1){
               temp_velo1=velocidade1;
               velo_cont1=temp_velo1;
               }
                  else{
                     if(velo_cont1!=0)velo_cont1--;
                    
                       else{ 
                           output_a(posicao1[bobina1]);//saida para o motor
                           velo_cont1=temp_velo1;
                  
                           if(t_sentido1==1){
                           bobina1++;
                           if(bobina1==4)bobina1=0;
                           }
                     
                           if(t_sentido1==0){
                           if(bobina1==0)bobina1=3;
                           bobina1--;
                           }
                          c_passo1--; 
                           if(c_passo1==0)output_a(posicao1[4]);
                        }         
                  }
                 
            }
         }  
      
      
}

void Motor2( int t_sentido2, int velocidade2,long int passo2){

static BYTE const posicao2[5] = {0b1000,0b0001,0b0010,0b0100,0b0000};//sequencia se acionamento do motor
static int temp_velo2,velo_cont2,bobina2;
static long int s_passo2,c_passo2;

   
      if(s_passo2!=passo2){
      s_passo2=passo2;
      c_passo2=s_passo2;
      }
         else{            
            if(c_passo2!=0){
               if(temp_velo2!=velocidade2){
               temp_velo2=velocidade2;
               velo_cont2=temp_velo2;
               }
                  else{
                     if(velo_cont2!=0)velo_cont2--;                     
                       else{ 
                           output_B(posicao2[bobina2]);//saida para o motor
                           velo_cont2=temp_velo2;
                  
                           if(t_sentido2==1){
                           bobina2++;
                           if(bobina2==4)bobina2=0;
                           }
                     
                           if(t_sentido2==0){
                           if(bobina2==0)bobina2=3;
                           bobina2--;
                           }
                          c_passo2--;  
                          if(c_passo2==0)output_B(posicao2[4]);
                        }         
                  }
                 
            }
         }  
      
} 
 #int_TIMER0
void  TIMER0_isr(void){

static int timer;

   if(timer<12)timer++;
   else{
  Motor1(sentido_1, velocidade_1,passo_1);
  Motor2(sentido_2, velocidade_2,passo_2);
 
   timer=0;
   }

}

void main(void) {
   setup_timer_0 (RTCC_DIV_32|RTCC_INTERNAL );
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   set_tris_a(0b00010000);
   set_tris_b(0b11110000);

printf("\r\nvesão RX 628 6 \r\n"); 
delay_ms(1900);

   while (TRUE) {   

habilita=1;

if(input(pin_b6)==1){
motor_1=1;
motor_2=1;
habilita=0;
f_teste=!f_teste;
 sentido_1=1;
 velocidade_1=3;
 passo_1=30+f_teste;
 sentido_2=1;
 velocidade_2=4+f_teste;
 passo_2=15+f_teste;
 delay_ms(800);
printf("\r\nem teste \r\n"); 
}
else RecebeComando(); 


  
   }
}

