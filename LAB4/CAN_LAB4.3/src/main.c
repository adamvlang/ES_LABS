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

UINT16 ids;

UINT16 divid = 1023;

UINT32 Ident;

int i;

void readADC(void)
{
	UINT32 readPot, readLight, readTemp;
	UINT16 potMSB, potLSB, lightMSB, lightLSB, tempMSB, tempLSB;

		
	//Reading ADC channels
	readLight = adc_get_value(&AVR32_ADC, ADC_LIGHT_CHANNEL);
	readTemp = adc_get_value(&AVR32_ADC, ADC_TEMPERATURE_CHANNEL);
		
	
	//Setting MSB and LSB for the ADC channels, to be able to send over CAN
	lightMSB = (readLight >> 8) & 0x00000003;
	lightLSB = readLight & 0x000000FF;
				
	tempMSB = (readTemp >> 8) & 0x00000003;
	tempLSB = readTemp & 0x000000FF;
	
	msg[0] = lightMSB;
	msg[1] = lightLSB;
	msg[2] = tempMSB;
	msg[3] = tempLSB;
	msg[4] = 0;
	msg[5] = 0;
	msg[6] = 0;
	msg[7] = 0;

}

void printLCD(void)
{
	UINT16 light, temper;
	UINT16 lightPro, temperPro;
	// Read light, 2 MSB msg[2], 8 LSB msg[3]
	light = (((UINT16)msg[2]) << 8 ) | msg[3];
						
	// Read temp, 2 MSB msg[0], 8 LSB msg[1]
	temper = ((UINT16)msg[0] << 8) | msg[1];
						
	//Calculate percentages
	lightPro = (100*light)/divid;
	temperPro = (100*temper)/divid;
								
	dip204_clear_display();
	dip204_set_cursor_position(1, 1);
	dip204_printf_string("Active nodes:");
	dip204_set_cursor_position(1, 2);
	dip204_printf_string("Temp:");
	dip204_set_cursor_position(1, 3);
	dip204_printf_string("Light:");
	dip204_set_cursor_position(1, 4);
	dip204_printf_string("# msg:");
	dip204_set_cursor_position(12, 2);
	dip204_printf_string("Abs:");
	dip204_set_cursor_position(12, 3);
	dip204_printf_string("Abs:");
	dip204_set_cursor_position(12, 4);
	dip204_printf_string("Abs:");
	dip204_set_cursor_position(8, 2);
	dip204_printf_string("%d", temperPro);
	dip204_set_cursor_position(8, 3);
	dip204_printf_string("%d", lightPro);
	dip204_set_cursor_position(8, 4);
	dip204_printf_string("%d", i);
	dip204_set_cursor_position(17, 2);
	dip204_printf_string("%d", temper);
	dip204_set_cursor_position(17, 3);
	dip204_printf_string("%d", light);
	dip204_set_cursor_position(17, 4);
	dip204_printf_string("%d", msg[5]);
	dip204_hide_cursor();
}
void initBoard(void)
{
	//Enable ADC channels
	adc_enable( &AVR32_ADC, ADC_TEMPERATURE_CHANNEL );
	adc_enable( &AVR32_ADC, ADC_LIGHT_CHANNEL );

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
}

UINT8 nodeCount(UINT16 newId)
{
	UINT8 l;
	//Adds any new nodes to its corresponding position
	ids |= (1 << (newId & 0xF));

	for(int j = 0; j < 16 ; ++j)
	{
		//If counts the number of nodes active within ~1000 ms
		UINT16 ids_new = ((ids >> j) & 0x1);

		//If there was a node found at the j'th bit 1 is added to l
		if(ids_new == 1)
		{
			++l;
		}
	}
	//If the board itself is active on the bus we add 1
	if(CANRxReady(0) || CANTxReady(0))
	{
		++l;
	}
	return l;
}

int main(void) {
	
	initBoard();

	UINT16 Mask = 0xFFF0; 
	UINT16 flt = 0x1200;
	UINT16 Flt[] = {flt,flt,flt,flt,flt,flt};
		
	InitializeCANExtended(0, CAN_250kbps, Mask, Flt);

	UINT8 nodes;

	while(1){
		
		adc_start(&AVR32_ADC);
		ids &= 0x0;
		
		//Clear memory contents
		ClearMessages(msg);
		//Read any message available
		if(CANRxReady(0)){
			if( CANGetMsg(0, &Ident, msg, &mSize )) // Gets message and returns //TRUE if message received.
			{	
				nodes = nodeCount(Ident);			
			}
		}

		if(CANTxReady(0))
		{
			
			readADC();
			CANSendMsg(0, 0x120E, msg, 8, 0);
			delay_ms(1000);
		}

		printLCD();
		dip204_set_cursor_position(15, 1);
		dip204_printf_string("%d", nodes);
	}
	return 0;
}