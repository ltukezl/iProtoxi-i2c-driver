/*
 * i2c.h
 *
 * Created: 3.4.2014 13:50:48
 *  Author: Tuomo
 */ 

#ifndef i2c
#define i2c

void I2C_init();
int I2C_read_register(int SLA_W, int SLA_R, int TRG_REG);
void I2C_write_to_register(int SLA_W, int TRG_REG, int MSG);

#endif