#include "../I2cPort/I2cPort.h"
#include "LSM6DS3.h"

LSM6DS3::LSM6DS3()
{
	this->i2c = new I2cPort(Device_add,2);
	write(0x01,1);
	write(0x15,0);
}

LSM6DS3::~LSM6DS3()
{
	delete i2c;
}

void LSM6DS3::write(int add,int val)
{
	i2c->openConnection();
	i2c->writeByte(add,val);
	i2c->closeConnection();
}

uint8_t LSM6DS3::read(int add)
{
	i2c->openConnection();
	uint8_t buf = i2c->readByte(add);
	i2c->closeConnection();
	return buf;
}

bool LSM6DS3::check()
{
	int r = read(Device_check);
	if(r==105)
	return true;
	else
	return false;
}

//ACCELEROMETER SETTINGS
//OUTPUT DATA RATE LEVELS ACCELEROMETER
//XL_ODR_LEVEL0		POWER DOWN
//XL_ODR_LEVEL1		13Hz
//XL_ODR_LEVEL2		26Hz
//XL_ODR_LEVEL3		52Hz
//XL_ODR_LEVEL4		104Hz
//XL_ODR_LEVEL5		208Hz
//XL_ODR_LEVEL6		416Hz
//XL_ODR_LEVEL7		833Hz
//XL_ODR_LEVEL8		1.66kHz
//XL_ODR_LEVEL9		3.33kHz
//XL_ODR_LEVEL10	6.66kHz

//FULL SCALE DETECTION LEVELS ACCELEROMETER
//FS_xl_LEVEL0		+/- 2g
//FS_xl_LEVEL1		+/- 4g
//FS_xl_LEVEL2		+/- 8g
//FS_xl_LEVEL3		+/- 16g

//ANTI-ALIASING  FILTER BANDWIDTH SELECTION
//AA_LEVEL0		50Hz
//AA_LEVEL1		100Hz
//AA_LEVEL2		200Hz
//AA_LEVEL3		400Hz

//SCALING VALUES ACCELEROMETER
// +/- 2g		0.061	mg/LSB
// +/- 4g		0.122	mg/LSB
// +/- 8g		0.244	mg/LSB
// +/- 16g		0.488	mg/LSB

void LSM6DS3::xl_set(int odr = 10 ,int fs = 0,int aa = 0)
{
	switch(fs)
	{
		case 0 : xlscale = 0.061 ;
			 break;
		case 1 : xlscale = 0.488 ;
			 break;
		case 2 : xlscale = 0.122 ;
			 break;
		case 3 : xlscale = 0.244 ;
			 break;
		default: xlscale = 0.061 ;
	}
	int res = ((odr<<4)|((fs<<2)|aa));
	write(CTRL1_XL,res);
}

//GYROSCOPE SETTINGS
//OUTPUT DATA RATE GYROSCOPE LEVELS
//G_ODR_LEVEL0		POWER DOWN
//G_ODR_LEVEL1		13Hz
//G_ODR_LEVEL2		26Hz
//G_ODR_LEVEL3		52Hz
//G_ODR_LEVEL4		104Hz
//G_ODR_LEVEL5		208Hz
//G_ODR_LEVEL6		416Hz
//G_ODR_LEVEL7		833Hz
//G_ODR_LEVEL8		1.66kHz

//FULL SCALE SELECTION GYROSCOPE
//FS_G_LEVEL0		245dps
//FS_G_LEVEL1		500dps
//FS_G_LEVEL2		1000dps
//FS_G_LEVEL3		2000dps

//FS at 125dps also possible support not provided in this library

//SCALING VALUES GYROSCOPE
//245 dps		8.75	mdps/LSB
//500dps		17.50   mdps/LSB
//1000dps		35	mdps/LSB
//2000dps		70 	mdps/LSB

void LSM6DS3::g_set(int odr = 0,int fs = 0)
{
	switch(fs)
	{
		case 0 : gscale = 8.75 ;
			 break;
		case 1 : gscale = 17.50 ;
			 break;
		case 2 : gscale = 35 ;
		 	 break;
		case 3 : gscale = 70 ;
			 break;
		default: gscale = 8.75 ;
	}
	int res = ((odr<<4)|(fs<<2));
	write(0x11,res);
}

raw LSM6DS3::raw_xl()
{
	raw temp_raw;
	xl_x0 = read(0x28);
	xl_x1 = read(0x29);
	temp_raw.xaxis = (int16_t)(xl_x0 | (xl_x1<<8));
	xl_y0 = read(0x2A);
	xl_y1 = read(0x2B);
	temp_raw.yaxis = (int16_t)(xl_y0 | (xl_y1<<8));
	xl_z0 = read(0x2C);
	xl_z1 = read(0x2D);
	temp_raw.zaxis = (int16_t)(xl_z0 | (xl_z1<<8));
	return temp_raw;
}

raw LSM6DS3::raw_g()
{
	raw temp_raw ;
	g_x0 = read(0x22);
	g_x1 = read(0x23);
	temp_raw.xaxis = (int16_t)(g_x0 | (g_x1<<8));
	g_y0 = read(0x24);
	g_y1 = read(0x25);
	temp_raw.yaxis = (int16_t)(g_y0 | (g_y1<<8));
	g_z0 = read(0x26);
	g_z1 = read(0x27);
	temp_raw.zaxis = (int16_t)(g_z0 | (g_z1<<8));
	return temp_raw;
}

raw LSM6DS3::scaled_g()
{
	raw temp_scale ;
	temp_scale = raw_g();
	temp_scale.xaxis = temp_scale.xaxis*xlscale*0.001 ;
	temp_scale.yaxis = temp_scale.yaxis*xlscale*0.001 ;
	temp_scale.zaxis = temp_scale.zaxis*xlscale*0.001 ;
	return temp_scale;
}

raw LSM6DS3::scaled_xl()
{
	raw temp_scale ;
	temp_scale = raw_xl();
	temp_scale.xaxis = temp_scale.xaxis*xlscale*0.001 ;
	temp_scale.yaxis = temp_scale.yaxis*xlscale*0.001 ;
	temp_scale.zaxis = temp_scale.zaxis*xlscale*0.001 ;
	return temp_scale;
}

