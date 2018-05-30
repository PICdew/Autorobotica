#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=20000000)
#include <lcd.c>
#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)


int f_origem1,f_origem2,f_origem3,f_origem4,ir;

void SemSinal (void){

static int c_origem;
static int a_origem1,a_origem2,a_origem3,a_origem4;

  if(c_origem==50){
  
   if(f_origem1>a_origem1){
   f_origem1=1;
   a_origem1=f_origem1;
   ir=1;
   }
   else {
   a_origem1=0;
   f_origem1=0;
   ir=0;
   }  
   if(f_origem2>a_origem2){
   f_origem2=1;
   a_origem2=f_origem2;
   ir=2;
   }
   else {
   a_origem2=0;
   f_origem2=0;
   ir=0;
   }
   if(f_origem3>a_origem3){
   f_origem3=1;
   a_origem3=f_origem3;
   ir=3;
   }
   else {
   a_origem3=0;
   f_origem3=0;
   ir=0;
   }
   if(f_origem4>a_origem4){
   f_origem4=1;
   a_origem4=f_origem4;
   ir=4;
   }
   else {
   a_origem4=0;
   f_origem4=0;
   ir=0;
   }
 c_origem=0;   
   
  }
   
   c_origem++;

}

void main(void){
   while(true){
 
  } 
} 
