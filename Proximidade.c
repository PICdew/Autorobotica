#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=20000000)
#include <lcd.c>
#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)

int f_habilita=0,f_frente=0,f_re=0,f_lado1=0,f_lado2=0,f_contpasso1=0,
f_contpasso2=0,f_desvio=0,f_gira=0,f_checksensor=0,f_vira=0;
int motor1=0,motor2=0,sentido1=0,sentido2=0,velocidade1=0,velocidade2=0;
long int passo1=0,passo2=0,dis_sensor1=0,dis_sensor2=0;
int ir,f_ir,origem1,origem2,origem3,origem4,dury1,dury2,dury3,dury4;

int f_origem1,f_origem2,f_origem3,f_origem4;
int s_direcao=0,f_orientacao=0;
long int cont=0;
long int frequencia=0,dury=0;
long int s_proximidade,f_proximidade=0,f_proximidade1,f_proximidade2,f_proximidade3,f_proximidade4,
f_chegando,t_re;

void Proximidade(void){
 static int t_proximidade,c_proximidade,a_proximidade,
 b_proximidade;
 
 if(f_proximidade==1){
   
  if(c_proximidade<10){
  a_proximidade=a_proximidade+s_proximidade;
  c_proximidade++;
  }
  else{
  c_proximidade=0;
  t_proximidade=a_proximidade;
  a_proximidade=0;
  }
   
   if(f_proximidade1>2){
      if(ir==1){
      f_chegando=1;
      }
      f_chegando=0;
     }
     
   if(f_proximidade2>2){
      if(ir==2){
      f_chegando=1;
      }
      f_chegando=0;
     }   

   if(f_proximidade3>2){
      if(ir==3){
      f_chegando=1;
      }
      f_chegando=0;
     }
    if(f_proximidade4>2){
      if(ir==4){
      f_chegando=1;
      }
      f_chegando=0;
     }
   
   if((f_chegando==1)&&(f_contpasso1==0)){  
   motor1=1;
   motor2=1;
   sentido1=0;
   sentido2=0;
   passo1=20;
   passo2=20;
   velocidade1=2;
   velocidade2=2;         
   
      if(((dis_sensor1>1)||(dis_sensor2>1)||(t_proximidade>4))&&(f_contpasso1==0)){
      motor1=1;
      motor2=1;
      sentido1=0;
      sentido2=0;
      passo1=10;
      passo2=10;
      velocidade1=3;
      velocidade2=3;
      motor1=0;
      f_contpasso1=1;
      t_proximidade=1;
            
                 
         if(((dis_sensor1>5)||(dis_sensor2>5)||(t_proximidade>10))){
         ir==0;
         origem1=0;
         origem2=0;
         origem3=0;
         origem4=0;
         }
   
      }
      f_contpasso1=1;
      f_contpasso2=1;

   }
 
      if(f_chegando==0){   
       if((b_proximidade==0)&&(f_contpasso1==0)&&   
       ((dis_sensor1<3)||(dis_sensor2<3))){
       b_proximidade=2;
       f_checksensor=0;
       f_re=1;     
       }         
       if((f_contpasso1==0)&&(b_proximidade==2)&&(f_re==0)){
       b_proximidade=3;
       f_checksensor=0;
       f_gira=1; 
       }
         
       if((f_contpasso1==0)&&(b_proximidade==3)&&(f_re==0)){
       b_proximidade=3;
       f_checksensor=0;
       f_gira=1; 
       }   
        
   }             
       if((dis_sensor1>3)||(dis_sensor1>3)&&(f_proximidade>10)){
       ir=0;
       f_chegando=1;
       }
}
}


void main(void){
   while(true){
   Proximidade();
   }
}

