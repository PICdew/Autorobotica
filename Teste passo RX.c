#include <16f628a.h>
#FUSES NOWDT, INTRC_IO, NOPUT, NOPROTECT, NOBROWNOUT, MCLR, NOLVP, NOCPD
#use delay(clock=10000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_B6,bits=8)
#use standard_io(a)
//#use standard_io(b)

int motor,motor_1,motor_2,habilita_1,habilita_2,sentido_1,sentido_2,rampa_1,rampa_2;
long velocidade_1,velocidade_2,passo_1,passo_2,rampa;
int Comando[7];
long int passo1,passo2,cont;

 
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


void Motor1( int1 t_habilita1, int t_sentido1, int velocidade1,long int passo1){

static int posicao1[4] = {0b1010,0b0110,0b0101,0b1001};
static int temp_velo1,velo_cont1,bobina1;
static long int s_passo1,c_passo1;

   if (t_habilita1==1){   
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
                           output_a(posicao1[bobina1]);
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
                        }         
                  }
                 
            }
         }  
      }
}



void Motor2( int1 t_habilita2, int t_sentido2, int velocidade2,long int passo2){

static int posicao2[4] = {0b1010,0b0110,0b0101,0b1001};
static int temp_velo2,velo_cont2,bobina2;
static long int s_passo2,c_passo2;

   if (t_habilita2==1){   
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
                        //   output_B(posicao2[bobina2]);
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
                        }         
                  }
                 
            }
         }  
      }
}

#int_TIMER0
void  TIMER0_isr(void){
   void RecebeComando(void);
static int timer;

   if(timer<2)timer++;
   else{
  Motor1(habilita_1, sentido_1, velocidade_1,passo_1);
  Motor2(habilita_2, sentido_2, velocidade_2,passo_2);
  
 
   timer=0;
   }
}

void main(){
   setup_timer_0 (RTCC_DIV_4|RTCC_INTERNAL );
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   set_tris_a(0b00000000);
   
   while (true){
    printf("\r\nrecebendo comando");
  sentido_1=1;
   habilita_1=1;
   velocidade_1=20;
   passo_1=10000;
   sentido_2=1;
   habilita_2=1;
   velocidade_2=20;
   passo_2=10000;

   delay_ms(10);
   }
   
   
}



