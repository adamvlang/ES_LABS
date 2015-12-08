/* Labb 1 Task 1: Light all leds */
#include <asf.h>

void light_all ()
{
	int light[] = { 28, 29, 30, 19, 20, 21, 22};
	for(int i; i<7; ++i)
	{
		AVR32_GPIO.port[1].gpers = 1 <<light[i];
		AVR32_GPIO.port[1].oders = 1 <<light[i];
		AVR32_GPIO.port[1].ovrc = 1 <<light[i];
	}
}


int main ()
{
	board_init();
	light_all();
	
	return 0;

}
