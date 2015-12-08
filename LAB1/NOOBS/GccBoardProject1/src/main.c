#include "asf.h"
#include "gpio.h"
#include "board.h"
//#include "conf_example.h"
#include "adc.h"
#include "pwm.h"
//#include "io.h"


int state = 0;
bool in_assignment_three = false;
__attribute__((__interrupt__)) void led_switch(void){
	if(in_assignment_three){
		int led_pin[] = {19, 20};
		if(state == 0){
			AVR32_GPIO.port[1].ovrs = 1 <<led_pin[0];
			AVR32_GPIO.port[1].ovrc = 1 << led_pin[1];
			state = 1;
		}
		else if(state == 1){
			AVR32_GPIO.port[1].ovrs = 1 <<led_pin[1];
			AVR32_GPIO.port[1].ovrc = 1 << led_pin[0];
			state = 0;
		}
	}
	gpio_clear_pin_interrupt_flag(85);
}
__attribute__((__interrupt__)) void lab2_led_switch(void){
	int red = 51;
	int green = 52;
	if(state == 0){
		gpio_clr_gpio_pin(red);
		gpio_set_gpio_pin(green);
		state = 1;
	}
	else if(state == 1){
		gpio_set_gpio_pin(red);
		gpio_clr_gpio_pin(green);
		state = 0;
	}
	gpio_clear_pin_interrupt_flag(85);
}
void lab1(){
	//	lab1_1();
	//lab1_2();
	//lab1_3();
	//lab1_4();
	//lab1_5();
}
void lab1_1(){
	int led_port[] = {1,1,1,1,1,1,1,1};
	int led_pin[] = {27,28,29,30,19,20,21,22};
	for(int i = 0; i < 8; ++i){
		//AVR32_GPIO.port[led_port[i]].gpers = 1 << led_pin[i];
		AVR32_GPIO.port[led_port[i]].ovrc = 1 << led_pin[i];
	}
}

void lab1_2(){
	int led_port[] = {1,1,1,1,1,1,1,1};
	int led_pin[] = {27,28,29,30,19,20,21,22};
	int j = 0;
	AVR32_GPIO.port[2].gpers <<18;
	while(1){
		int i=(AVR32_GPIO.port[2].pvr >> 18) & 0x01;
		if(i==1)
		{
			AVR32_GPIO.port[led_port[j]].ovrs = 1 << led_pin[j];
			
		}
		else if(i==0)
		{
			AVR32_GPIO.port[led_port[j]].ovrc = 1 << led_pin[j];
			
		}
	}

}
void lab1_3(){

	AVR32_GPIO.port[2].gpers << 18;
	in_assignment_three = true;
	INTC_init_interrupts();
	int button_pin = 85;
	INTC_register_interrupt(&led_switch, (AVR32_GPIO_IRQ_0+button_pin/8), AVR32_INTC_INT0);
	gpio_enable_gpio_pin(button_pin);
	gpio_enable_pin_interrupt(button_pin, GPIO_FALLING_EDGE);
	Enable_global_interrupt();
	while (1)
	{
	}

}

void lab1_4(){
	int led_port[] = {1,1,1,1,1,1,1,1};
	int led_pin[] = {27,28,29,30,19,20,21,22};
	int j = 0;
	AVR32_GPIO.port[2].gpers <<18;
	while(1){
		int i=(AVR32_GPIO.port[2].pvr >> 18) & 0x01;
		if(i==1)
		{
			AVR32_GPIO.port[1].ovrs = 1 << led_pin[4];
			AVR32_GPIO.port[1].ovrc = 1 << led_pin[5];
		}
		else if(i==0)
		{
			AVR32_GPIO.port[1].ovrs = 1 << led_pin[5];
			AVR32_GPIO.port[1].ovrc = 1 << led_pin[4];
			
		}
	}

}
void lab1_5(){
	while(1){
		if((~AVR32_GPIO.port[2].pvr & 0x1240000) == 0x1240000)
		{
			AVR32_GPIO.port[1].ovrc = 0x78780000;  //Set all leds high
		}
		else
		{
			AVR32_GPIO.port[1].ovrs = 0x78780000;
		}
	}
}
void lab2(){
	//lab1();
	//lab2_1();
	//lab2_2();
	//lab2_3();
	//lab2_4();
	//lab2_5();
}
void lab2_1(){
	unsigned int pins[] = {59,60,61,62,51,52,53,54};
	for(int i=0; i <8; ++i)
	{
		gpio_enable_gpio_pin(pins[i]);
		gpio_clr_gpio_pin(pins[i]);
	}
}

void lab2_2(){
	int led = 62;
	int btn = 88;
	gpio_enable_gpio_pin(led);
	gpio_enable_gpio_pin(btn);
	while(1){
		int pushed = gpio_get_pin_value(btn);
		if(pushed == 0){
			gpio_clr_gpio_pin(led);
		}
		else {
			gpio_set_gpio_pin(led);
		}
	}
}

void lab2_3(){
	int red = 51;
	int green = 52;
	int button_pin = 85;
	INTC_register_interrupt(&lab2_led_switch, (AVR32_GPIO_IRQ_0+button_pin/8), AVR32_INTC_INT0);
	gpio_enable_gpio_pin(button_pin);
	gpio_enable_pin_glitch_filter(button_pin);
	gpio_enable_pin_interrupt(button_pin, GPIO_FALLING_EDGE);
	Enable_global_interrupt();
	gpio_enable_gpio_pin(red);
	gpio_enable_gpio_pin(green);
	gpio_enable_gpio_pin(button_pin);
	while(1){
		
	}
}

void lab2_4(){
	int red = 51;
	int green = 52;
	int btn = 85;
	gpio_enable_gpio_pin(red);
	gpio_enable_gpio_pin(green);
	gpio_enable_gpio_pin(btn);
	
	while(1){
		int pushed = gpio_get_pin_value(btn);
		if(pushed == 0){
			gpio_clr_gpio_pin(red);
			gpio_set_gpio_pin(green);
		}
		else
		{
			gpio_set_gpio_pin(red);
			gpio_clr_gpio_pin(green);
		}
		
	}
}

void lab2_5(){

	int joystick[5] = {25,26,27,28,20};
	int led[5] = {59,60,62,61,51};
	for(int i = 0;i<5;++i)
	{
		gpio_enable_gpio_pin(joystick[i]);
	}

	while(1)
	{
		for(int i = 0; i < 5 ; ++i){
			int btn = gpio_get_pin_value(joystick[i]);
			if(btn == 0){
				gpio_clr_gpio_pin(led[i]);
			}
			else{
				gpio_set_gpio_pin(led[i]);
			}
		}
	}

}
void lab3_1(){
	int buttons[] = {88, 85, 82};
	int leds[] = {1, 2, 4, 8, 32, 128};
	for(int i = 0; i < 3 ; ++i){
		gpio_enable_gpio_pin(buttons[i]);
	}
	while(1){
		for(int i = 0; i < 3; ++i){
			int r = gpio_get_pin_value(buttons[i]);
			if(r == 0){
				LED_On(leds[i]);
				LED_On(leds[i+3]);
			}
			else
			{
				LED_Off(leds[i]);
				LED_Off(leds[i+3]);
			}
		}
	}
	
}
void lab3_2(){
	//Display lights only the selected leds and turns the other off
	//ON turns 'em on
}

void lab4_1(){
	//resolution of ADC - 10 bit = 1023
}

void lab4_2(){
	
	// temp				PA21/ADC0
	// potentiometer	PA22/ADC1
	// photoresistor	PA23/ADC2
	int leds[] = {59, 60, 61, 62, 52, 54};
	int limits[] = {50, 80, 150, 200, 300, 400};
	int nr_of_limits = 6;
	int adc_lightchannel = 2;
	for(int i = 0; i < nr_of_limits; ++i){gpio_enable_gpio_pin(leds[i]);}
	adc_enable(&AVR32_ADC, adc_lightchannel);
	while(1){

		adc_start(&AVR32_ADC);
		int adc_value_light = adc_get_value(&AVR32_ADC,adc_lightchannel);
		for(int i = 0; i < nr_of_limits; ++i){
			if(adc_value_light > limits[i]){
				gpio_clr_gpio_pin(leds[i]);
			}
			else{
				gpio_set_gpio_pin(leds[i]);
			}
		}
	}
}

void lab5(){
	//How many PWM channels exist? 7
	adc_enable(&AVR32_ADC, 1);
	unsigned int channel_id = 2;
	avr32_pwm_channel_t pwm_channel ={ .ccnt = 0};
	gpio_enable_module_pin(AVR32_PWM_2_PIN,AVR32_PWM_2_FUNCTION);
	pwm_channel.CMR.cpre = AVR32_PWM_CPRE_MCK_DIV_256;
	pwm_channel.cprd = 20;
	pwm_start_channels(1 << channel_id);

	while(1)
	{
		
		adc_start(&AVR32_ADC);
		int adc_pot_value = adc_get_value(&AVR32_ADC,1);
		
		pwm_channel.cdty = pwm_channel.cprd*adc_pot_value/1023;
		pwm_channel_init(channel_id,&pwm_channel);
		
	}
}

int main(void) {
	board_init();
	lab5();
	//lab1();
	//lab2();
	//lab3_1();
	//lab3_2();
	//lab4_2();
	//lab5();
	return 0;
}
