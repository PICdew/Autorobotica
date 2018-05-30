#include <16f877a.h>
#use delay(clock=1600000)
#fuses hs
#include <lcd.c>

int acumul_lig;
int acumul_des;
int cont_sensor;
float distancia;


 sensor_prox(void){
   output_high(pin_b7);
   set_adc_channel(0);   
   acumul_lig=acumul_lig+read_adc();
   output_low(pin_b7);
   acumul_des=acumul_des+read_adc();
   if(cont_sensor<10)cont_sensor++;
   distancia=acumul_lig-acumul_des;
   cont_sensor=0;
  
   }
   
   
void main(){

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
   sensor_prox();
   printf(lcd_putc,"\fdistancia %f", distancia);
   }
}
