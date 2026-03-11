#include "bno.h"

void BNO_reset() {
	usleep(2000);
	i2c_write(BNO055_SYS_TRIGGER, 0x2);
	usleep(30000);
	i2c_write(BNO055_SYS_TRIGGER, 0x00);
}

void BNO_Calib(void) {
	i2c_read(BNO055_CALIB_STAT, &def, 2);
	if (def != 0x3f) {
		printf("NOT CALIBRATED \r\n");
		printf(def);
	} else {
		printf("---CALIBRATED- \r\n");
	}
}

void readAccData(int16_t *destination) {
	uint8_t rawData[6];  // x/y/z gyro register data stored here
	i2c_read(BNO055_ACC_DATA_X_LSB, &rawData[0], 6); // Read the six raw data registers sequentially into data array
	destination[0] = ((int16_t) rawData[1] << 8) | rawData[0]; // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t) rawData[3] << 8) | rawData[2];
	destination[2] = ((int16_t) rawData[5] << 8) | rawData[4];
}

void readGyroData(int16_t *destination) {
	uint8_t rawData[6];  // x/y/z gyro register data stored here
	i2c_read(BNO055_GYR_DATA_X_LSB, &rawData[0], 6); // Read the six raw data registers sequentially into data array
	destination[0] = ((int16_t) rawData[1] << 8) | rawData[0]; // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t) rawData[3] << 8) | rawData[2];
	destination[2] = ((int16_t) rawData[5] << 8) | rawData[4];
}

void readMagData(int16_t *destination) {
	uint8_t rawData[6];  // x/y/z gyro register data stored here
	i2c_read(BNO055_MAG_DATA_X_LSB, &rawData[0], 6); // Read the six raw data registers sequentially into data array
	destination[0] = ((int16_t) rawData[1] << 8) | rawData[0]; // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t) rawData[3] << 8) | rawData[2];
	destination[2] = ((int16_t) rawData[5] << 8) | rawData[4];
}

void readEulData(int16_t *destination) {
	uint8_t rawData[6];  // x/y/z gyro register data stored here
	i2c_read(BNO055_EUL_HEADING_LSB, &rawData[0], 6); // Read the six raw data registers sequentially into data array
	destination[0] = ((int16_t) rawData[1] << 8) | rawData[0]; // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t) rawData[3] << 8) | rawData[2];
	destination[2] = ((int16_t) rawData[5] << 8) | rawData[4];
}

void readQuatData(int16_t *destination) {
	uint8_t rawData[8];
	i2c_read(BNO055_QUA_DATA_W_LSB, &rawData[0], 8);
	destination[0] = ((int16_t) rawData[1] << 8) | rawData[0];
	destination[1] = ((int16_t) rawData[3] << 8) | rawData[2];
	destination[2] = ((int16_t) rawData[5] << 8) | rawData[4];
	destination[3] = ((int16_t) rawData[7] << 8) | rawData[6];
}

void BNO_POST() {
	int8_t k = 0;
	i2c_read( BNO055_CHIP_ID, &def, 2);
	if (def == 160) {
		k += 1;
	}
	i2c_read(BNO055_ACC_ID, &def, 2);
	if (def == 251) {
		k += 1;
	}
	i2c_read(BNO055_GYRO_ID, &def, 2);
	if (def == 15) {
		k += 1;
	}
	i2c_read(BNO055_MAG_ID, &def, 2);
	if (def == 50) {
		k += 1;
	}
	if (k == 4) {
		printf("CHIP DATA \r\n");
		usleep(1000);
		uint8_t lsb = 0, msb = 0;
		i2c_read(BNO055_SW_REV_ID_LSB, &def, 2);
		lsb = def;
		i2c_read(BNO055_SW_REV_ID_MSB, &def, 2);
		msb = def;
		i2c_read(BNO055_BL_REV_ID, &def, 2);
		usleep(25000);
		i2c_read(BNO055_ST_RESULT, &def, 4);
	}
}

void SetMode(OPRMode_t mode) {
	i2c_write(BNO055_OPR_MODE, mode);
	usleep(30000);
}

void GetMode() {
	i2c_read(BNO055_OPR_MODE, &def, 2);
	printf(def);
}

void BNO_init() {
	sysg |= 0x20;
	SetMode(BNO055_OPERATION_MODE_CONFIG);
	GetMode();
	usleep(25000);
	i2c_write(BNO055_PAGE_ID, 0x01);
	i2c_write(BNO055_ACC_CONFIG,acc_normal << 5 | B_31hz << 2 | R_4G);
	i2c_write(BNO055_GYRO_CONFIG_0, B_23hz << 3 | R_2000);
	i2c_write(BNO055_GYRO_CONFIG_1, Gyro_normal);
	i2c_write(BNO055_MAG_CONFIG,Mag_Normal << 5 | Mag_Regular << 3 | MB_30hz);
	i2c_write(BNO055_PAGE_ID, 0x00);
	i2c_write(BNO055_TEMP_SOURCE, 0x01);
	i2c_write(BNO055_UNIT_SEL, 0x01);
	i2c_write(BNO055_AXIS_MAP_CONFIG, REMAP_CONFIG_P0);
	i2c_write(BNO055_AXIS_MAP_SIGN, REMAP_SIGN_P3);
	SetPowerMode(NormalPwr);
	SetMode(BNO055_OPERATION_MODE_NDOF);
	usleep(25000);
	i2c_write(BNO055_SYS_TRIGGER, &sysg);
	usleep(30000);
	BNO_Calib();
	i2c_write(BNO055_SYS_TRIGGER, 0x00);
	GetMode();
}

void SetPowerMode(PWRMode_t mode_p) {
	uint8_t vref = 0;
	i2c_write(BNO055_PWR_MODE, mode_p);
	i2c_read(BNO055_PWR_MODE, &vref, 2);
	if (vref == 0) {
		printf("PWR MODE \n");
	} else if (vref == 1) {
		printf("LOW PWR MODE \n");
	}
}

void BNO_setPage(uint8_t page) {
	uint8_t vref = 0;
    i2c_write(BNO055_PAGE_ID, page);
	i2c_read(BNO055_PAGE_ID, &vref, 2);
	if (vref == 0) {
		printf("PAGE 0 \n");
	} else if (vref == 1) {
		printf("PAGE 1 \n");
	}
}