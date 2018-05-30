/*******************************************************************************
*              Sistema de navegaï¿½ï¿½o para robï¿½s autï¿½nomos
*
*                                AutoRobotica
*
* Comando 29:   Julho de 2014                                   Eng. Raul S F
********************************************************************************
********************************************************************************
* Historico
* Revisao 19.2 :proximidade, distï¿½ncia
* Revisao 20 ;03/11/1023; recepï¿½ï¿½o de potï¿½ncia
* Revisao 22:02/11/2013;
* Revisao 23:03/11/2013; bitstop
* Revisao 23:03/11/2013; acumulador botï¿½o de 1 para 2,c_origem
* Revisao 17:27/01/2014; calculo de proximidade
* Revisao 17:27/01/2014; Função seguir
* Revisao 13:redução da variavel de envio serial
* Revisao 13;26/04/2016; reduçao rotina da Direcao(void)
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

#priority CCP1,TIMER2,TIMER0

int f_habilita=0,f_frente=0,f_re=0,f_lado1=0,f_lado2=0,a_lado1=0,a_lado2=0,f_contpasso1=0,
f_contpasso2=0,f_desvio=0,f_gira=0,f_checksensor=0,f_vira=0,t_direcao=0,recebido=0;
int motor1=0,motor2=0,sentido1=0,sentido2=0,velocidade1=0,velocidade2=0;
long int passo1=0,passo2=0,dis_sensor1=0,dis_sensor2=0;
int ir=0, origem1=0,origem2=0,origem3=0,origem4=0,origem5=0,origem6=0,origem7=0,origem8=0,
versao=0,teste;
int f_proximidade=0,f_proximidade2=0,l_proximidade,h_proximidade,proximidade_a,proximidade_b,t_proximidade=0;

int f_origem1,f_origem2,f_origem3,f_origem4;
int s_direcao=0,f_orientacao=0,contccp,contcmd,seguir=0,f_seguir=0,ida_volta;

int chegando=0,saindo=0, pronto=0,t_contpasso1=0,t_contpasso2=0,complemento;
 
int codico=0,controle=0,start=0,t_menu=0,potencia=0;
int h_potencia1=0,h_potencia2=0,h_potencia3=0,h_potencia4=0;

int obstaculo=6,distancia=3;


int f_ir=0,pisca=0,rx=0;

void SensorProx(void){
static int cont1;

 static long int t_sensor1_1=0;
 static long int t_sensor1_2=0;
 static long acumul_lig1=0;
 static long acumul_des1=0;
 static int t_cont1=0;
  
 static long int t_sensor2_1=0;
 static long int t_sensor2_2=0;
 static long acumul_lig2=0;
 static long acumul_des2=0;
 
  if(cont1==10){
   set_adc_channel(0);
   delay_us(3);
   t_sensor1_2=read_adc();
   acumul_des1=acumul_des1+ t_sensor1_2;
   set_adc_channel(1);
   delay_us(3);
   t_sensor2_2=read_adc();
   acumul_des2=acumul_des2+ t_sensor2_2;
  
   output_high(pin_a2);
    delay_us(50);
    set_adc_channel(0);
   delay_us(3);
   t_sensor1_1=read_adc();
   
   if(t_sensor1_1>t_sensor1_2){ 
   t_sensor1_1=t_sensor1_2;
   }
   acumul_lig1=acumul_lig1+ t_sensor1_1;
   set_adc_channel(1);
   delay_us(3);
   t_sensor2_1=read_adc();
   output_low(pin_a2);
   
   if(t_sensor2_1>t_sensor2_2){ 
   t_sensor2_1=t_sensor2_2;
   }
   acumul_lig2=acumul_lig2+ t_sensor2_1;

   
    if((acumul_des1-acumul_lig1)<255){
      dis_sensor1=(acumul_des1-acumul_lig1);
    }
    if((acumul_des2-acumul_lig2)<255){
      dis_sensor2=(acumul_des2-acumul_lig2);
    }
  } 
 if(t_cont1>20){
 acumul_lig1=0;
 acumul_des1=0;
 acumul_lig2=0;
 acumul_des2=0;
 cont1=0;
 t_cont1=0;
 }
t_cont1++;
cont1++;

}

void Direcao(void){

      if((input(pin_c5)==0)&&(input(pin_c4)==1)&&(input(pin_c6)==1)&&(input(pin_c7)==1))t_direcao=1;
      if((input(pin_c4)==0)&&(input(pin_c5)==0)&&(input(pin_c6)==1)&&(input(pin_c7)==1))t_direcao=1;
      if((input(pin_c5)==0)&&(input(pin_c4)==1)&&(input(pin_c6)==0)&&(input(pin_c7)==1))t_direcao=2;
      if((input(pin_c6)==0)&&(input(pin_c4)==1)&&(input(pin_c5)==1)&&(input(pin_c7)==1))t_direcao=3;
      if((input(pin_c5)==0)&&(input(pin_c6)==0)&&(input(pin_c7)==0)&&(input(pin_c4)==1))t_direcao=3;
      if((input(pin_c6)==0)&&(input(pin_c7)==0)&&(input(pin_c4)==1)&&(input(pin_c5)==1))t_direcao=4;
      if((input(pin_c7)==0)&&(input(pin_c4)==1)&&(input(pin_c5)==1)&&(input(pin_c6)==1))t_direcao=5;
      if((input(pin_c4)==0)&&(input(pin_c7)==0)&&(input(pin_c5)==1)&&(input(pin_c6)==1))t_direcao=5;
      if((input(pin_c4)==0)&&(input(pin_c5)==1)&&(input(pin_c6)==1)&&(input(pin_c7)==1))t_direcao=6;
      if((input(pin_c5)==0)&&(input(pin_c7)==0)&&(input(pin_c4)==1)&&(input(pin_c6)==1))t_direcao=3;
/*
 int c_recebimento=0,c_lado_a=0,c_lado_b=0,c_lado_c=0,c_lado_d=0,c_lado_e=0,c_lado_f=0;

//   if(c_recebimento<1){//5
   
      if((input(pin_c5)==0)&&(input(pin_c6)==1)&&(input(pin_c7)==1))c_lado_a++;
      if((input(pin_c4)==0)&&(input(pin_c5)==0)&&(input(pin_c6)==1)&&(input(pin_c7)==1))c_lado_a++;
      if((input(pin_c5)==0)&&(input(pin_c6)==0)&&(input(pin_c7)==1))c_lado_b++;
      if((input(pin_c6)==0)&&(input(pin_c5)==1)&&(input(pin_c7)==1))c_lado_c++;
      if((input(pin_c5)==0)&&(input(pin_c6)==0)&&(input(pin_c7)==0))c_lado_c++;
      if((input(pin_c6)==0)&&(input(pin_c7)==0)&&(input(pin_c5)==1))c_lado_d++;
      if((input(pin_c7)==0)&&(input(pin_c5)==1)&&(input(pin_c6)==1))c_lado_e++;
      if((input(pin_c4)==0)&&(input(pin_c7)==0)&&(input(pin_c5)==1)&&(input(pin_c6)==1))c_lado_e++;
      if((input(pin_c4)==0)&&(input(pin_c5)==1)&&(input(pin_c6)==1)&&(input(pin_c7)==1))c_lado_f++;
      if((input(pin_c5)==0)&&(input(pin_c6)==0)&&(input(pin_c4)==1)&&(input(pin_c7)==1))c_lado_c++;
   c_recebimento++;
//   }   
   
//   else{
   c_recebimento=0;
   
    if((c_lado_a>c_lado_b)&&(c_lado_a>c_lado_c)&&(c_lado_a>c_lado_d)&&
    (c_lado_a>c_lado_e)&&(c_lado_a>c_lado_f))t_direcao=1;
   
      else{   
      if((c_lado_b>c_lado_a)&&(c_lado_b>c_lado_c)&&(c_lado_b>c_lado_d)&&
      (c_lado_b>c_lado_e)&&(c_lado_b>c_lado_f))t_direcao=2;
      
      else{       
      if((c_lado_c>c_lado_a)&&(c_lado_c>c_lado_b)&&(c_lado_c>c_lado_d)&&
      (c_lado_c>c_lado_e)&&(c_lado_c>c_lado_f))t_direcao=3;
   
      else{
      if((c_lado_c>c_lado_a)&&(c_lado_c==c_lado_b)&&(c_lado_c==c_lado_d)&&
      (c_lado_c>c_lado_e)&&(c_lado_c>c_lado_f))t_direcao=3;

      else{
      if((c_lado_d>c_lado_a)&&(c_lado_d>c_lado_b)&&(c_lado_d>c_lado_c)&&
      (c_lado_d>c_lado_e)&&(c_lado_d>c_lado_f))t_direcao=4;
   
      else{   
      if((c_lado_e>c_lado_a)&&(c_lado_e>c_lado_b)&&(c_lado_e>c_lado_c)&&
      (c_lado_e>c_lado_d)&&(c_lado_e>c_lado_f))t_direcao=5;
   
      else{   
      if((c_lado_f>c_lado_a)&&(c_lado_f>c_lado_b)&&(c_lado_f>c_lado_c)&&
      (c_lado_f>c_lado_d)&&(c_lado_f>c_lado_e))t_direcao=6; 
      
      }
      }
      }
      }
      }
      }
      c_lado_a=0;   c_lado_b=0;   c_lado_c=0;   c_lado_d=0;   c_lado_e=0;   c_lado_f=0;

     //}*/
}

void Orientacao(void){

   if ((f_desvio==0)&&(f_vira==0)&&(f_gira==0)&&(f_re==0)){  /////
      if(f_orientacao==1){
      
         if(s_direcao==1){
         f_frente=0;
         f_gira=1;
         f_lado1=1;
         f_lado2=0;
         }
         
         if(s_direcao==2){
         f_frente=0;
         f_gira=0;
         f_vira=1;
         f_lado1=1;
         f_lado2=0;
         }
         
         if(s_direcao==3){
         f_frente=1;
         f_lado1=1;
         f_lado2=1;
         }
         
         if(s_direcao==4){
         f_frente=0;
         f_vira=1;
         f_gira=0;
         f_lado1=0;
         f_lado2=1;
         }
         
         if(s_direcao==5){
         f_frente=0;
         f_gira=1;
         f_lado1=0;
         f_lado2=1;
         }
         
         if(s_direcao==6){
         f_frente=0;
         f_gira=1;
         f_lado1=0;
         f_lado2=1;
         }
      }
   }
}

void Origem(void){
   if(recebido==1){
      if(controle==10){//codigo dos controles recebidos       
       f_origem1++;
       recebido=0;
        if(f_ir==1){
        if(h_potencia1==0){
         s_direcao=t_direcao;
         h_potencia1=potencia;
         f_proximidade=potencia;
         }
         if(potencia>8)h_potencia1=0;           
        }
       }
       
       if(controle==20){//codigo dos controles recebidos
       f_origem2++;
       recebido=0;
        if(ir==2){
         if(potencia<=h_potencia2){
         s_direcao=t_direcao;   
         }
         
          h_potencia2=potencia; 
        }
       }
       
       if(controle==30){//codigo dos controles recebidos
       f_origem3++;
       recebido=0;
        if(ir==3){
        if(potencia<=h_potencia3){
         s_direcao=t_direcao;
         }
         
         h_potencia3=potencia; 
        }
       }
       
       if(controle==40){//codigo dos controles recebidos
       f_origem4++;
       recebido=0;
        if(ir==4){
         if(potencia<=h_potencia4){
         s_direcao=t_direcao;   
         }
         
         h_potencia4=potencia;
        }
       }
   }  
}

void CheckSensor(void){///
static int a_checksensor1=0,a_checksensor2=0,b_checksensor1=0,b_checksensor2=0;
      
         
    if(ir>0){ ////
   
       if(f_checksensor==1){   
         if((dis_sensor1<obstaculo)&&(a_checksensor1==1))f_lado1=0;
         if((dis_sensor2<obstaculo)&&(a_checksensor1==1))f_lado2=0;
//        if((dis_sensor1<30)&&(dis_sensor2<30)&&(a_checksensor1==1))f_desvio=0;

         if((f_desvio==0)&&(a_checksensor1==1)){
      f_frente=0;  ////
      f_vira=0;    ////
      f_gira=0;    ////
//      f_re=0;
//      f_contpasso1=0;
//      f_contpasso2=0;

//         f_desvio=0;
         f_lado1=0;
         f_lado2=0;         
         a_checksensor1=0;
         f_orientacao=1;
         }
         
         if(a_checksensor1==0){
            
            if((dis_sensor1>obstaculo)&&(dis_sensor2>obstaculo)&&(a_checksensor1==0)){
               if(dis_sensor1>dis_sensor2)a_lado1=1;
               if(dis_sensor2>dis_sensor1)a_lado2=1;
               a_checksensor1=1;
               b_checksensor1=dis_sensor1;
               b_checksensor2=dis_sensor2;
               f_re=1;
               f_frente=0;  ////
               f_vira=0;    ////
               f_gira=0; 
               f_lado1=1;
               f_lado2=1;
               f_orientacao=0;
               f_desvio=1;
            
               if(dis_sensor1>dis_sensor2){
               f_lado1=1;
               f_lado1=0;
               }
               
               if(dis_sensor2>dis_sensor1){
               f_lado1=0;
               f_lado1=1;
               }
            }
            
            if(((dis_sensor1>obstaculo)&&(dis_sensor1<200))&&(a_checksensor1==0)){
            a_checksensor1=1;
            b_checksensor1=dis_sensor1;
            b_checksensor2=dis_sensor2;
            f_desvio=1;
            f_frente=0;  ////
            f_vira=0;    ////
            f_gira=0;
            f_lado1=1;
            f_lado2=0;
            f_orientacao=0;            
            }
            
            if(((dis_sensor2>obstaculo)&&(dis_sensor2<200))&&(a_checksensor1==0)){
            a_checksensor1=1;
            b_checksensor1=dis_sensor1;
            b_checksensor2=dis_sensor2;
            f_desvio=1;
            f_frente=0;  ////
            f_vira=0;    ////
            f_gira=0;
            f_lado2=1;
            f_lado1=0; 
            f_orientacao=0;
            }                                         
          }
   }      
  } 
}

void Frente(void){
static int t_frente;
   if(ir>0){
   if(f_frente==0)t_frente=0;
     if((f_desvio==0)&&(f_frente==1)&&(f_re==0)){
     if(f_ir==0)t_frente=0;
//     if(t_frente==0){
      f_contpasso1=0;
      motor1=1;
      sentido1=1;  
      passo1=50;//40
//      velocidade1=1;
      f_contpasso2=0;
      motor2=1;
      sentido2=1;  
      passo2=50;//40
//      velocidade2=1;
//      t_frente=1;
      if(f_proximidade<6){
      velocidade1=1;
      velocidade2=1;
      }
      if(f_proximidade>5){
      velocidade1=2;
      velocidade2=2;
      }
      
      if(f_proximidade>8){
      velocidade1=3;
      velocidade2=3;
      }

//      }
/*      
      if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_frente==2)){
      f_contpasso1=1;
      motor1=1;
      sentido1=1;  
      passo1=30;
      velocidade1=3;
      f_contpasso2=1;
      motor2=1;
      sentido2=1;  
      passo2=30;
      velocidade2=3;
      }
       
      if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_frente==1)){
      f_contpasso1=1;
      motor1=1;
      sentido1=1;  
      passo1=40;
      velocidade1=2;
      f_contpasso2=1;
      motor2=1;
      sentido2=1;  
      passo2=40;
      velocidade2=2;
      t_frente=2; 
      }
*/      
  }
   } 
}

void Para(void){
   if(ir==0){  ////
      f_habilita=0;
      motor1=0;
      motor2=0;
   }
   else f_habilita=1;
}

void Re(void){
static int t_re=0;
   if(ir>0){
     if(f_re==1){
      if(t_re==0){
      motor1=1;
      motor2=1;
      sentido1=0;
      sentido2=0;
      passo1=15;//20
      passo2=15;//20
      velocidade1=2;
      velocidade2=2;
      f_contpasso1=1;
      f_contpasso2=1;
      t_re=1;
      }
/*         if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_re==1)&&(a_lado1==1)&&
         (a_lado2==0)){
         motor1=1;
         motor2=0;
         sentido1=0;
         sentido2=1;
         passo1=2;
         passo2=2;
         velocidade1=3;
         velocidade2=3;
         f_contpasso1=1;
         f_contpasso2=0;
         t_re=2; 
         }
         
         if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_re==1)&&(a_lado1==0)&&
         (a_lado2==1)){
         motor1=0;
         motor2=1;
         sentido1=1;
         sentido2=0;
         passo1=3;
         passo2=3;
         velocidade1=3;
         velocidade2=3;
         f_contpasso1=1;
         f_contpasso2=0;
         t_re=2; 
         }
*/         
         if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_re==1)){
         f_re=0;
//         motor1=0;
//         motor2=0;
//         sentido1=0;
//         sentido2=0;
         t_re=0;
         a_lado1=0;
         a_lado2=0;
         }
      }
      else t_re=0;
   }
}

void Gira(void){
static int t_gira=0;
   if(ir>0){////
     if((f_desvio==0)&&(f_gira==1)){
      if((f_gira==1)&&(t_gira==0)&&(f_lado1==1)){
      motor1=1;
      motor2=1;
      sentido1=1;
      sentido2=0;
      passo1=3;
      passo2=3;
      velocidade1=1;
      velocidade2=1;
      f_contpasso1=1;
      f_contpasso2=0;
      t_gira=1;
      }
      
      if((f_gira==1)&&(t_gira==0)&&(f_lado2==1)){
      motor1=1;
      motor2=1;
      sentido1=0;
      sentido2=1;
      passo1=3;
      passo2=3;
      velocidade1=1;
      velocidade2=1;
      f_contpasso1=1;
      f_contpasso2=1;
      t_gira=1;
      }
         if((f_contpasso1==0)&&(t_gira==1)){
         f_gira=0;
//         motor1=0;
//         motor2=0;
//         sentido1=0;
//         sentido2=0;
//         velocidade1=1;//10
//         velocidade2=1;//10
         t_gira=0; 
         }
     }
    else t_gira=0; 
   }
}

void Vira(void){
static int t_vira=0, c_vira=0;
   if(ir>0){
      if(f_desvio==0){
     if(f_vira==1){
     if(c_vira>0)c_vira++; 
      if((t_vira==0)&&(f_lado1==1)){       
      motor1=1;
      motor2=0;
      sentido1=1;
     // sentido2=0;
      passo1=50;//100
     // passo2=20;//100
      velocidade1=2;
     // velocidade2=2;
      f_contpasso1=1;
      f_contpasso2=0;
      t_vira=1;
      c_vira=1;
      }
 /*     
      if(t_vira==2){
      motor1=1;
      motor2=0;
      sentido1=1;
      //sentido2=0;
      passo1=40;//8
      //passo2=5;//8
      velocidade1=2;
      //velocidade2=2;
      f_contpasso1=1;
      f_contpasso2=0;
      t_vira=3;   
      }
 */           
      if((t_vira==1)&&(s_direcao==3)){
      f_contpasso1=0;
      motor1=1;
      motor2=0;
      sentido1=1;
      //sentido2=0;
      passo1=1;//100
      //passo2=5;//100
      velocidade1=1;
      //velocidade2=1;
      f_contpasso1=1;
      f_contpasso2=0;
      t_vira=2;
      }
      
      if((t_vira==0)&&(f_lado2==1)){
      motor1=0;
      motor2=1;
      //sentido1=1;
      sentido2=1;
      //passo1=5;//100
      passo2=5;//100
      //velocidade1=2;
      velocidade2=2;
      f_contpasso1=0;
      f_contpasso2=1;
      t_vira=4;
      c_vira=1;
      }
/*      
      if(t_vira==5){
      motor1=0;
      motor2=1;
      //sentido1=0;
      sentido2=1;
      //passo1=5;//8
      passo2=20;//8
      //velocidade1=2;
      velocidade2=2;
      f_contpasso1=0;
      f_contpasso2=1;
      t_vira=6;   
      }
*/           
      if((t_vira==4)&&(s_direcao==3)){
      f_contpasso2=0;
      motor1=0;
      motor2=1;
      //sentido1=1;
      sentido2=0;
      //passo1=5;//100
      passo2=1;//100
      //velocidade1=1;
      velocidade2=1;
      f_contpasso1=0;
      f_contpasso2=1;
      t_vira=5;
      }
      
     }
     else t_vira=0; 
     
        if(((f_contpasso1==0)&&(f_contpasso2==0))&&((t_vira==2)||(t_vira==4)||(t_vira==5)||(t_vira==1)||(c_vira>30))){
         f_vira=0;
//         motor1=0;
//         motor2=0;
         sentido1=0;
         sentido2=0;
//         velocidade1=1;
//         velocidade2=1;
         t_vira=0; 
         c_vira=0;
         }
        
   }
  }
}

void Desvio(void){
 if(ir>0){
static int t_desvio=0;
   if(f_habilita==1){
      if(f_desvio==1){
         
            if(f_lado1==1){
            motor1=0;
            motor2=1;
            passo1=20;//100///
            sentido2=0;
            velocidade1=2;
            f_contpasso1=1;
            t_desvio=1;
            }
            
            if(f_lado2==1){
            motor1=1;
            motor2=0;
            passo2=20;//100///
            sentido1=0;
            velocidade2=2;
            f_contpasso2=1;
            t_desvio=1;
            }     
                     
            if((f_contpasso1==0)&&(f_contpasso2==0)&&(t_desvio==1)&&(f_lado1==0)&&(f_lado2==0)){
            motor1=1;
            motor2=1;
            sentido1=1;
            sentido2=1;
            passo1=20;//100
            passo2=20;//100
            velocidade1=2;
            velocidade2=2;
            f_contpasso1=1;
            f_contpasso2=1;
            t_desvio=2;
            }
            
            if((f_contpasso1==0)&&(f_contpasso2==0)&&(f_lado1==0)&&(f_lado2==0)&&(t_desvio==2)){
            motor1=0;
            motor2=0;
            velocidade1=2;
            velocidade2=2;
            t_desvio=0;
            f_desvio=0;
            }         
   }
   else t_desvio=0; 
 }

  } 
}

void ContPasso(void){
static int t_contpasso1=0,a_contpasso1=0,t_contpasso2=0,a_contpasso2=0;

   if (f_habilita==1){
      if(f_contpasso1==1){
         if(passo1<t_contpasso1){
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
         if(passo2<t_contpasso2){
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
      if(f_contpasso1==0){
      t_contpasso1=0;
      a_contpasso1=0;
      }
      if(f_contpasso2==0){
      t_contpasso2=0;
      a_contpasso2=0;      
      }
   }
}

void EmExecucao(void){
 static int executando=0,c_executando=0;
 if(t_menu==0){
    if(c_executando==5){///atualização do display 
      if((f_ir==0)&&(pronto==0))executando=0;
      if(f_re==1)executando=1;
      if((f_frente==1)&&(f_seguir==0)&&(f_ir>0))executando=8;
      if((f_lado1==1)&&(f_lado2==0)&&(f_ir>0))executando=2;
      if((f_lado1==0)&&(f_lado2==1)&&(f_ir>0))executando=3;
      if((f_gira==1)&&(ir>0))executando=4;
      if((f_seguir>0)&&(f_ir>0))executando=5;
      if((chegando>0)&&(ir>0))executando=6;
      if((saindo>0)&&(ir>0))executando=7;      
      if(pronto==1)executando=9;
                             
      switch(executando){
      
   case 0: printf(lcd_putc,"\fAGUARDANDO\,Or%i\,Ir%i\nFren\,D%lu\,D%lu\P%i", s_direcao,ir,dis_sensor1,dis_sensor2,f_proximidade);
      break;
      
      case 1:printf(lcd_putc,"\fD1%lu\,D2%lu\,Or%i\r%i\nRe\,P%i\,Ir%i",dis_sensor1,dis_sensor2,s_direcao,f_ir,f_proximidade,ir);
      break;
      
      case 8: printf(lcd_putc,"\fD%lu\D%lu\,Or%i\,Ir%i\nFren\,f%i\,P%i\P%i",dis_sensor1,
      dis_sensor2, s_direcao,ir,codico,potencia,f_proximidade);
      break;
      
      case 2:printf(lcd_putc,"\fD1%lu\,D2%lu\,Or%i\r%i\nDireita\,P%i\,Ir%i",dis_sensor1,dis_sensor2,s_direcao,f_ir,f_proximidade,ir);
      break;
      
      case 3:printf(lcd_putc,"\fD1%lu\,D2%lu\,Or%i\r%i\nEsquerda\,P%i\,Ir%i",dis_sensor1,dis_sensor2,s_direcao,f_ir,f_proximidade,ir);
      break;   
      
      case 4:printf(lcd_putc,"\fD1%lu\,D2%lu,Or%i\r%i\nGirando\,P%i\,Ir%i",dis_sensor1,dis_sensor2,s_direcao,f_ir,f_proximidade,ir);
      break;
      
      case 5:printf(lcd_putc,"\fSEGUINDO\,Or%i\,Ir%i\r%i\nf%i\,d%i,\P%i",s_direcao,f_ir,ir,controle,codico,f_proximidade);
      break;
      
      case 6:printf(lcd_putc,"\fCHEGANDO\,Or%i\r%i\nIr%i\,f%i\,d%i\P%i", s_direcao,f_ir,ir,controle,codico,f_proximidade);
      break;
      
      case 7:printf(lcd_putc,"\fSAINDO\,Or%i\nIr%i\nf%i\,d%i,\,P%i", s_direcao,ir,controle,codico,f_proximidade);
      break;
      
      case 9:printf(lcd_putc,"\fSERVIDOR\nALCANCADO\ Cod%i",codico);
      break;
      

      default:printf(lcd_putc,"\fD1 %lu\,D2%lu\npronto\,P%i",dis_sensor1,dis_sensor2,f_proximidade2);
      break;
      }
      c_executando=0;
    }
    c_executando++;
 }
   }

void SemSinal (void){     //

static int c_origem=0;
static int a_origem1=0,a_origem2=0,a_origem3=0,a_origem4=0;

   if(f_origem1>0){
   origem1=1;
   }
   
   if(f_origem2>0){
   origem2=2;
   }
   
   if(f_origem3>0){
   origem3=3;
   }
   
   if(f_origem4>0){
   origem4=4;
   }

  if(c_origem==80){//40 tempo agurdando por um sinal valido
  
   if(f_origem1>a_origem1){
   a_origem1=f_origem1;
   }
   else {
   a_origem1=0;
   f_origem1=0;
   origem1=0;
   }  
  if(f_origem2>a_origem2){
   a_origem2=f_origem2;

   }
   else {
   a_origem2=0;
   f_origem2=0;
   origem2=0;
   }
   if(f_origem3>a_origem3){
   a_origem3=f_origem3;
   }
   else {
   a_origem3=0;
   f_origem3=0;
   origem3=0;
   }
   if(f_origem4>a_origem4){
   a_origem4=f_origem4;
   }
   else {
   a_origem4=0;
   f_origem4=0;
   origem4=0;
   }

 c_origem=0;   
   
  }   
   c_origem++;
}

void Proximidade(void){
 static int b_proximidade=0,c_seguir=0;
   if((f_ir>0)&&(f_proximidade!=0)){

    if(seguir>0){
    c_seguir++;
      if(c_seguir==200){
      if(f_proximidade==0)seguir=0;
      c_seguir=0;
      }
    }
    
    if(f_proximidade>6){
    f_orientacao=1;
    }
              if((f_seguir>0)&&((f_proximidade<6)||((f_proximidade>0)&&((dis_sensor1>obstaculo)||(dis_sensor2>obstaculo))))){
         //   ir=0;
            f_desvio=0;
            f_frente=0;  ////
            f_vira=0;    ////
            f_gira=0;
            f_re=0;
            f_lado2=0;
            f_lado1=0; 
            f_orientacao=0;
           // f_proximidade=0;
            ir=0;
            //f_orientacao=0;
               if(f_seguir>0)seguir=1;
               if(f_seguir==0){
               chegando=0;
               saindo=0;
               t_proximidade=0;
              // f_proximidade=0;
               f_ir=0;
              
               pronto=1;//pronto
               t_proximidade=0;                              
               }
          } 
   
      if((f_proximidade<3)&&(chegando>0)&&(t_proximidade==0)){
      motor1=1;
      motor2=1;
      sentido1=1;
      sentido2=1;
      passo1=5;
      passo2=5;
      velocidade1=1;
      velocidade2=1; 
      f_contpasso1=1;
      f_contpasso2=1;
      t_proximidade=1;
      f_orientacao=0;
      }
//     if(((dis_sensor1>1)||(dis_sensor2>1)||(t_proximidade<250))&&(f_contpasso1==0)){/////
         if(((f_contpasso1==0)||(f_contpasso2==0))&&(t_proximidade==1)){
         motor1=1;
         motor2=1;
         sentido1=1;
         sentido2=1;
         passo1=15;
         passo2=15;
         velocidade1=2;
         velocidade1=2;
         f_contpasso1=1;
         t_proximidade=2;
         }
         
          if((saindo>0)&&(b_proximidade==2)&&(f_gira==0)){ 
          saindo=0;
          b_proximidade=0;
          f_checksensor=1;
          f_lado1=1;
          f_lado2=0;
          f_gira=1;
          f_orientacao=1;
         }
         
         if((saindo>0)&&(b_proximidade==1)&&(f_re==0)){ 
          b_proximidade=2;
          f_checksensor=1;
          f_lado1=1;
          f_lado2=0;
          f_gira=1;          
         }
    
         if((saindo>0)&&(b_proximidade==0)){ 
         f_orientacao=0;
          b_proximidade=1;
          f_checksensor=0;
          f_lado1=1;
          f_lado2=1;
          f_re=1;
          f_desvio=0;
         f_frente=0;  ////
         f_vira=0;    ////
         f_gira=0;
         f_orientacao=0;
          }
 
 //       if((f_proximidade>9)&&((chegando==1)||((chegando>0)&&((dis_sensor1>distancia_1)||(dis_sensor2>distancia_1))))){ 
        if((chegando>0)&&((chegando>0)||(dis_sensor2>obstaculo)||(dis_sensor1>obstaculo))){
            ir=0;
            f_desvio=0;
            f_frente=0;  ////
            f_vira=0;    ////
            f_gira=0;
            f_re=0;
            f_lado2=0;
            f_lado1=0; 
            f_orientacao=0;
           // f_proximidade=0;
               if(f_seguir>0)seguir=1;
               if(f_seguir==0){
               chegando=0;
               saindo=0;
               t_proximidade=0;
              // f_proximidade=0;
               f_ir=0;
               ir=0;
               pronto=1;
               t_proximidade=0;                              
               }
          } 
       
    }
   
 }

void EnviaComando( int t_motor1=0,int t_motor2=0, int t_sentido1=0, int t_sentido2=0,
int t_velocidade1=0, int t_velocidade2=0){
static int endereco=0,comando,t_comando,t_complemento,contenvio;

endereco='e';

if(t_motor1==1)bit_set(comando,7);
else bit_clear(comando,7);

if(t_motor2==1)bit_set(comando,6);
else bit_clear(comando,6);

if(t_sentido1==1)bit_set(comando,5);
else bit_clear(comando,5);

if(t_sentido2==1)bit_set(comando,4);
else bit_clear(comando,4);

if(bit_test (velocidade1,0))bit_set(comando,3);
else bit_clear(comando,3);

if(bit_test (velocidade1,1))bit_set(comando,2);
else bit_clear(comando,2);

if(bit_test (velocidade1,2))bit_set(comando,1);
else bit_clear(comando,1);

if(bit_test (velocidade1,3))bit_set(comando,0);
else bit_clear(comando,0);

if(bit_test (velocidade2,0))bit_set(complemento,3);
else bit_clear(complemento,3);

if(bit_test (velocidade2,1))bit_set(complemento,2);
else bit_clear(complemento,2);

if(bit_test (velocidade2,2))bit_set(complemento,1);
else bit_clear(complemento,1);

if(bit_test (velocidade2,3))bit_set(complemento,0);
else bit_clear(complemento,0);

if((t_comando!=comando)||(t_complemento!=complemento)||(contenvio==30)){
t_comando=comando;
t_complemento=complemento;
contenvio=0;
printf ("%c%c%c\r\n"endereco,comando,complemento);
}
contenvio++;
}  

void Funcao(void){     
static int c_led=0,c_botao=0,botao0=0,botao1=0,
botao2=0,botao3=0,botao4=0,botao5=0,c_ir=0,t_led;
   
   c_botao++; 
   if(c_botao==3){
   botao0=0;//
   botao1=0;
   botao2=0;
   botao3=0;
   botao4=0;
   botao5=0;
   c_ir=0;
   c_botao=0;
   }
   output_low(pin_b0);
      if(input(pin_b0)==1)botao0++;//>
      output_low(pin_b1);
      if(input(pin_b1)==1)botao1++;//<
      output_low(pin_b2);
      if(input(pin_b2)==1)botao2++;//+
      output_low(pin_b3);
      if(input(pin_b3)==1)botao3++;//-
      output_low(pin_b4);
      if(input(pin_b4)==1)botao4++;//Clean, ESC
      
   if((f_desvio==1)||(f_re==1)){
   f_orientacao=0;
   }
   else{if(f_proximidade>distancia){
   f_orientacao=1;
   }
   }
 if(f_seguir==1)t_led=5;
 else t_led=11;
 
 if(c_led==t_led){
 pisca=!pisca;
 c_led=0;
 }
 else c_led++;
 
 
 if((((botao3==2)&&(t_menu==0))||((codico==34))&&(chegando==0))){//ir para 4
 f_ir=4;
 f_orientacao=1;
 f_checksensor=1;
 pronto=0;
   }   
   if(origem4==4){
   output_high(pin_b3);
      if((pisca==1)&&(f_ir==4))output_low(pin_b3);
      else output_high(pin_b3); 
   }
   
 if((((botao2==2)&&(t_menu==0))||((codico==33))&&(chegando==0))){//ir para 3
 f_ir=3;
 f_orientacao=1;
 f_checksensor=1;
 pronto=0;
   }   
   if(origem3==3){
   output_high(pin_b2);
      if((pisca==1)&&(f_ir==3))output_low(pin_b2);
      else output_high(pin_b2); 
   }
   else output_low(pin_b2);
   
   if((((botao1==2)&&(t_menu==0))||((codico==32))&&(chegando==0))){//ir para 2
   f_ir=2;
   f_orientacao=1;
   f_checksensor=1;
   pronto=0;
   }   
   if(origem2==2){
   output_high(pin_b1);
      if((pisca==1)&&(f_ir==2))output_low(pin_b1);
      else output_high(pin_b1); 
   }
   else output_low(pin_b1);
   
   if((((botao0==2)&&(t_menu==0))||((codico==31))&&(chegando==0))){//ir para 1
   f_ir=1;
   f_orientacao=1;
   f_checksensor=1;
   pronto=0;
   }   
   if((origem1==1)||(origem5==5)){
   output_high(pin_b0);
      if((pisca==1)&&(f_ir==1))output_low(pin_b0);
      else output_high(pin_b0); 
   }
   else output_low(pin_b0);
   
  if((origem1==f_ir)||(origem2==f_ir)||(origem3==f_ir)||(origem4==f_ir)||((f_ir==1)
  &&(origem5==5))||((f_ir==2)&&(origem6==6))||((f_ir==3)&&(origem7==7))||((f_ir==4)&&(origem8==8))){
   
   If(seguir==0||(f_proximidade>distancia)){ 
   if((origem1==1)&&(f_ir==1)){ir=1;pronto=0;}
   if((origem2==2)&&(f_ir==2)){ir=2;pronto=0;}
   if((origem3==3)&&(f_ir==3)){ir=3;pronto=0;}
   if((origem4==4)&&(f_ir==4)){ir=4;pronto=0;}
  } 
   
  }
  else {ir=0;
  }
   if((botao4==2)||(codico==50)){//STOP
      if(t_menu==0){
      f_ir=0;
      ir=0;
      chegando=0;
      saindo=0;
      pronto=0;
      seguir=0;
      f_seguir=0;
      f_re=0;
      f_desvio=0;
      f_frente=0;  ////
      f_vira=0;    ////
      f_gira=0;
//      f_orientacao=0;
      pronto=0;
      }
      if(t_menu>0){
      t_menu=0;
      }
   }
   
   if((botao2==2)&&(t_menu==2)){
   f_seguir=1;//Seguir/FOLLOW
   
   if((botao3==2)&&(t_menu==2))f_seguir=0;//Seguir=0
   }
   if((motor1==0)&&(motor2==0))output_high(pin_b4);
    else output_low(pin_b4);
   
   if(codico==18)f_seguir=1,f_ir=1,pronto=0;//comando seguir controle x + codico 8
   if(codico==28)f_seguir=2,f_ir=2,pronto=0;
   if(codico==38)f_seguir=3,f_ir=3,pronto=0;
   if(codico==48)f_seguir=4,f_ir=4,pronto=0;
}

void Menu(void){
static int c_menu=0;

   if(c_menu==20){//tempo de mudanca do menu
   if(t_menu>0){
   
    if(input(pin_b0)==1){
     t_menu++;
    if(t_menu==10)t_menu=0;
   }
    if(input(pin_b1)==1){
    if(t_menu==1)t_menu=10; 
     t_menu--;
    }    
   }     
   if(input(pin_c0)==1)t_menu=1;
    
   if(t_menu==1)printf(lcd_putc,"\fMenu\nSelec < ou >");
     
   if(t_menu==2){
   printf(lcd_putc,"\fSEGUIR=%i\nSelc. + ou -"seguir);
   }

   if(t_menu==3){
   printf(lcd_putc,"\fIda e Volta=%i\nSelc. + ou -"ida_volta);
   }
   
   if(t_menu==4){   
   printf(lcd_putc,"\fSev.Ponte=%i\nSelc. + ou -"ida_volta);
   }         
   
   if(t_menu==5){printf(lcd_putc,"\fD1%lu\,D2%lu\,Or%i\,Ir%i\nChegando\,f%i\,d%i\P%i",dis_sensor1,
      dis_sensor2, s_direcao,ir,controle,codico,f_proximidade);
   }
     
   if(t_menu==6){printf(lcd_putc,"\fD1%lu\,D2%lu\,Or%i\,Ir%i\nSaindo\,f%i\,d%i,\,P%i",dis_sensor1,
      dis_sensor2, s_direcao,ir,controle,codico,f_proximidade);
   }
          
   if(t_menu==7){printf(lcd_putc,"\fDh %i\,Dl%i\nP%i",h_proximidade,l_proximidade,f_proximidade);
   }  
   
   if(t_menu==8)versao=1;
   
   if(t_menu==9){
   printf(lcd_putc,"\fmotor1=%i\motor2=%i\npasso%i\,%i\sedcmd%i",
   motor1,motor2,f_contpasso1,f_contpasso2,contcmd);
   }
    
//printf(lcd_putc,"\fCont%i\,CP%i\Tm0%i\nTm2%i\Cod\,f%i\,d%i\P%lu",conta,
//  contccp,cont0,cont2,codico,s_direcao,f_proximidade);
//   printf(lcd_putc,"\fdistancia:%lu",dis_sensor1);
   c_menu=0;
   }
   c_menu++;
}

void recebe(void){
if(kbhit()){
rx=getc();
if(rx==49)f_ir=1;
if(rx==50)f_ir=2;
if(rx==51)f_ir=3;
if(rx==52)f_ir=4;
if(rx==53){
      f_ir=0;
      ir=0;
      chegando=0;
      saindo=0;
      pronto=0;
      seguir=0;
      f_seguir=0;
      f_re=0;
      f_desvio=0;
      f_frente=0;  ////
      f_vira=0;    ////
      f_gira=0;
//      f_orientacao=0;
      pronto=0;
}
}
}
#int_ccp2 
void Sinal2(void){
//teste++;
//   output_high(pin_c3);
//   output_low(pin_c3);
//   output_high(pin_c3);
//   output_low(pin_c3);
}

#int_ccp1 
void Sinal(void){
   disable_interrupts(INT_CCP1);
   output_high(pin_c1);
   output_low(pin_c1); 
   enable_interrupts(INT_TIMER2); 
   start=0;
   
  
}

#int_TIMER0
void  TIMER0_isr(void){
static int timer=0;
   restart_wdt();
   if(timer<11)timer++;
   else{
   restart_wdt();
   Para();  
   ContPasso();
   set_timer0(1);
   EnviaComando(motor1,motor2,sentido1,sentido2,velocidade1,velocidade2);
   restart_wdt();
   timer=0;   
   }
  
} 

#int_TIMER2
void  TIMER2_isr(void){
static int t_controle=0,t_codico=0,a_controle=0,c_controle=0,c_codico=0,b_codico=0,
t_codico1=0,t_codico2=0,t_codico3=0,b_controle=0,
ca_controle=0,c_potencia=0,t_potencia=0, pot_1=9, pot_2=9, pot_3=9,pot_4=9;

   if(start==11){
   disable_interrupts(INT_TIMER2);
   clear_interrupt(INT_CCP1);
   enable_interrupts(INT_CCP1);
   start=0;
   }
   if(start==10){
   setup_timer_2(T2_DIV_BY_16,255,16),start=11;
   }
   if(start==9){
   setup_timer_2(T2_DIV_BY_16,255,16),start=10;
   }
   if(start==8){
   setup_timer_2(T2_DIV_BY_16,255,16),start=9;
   }
   
   if(start==7){
   disable_interrupts(INT_TIMER2);
   setup_ccp1(CCP_CAPTURE_FE);
   clear_interrupt(INT_CCP1);
   enable_interrupts(INT_CCP1);   
   }
    
      if(start==6){
       if((f_proximidade<distancia)&&(f_seguir==0)&&(f_ir>0)&&(t_proximidade==0)){
//        if(f_ir==(controle/10)){
//        chegando=1;
//        }
//        else saindo=1;
         if(f_ir==(controle/10))proximidade_a=f_proximidade;
         if(f_ir!=(controle/10))proximidade_b=f_proximidade;
         if((proximidade_a>proximidade_b)&&(saindo==0))chegando=1;
         if((proximidade_a<proximidade_b)&&(chegando==0))saindo=1;
         proximidade_a=0;
         proximidade_b=0;
       }
       if(t_codico1==t_codico){
         codico=t_codico;
         b_codico=0;
       }
       if(t_codico2==t_codico){
         codico=t_codico;
         b_codico=0;
       }
       if(t_codico3==t_codico){
         codico=t_codico;
         b_codico=0;
       }
       
       if(b_codico==0){
         t_codico1=t_codico;
         b_codico=1;
         }
         else{if(b_codico==1){
            t_codico2=t_codico;
            b_codico=2;
            }
            else{t_codico3=t_codico;
            b_codico=0;
            }
         }
//      output_high(pin_c3);
//      output_low(pin_c3);
         start=7;
      }
       
      if(start==5){         
         direcao();
         pot_4=pot_3;
         pot_3=pot_2;
         pot_2=pot_1;
         pot_1=t_potencia;
        // potencia=(pot_1+pot_2+pot_3)/3;
         controle=t_controle;
         potencia=t_potencia; 
//           if(potencia==9)f_proximidade=(255-h_proximidade);
//         }
         recebido=1;
//         output_low(pin_c3);        

//f_proximidade=potencia;
     
      start=6;
      }
     
     if(start==4){
//      output_high(pin_c3);
//      output_low(pin_c3);
      c_potencia--;
      if(input(PIN_C2)==0){
      h_proximidade=read_adc();
      bit_set(t_potencia,c_potencia);
      }
//      output_low(pin_c3);
        if(c_potencia==0){
         if((t_potencia>0)&&(t_potencia<11)){ //filtro       
        start=5;
         }
         else{//string invalida
         start=8;        
          }
        }
  }
   
   if(start==3){
//   output_high(pin_c3);
//   output_low(pin_c3);
   c_codico--;
      if(input(PIN_C2)==0){
      h_proximidade=read_adc();
      bit_set(t_codico,c_codico);
      }
//      output_low(pin_c3);
        if(c_codico==0){
         if((t_codico>0)&&(t_codico<99)){//filtro do codico //filtro        
         start=4;
         }
         else{//string invalida
          setup_timer_2(T2_DIV_BY_16,255,16);
          start=8;
          }
        }
  }
  
  if(start==2){
  set_adc_channel(4);
//   output_high(pin_c3);
//   output_low(pin_c3);
    c_controle--;
      if(input(PIN_C2)==0){
//       h_proximidade=read_adc();
      bit_set(t_controle,c_controle); 
      }
//      output_low(pin_c3);
        if(c_controle==0){
        b_controle=(t_controle%10);
         if((b_controle==0)&&(b_controle<5)){//filtro    
        c_codico=6;//numero de bits 
        start=3;
         }
         else{//string invalida
//         setup_timer_2(T2_DIV_BY_16,255,16);
         start=8;
         }
        }   
  }
 
if(start==1){
//   output_high(pin_c3);
//   output_low(pin_c3);
   setup_timer_2(T2_DIV_BY_4,139,16);//12us   1,7ms
   ca_controle--;
   
   if(input(PIN_C2)==0){
//    set_adc_channel(4);
   bit_set(a_controle,ca_controle);
//   l_proximidade=read_adc();
   }  
   
 if(ca_controle==0){
      if(a_controle==3){
      start=2; 
      c_controle=8;//comprimentos em bits
      c_potencia=6;//comprimentos em bits
      }
      else{//string invalida
      setup_timer_2(T2_DIV_BY_16,255,16);
      start=8;
      }
//   codico=t_codico;
   t_potencia=0;
   t_codico=0;
   }  
   }   
   if(start==0){
//   output_high(pin_c3);
//  output_low(pin_c3);
   ca_controle=2;//comprimentos em bits
   a_controle=0;
   t_controle=0;
   setup_timer_2(T2_DIV_BY_4,80,16);//64,8us   1,0ms
   start=1;
  }
}  

void main(void){
  printf ("e0\r\n"); 
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);///
   setup_timer_2(T2_DIV_BY_4,68,16);
   disable_interrupts(INT_TIMER2);
   setup_ccp1(CCP_CAPTURE_FE);    
   enable_interrupts(INT_CCP1);
   setup_ccp2(CCP_CAPTURE_FE);    
   enable_interrupts(INT_CCP2);
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4_AN5);
   setup_adc(ADC_CLOCK_DIV_16);
   setup_timer_0 (RTCC_DIV_32|RTCC_INTERNAL );
   enable_interrupts(INT_TIMER0);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_init();
   set_tris_c(0b11110101);
   set_tris_b(0b01011111); 
   set_tris_a(0b00101011);
   output_high(pin_b0);
   output_high(pin_b1);
   output_high(pin_b2);
   output_high(pin_b3);
   output_high(pin_b4);
   dis_sensor1=0;
   dis_sensor2=0;
   output_low(pin_b0);
   output_low(pin_b1);
   output_low(pin_b2);
   output_low(pin_b3);
   output_low(pin_b4);   
   enable_interrupts(GLOBAL);
   versao=1;
   printf ("e0\r\n");
   while(true){ 
   
 //Lado 1=direita=motor2=pin_a3=pin_b2
//Lado 2=esquerda=motor1=pin_a1=pin_b1
   
   if(versao==1){
   printf(lcd_putc,"AutoRobotica\nv. comando 29"); 
   delay_ms(200);//300
   versao=0;
   }
     
//   f_checksensor=1;
   contccp++;
   restart_wdt();
   delay_ms(10);
   Origem();
   Orientacao();  
   CheckSensor();  
   SensorProx();
   Desvio();
   Funcao();
   Re();
   Gira();
   Vira();   
   Frente();              
   SemSinal();   
//   Proximidade();  //  
   EmExecucao();//
   menu();
//   Recebe();
   }  
}



