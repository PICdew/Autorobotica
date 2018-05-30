#include <16f877a.h>
#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=20000000)
#include <lcd.c>
#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)

int frequencia,ir, origem1,origem2,origem3,origem4,dury,dury1,dury2,dury3,dury4;
int f_origem1,f_origem2,f_origem3,f_origem4;
$  int t_chegou,f_chegou;

void Direcao(){
}

void Origem(void){
$ static int c_chegou; 
 if(frequencia==1.5){
 origem1=1;
 f_origem1++;
  dury1=dury;
$ c_chegou++;
$ f_chegou=(f_chegou+t_chegou); 
$  if(c_chegou=5){
   c_chegou=0;
    if(f_chegou>6){
    chegou1=f_chegou;
    f_chegou=o;
    }
    else chegou1=0;
   }
  if(ir=1){
  Direcao();
  }
$  else origem1=0; 
 }
 
 if(frequencia==2){
 origem2=1;
 f_origem2++;
 dury2=dury;
  if(ir=2){
  Direcao();
  }
 }
 
 if(frequencia==2.5){
 origem3=1;
 f_origem3++;
 dury3=dury;
  if(ir=3){
  Direcao();
  }
 }
 
 if(frequencia==3){
 origem4=1;
 f_origem4++;
 dury4=dury;
  if(ir=4){
  Direcao();
  }     
 }
}  

void main(void){
   while(true){
   Origem();
  } 
} 
 
