/*
 * CFile1.c
 *
 * Created: 3.4.2014 13:03:50
 *  Author: Tuomo
 */ 

#include <avr/io.h>
#include "Bluetooth.h"
#include "i2c.h"
#include <stdlib.h>

char merkit[200];

int main()
{
	BT_init();
	I2C_init();
	I2C_write_to_register(0x3c, 0x02, 0x00); //set continus reading mode
	USART_Transmit("ready\r\n");
	while(1)
	{
		switch(USART_Receive())
		{
			case '1':
				USART_Transmit("X coord\r\n");
				itoa(I2C_read_register(0x3C, 0x3D, 0x04),merkit,10); // read x axis low bits and read, but don't transmit every other register so you can get new data
				USART_Transmit(merkit);
				USART_Transmit("\r\n");
				I2C_read_register(0x3C, 0x3D, 0x03);
				//(USART_Transmit("Y coord\r\n");
				I2C_read_register(0x3C, 0x3D, 0x07);
				I2C_read_register(0x3C, 0x3D, 0x08);
				//USART_Transmit("Z coord\r\n");
				I2C_read_register(0x3C, 0x3D, 0x05);
				I2C_read_register(0x3C, 0x3D, 0x06);
				break;		
				
			case '2':
				break;
		}

	}

	return 0;
}