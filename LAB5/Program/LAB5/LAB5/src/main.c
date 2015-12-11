#include <asf.h>

int config_dip204(void) {
	static const gpio_map_t DIP204_SPI_GPIO_MAP =
	{
		{DIP204_SPI_SCK_PIN, DIP204_SPI_SCK_FUNCTION }, // SPI Clock.
		{DIP204_SPI_MISO_PIN, DIP204_SPI_MISO_FUNCTION}, // MISO.
		{DIP204_SPI_MOSI_PIN, DIP204_SPI_MOSI_FUNCTION}, // MOSI.
		{DIP204_SPI_NPCS_PIN, DIP204_SPI_NPCS_FUNCTION} // Chip Select NPCS.
	};
	
	spi_options_t spiOptions =
	{
		.reg = DIP204_SPI_NPCS,
		.baudrate = 1000000,
		.bits = 8,
		.spck_delay = 0,
		.trans_delay = 0,
		.stay_act = 1,
		.spi_mode = 0,
		.modfdis = 1
	};
	
	gpio_enable_module(DIP204_SPI_GPIO_MAP,
	sizeof(DIP204_SPI_GPIO_MAP) / sizeof(DIP204_SPI_GPIO_MAP[0]));
	spi_initMaster(DIP204_SPI, &spiOptions);
	spi_selectionMode(DIP204_SPI, 0, 0, 0);
	spi_enable(DIP204_SPI);
	spi_setupChipReg(DIP204_SPI, &spiOptions, FOSC0);
	delay_init( FOSC0 );
	dip204_init(100, 1);
}

static void software_delay(void){
	volatile int i;
	for (i=0; i<1000000; i++);
}

void blink_loop(void){
	// Blink led loop
	int state = 0;
	while(1){
		if (state == 0) {
			LED_Display(LED0);
			state = 1;
		}
		else {
			LED_Display(LED1);
			state = 0;
		}
		software_delay();
		
	}
}


void part1 (void)
{

	// Parameters, change these for different clock freqs
	// 2 MHz -> 3 0 1 3
	// 12MHz -> 3 0 1 1
	// 33 MHz -> 10 1 1 0
	// 48 MHz -> 15 1 1 0
	// 66 MHz -> 10 1 0 0
	
	int PLLMUL = 15;
	int PLLDIV = 1;
	int PLLDIV2 = 1;
	int CPUSEL = 0;

	// Setup clock speed
	pm_switch_to_osc0(&AVR32_PM, FOSC0, OSC0_STARTUP);
	pm_pll_setup(&AVR32_PM,				0, //PLL
										PLLMUL, //MUL
										PLLDIV, //DIV
										0, //OSC
										16 ); // LOCKCOUNT
	pm_pll_set_option(&AVR32_PM,		0, //PLL
										1, // PLL_FREQ
										PLLDIV2, // PLL_DIV2
										0);// PLL_WBWDISABLE
	pm_pll_enable(&AVR32_PM, 0);
	pm_wait_for_pll0_locked(&AVR32_PM);
	pm_cksel(&AVR32_PM,
					1,	//pbadiv
					0, //pbasel
					1, //pbbdiv
					0, //pbbsel
					1,	//hsbdiv
					CPUSEL); //hsbsel (CPUSEL)	
	pm_switch_to_clock(&AVR32_PM, AVR32_PM_MCCTRL_MCSEL_PLL0);
	
	blink_loop();
	
}

void set_cpu_freq();

void part2(int cpu_freq, int bus_freq){
	// Args: CPU, BUS
	set_cpu_freq(cpu_freq, bus_freq);
	/*
	dip204_clear_display();
	dip204_set_cursor_position(1,1);
	dip204_printf_string("CPU: %i Hz", cpu_freq);
	dip204_set_cursor_position(1,2);
	dip204_printf_string("PBA: %i Hz", bus_freq);
	dip204_hide_cursor();
	*/
	blink_loop();
}

void set_cpu_freq(int cpu_freq, int bus_freq){
	// Define struct
	// Input parameters in MHz
	pm_freq_param_t freq_parameters;
	freq_parameters.cpu_f = cpu_freq*1000000;
	freq_parameters.pba_f = bus_freq*1000000;
	freq_parameters.osc0_f = FOSC0;
	freq_parameters.osc0_startup = OSC0_STARTUP;
	// Set frequency
	pm_configure_clocks(&freq_parameters);
}


void set_interrupts(unsigned int ticks_to_interrupt, unsigned int rtcsel);
void rtc_irq();
void but_interrupt();

void part3(int cpu_freq, int bus_freq){
	set_cpu_freq(cpu_freq, bus_freq);
	set_interrupts(0, 14);
	/*
	dip204_clear_display();
	dip204_set_cursor_position(1,1);
	dip204_printf_string("CPU: %i Hz", cpu_freq);
	dip204_set_cursor_position(1,2);
	dip204_printf_string("PBA: %i Hz", bus_freq);
	dip204_hide_cursor();
	*/
	while(1){}
}

void set_interrupts(unsigned int ticks_to_interrupt, unsigned int rtcsel){
	
	Disable_global_interrupt();
	INTC_init_interrupts();

	// Register the RTC interrupt handler to the interrupt controller.
	INTC_register_interrupt(&rtc_irq, AVR32_RTC_IRQ, AVR32_INTC_INT0);
	rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, rtcsel);
	// Set top value to 0 to generate an interrupt every seconds */
	rtc_set_top_value(&AVR32_RTC, ticks_to_interrupt);
	// Enable the interrupts
	rtc_enable_interrupt(&AVR32_RTC);
	// Enable the RTC
	rtc_enable(&AVR32_RTC);
	
	// Button interrupt
	INTC_register_interrupt(&but_interrupt, (AVR32_GPIO_IRQ_0+88/8), AVR32_INTC_INT0);
	gpio_enable_pin_glitch_filter(88);
	gpio_enable_pin_interrupt(88, GPIO_FALLING_EDGE);
	
	Enable_global_interrupt();
}


__attribute__((__interrupt__))

void rtc_irq(void){
	static int led_state = 0;
	
	if (led_state == 0) {
		LED_On(LED0);
		LED_Off(LED1);
		led_state = 1;
	}
	else {
		LED_On(LED1);
		LED_Off(LED0);
		led_state = 0;
	}
	rtc_clear_interrupt(&AVR32_RTC);
}

volatile int vol_state = 0;

__attribute__((__interrupt__))

void but_interrupt(void){
	if (vol_state == 0)
	{
		LED_On(LED2);
		vol_state = 1;
	}
	else if (vol_state == 1)
	{
		LED_Off(LED2);
		vol_state = 0;
	}
	
	gpio_clear_pin_interrupt_flag(88);
}

void part4(void){
	set_interrupts(0, 14);
	while(1){
	SLEEP(AVR32_PM_SMODE_IDLE);	
	}
}

int main(void) {
	board_init();
	//config_dip204();
	
	// Manually define clock settings
	//part1();
	// Using support functions
	//part2(12,6);
	// Blink leds with interrupt
	//part3(12,6);
	// Use sleep mode
	part4();
	
	return 0;
	
}