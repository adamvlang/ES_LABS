#include "asf.h"

int PWM_prog(void) {
	board_init();
	unsigned int channel_id = 3;
	avr32_pwm_channel_t pwm_channel = { .ccnt = 0 }; // One	channel config.

	gpio_enable_module_pin(EXAMPLE_PWM_PIN,
	EXAMPLE_PWM_FUNCTION);
	pwm_channel.CMR.cpre = AVR32_PWM_CPRE_MCK_DIV_256; //	Channel prescaler.

	pwm_channel.cdty = 1; // Channel duty cycle, should be <	CPRD.

	pwm_channel.cprd = 20; // Channel period.
	// With these settings, the output waveform period will be :
	// (115200/256)/20 == 22.5Hz == (MCK/prescaler)/period, with	MCK == 115200Hz,

	// prescaler == 256, period == 20.
	pwm_channel_init(channel_id, &pwm_channel); // Set channel	configuration to channel 3.
	pwm_start_channels(1 << channel_id); // Start channel 3.
	while(1){
	}
	return 0;
}