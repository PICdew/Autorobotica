#include <16f877a.h>
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#use standard_io(c)
#fuses hs
#include <lcd.c>



byte const posicao[4] = {0b1010,0b0110,0b0101,0b1001};
int1 habilita;
int sentido;
int velocidade=10;
int passo;
int timer;
int temp_velo;
int velo_cont;
long int valor;
float tensao;
int cont_sensor;
int16 acumul_lig;
int16 acumul_des;
int16 distancia;
int alerta;
int medida;


void motor(int1 habilita, int sentido, int velocidade){

   if (habilita==1){
      if(temp_velo!=velocidade){
      temp_velo=velocidade;
      velo_cont=temp_velo;
      }
         else{
            if(velo_cont!=0)velo_cont--;
            else{
         output_c(posicao[passo]);
         velo_cont=temp_velo;
   
      if(sentido==1){
      passo++;
         if(passo==4)passo=0;
      }
      
      if(sentido==0){
         if(passo==0)passo=3;
         passo--;
      }
            }
         
         }
   }
}

int16 sensor(int16 distancia ){
      long int temp1=0;
   long int temp2=0;
   output_high(pin_b2);
   set_adc_channel(0);   
    delay_ms(10);
    temp1=read_adc();
    temp1=temp1-65535;
    acumul_lig=acumul_lig+temp1;
    
     output_low(pin_b2);
     set_adc_channel(0);   
    delay_ms(10);
    temp2=read_adc();
    temp2=temp2-65535;
    acumul_des=acumul_des+temp2;
    delay_ms(10);
      if(cont_sensor<10){
      cont_sensor++;
      }
      else{
      distancia=acumul_des-acumul_lig;    
      acumul_lig=0;
      acumul_des=0;      
      cont_sensor=0;
      
      
     }
     alerta=distancia;
     if(distancia>150){
//     output_high(pin_c3);
     }
     else{
//     output_low(pin_c3);
     }
   return(distancia);
}


#int_TIMER0
void  TIMER0_isr(void) 
{
   if(timer<2)timer++;
   else{
  motor(habilita, sentido, velocidade);
  distancia=sensor(distancia);
   timer=0;
   }
}


void main(void){
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_16);
   setup_timer_0 (RTCC_DIV_2|RTCC_INTERNAL );
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_init();
   port_b_pullups(true);
  
   
   while(true){
   set_adc_channel(0);   
   delay_ms(200);
   valor=read_adc();
   output_low(pin_a4);
   tensao=valor*0.01960;
   delay_ms(10);
   
   printf(lcd_putc,"\fvelocidade:%u\ndistancia:%lu",velocidade,distancia);
   
   habilita=1;
   sentido=1;
   
   if(input(pin_b0)==0)velocidade++;
   if(input(pin_b1)==0)velocidade--;
   delay_ms(400);
   output_high(pin_a4);
   }
}


