#include <asf.h>

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
void first(){
	int led_port[] = {1,1,1,1,1,1,1,1};
	int led_pin[] = {27,28,29,30,19,20,21,22};
	for(int i = 0; i < 8; ++i){
		//AVR32_GPIO.port[led_port[i]].gpers = 1 << led_pin[i];
		//AVR32_GPIO.port[led_port[i]].oders = 1 << led_pin[i];
		AVR32_GPIO.port[led_port[i]].ovrc = 1 << led_pin[i];
	}
}

void second(){
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
void third(){

	AVR32_GPIO.port[2].gpers << 18;
	in_assignment_three = true;
	INTC_init_interrupts();
	int button_pin = 85;
	INTC_register_interrupt(&led_switch, (AVR32_GPIO_IRQ_0+button_pin/8), AVR32_INTC_INT0);
	gpio_enable_gpio_pin(button_pin);
	gpio_enable_pin_glitch_filter(button_pin);
	gpio_enable_pin_interrupt(button_pin, GPIO_FALLING_EDGE);
	Enable_global_interrupt();
	while (1)
	{
		//int i = (AVR32_GPIO.port[2].pvr >> 18) & 0x01;
		//if(state == 1 && i == 0){
		//AVR32_GPIO.port[1].ovrs = 1 <<led_pin[0];
		//AVR32_GPIO.port[1].ovrc = 1 << led_pin[1];
		//state = 2;
		//
		//}
		//else if(state == 2 && i == 1){
		//AVR32_GPIO.port[1].ovrs = 1 <<led_pin[1];
		//AVR32_GPIO.port[1].ovrc = 1 << led_pin[0];
		//state = 1;
	}
	//}
}

void fourth(){
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
void extras(){
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

int main(void) {
	board_init();
	//first();
	//second();
	//third();
	//fourth();
	extras();
	return 0;
}