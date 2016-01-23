/*
 * led.c
 *
 * Created: 6.3.2014 16:08:33
 *  Author: tuomo
 */ 

#include <avr/io.h>

unsigned char data;

void BT_init()
{
	unsigned int baud_rate = (unsigned long)(16000000/ 16 /115200); //set baudrate = clock / 16 / bauds
	UCSR1B |=  (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1); //Enable interrups on receive and transmit
	UCSR1C = (3<<UCSZ10); //Set 8 bit frame and set stop bit 1
	UBRR1H = (unsigned char)(baud_rate>>8);
	UBRR1L = (unsigned char) baud_rate;

	 
}	

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	/* Get and return received data from buffer */
	return UDR1;
}

void USART_Transmit( char *data )
{
		int i = 0;
		/*set char to buffer until null pointer*/
		while(data[i] != 0x00)
		{
			/* Wait for empty transmit buffer */	
			while ( !( UCSR1A & (1<<UDRE1)) )
			;
			/* Put data into buffer, sends the data */
			UDR1 = data[i];
			i++; // next char
		}
		i = 0; // reset pointer to first char
}