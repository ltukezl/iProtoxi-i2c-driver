/*
 * CFile1.c
 *
 * Created: 3.4.2014 13:49:45
 *  Author: Tuomo
 */ 

#include <avr\io.h>
#include "Bluetooth.h"
#include <stdlib.h>

char merkit[200];
int data;
 
 
void I2C_init()
{
	TWBR |= (1<<TWBR4); //init scl freq
}

void Send_start_bit()
{		
	
	//Send start condition and and wait for twint to go up
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); //start condition
	while(!(TWCR & (1<<TWINT))); // wait for twint to go up

	if(((TWSR & 0xf8) != 0x08) == ((TWSR & 0xf8) != 0x10)) //check for errors
	{
		USART_Transmit("start error or repeated start error   \r\n");
		itoa(TWSR,merkit,10);
		USART_Transmit(merkit); //send status register if error is found
	}	
}

void Send_data_bit(int target)
{
	//send slave address or target register addresses or data bits
	TWDR = target; //put data to register

	TWCR = (1<<TWINT) | (1<<TWEN); // send it
	while(!(TWCR & (1<<TWINT))); // wait for twint to go up
	
	if((((TWSR & 0xf8) != 0x18) == ((TWSR & 0xf8) != 0x28)) == ((TWSR & 0xf8) != 0x40))
	{ //check for errors
		USART_Transmit("Error while transmitting SLA+W, Target register or SLA+R    \r\n");
		itoa(TWSR,merkit,10);
		USART_Transmit(merkit); //send status register if error is found
	}	
}

int receive_data()
{
	TWCR = (1<<TWINT) | (1<<TWEN); // send it
	while(!(TWCR & (1<<TWINT))); // wait for twint to go up
	return TWDR;
}

void send_stop_bit()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); // set stop bit
}


int I2C_read_register(int SLA_W, int SLA_R, int TRG_REG)
{
	
	Send_start_bit();	
	Send_data_bit(SLA_W);
	Send_data_bit(TRG_REG);
	Send_start_bit();	
	Send_data_bit(SLA_R);
	data = receive_data();
	send_stop_bit();
	
	return data;
}

void I2C_write_to_register(int SLA_W, int TRG_REG, int MSG)
{
	Send_start_bit();
	Send_data_bit(SLA_W);
	Send_data_bit(TRG_REG);
	Send_data_bit(MSG);
	send_stop_bit();	
}