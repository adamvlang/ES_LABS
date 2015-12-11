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

UINT16 ownId = 0x1202;

UINT32 Ident;

struct frame
{
	UINT16 ID;
	UINT8 mssg[8];

}nFrame[15];

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
	
	nFrame[0x00F & ownId].mssg[0] = tempMSB;
	nFrame[0x00F & ownId].mssg[1] = tempLSB;
	nFrame[0x00F & ownId].mssg[2] = lightMSB;
	nFrame[0x00F & ownId].mssg[3] = lightLSB;
	nFrame[0x00F & ownId].mssg[4] = 0;
	nFrame[0x00F & ownId].mssg[5] = 0;
	nFrame[0x00F & ownId].mssg[6] = 0;
	nFrame[0x00F & ownId].mssg[7] = 0;
}

void ownADC(void)
{
	UINT16 light = 0;
	UINT16 temper= 0;
	
	readADC();

	// Read light, 2 MSB msg[2], 8 LSB msg[3]
	light = (((UINT16)nFrame[0x00F & ownId].mssg[2]) << 8 ) | nFrame[0x00F & ownId].mssg[3];
	
	// Read temp, 2 MSB msg[0], 8 LSB msg[1]
	temper = (((UINT16)nFrame[0x00F & ownId].mssg[0]) << 8 ) | nFrame[0x00F & ownId].mssg[1];
	
	dip204_set_cursor_position(6, 2);
	dip204_printf_string("%d", light);
	dip204_set_cursor_position(6, 3);
	dip204_printf_string("%d", temper);

}

UINT8 nodeCount(void)
{
	UINT8 l;
	ids = 0;

	for(int j = 0; j < 16 ; ++j)
	{
		//Adds any new nodes to its corresponding position in nodeCount bit seq.
		ids |= (1 << (nFrame[j].ID & 0x000F));

		UINT16 ids_new = ids;
		//If counts the number of nodes active within ~1000 ms
		ids_new &= ((ids_new >> j) & 0x01);

		//If there was a node found at the j'th bit 1 is added to l
		if(ids_new == 1)
		{
			++l;
		}
	}
	return l;
	
}

__attribute__((__interrupt__)) static void interrupt(void)
{
		
	struct frame nFrame;

	rtc_clear_interrupt(&AVR32_RTC);
}

void average(void)
{
	UINT16 lighttot= 0; 
	UINT16 tempertot = 0;
	UINT16 actNodes = nodeCount();

	for(int i = 0; i < 16; ++i)
	{
		lighttot += ((((UINT16)nFrame[i].mssg[2]) << 8 ) | nFrame[i].mssg[3]);
		tempertot += ((((UINT16)nFrame[i].mssg[0]) << 8 ) | nFrame[i].mssg[1]);
	}
	dip204_set_cursor_position(15, 3);
	dip204_printf_string("%d",  (tempertot/actNodes));
	dip204_set_cursor_position(15, 2);
	dip204_printf_string("%d",  (lighttot/actNodes));
}

void printLCD(void)
{					
	dip204_set_cursor_position(1, 1);
	dip204_printf_string("Active nodes:");
	dip204_set_cursor_position(1, 3);
	dip204_printf_string("O T:");
	dip204_set_cursor_position(10, 3);
	dip204_printf_string("A T:");
	dip204_set_cursor_position(1, 2);
	dip204_printf_string("O L:");
	dip204_set_cursor_position(10, 2);
	dip204_printf_string("A L:");
	dip204_set_cursor_position(15, 1);
	dip204_printf_string("%d", nodeCount());
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

	// Register the RTC interrupt handler to the interrupt controller.
	INTC_register_interrupt(&interrupt, AVR32_RTC_IRQ, AVR32_INTC_INT0);
	rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, 14);
	// Set top value to 0 to generate an interrupt every seconds */
	rtc_set_top_value(&AVR32_RTC, 0);
	// Enable the interrupts
	rtc_enable_interrupt(&AVR32_RTC);
	// Enable the RTC
	rtc_enable(&AVR32_RTC);
	
	// Delay to let the Oscillator get started
	delay_init( FOSC0 );
	
	// Initializes the display
	config_dpi204();
	dip204_init(100,1);
	dip204_clear_display();
}

int main(void) {
	
	initBoard();

	UINT16 Mask = 0xFFF0; 
	UINT16 flt = 0x1200;
	UINT16 Flt[] = {flt,flt,flt,flt,flt,flt};
		
	InitializeCANExtended(0, CAN_250kbps, Mask, Flt);

	while(1){

		adc_start(&AVR32_ADC);

		//Clear memory contents
		ClearMessages(msg);

		//Read any message available
		if(CANRxReady(0)){
			if( CANGetMsg(0, &Ident, msg, &mSize )) // Gets message and returns //TRUE if message received.
			{					
				nFrame[0x00F & Ident].ID = Ident;

				//Adding frame to the struct
				for(int i = 0; i < 8; ++i)
				{
					nFrame[0x00F & Ident].mssg[i] = msg[i];
				}
			}
		}

		if(CANTxReady(0))
		{
			//readADC();
			CANSendMsg(0, ownId, nFrame[0x00F & ownId].mssg, 8, 0);
			delay_ms(1000);
		}
		
		dip204_clear_display();
		printLCD();
		ownADC();
		average();
		nodeCount();
		dip204_hide_cursor();
		
		
	}
	return 0;
}