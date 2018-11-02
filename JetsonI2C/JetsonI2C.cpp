#include <stdlib.h>
#include <iostream>

int main()
{	
	int file;
	int adapter_nr = 0;
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
	
	__u8 reg = 0x16;
	__s32 res;
	char buf[10];
	while(true)
	{
		res = i2c_smbus_read_word_data(file, reg);
		if (res < 0) 
		{
			std::cout << "read failed" std::endl;
		} 
		else
		{
			std::cout << buf << std::endl;
		}
	}
	return 0;
}