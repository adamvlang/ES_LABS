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
#define Switch1 88
#define RX 85

UINT8 msg[8], mSize;

UINT16 ids;

UINT16 ownId = 0x1202;

UINT32 Ident;

volatile int warmWarn = 0;
volatile int emergency = 0;
volatile int emergAck = 0;
volatile int faulty = 0;
/******************************/
volatile int state = 0;
/******************************/
//Initiate struct
struct frame
{
	UINT16 ID;
	UINT8 mssg[8];
}nFrame[15];


struct frame youngFrame[15];
struct frame emptyStruct[15];


void readADC(void)
{
	// Reads values of pot, light and temperature
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
	
	//Adding measurements to struct
	youngFrame[0x00F & ownId].mssg[0] = tempMSB;
	youngFrame[0x00F & ownId].mssg[1] = tempLSB;
	youngFrame[0x00F & ownId].mssg[2] = lightMSB;
	youngFrame[0x00F & ownId].mssg[3] = lightLSB;
	youngFrame[0x00F & ownId].mssg[4] = 0;
	youngFrame[0x00F & ownId].mssg[5] = 0;
	youngFrame[0x00F & ownId].mssg[6] = 0;
	youngFrame[0x00F & ownId].mssg[7] = 0;
}

void ownADC(void)
{
	// Reads ADC on own board and displays values
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
	// Count nodes by iterating over addresses 
	UINT8 nodes;

	// 15 addresses available
	for(int j = 0; j < 15 ; ++j)
	{
		ids = nFrame[j].ID;
		//If there was a node found at the j'th bit 1 is added to l
		if(ids != 0)
		{
			++nodes;
		}
	}
	return nodes;
	
}

// Prototype
void blink(void);

__attribute__((__interrupt__)) static void interrupt(void)
{	
	// Send message every second on rtc interrupt
	blink();
	for(int i = 0; i < 15; ++i)
	{
		nFrame[i] = youngFrame[i];
		youngFrame[i] = emptyStruct[i];
	}
	
	//Send message
	if(CANTxReady(0))
	{
		CANSendMsg(0, ownId, nFrame[0x00F & ownId].mssg, 8, 0);
	}
	
	if (warmWarn == 1){
		static int led_state = 0;
		if (led_state == 0) {
			LED_On(16);
			led_state = 1;
		}
		else {
			LED_Off(16);
			led_state = 0;
		}
	}
	if (emergency == 1){
		static int led_state = 0;
		if (led_state == 0) {
			LED_On(16);
			LED_On(64);
			led_state = 1;
		}
		else {
			LED_Off(16);
			LED_Off(64);
			led_state = 0;
		}
	}
	if (faulty == 1)
	{
		static int led_state = 0;
		if (led_state == 0) {
			LED_On(4);
			led_state = 1;
		}
		else {
			LED_Off(4);
			led_state = 0;
		}
	}
	
	rtc_clear_interrupt(&AVR32_RTC);
}

__attribute__((__interrupt__)) void but_interrupt(void)
{

	if (emergency == 1)
	{
		//AVR32_GPIO.port[2].ovrc = 1 << 24;
		emergAck = 1;
	}
	gpio_clear_pin_interrupt_flag(Switch1);
	
}


__attribute__((__interrupt__)) void RX_interrupt(void)
{

	LED_On(LED2);
	gpio_clear_pin_interrupt_flag(RX);
}

void average(void)
{
	int x=0;
	UINT16 night = 0;
	UINT16 warm = 0;	
	UINT16 cold = 0;
	UINT16 lighttot= 0; 
	UINT16 tempertot = 0;
	UINT16 actNodes = nodeCount();
	UINT16 warningNode = 0;
	
	//Calculating total light and temp received
	for(int i = 0; i < 15; ++i)
	{
		lighttot += ((((UINT16)nFrame[i].mssg[2]) << 8 ) | nFrame[i].mssg[3]);
		tempertot += ((((UINT16)nFrame[i].mssg[0]) << 8 ) | nFrame[i].mssg[1]);
	}
	
	for(int i = 0; i < 15; ++i)
	{
		if(((((UINT16)nFrame[i].mssg[2]) << 8 ) | nFrame[i].mssg[3]) < ((lighttot/actNodes)/2) && ((((UINT16)nFrame[i].mssg[2]) << 8 ) | nFrame[i].mssg[3]) != 0)
		{
			++night;
		}
		if(((((UINT16)nFrame[i].mssg[0]) << 8 ) | nFrame[i].mssg[1]) < ((tempertot/actNodes)*0.75) && ((((UINT16)nFrame[i].mssg[0]) << 8 ) | nFrame[i].mssg[1]) != 0)
		{
			++warm;
		}
		if(((((UINT16)nFrame[i].mssg[0]) << 8 ) | nFrame[i].mssg[1]) > ((tempertot/actNodes)*1.10) && ((((UINT16)nFrame[i].mssg[0]) << 8 ) | nFrame[i].mssg[1]) != 0)
		{
			++cold;
			nFrame[i].mssg[0] = 0;
			nFrame[i].mssg[1] = 0;
			nFrame[i].mssg[2] = 0;
			nFrame[i].mssg[3] = 0;
			--actNodes;
			faulty = 1;
		}
	}
	lighttot = 0;
	tempertot = 0;
	//Calculating total light and temp received
	for(int i = 0; i < 15; ++i)
	{
		lighttot += ((((UINT16)nFrame[i].mssg[2]) << 8 ) | nFrame[i].mssg[3]);
		tempertot += ((((UINT16)nFrame[i].mssg[0]) << 8 ) | nFrame[i].mssg[1]);
	}

		//Printing values to display
		dip204_set_cursor_position(15, 3);
		dip204_printf_string("%d",  (tempertot/actNodes));
		dip204_set_cursor_position(15, 2);
		dip204_printf_string("%d",  (lighttot/actNodes));
		dip204_set_cursor_position(4, 4);
		dip204_printf_string("%d",  night);

		if (night == 0 && cold == 0)
		{
			LED_Display(1);
			warmWarn = 0;
			faulty = 0;
		}

		else if(warm == 1)
		{
			warmWarn = 1;
			LED_Off(1);
			
		}
		else if(warm == 2 && emergAck == 0)
		{
			emergency = 1;
			LED_Off(1);
		}
		
		if (emergency == 1)
		{
		
			if(emergAck == 1)
			{
				if(night < 1)
				{
					emergency = 0;
					emergAck = 0;
				}
			}
			
		}
}


void printLCD(void)
{
	dip204_set_cursor_position(1, 1);
	dip204_printf_string("Active nodes:");
	dip204_set_cursor_position(1, 3);
	dip204_printf_string("O T:");
	dip204_set_cursor_position(1, 4);
	dip204_printf_string("N:");
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
	for(int i = 0; i < 15; ++i)
	{
		emptyStruct[i].ID = 0;
	}

	//Enable ADC channels
	adc_enable( &AVR32_ADC, ADC_TEMPERATURE_CHANNEL );
	adc_enable( &AVR32_ADC, ADC_LIGHT_CHANNEL );

	//spidatareadpointer=&spidataread;
	pm_switch_to_osc0(&AVR32_PM, FOSC0, OSC0_STARTUP);
	
	// Configures the MCP2515 SPI  communication.
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
	
	// Button interrupt
	INTC_register_interrupt(&but_interrupt, (AVR32_GPIO_IRQ_0+Switch1/8), AVR32_INTC_INT0);
	gpio_enable_pin_glitch_filter(Switch1);
	gpio_enable_pin_interrupt(Switch1, GPIO_FALLING_EDGE);
	
	// Receive interrupt
	INTC_register_interrupt(&RX_interrupt, (AVR32_GPIO_IRQ_0+RX/8), AVR32_INTC_INT0);
	gpio_enable_pin_glitch_filter(RX);
	gpio_enable_pin_interrupt(RX, GPIO_FALLING_EDGE);
	
	Enable_global_interrupt();
	// Delay to let the Oscillator get started
	delay_init(FOSC0);
	
	// Initializes the display
	config_dpi204();
	dip204_init(100,1);
	dip204_clear_display();
}


void blink(void){
	if (state == 0){
		LED_On(LED3);
		state = 1;
		}
	else if (state == 1){
		LED_Off(LED3);
		state = 0;
		}	
}


int main(void) 
{
	initBoard();

	//Filtering incoming messages
	UINT16 Mask = 0xFFF0; 
	UINT16 flt = 0x1200;
	UINT16 Flt[] = {flt,flt,flt,flt,flt,flt};
		
	InitializeCANExtended(0, CAN_250kbps, Mask, Flt);

	while(1)
	{

		adc_start(&AVR32_ADC);

		//Clear memory contents
		ClearMessages(msg);
		
		//If the dongle is connected to a bus
		if(CANRxReady(0) || CANTxReady(0))
		{
			// Setting own id.
			nFrame[0x00F & ownId].ID = ownId;

			//Write to display and read ADC
			dip204_clear_display();
			printLCD();
			ownADC();
			average();
			dip204_hide_cursor();

			//Read any message available
			if(CANRxReady(0))
			{
				if( CANGetMsg(0, &Ident, msg, &mSize )) // Gets message and returns //TRUE if message received.
				{					
					//Adding received ID to struct
					youngFrame[0x00F & Ident].ID = Ident;
					
					//Adding frame to the struct
					for(int i = 0; i < 8; ++i)
					{
						//Adding received message to struct
						youngFrame[0x00F & Ident].mssg[i] = msg[i];
					}
				}
				
			}
			delay_ms(1000);

		}
		// If the dongle isn't connected
		else
		{
			//Write to display and read ADC
			dip204_clear_display();
			printLCD();
			ownADC();
			dip204_hide_cursor();
			for(int j = 0; j < 16 ; ++j)
			{
				nFrame[j].ID = 0;
			}
			
			delay_ms(1000);
		}
		
	}

	return 0;
}
	
