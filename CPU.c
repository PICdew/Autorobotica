
/*******************************************************************************
*              Sistema de navegação para robôs autônomos
*
*                             Meca TCC 2012
*
* CPU.1:   Agosto de 2012                                           Raul S F
********************************************************************************
*/

#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=20000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_B4,bits=8)
#include <lcd.c>
#use fast_io(a)
//#use standard_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(b)

int f_habilita,f_frente=0,f_re,f_lado1,f_lado2,f_contpasso1,
f_contpasso2,f_desvio,f_gira;
int motor1,motor2,sentido2,velocidade1,velocidade2;

int motor_1,motor_2,sentido_1,sentido_2;
long velocidade_1,velocidade_2,passo_1,passo_2;
long int passo1,passo2,dis_sensor1,dis_sensor2;


void CheckSensor(void){
static int a_checksensor1,a_checksensor2;

   if(f_habilita==1){
                  
         if(((f_desvio==0)&&(f_re==0)&&(f_gira==0))&&(a_checksensor1==1)){
         f_desvio=0;
         f_lado1=0;
         f_lado1=0;         
         a_checksensor1=0;
                  }
         if(a_checksensor1==0){
      
            if((dis_sensor1>2)&&(dis_sensor1<19)&&(a_checksensor1==0)){
            a_checksensor1=1;
            f_desvio=1;
            f_lado1=1;
            f_lado2=0;
            }
            
            if((dis_sensor2>2)&&(dis_sensor2<19)&&(a_checksensor1==0)){
            a_checksensor1=1;
            f_desvio=1;
            f_lado2=1;
            f_lado1=0;
            }            
         
            if((dis_sensor1>40)&&(dis_sensor2>40)&&(a_checksensor1==0)){
            a_checksensor1=1;
            f_re=1;
                     
            }            
            
            if(((dis_sensor1>40)&&(dis_sensor2<40))||
            ((dis_sensor2>40)&&(dis_sensor2<40)&&(a_checksensor1==0))){
            a_checksensor1=1;
            f_gira=1;
            f_lado2=0;
            f_lado1=1;
            } 
          }
            if(dis_sensor1==0)f_lado1=0;
            if(dis_sensor2==0)f_lado2=0;
      
   }
}

void Frente(void){

   if(f_habilita==1){

      if((f_frente==1)&&(f_desvio==0)){
      f_contpasso1=0;
      motor_1=1;
      sentido_1=1;  
      passo_1=2;
      velocidade_1=4;
      
      motor_2=1;
      sentido2=1;  
      passo_2=3;
      velocidade_2=4;
      }      
   }
}

void Re(void){
static int1 t_re;
   if(f_habilita==1){
      if((f_re==1)&&(t_re==0)){
      motor_1=1;
      motor_2=1;
      sentido_1=0;
      sentido_2=0;
      passo_1=2;
      passo_2=2;
      velocidade_1=4;
      velocidade_2=4;
      f_contpasso1=1;
      f_contpasso2=1;
      t_re=1;
      }
         if((f_contpasso1==0)&&(t_re==1)){
         f_re=0;
         motor_1=0;
         motor_2=0;
         sentido_1=0;
         sentido_2=0;
         velocidade_1=4;
         velocidade_2=4;
         t_re=0; 
         }
   }
}


void Gira(void){
static int t_gira;
   if(f_habilita==1){
      if((f_gira==1)&&(t_gira==0)){
      motor_1=1;
      motor_2=1;
      sentido_1=1;
      sentido_2=0;
      passo_1=2;
      passo_2=2;
      velocidade_1=4;
      velocidade_2=4;
      f_contpasso1=1;
      f_contpasso2=1;
      t_gira=1;
      }
         if((f_contpasso1==0)&&(t_gira==1)){
         f_gira=0;
         motor_1=0;
         motor_2=0;
         sentido_1=0;
         sentido_2=0;
         velocidade_1=4;
         velocidade_2=4;
         t_gira=0; 
         }
   }
}

void Desvio(void){
static int t_desvio;
   if(f_habilita==1){
      if(f_desvio==1){
         
            if(f_lado1==1){
            motor_1=1;
            motor_2=0;
            passo_1=2;
            sentido_1=1;
            velocidade_1=4;
            f_contpasso1=1;
            t_desvio=1;
            }
            
            if(f_lado2==1){
            motor_1=0;
            motor_2=1;
            passo_2=2;
            sentido_2=1;
            velocidade_2=4;
            f_contpasso2=1;
            t_desvio=1;
            }     
      }           
     
            if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_desvio==1)&&(f_lado1==0)&&(f_lado2==0)){
            motor_1=1;
            motor_2=1;
            sentido_1=1;
            sentido_2=1;
            passo_1=2;
            passo_2=2;
            velocidade_1=4;
            velocidade_1=4;
            f_contpasso1=1;
            f_contpasso2=1;
            t_desvio=2;
            }
            
            if((f_contpasso1==0)&&(f_contpasso2==0)&&(f_lado1==0)&&(f_lado2==0)&&(t_desvio==2)){
            motor_1=0;
            motor_2=0;
            velocidade_1=4;
            velocidade_2=4;
            t_desvio=0;
            f_desvio=0;
            }
         
   }
   else t_desvio=0; 
}

void ContPasso(void){
static int t_contpasso1,a_contpasso1,t_contpasso2,a_contpasso2;

   if (f_habilita==1){
      if(f_contpasso1==1){
         if(passo_1==t_contpasso1){
         f_contpasso1=0;
         a_contpasso1=0;
         t_contpasso1=0;
         }
         else{
            if(a_contpasso1==velocidade_1){
            a_contpasso1=0;
            t_contpasso1++;
            }
            else{ a_contpasso1++;}      
         }
      }
            if(f_contpasso2==1){
         if(passo_2==t_contpasso2){
         f_contpasso2=0;
         a_contpasso2=0;
         t_contpasso2=0;
         }
         else{
            if(a_contpasso2==velocidade_2){
            a_contpasso2=0;
            t_contpasso2++;
            }
            else{ a_contpasso2++;}      
         }
      }
   }
}

void EmExecucao(void){
 static int executando;
 
   if(f_frente==1)executando=0;
   if(f_re==1)executando=1;
   if(f_lado1==1)executando=2;
   if(f_lado2==1)executando=3;
   if(f_gira==1)executando=4;
   if((motor_1==0)&&(motor_2==0))executando=5;
         
   
   switch(executando){
   
   case 0: printf(lcd_putc,"\fD1 %lu \,D2 %lu\nFrente",dis_sensor1,dis_sensor2);
   break;
   
   case 1:printf(lcd_putc,"\fD1 %lu \,D2 %lu\nRe",dis_sensor1,dis_sensor2);
   break;
   
   case 2:printf(lcd_putc,"\fD1 %lu \,D2 %lu\nDireita",dis_sensor1,dis_sensor2);
   break;
   
   case 3:printf(lcd_putc,"\fD1 %lu \,D2 %lu\nEsquerda",dis_sensor1,dis_sensor2);
   break;   
   
   case 4:printf(lcd_putc,"\fD1 %lu \,D2 %lu\nGirando",dis_sensor1,dis_sensor2);
   break;
   
   case 5:printf(lcd_putc,"\fD1 %lu \,D2 %lu\nParado",dis_sensor1,dis_sensor2);
   break;
   
   default:printf(lcd_putc,"\fD1 %lu \,D2 %lu\nParado",dis_sensor1,dis_sensor2);
   break;
   }
   }

void Motor1( int t_sentido1, int velocidade1,long int passo1){

static BYTE const posicao1[5] = {0b1001,0b0101,0b0110,0b1010};//sequencia se acionamento do motor
static int temp_velo1,velo_cont1,bobina1;
static long int s_passo1,c_passo1;

if(motor_1==1){
           
          
               if(temp_velo1!=velocidade1){
               temp_velo1=velocidade1;
               velo_cont1=temp_velo1;
               }
                  else{
                     if(velo_cont1!=0)velo_cont1--;
                    
                       else{ 
                           output_b(posicao1[bobina1]);//saida para o motor
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
     else output_a(0);    
}      
      

void Motor2( int t_sentido2, int velocidade2,long int passo2){

static BYTE const posicao2[5] ={0b1001,0b0101,0b0110,0b1010};//sequencia se acionamento do motor
static int temp_velo2,velo_cont2,bobina2;
static long int s_passo2,c_passo2;

if(motor_2==1){

               if(temp_velo2!=velocidade2){
               temp_velo2=velocidade2;
               velo_cont2=temp_velo2;
               }
                  else{
                     if(velo_cont2!=0)velo_cont2--;                     
                       else{ 
                           output_c(posicao2[bobina2]);//saida para o motor
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
else output_b(0); 
} 


#int_TIMER0
void  TIMER0_isr(void){

static int timer;

   if(timer<12)timer++;
   else{
   
//   SensorProx();
 //  CheckSensor();
   set_timer1(1);
   ContPasso();

   Re();
   Desvio();
   Gira();
   Frente(); 
   set_timer1(1);
   Motor1(sentido_1, velocidade_1,passo_1);
  motor2(sentido_2, velocidade_2,passo_2);
   }
} 

void main(void){

   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_timer_0 (RTCC_DIV_32|RTCC_INTERNAL );
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_init(); 
   set_tris_c(0b11110000);
   set_tris_b(0b11110000); 
   set_tris_a(0b00000000);
 
 printf(lcd_putc,"versão CPU .1"); 
// printf("\fversão CPU.1"); 
 delay_ms(100);

   while(true){ 
   
  // printf(lcd_putc,"\fm1:%u\,m2:%u\nsent1:%u\ ,sent2:%u"motor_1,motor_2,sentido_1,sentido_2); 
      EmExecucao();

      f_habilita=1;
    if(input(pin_c4)==1){
   f_re=1;
   }
   else f_re=0;

   if(input(pin_c5)==1){
    f_gira=1;
   }
   else f_gira=0;
    
  
  if(input(pin_c6)==1){
    f_desvio=1;
    f_lado1=1;
    f_lado2=0;
   }
   else f_desvio=0,f_lado1=0,f_lado2=0;

   
   if(input(pin_c7)==1){
    f_desvio=1;
    f_lado1=0;
    f_lado2=1;
   }
   delay_ms(400);
}
}

 
        
   

