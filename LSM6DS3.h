#include "../I2cPort/I2cPort.h"
#include "../Extras/RAW.h"

#define FUNC_CFG_ACCESS 0x01 
#define WHO_AM_I	0x0F  //Read and check for 0x69 to certify device
#define	CTRL1_XL	0x10
#define CTRL2_G		0x11
#define CTRL3_C		0x12
#define CTRL9_XL	0x18
#define CTRL10_C	0x19
#define OUTX_L_G	0x22
#define OUTX_H_G	0x23
#define OUTY_L_G	0x24
#define OUTY_H_G	0x25
#define OUTZ_L_G	0x26
#define OUTZ_H_G	0x27
#define OUTX_L_XL	0x28
#define OUTX_H_XL	0x29
#define OUTY_L_XL	0x2A
#define OUTY_H_XL	0x2B
#define OUTZ_L_XL	0x2C
#define OUTZ_H_XL	0x2D
#define Device_add	0x6A
#define Device_check    0x0F

//ACCELEROMETER SETTING VALUES
//ACCELEROMETER OUTPUT DATA RATE SETTING
#define XL_ODR_LEVEL0	0b00000000
#define XL_ODR_LEVEL1	0b00000001
#define XL_ODR_LEVEL2	0b00000010
#define XL_ODR_LEVEL3	0b00000011
#define XL_ODR_LEVEL4	0b00000100
#define XL_ODR_LEVEL5	0b00000101
#define XL_ODR_LEVEL6	0b00000110
#define XL_ODR_LEVEL7	0b00000111
#define XL_ODR_LEVEL8	0b00001000
#define XL_ODR_LEVEL9	0b00001001
#define XL_ODR_LEVEL10	0b00001010

//ACCELEROMETER FULL SCALE SELECTION SETTING
#define FS_xl_LEVEL0	0b00000000
#define FS_xl_LEVEL1	0b00000010
#define FS_xl_LEVEL2	0b00000011
#define FS_xl_LEVEL3	0b00000001

//ANTI ALIASING FILTER SETTING
#define AA_LEVEL0	0b00000011
#define AA_LEVEL1	0b00000010
#define AA_LEVEL2	0b00000001
#define AA_LEVEL3 	0b00000000

//GYROSCOPE SETTING VALUES
//GYROSCOPE OUTPUT DATA RATE SETTING
#define G_ODR_LEVEL0	0b00000000
#define G_ODR_LEVEL1    0b00000001
#define G_ODR_LEVEL2	0b00000010
#define G_ODR_LEVEL3	0b00000011
#define G_ODR_LEVEL4    0b00000100
#define G_ODR_LEVEL5	0b00000101
#define G_ODR_LEVEL6	0b00000110
#define G_ODR_LEVEL7	0b00000111
#define G_ODR_LEVEL8	0b00001000

//GYROSCOPE FULL SCALE SELECTION SETTING
#define FS_G_LEVEL0	0b00000000
#define FS_G_LEVEL1	0b00000001
#define FS_G_LEVEL2	0b00000010
#define FS_G_LEVEL3	0b00000011


class LSM6DS3
{
	public :
	I2cPort  *i2c;

	//Scaling Values
	double gscale;
	double xlscale;

	//ACCEL RAW VALUE VARIABLES
	uint8_t xl_x0,xl_x1;
	uint8_t xl_y0,xl_y1;
	uint8_t xl_z0,xl_z1;
	
	//GYRO RAW VALUE VARIABLES
	uint8_t g_x0,g_x1;
	uint8_t g_y0,g_y1;
	uint8_t g_z0,g_z1;

	LSM6DS3();
	~LSM6DS3();

	void write(int add,int val);
	uint8_t  read(int add);

	bool check();
	void xl_set(int,int,int);
	void g_set(int,int);

	raw raw_xl();
	raw raw_g();

	raw scaled_xl();
	raw scaled_g();
};
