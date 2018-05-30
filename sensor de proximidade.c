#include <16f877a.h>
#use delay(clock=1600000)
#fuses hs
#include <lcd.c>


int cont_sensor;
int16 acumul_lig;
int16 acumul_des;
int16 distancia;
int alerta;




void main(){
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_16);   
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_init();
   port_b_pullups(true);
   
   while(true){
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
      printf(lcd_putc,"\ndistancia:%lu",distancia); 
      
     }
     alerta=distancia;
     if(distancia>150){
     output_high(pin_c3);
     }
     else{
     output_low(pin_c3);
     }
     }
   
}

