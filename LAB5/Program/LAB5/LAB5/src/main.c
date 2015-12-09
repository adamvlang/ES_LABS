#include <asf.h>

static void software_delay(void){
	volatile int i;
	for (i=0; i<1000000; i++);
}

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	int state = 0;

	// Parameters, change these for different clock freqs
	// 12MHz -> 3 0 1 1
	
	int PLLMUL = 3; 
	int PLLDIV = 0;
	int PLLDIV2 = 1;
	int CPUSEL = 1;

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
	
	// Blink led loop
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
