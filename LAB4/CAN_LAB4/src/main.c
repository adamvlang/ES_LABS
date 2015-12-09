/********************************************************
Name : main.c

CAN example

**********************************************************/

#include <asf.h>
#include "can.h"

#define CAN_1000kbps 1
#define CAN_500kbps 5
#define CAN_250kbps 7
#define CAN_125kbps 10

UINT8 msg[8], mSize;
UINT16 light, temper;
UINT16 lightPro, temperPro, potPro;
UINT16 divid = 1023;

UINT32 Ident;

int main(void) {
	
	//spidatareadpointer=&spidataread;
	pm_switch_to_osc0(&AVR32_PM, FOSC0, OSC0_STARTUP);
	
	// Configures the MCP2515 SPI communication.
	config_SPI_SPARE();

	// Enables receive interrupts.
	Disable_global_interrupt();
	INTC_init_interrupts();
	Enable_global_interrupt();
	
	// Delay to let the Oscillator get started
	delay_init( FOSC0 );
	
	// Initializes the display
	config_dpi204();
	dip204_init(100,1);
	dip204_clear_display();
	
	UINT16 Mask = 0xF000; 
	UINT16 flt = 0x1000;
	UINT16 Flt[] = {flt,flt,flt,flt,flt,flt};
	InitializeCANExtended(0, CAN_250kbps, Mask, Flt);
	


	while(1){
		
		//Clear memory contents
		ClearMessages(msg);
		//Read any message available
		if(CANRxReady(0)){
			if( CANGetMsg(0, &Ident, msg, &mSize )) // Gets message and returns //TRUE if message received.
			{	
					// Read light, 2 MSB msg[2], 8 LSB msg[3]
					light = (((UINT16)msg[2]) << 8 ) | msg[3];
					
					// Read temp, 2 MSB msg[0], 8 LSB msg[1]
					temper = ((UINT16)msg[0] << 8) | msg[1];
					
					//Calculate percentages
					lightPro = ((100*light)/divid);
					temperPro = (100*temper)/divid;
					potPro = (100*msg[5])/255;
					
					
					dip204_clear_display();
					dip204_set_cursor_position(1, 1);
					dip204_printf_string("Rx ID:");
					dip204_set_cursor_position(1, 2);
					dip204_printf_string("Temp:");
					dip204_set_cursor_position(1, 3);
					dip204_printf_string("Light:");
					dip204_set_cursor_position(1, 4);
					dip204_printf_string("Pot:");
					dip204_set_cursor_position(12, 2);
					dip204_printf_string("Abs:");
					dip204_set_cursor_position(12, 3);
					dip204_printf_string("Abs:");
					dip204_set_cursor_position(12, 4);
					dip204_printf_string("Abs:");
					dip204_set_cursor_position(8, 1);
					dip204_printf_string("%x", Ident);
					dip204_set_cursor_position(8, 2);
					dip204_printf_string("%d", temperPro);
					dip204_set_cursor_position(8, 3);
					dip204_printf_string("%d", lightPro);
					dip204_set_cursor_position(8, 4);
					dip204_printf_string("%d", potPro);
					dip204_set_cursor_position(17, 2);
					dip204_printf_string("%d", temper);
					dip204_set_cursor_position(17, 3);
					dip204_printf_string("%d", light);
					dip204_set_cursor_position(17, 4);
					dip204_printf_string("%d", msg[5]);
					dip204_hide_cursor();
			}
			
		}

	}
	return 0;
}