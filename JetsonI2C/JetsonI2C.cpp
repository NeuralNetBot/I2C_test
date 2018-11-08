#include <stdlib.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <sstream>

const int COMMAND_REGISTER_BIT = 0x80;
const int MULTI_BYTE_BIT    = 0x20;

const int ENABLE_REGISTER   = 0x00;
const int ATIME_REGISTER    = 0x01;
const int PPULSE_REGISTER   = 0x0E;

const int ID_REGISTER       = 0x12;
const int CDATA_REGISTER    = 0x14;
const int RDATA_REGISTER    = 0x16;
const int GDATA_REGISTER    = 0x18;
const int BDATA_REGISTER    = 0x1A;
const int PDATA_REGISTER    = 0x1C;

int read_word_register(int file, int address)
{
	uint8_t buf;
	s32 retval = i2c_smbus_read_byte_data(file, COMMAND_REGISTER_BIT | MULTI_BYTE_BIT | address);
	uint16_t value = ((uint16_t)buf[1] << 8) | (uint16_t)buf[0];
	
	if(retval < 0)
	{
		return retval;
	}
	else 
	{
		return (int)retval;
	} 
}

int main()
{	
	int file;
	int adapter_nr = 1;
	char filename[20];

	snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
	file = open(filename, O_RDWR);
	if (file < 0)
	{
		std::cout << "open failed" std::endl;
		exit(1);
	}

	int addr = 0x39;

	if (ioctl(file, I2C_SLAVE, addr) < 0)
	{
		std::cout << "init failed" std::endl;
		exit(1);
	}
	i2c_smbus_write_byte(COMMAND_REGISTER_BIT | 0x00, 0b00000011); //power on, color sensor on

	__s32 res;
	while(true)
	{
		res = read_word_register(file, RDATA_REGISTER);
		if (res < 0) 
		{
			std::cout << "read failed" std::endl;
		} 
		else
		{
			std::cout << res << std::endl;
		}
	}
	return 0;
}