
/*******************************************************************************
*              Sistema de navegação para robôs autônomos
*
*                             Meca TCC 2012
*
* Comando 7:   Julho de 2012                                           Raul S F
********************************************************************************
*/

#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_B4,bits=8)
#include <lcd.c>
#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)
//#use fast_io(b)

int f_habilita,f_frente=0,f_re,f_lado1,f_lado2,f_contpasso1,
f_contpasso2,f_desvio,f_gira,f_checksensor;
int motor1,motor2,sentido1,sentido2,velocidade1,velocidade2;
long int passo1,passo2,dis_sensor1,dis_sensor2;

void SensorProx(void){

static int cont1;
   if(cont1==1){
 static long int t_sensor1_1;
 static long int t_sensor1_2;
 static long acumul_lig1;
 static long acumul_des1;
 static int t_cont1;
  
 static long int t_sensor2_1;
 static long int t_sensor2_2;
 static long acumul_lig2;
 static long acumul_des2;
 
 if(t_cont1<20){
    output_high(pin_a2);
    set_adc_channel(0);
   delay_us(10);
   t_sensor1_1=read_adc();
   set_adc_channel(1);
   delay_us(10);
   t_sensor2_1=read_adc();

   acumul_lig1=acumul_lig1+t_sensor1_1;
   acumul_lig2=acumul_lig2+t_sensor2_1;
   
   output_low(pin_a2);
    set_adc_channel(0);
   delay_us(10);
   t_sensor1_2=read_adc();
   set_adc_channel(1);
   delay_us(10);
   t_sensor2_2=read_adc();

   
   acumul_des1=acumul_des1+ t_sensor1_2;
   acumul_des2=acumul_des2+ t_sensor2_2;
 
 }
 t_cont1++;
 if(t_cont1>20){
 dis_sensor1=(acumul_lig1-acumul_des1);
 dis_sensor2=(acumul_lig2-acumul_des2); 
 acumul_lig1=0;
 acumul_des1=0;
 acumul_lig2=0;
 acumul_des2=0;
 
 t_cont1=0;
 }
 cont1=0;
}
cont1++;

}


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
         
            if((dis_sensor1>20)&&(dis_sensor2>20)&&(a_checksensor1==0)){
            a_checksensor1=1;
            f_re=1;
                     
            }            
            
            if(((dis_sensor1>40)||(dis_sensor2>40))&&(a_checksensor1==0)){
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
      motor1=1;
      sentido1=1;  
      passo1=50;
      velocidade1=1;
      
      motor2=1;
      sentido2=1;  
      passo2=50;
      velocidade2=1;
      }      
   }
}

void Re(void){
static int1 t_re;
   if(f_habilita==1){
      if((f_re==1)&&(t_re==0)){
      motor1=1;
      motor2=1;
      sentido1=0;
      sentido2=0;
      passo1=40;
      passo2=40;
      velocidade1=50;
      velocidade2=50;
      f_contpasso1=1;
      f_contpasso2=1;
      t_re=1;
      }
         if((f_contpasso1==0)&&(t_re==1)){
         f_re=0;
         motor1=0;
         motor2=0;
         sentido1=0;
         sentido2=0;
         velocidade1=10;
         velocidade2=10;
         t_re=0; 
         }
   }
}

void Gira(void){
static int t_gira;
   if(f_habilita==1){
      if((f_gira==1)&&(t_gira==0)){
      motor1=1;
      motor2=1;
      sentido1=1;
      sentido2=0;
      passo1=40;
      passo2=40;
      velocidade1=1;
      velocidade2=1;
      f_contpasso1=1;
      f_contpasso2=1;
      t_gira=1;
      }
         if((f_contpasso1==0)&&(t_gira==1)){
         f_gira=0;
         motor1=0;
         motor2=0;
         sentido1=0;
         sentido2=0;
         velocidade1=10;
         velocidade2=10;
         t_gira=0; 
         }
   }
}

void Desvio(void){
static int t_desvio;
   if(f_habilita==1){
      if(f_desvio==1){
         
            if(f_lado1==1){
            motor1=1;
            motor2=0;
            passo1=40;
            sentido1=1;
            velocidade1=1;
            f_contpasso1=1;
            t_desvio=1;
            }
            
            if(f_lado2==1){
            motor1=0;
            motor2=1;
            passo2=40;
            sentido2=1;
            velocidade2=1;
            f_contpasso2=1;
            t_desvio=1;
            }     
      }           
     
            if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_desvio==1)&&(f_lado1==0)&&(f_lado2==0)){
            motor1=1;
            motor2=1;
            sentido1=1;
            sentido2=1;
            passo1=70;
            passo2=70;
            velocidade1=1;
            velocidade2=1;
            f_contpasso1=1;
            f_contpasso2=1;
            t_desvio=2;
            }
            
            if((f_contpasso1==0)&&(f_contpasso2==0)&&(f_lado1==0)&&(f_lado2==0)&&(t_desvio==2)){
            motor1=0;
            motor2=0;
            velocidade1=3;
            velocidade2=3;
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
         if(passo1==t_contpasso1){
         f_contpasso1=0;
         a_contpasso1=0;
         t_contpasso1=0;
         }
         else{
            if(a_contpasso1==velocidade1){
            a_contpasso1=0;
            t_contpasso1++;
            }
            else{ a_contpasso1++;}      
         }
      }
            if(f_contpasso2==1){
         if(passo2==t_contpasso2){
         f_contpasso2=0;
         a_contpasso2=0;
         t_contpasso2=0;
         }
         else{
            if(a_contpasso2==velocidade2){
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
   if((motor1==0)&&(motor2==0))executando=5;
         
   
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

void EnviaComando( int t_motor1,int t_motor2, int t_sentido1, int t_sentido2, 
int t_velocidade1, int t_velocidade2){
static int cmd[7];
static int t_cmd[7];

cmd[0]='C';
cmd[1]=t_motor1;
cmd[2]=t_motor2;
cmd[3]=t_sentido1;
cmd[4]=t_sentido2;
cmd[5]=t_velocidade1;
cmd[6]=t_velocidade2;


   if((t_cmd[1]!=cmd[1])||(t_cmd[2]!=cmd[2])||(t_cmd[3]!=cmd[3])
   ||(t_cmd[4]!=cmd[4])||(t_cmd[5]!=cmd[5])||(t_cmd[6]!=cmd[6])
 ){
   t_cmd[0]=cmd[0];
   t_cmd[1]=cmd[1];
   t_cmd[2]=cmd[2];
   t_cmd[3]=cmd[3];
   t_cmd[4]=cmd[4];
   t_cmd[5]=cmd[5];
   t_cmd[6]=cmd[6];
   
   printf("%c%c%c%c%c%c%c\r\n"cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6]); 
   }
}  

#int_TIMER0
void  TIMER0_isr(void){
static int timer;

   if(timer<12)timer++;
   else{
   
//   SensorProx();
  CheckSensor();

   Re();
   Gira();
   Desvio();   
   Frente();
   ContPasso(); 

   EnviaComando(motor1,motor2,sentido1,sentido2,velocidade1,velocidade2);
   timer=0;
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
   set_tris_b(0b1100001111); 
   set_tris_a(0b0000000011);
 
 printf(lcd_putc,"versão comando 7"); 
// printf("\fversão comando 7"); 
 delay_ms(100);

   while(true){ 
   
  // printf(lcd_putc,"\fm1:%u\,m2:%u\nsent1:%u\ ,sent2:%u"motor1,motor2,sentido1,sentido2); 
      EmExecucao();
//      f_checksensor=1;
      f_habilita=1;
//        SensorProx();
   
    if(input(pin_b0)==1){

    dis_sensor2=0;
    dis_sensor1=10;
   }
            
   if(input(pin_b1)==1){
    dis_sensor2=10;
    dis_sensor1=0;
   }
  
  
  if(input(pin_b2)==1){
      dis_sensor2=21;
      dis_sensor1=21;
   }

   
   if(input(pin_b3)==1){
        dis_sensor2=41;
      dis_sensor1=0;
   
   }
   if((input(pin_b0)==0)&&(input(pin_b1)==0)&&(input(pin_b2)==0)&&(input(pin_b3)==0)){
   dis_sensor2=0;
   dis_sensor1=0;
   }  
delay_ms(400);  
}
}

 

