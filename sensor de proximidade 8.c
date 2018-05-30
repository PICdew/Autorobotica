#include <16f877a.h>
#use delay(clock=20000000)
#fuses hs
#include <lcd.c>



long dis_sensor1;
long dis_sensor2;
int alerta;
int status[7];

void SensorProx(void){


static int cont1;
   if(cont1==50){
 static long int t_sensor1_1;
 static long int t_sensor1_2;
 static long acumul_lig1;
 static long acumul_des1;
 static int cont_sensor1;
 static int t_cont1;
  
 static long int t_sensor2_1;
 static long int t_sensor2_2;
 static long acumul_lig2;
 static long acumul_des2;
 static int cont_sensor2;
 static int t_cont2; 
 
 if(t_cont1=20){
 
   
   set_adc_channel(0);
//   delay_us(3);
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
 }
 t_cont1++;
dis_sensor1=(acumul_des1-acumul_lig1);
 dis_sensor2=(acumul_des2-acumul_lig2);
 
 if(t_cont1>20){
 acumul_lig1=0;
 acumul_des1=0;
 acumul_lig2=0;
 acumul_des2=0;
 cont1=0;
 t_cont1=0;
 }
}
cont1++;

}

#int_TIMER0
void  TIMER0_isr(void){
static int timer;

   if(timer<12)timer++;
   else{
      SensorProx();
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
   port_b_pullups(true);
   
   printf(lcd_putc,"\fsensor de prox_7");
   delay_ms(1);
   
   while(true){
  
   printf(lcd_putc,"\fdistancia:%lu",dis_sensor1);
   printf(lcd_putc,"\ndistancia:%lu",dis_sensor2);
   delay_ms(100);
   alerta=dis_sensor1;
   
   if(status[0]=1);
     if(dis_sensor1>3){
     output_high(pin_c3);
     }
     else{
     output_low(pin_c3);
     }
     }
   
}

