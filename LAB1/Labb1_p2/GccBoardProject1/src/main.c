#include <asf.h>
#define EXAMPLE_PWM_PIN AVR32_PWM_3_PIN
#define EXAMPLE_PWM_FUNCTION AVR32_PWM_3_FUNCTION

#define switch1 88

volatile int vol_state = 1;

__attribute__((__interrupt__)) static void interrupt(void)
{
	if (vol_state == 1)
	{
		vol_state = 2;
	}
	else if (vol_state == 2)
	{
		vol_state = 1;
	}
	
	gpio_clear_pin_interrupt_flag(switch1);
}



void initLED (int port, int bit)
{
	AVR32_GPIO.port[port].gpers = 1 << bit;
	AVR32_GPIO.port[port].oders = 1 << bit;
}

void lightLED (int port, int bit)
{
	AVR32_GPIO.port[port].ovrc = 1 << bit;
}

void closeLED (int port, int bit)
{
	AVR32_GPIO.port[port].ovrs = 1 << bit;
}

void part11()
{
	// Light all leds
	int light[] = {27, 28, 29, 30, 19, 20, 21, 22};
	for(int i=0; i<8; ++i)
	{
		lightLED(1, light[i]);
	}
}

void part12()
{
	// Turn off one when pressing a button
	while(1)
	{
		int i=(AVR32_GPIO.port[2].pvr >> 24) & 0x01;
		
		if(i==1)
		{
			lightLED(1, 22);
		}
		else if (i==0)
		{
			closeLED(1, 22);
		}
	}
	
}

void part13()
{
//Change state of led with interrupt
	// Interrupt initiation
	INTC_init_interrupts();
	INTC_register_interrupt(&interrupt, (AVR32_GPIO_IRQ_0+88/8), AVR32_INTC_INT0);
	// Set response time for switch
	gpio_enable_pin_glitch_filter(switch1);
	// Enable a pin and define type
	gpio_enable_pin_interrupt(switch1, GPIO_FALLING_EDGE);
	// Enable global interrupts
	Enable_global_interrupt();

	// Initial state
	vol_state = 1;
	while(1)
	{
		
		if (vol_state == 1)
		{
			lightLED(1, 20);
			closeLED(1, 19);
		}
		else if (vol_state == 2)
		{
			lightLED(1, 19);
			closeLED(1, 20);
		}
		
	}
	
}

void part14()
{
//Change state of led with interrupt
	// Interrupt initiation
	INTC_init_interrupts();
	INTC_register_interrupt(&interrupt, (AVR32_GPIO_IRQ_0+88/8), AVR32_INTC_INT0);
	// Set response time for switch
	gpio_enable_pin_glitch_filter(switch1);
	// Enable a pin and define type
	gpio_enable_pin_interrupt(switch1, GPIO_RISING_EDGE);
	// Enable global interrupts
	Enable_global_interrupt();

	// Initial state
	vol_state = 1;
	while(1)
	{
		int i=(AVR32_GPIO.port[2].pvr >> 24) & 0x01;
		

		if (vol_state == 1)
		{
			lightLED(1, 20);
			closeLED(1, 19);
		}
		else if (vol_state == 2)
		{
			lightLED(1, 19);
			closeLED(1, 20);
		}
		
	}
	
}


void part15()
{
	int buttons = (1<<24)|(1<<21)|(1<<18);
	int cool = (1<<24)|(1<<18);
	int i = 0;
	while(1)
	{
		// Read all buttons
		i = ~AVR32_GPIO.port[2].pvr & buttons;
		
		
		if(i == cool)
		{
			lightLED(1, 22);
		}
		else if (i==0)
		{
			closeLED(1, 22);
		}
	}
}

void part16()
{
	int LEDs = (1<<19)|(1<<20)|(1<<21)|(1<<22)|(1<<27)|(1<<28)|(1<<29)|(1<<30);
	
	// Light all leds
	AVR32_GPIO.port[1].ovrc = LEDs;	
}

void part21()
{
	unsigned int pin;
	unsigned int LEDs[] = {59, 60, 61, 62, 51, 52, 53, 54};
	for (int i = 0; i < 8; ++i )
	{
		pin = LEDs[i];
		gpio_enable_gpio_pin(pin);
		gpio_clr_gpio_pin(pin);
	}
	
}

void part22()
{
	unsigned int LEDPin = 59;
	unsigned int buttonPin = 88;
	unsigned int buttonVal = 0;
	
	gpio_enable_gpio_pin(buttonPin);
	gpio_enable_gpio_pin(LEDPin);
	
	while(1)
	{
		buttonVal = gpio_get_pin_value(buttonPin);
		
		if(buttonVal == 0)
		{
			gpio_clr_gpio_pin(LEDPin);
		}
		else if(buttonVal == 1)
		{
			gpio_set_gpio_pin(LEDPin);
		}
	}
	
}

void part23()
{
	unsigned int green = 51;
	unsigned int red = 52;
	unsigned int buttonPin = 88;
	unsigned int buttonVal = 0;
	int old = 1;
	
	gpio_enable_gpio_pin(buttonPin);
	gpio_enable_gpio_pin(green);
	gpio_enable_gpio_pin(red);
	
	// Set initial state
	unsigned int LEDVal = 0;
	gpio_clr_gpio_pin(green);
	gpio_set_gpio_pin(red);	
	
	// State loop
	while (1)
	{
		buttonVal = gpio_get_pin_value(buttonPin);
		
		// Detect falling edge
		if (buttonVal < old)
		// Detect rising edge
		//if (buttonVal > old)
		
		{		
			if (LEDVal == 1)
			{
				gpio_clr_gpio_pin(green);
				gpio_set_gpio_pin(red);
				LEDVal = 0;
			}
			else if (LEDVal == 0)
			{
				gpio_clr_gpio_pin(red);
				gpio_set_gpio_pin(green);
				LEDVal = 1;
			}
			
		} 
		old = buttonVal;
	}
	
}

void part25()
{
	/*
	left = PA25 = GPIO25
	up = PA26 = GPIO26
	right = PA27 = GPIO27
	down = PA28 = GPIO28
	button = PA20 = GPIO20	 
	*/
	int buttonVal = 1;	
	int up = 26;
	int right = 27;
	int down = 28;
	int left = 25;
	int button = 20;
	int l1 = 59;
	int l2 = 60;
	int l3 = 61;
	int l4 = 62;
	int all[] = {51, 52, 53, 54};
	
	gpio_enable_gpio_pin(up);
	gpio_enable_gpio_pin(l1);
	while (1)
	{
		if (!gpio_get_pin_value(up))
		{
			gpio_clr_gpio_pin(l1);
		}
		else if (!gpio_get_pin_value(right))
		{
			gpio_clr_gpio_pin(l2);
		}
		else if (!gpio_get_pin_value(down))
		{
			gpio_clr_gpio_pin(l3);
		}
		else if (!gpio_get_pin_value(left))
		{
			gpio_clr_gpio_pin(l4);
		}
		else if (!gpio_get_pin_value(button))
		{
			for (int i = 0; i < 4; ++i)
				{
					gpio_clr_gpio_pin(all[i]);
				}
		}
		else
		{	
			gpio_set_gpio_pin(51);
			gpio_set_gpio_pin(52);
			gpio_set_gpio_pin(53);
			gpio_set_gpio_pin(54);
			gpio_set_gpio_pin(59);
			gpio_set_gpio_pin(60);
			gpio_set_gpio_pin(61);
			gpio_set_gpio_pin(62);
		}
	}
}

void part31()
{
	int buttonPin = 88;
	int buttonVal = 1;
	int old = 1;
	int LED = 0x01;
		
	gpio_enable_gpio_pin(buttonPin);
	
	while (1)
	{
		buttonVal = gpio_get_pin_value(buttonPin);
		
		if (buttonVal < old)
		{
			// With display
			//LED_Display(LED);
			// With LED_On/Off
			LED_On(LED);
			
			// Shift led
			if (LED <= 0x80)
			{
				LED = (LED << 1);
			}
			else
			{
				LED = 0x01;
				// With LED_On()
				for (int i = 0; i < 8; ++i)
				{
					LED_Off(0x01 << i);
				}
			}
		}
		old = buttonVal;	
		
	}
	LED_Display(LED0);
	
	
}

void part41()
{
	// ADC 10 bit
	//adc_configure(&AVR32_ADC);
	adc_enable(&AVR32_ADC, ADC_LIGHT_CHANNEL);
	
	while(1){
		adc_start(&AVR32_ADC);
		int read = adc_get_value(&AVR32_ADC, ADC_LIGHT_CHANNEL);
		if(read < 100){ //max 1023
			LED_Display(0xFF);
		}
		else if(read < 200){ //max 1023
			LED_Display(0x7F);
		}
		else if(read < 300){ //max 1023
			LED_Display(0x3F);
		}
		else if(read < 400){ //max 1023
			LED_Display(0x1F);
		}
		else if(read < 500){ //max 1023
			LED_Display(0x0F);
		}
		else if(read < 600){ //max 1023
			LED_Display(0x07);
		}
		else if(read < 700){ //max 1023
			LED_Display(0x03);
		}
		else if(read < 800){ //max 1023
			LED_Display(0x01);
		}
		else{
			LED_Display(0x00);
		}
	}
}

int PWM_prog(unsigned long freq, unsigned long dutycycle) {
	
	//7 channels for pwm exist
	/* 0<dutycycle<100 [percent] */
	unsigned int channel_id = 3;
	unsigned int mck = 115200;
	unsigned long period, duty_time;
	
	avr32_pwm_channel_t pwm_channel = { .ccnt = 0 }; // One	channel config.

	gpio_enable_module_pin(EXAMPLE_PWM_PIN, EXAMPLE_PWM_FUNCTION);
	pwm_channel.CMR.cpre = AVR32_PWM_CPRE_MCK_DIV_256; //	Channel prescaler.

	// Calculate period and duty cycle
	period = (mck/256)/freq;
	duty_time = period*dutycycle/100;
	
	// Add to register
	pwm_channel.cdty = duty_time; // Channel duty cycle, should be < CPRD.
	pwm_channel.cprd = period; // Channel period.

	pwm_channel_init(channel_id, &pwm_channel); // Set channel	configuration to channel 3.
	pwm_start_channels(1 << channel_id); // Start channel 3.
	while(1){
	}
	return 0;
}


int main (void)
{
	board_init();
	//part11();
	//part12();
	//part13();
	//part14();
	//part15();
	//part16();
	//part21();
	//part22();
	//part23();
	//part25();
	//part31();
	part41();
	//PWM_prog(1, 70);
}
