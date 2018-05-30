#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=20000000)
#include <lcd.c>
#use standard_io(c)

 void Direcao();
int ir, origem1,origem2,origem3,origem4,dury1,dury2,dury3,dury4;
int a_origem,dury;
 long s_direcao;
long cont;
long frequencia;

void Origem(void){
static int a_origem1,a_origem2,a_origem3,a_origem4,c_origem;
static int a2_origem1,a2_origem2,a2_origem3,a2_origem4;
 
 if(frequencia==99){
 origem1=1;
 a_origem1++;
 dury1=dury;
  if(ir==1){
  Direcao();
  }
 }
 
 if(frequencia==49){
 origem2=1;
 a_origem2++;
 dury2=dury;
  if(ir==2){
  Direcao();
  }
 }
 
 if(frequencia==33){
 origem3=1;
 a_origem3++;
 dury3=dury;
  if(ir==3){
  Direcao();
  }
 }
 
 if(frequencia==3){
 origem4=1;
 a_origem4++;
 dury4=dury;
  if(ir==4){
  Direcao();
  }
  
  
  
 }
  if(c_origem==800){
  
   if(a_origem1==a2_origem1){
   origem1=0;
   a_origem1=0;
   a2_origem1=0;
   c_origem=0;
   }
   
   if(a_origem2==0){
   origem2=0;
   a_origem2=0;
   c_origem=0;
   }
   
   if(a_origem3==0){
   origem3=0;
   a_origem3=0;
   c_origem=0;
   }
   
   if(a_origem4==0){
   origem4=0;
   a_origem4=0;
   c_origem=0;
   }
   
   a2_origem1=a_origem1;
  } 
   c_origem++;
}

void Direcao(void){

static int c_recebimento,c_lado_a,c_lado_b,c_lado_c,c_lado_d,c_lado_e,c_lado_f;


   if(c_recebimento<3){
   
      if((input(pin_c5)==0)&&(input(pin_c6)==1)&&(input(pin_c7)==1))c_lado_a++;
      if((input(pin_c5)==0)&&(input(pin_c6)==0)&&(input(pin_c7)==1))c_lado_b++;
      if((input(pin_c6)==0)&&(input(pin_c5)==1)&&(input(pin_c7)==1))c_lado_c++;
      if((input(pin_c6)==0)&&(input(pin_c7)==0)&&(input(pin_c5)==1))c_lado_d++;
      if((input(pin_c7)==0)&&(input(pin_c5)==1)&&(input(pin_c6)==1))c_lado_e++;
      if((input(pin_c5)==0)&&(input(pin_c6)==0)&&(input(pin_c7)==0))c_lado_f++;
      
   c_recebimento++;
   }
   
   
   else{
   c_recebimento=0;
   
    if((c_lado_a>c_lado_b)&&(c_lado_a>c_lado_c)&&(c_lado_a>c_lado_d)&&
    (c_lado_a>c_lado_e)&&(c_lado_a>c_lado_f))s_direcao=1;
   
      else{   
      if((c_lado_b>c_lado_a)&&(c_lado_b>c_lado_c)&&(c_lado_b>c_lado_d)&&
      (c_lado_b>c_lado_e)&&(c_lado_b>c_lado_f))s_direcao=2;
      
      else{       
      if((c_lado_c>c_lado_a)&&(c_lado_c>c_lado_b)&&(c_lado_c>c_lado_d)&&
      (c_lado_c>c_lado_e)&&(c_lado_c>c_lado_f))s_direcao=3;
   
      else{   
      if((c_lado_d>c_lado_a)&&(c_lado_d>c_lado_b)&&(c_lado_d>c_lado_c)&&
      (c_lado_d>c_lado_e)&&(c_lado_d>c_lado_f))s_direcao=4;
   
      else{   
      if((c_lado_e>c_lado_a)&&(c_lado_e>c_lado_b)&&(c_lado_e>c_lado_c)&&
      (c_lado_e>c_lado_d)&&(c_lado_e>c_lado_f))s_direcao=5;
   
      else{   
      if((c_lado_f>c_lado_a)&&(c_lado_f>c_lado_b)&&(c_lado_f>c_lado_c)&&
      (c_lado_f>c_lado_d)&&(c_lado_f>c_lado_e))s_direcao=6;

//   return s_direcao;     
   
   
      }
      }
      }
      }
      }
      c_lado_a=0;   c_lado_b=0;   c_lado_c=0;   c_lado_d=0;   c_lado_e=0;   c_lado_f=0;

      }
}


#int_ccp1
void Sinal(void){

long t_dury,t_frequencia;
static short s_pulso,s_dury,s_frequencia;

   cont++; 
   Origem();
   if(s_pulso==0){
   set_timer1(0);
   setup_ccp1(CCP_CAPTURE_RE);
   s_pulso=1;
   s_dury=0;
   }
      else{
      if(s_dury==0){
      t_dury=CCP_1;
      setup_ccp1(CCP_CAPTURE_FE);
      s_dury=1;        
      }
         else{
         if(s_frequencia==0){
         t_frequencia=CCP_1;
         dury=t_dury*.04;
         frequencia=(t_frequencia-t_dury)*.04;
         s_pulso=0;
         s_dury=0;
         s_frequencia=0;
         }     
         }        
         
      } 

} 

void main(void){
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_ccp1(CCP_CAPTURE_FE);    // Configure CCP1 to capture rise
   enable_interrupts(INT_CCP1);   // Setup interrupt on falling edge
   enable_interrupts(GLOBAL);
   lcd_init();
   set_timer1(0);
//   s_pulso=0,s_dury=0,s_frequencia=0;
//   t_dury=0,t_frequencia=0,cont=0;
   
//    c_recebimento=0,c_lado_a=0,c_lado_b=0,c_lado_c=0,c_lado_d=0,c_lado_e=0;;
//    c_lado_f=0,s_direcao='o';
    lcd_init();
   ir=1;
 
   while(true){
   
   output_high(pin_a0);
   printf(lcd_putc,"\fOr%u\,%u\,%u\,%u\nDr%u\,%u\,%u\,%u"origem1,origem2,origem3,origem4,dury1,dury2,dury3,dury4);
   delay_ms(60);
     printf(lcd_putc,"\flado:%lu\nfre%lu\du:%du"s_direcao,frequencia,dury);
 //  printf(lcd_putc,"\flado:%lu\ncont%lu\nfre%lu\du:%du"s_direcao,cont,frequencia,dury); 
  output_low(pin_a0);
  delay_ms(500);
   }
}
     
