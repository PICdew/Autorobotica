#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=20000000)
#include <lcd.c>
#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)


int ir,f_ir,dury1,dury2,dury3,dury4,origem1,origem2,origem3,origem4;

void Funcao (void){

   if(origem1==1)output_high(pin_b0);
   else output_low(pin_b0);
   
   if(origem2==1)output_high(pin_b1);
   else output_low(pin_b1);
   
   if(origem3==1)output_high(pin_b2);
   else output_low(pin_b2);
   
   if(origem4==1)output_high(pin_b3);
   else output_low(pin_b3);
   
   output_low(pin_b3);
   if((input(pin_b3)==1)||(dury4==10)){
   f_ir=4;
   ir=f_ir;
   }
   
   output_low(pin_b1);
   if((input(pin_b1)==1)||(dury2==20)){
   f_ir=2;
   ir=f_ir;
   }
   
   output_low(pin_b0);
   if((input(pin_b0)==1)||(dury1==10)){
   f_ir=1;
   ir=f_ir;
   }
   
   output_low(pin_b2);
   if((input(pin_b2)==1)||(dury3==10)){
   f_ir=3;
   ir=f_ir;
   }
   
   
   if(input(pin_b0)==1){
   f_ir=0;
   ir=f_ir;
   }
 }

void main(void){
   while(true){
   Funcao ();
   }
}

