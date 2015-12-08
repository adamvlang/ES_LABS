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

UINT32 Ident;
UINT8 msg[8], mSize;
UINT16 light;

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
	UINT16 flt = 0x2000;
	UINT16 Flt[] = {flt,flt,flt,flt,flt,flt};
	InitializeCANExtended(0, CAN_250kbps, Mask, Flt);
	
	

	while(1){
		
		//Clear memory contents
		ClearMessages(msg);
		//Read any message available
		if(CANRxReady(0)){
			if( CANGetMsg(0, &Ident, msg, &mSize )) // Gets message and returns //TRUE if message received.
			{	
					// Read light, 2 most sig byte 2, 8 least sig byte 3
					light = (((UINT16)msg[2]) << 8 ) | msg[3];
					// Read temp
					
					dip204_clear_display();
					dip204_set_cursor_position(1, 1);
					dip204_printf_string("Rx ID:");
					dip204_set_cursor_position(1, 2);
					dip204_printf_string("Temp:");
					dip204_set_cursor_position(1, 3);
					dip204_printf_string("Light:");
					dip204_set_cursor_position(1, 4);
					dip204_printf_string("Pot:");
					dip204_set_cursor_position(13, 2);
					dip204_printf_string("Abs:");
					dip204_set_cursor_position(13, 3);
					dip204_printf_string("Abs:");
					dip204_set_cursor_position(13, 4);
					dip204_printf_string("Abs:");
					dip204_set_cursor_position(9, 1);
					dip204_printf_string("%x", Ident);
					dip204_set_cursor_position(9, 2);
					dip204_printf_string("%d", msg[1]);
					dip204_set_cursor_position(9, 3);
					dip204_printf_string("%d", light);
					dip204_set_cursor_position(9, 4);
					dip204_printf_string("%d", msg[5]);
					dip204_set_cursor_position(18, 2);
					dip204_printf_string("%x", msg[2]);
					dip204_set_cursor_position(18, 3);
					dip204_printf_string("%x", msg[3]);
					dip204_set_cursor_position(18, 4);
					dip204_printf_string("%d", msg[5]);
					dip204_hide_cursor();
			}
			
		}

	}
	return 0;
}