#ifndef __BNO_H__
#define __BNO_H__

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "stdbool.h"
#include "math.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "i2c.h"

#define BNO055_CHIP_ID          0x00
#define BNO055_ACC_ID           0x01
#define BNO055_MAG_ID           0x02
#define BNO055_GYRO_ID          0x03
#define BNO055_SW_REV_ID_LSB    0x04
#define BNO055_SW_REV_ID_MSB    0x05
#define BNO055_BL_REV_ID        0x06
#define BNO055_PAGE_ID          0x07
#define BNO055_ADDRESS          0x28

#define BNO055_PAGE_ID          0x07
#define BNO055_ACC_DATA_X_LSB   0x08
#define BNO055_ACC_DATA_X_MSB   0x09
#define BNO055_ACC_DATA_Y_LSB   0x0A
#define BNO055_ACC_DATA_Y_MSB   0x0B
#define BNO055_ACC_DATA_Z_LSB   0x0C
#define BNO055_ACC_DATA_Z_MSB   0x0D
#define BNO055_MAG_DATA_X_LSB   0x0E
#define BNO055_MAG_DATA_X_MSB   0x0F
#define BNO055_MAG_DATA_Y_LSB   0x10
#define BNO055_MAG_DATA_Y_MSB   0x11
#define BNO055_MAG_DATA_Z_LSB   0x12
#define BNO055_MAG_DATA_Z_MSB   0x13
#define BNO055_GYR_DATA_X_LSB   0x14
#define BNO055_GYR_DATA_X_MSB   0x15
#define BNO055_GYR_DATA_Y_LSB   0x16
#define BNO055_GYR_DATA_Y_MSB   0x17
#define BNO055_GYR_DATA_Z_LSB   0x18
#define BNO055_GYR_DATA_Z_MSB   0x19
#define BNO055_EUL_HEADING_LSB  0x1A
#define BNO055_EUL_HEADING_MSB  0x1B
#define BNO055_EUL_ROLL_LSB     0x1C
#define BNO055_EUL_ROLL_MSB     0x1D
#define BNO055_EUL_PITCH_LSB    0x1E
#define BNO055_EUL_PITCH_MSB    0x1F
#define BNO055_QUA_DATA_W_LSB   0x20
#define BNO055_QUA_DATA_W_MSB   0x21
#define BNO055_QUA_DATA_X_LSB   0x22
#define BNO055_QUA_DATA_X_MSB   0x23
#define BNO055_QUA_DATA_Y_LSB   0x24
#define BNO055_QUA_DATA_Y_MSB   0x25
#define BNO055_QUA_DATA_Z_LSB   0x26
#define BNO055_QUA_DATA_Z_MSB   0x27
#define BNO055_LIA_DATA_X_LSB   0x28
#define BNO055_LIA_DATA_X_MSB   0x29
#define BNO055_LIA_DATA_Y_LSB   0x2A
#define BNO055_LIA_DATA_Y_MSB   0x2B
#define BNO055_LIA_DATA_Z_LSB   0x2C
#define BNO055_LIA_DATA_Z_MSB   0x2D
#define BNO055_GRV_DATA_X_LSB   0x2E
#define BNO055_GRV_DATA_X_MSB   0x2F
#define BNO055_GRV_DATA_Y_LSB   0x30
#define BNO055_GRV_DATA_Y_MSB   0x31
#define BNO055_GRV_DATA_Z_LSB   0x32
#define BNO055_GRV_DATA_Z_MSB   0x33
#define BNO055_TEMP             0x34
#define BNO055_CALIB_STAT       0x35
#define BNO055_ST_RESULT        0x36
#define BNO055_INT_STATUS       0x37
#define BNO055_SYS_CLK_STATUS   0x38
#define BNO055_SYS_STATUS       0x39
#define BNO055_SYS_ERR          0x3A
#define BNO055_UNIT_SEL         0x3B
#define BNO055_OPR_MODE         0x3D
#define BNO055_PWR_MODE         0x3E
#define BNO055_SYS_TRIGGER      0x3F
#define BNO055_TEMP_SOURCE      0x40
#define BNO055_AXIS_MAP_CONFIG  0x41
#define BNO055_AXIS_MAP_SIGN    0x42
#define BNO055_ACC_OFFSET_X_LSB 0x55
#define BNO055_ACC_OFFSET_X_MSB 0x56
#define BNO055_ACC_OFFSET_Y_LSB 0x57
#define BNO055_ACC_OFFSET_Y_MSB 0x58
#define BNO055_ACC_OFFSET_Z_LSB 0x59
#define BNO055_ACC_OFFSET_Z_MSB 0x5A
#define BNO055_MAG_OFFSET_X_LSB 0x5B
#define BNO055_MAG_OFFSET_X_MSB 0x5C
#define BNO055_MAG_OFFSET_Y_LSB 0x5D
#define BNO055_MAG_OFFSET_Y_MSB 0x5E
#define BNO055_MAG_OFFSET_Z_LSB 0x5F
#define BNO055_MAG_OFFSET_Z_MSB 0x60
#define BNO055_GYR_OFFSET_X_LSB 0x61
#define BNO055_GYR_OFFSET_X_MSB 0x62
#define BNO055_GYR_OFFSET_Y_LSB 0x63
#define BNO055_GYR_OFFSET_Y_MSB 0x64
#define BNO055_GYR_OFFSET_Z_LSB 0x65
#define BNO055_GYR_OFFSET_Z_MSB 0x66
#define BNO055_ACC_RADIUS_LSB   0x67
#define BNO055_ACC_RADIUS_MSB   0x68
#define BNO055_MAG_RADIUS_LSB   0x69
#define BNO055_MAG_RADIUS_MSB   0x6A

// BNO055 Page 1
#define BNO055_PAGE_ID          0x07
#define BNO055_ACC_CONFIG       0x08
#define BNO055_MAG_CONFIG       0x09
#define BNO055_GYRO_CONFIG_0    0x0A
#define BNO055_GYRO_CONFIG_1    0x0B
#define BNO055_ACC_SLEEP_CONFIG 0x0C
#define BNO055_GYR_SLEEP_CONFIG 0x0D
#define BNO055_INT_MSK          0x0F
#define BNO055_INT_EN           0x10
#define BNO055_ACC_AM_THRES     0x11
#define BNO055_ACC_INT_SETTINGS 0x12
#define BNO055_ACC_HG_DURATION  0x13
#define BNO055_ACC_HG_THRESH    0x14
#define BNO055_ACC_NM_THRESH    0x15
#define BNO055_ACC_NM_SET       0x16
#define BNO055_GYR_INT_SETTINGS 0x17
#define BNO055_GYR_HR_X_SET     0x18
#define BNO055_GYR_DUR_X        0x19
#define BNO055_GYR_HR_Y_SET     0x1A
#define BNO055_GYR_DUR_Y        0x1B
#define BNO055_GYR_HR_Z_SET     0x1C
#define BNO055_GYR_DUR_Z        0x1D
#define BNO055_GYR_AM_THRESH    0x1E
#define BNO055_GYR_AM_SET       0x1F

typedef enum {  // BNO-55 operation modes
	BNO055_OPERATION_MODE_CONFIG = 0x00,
	// Sensor Mode
	BNO055_OPERATION_MODE_ACCONLY = 0x01,
	BNO055_OPERATION_MODE_MAGONLY = 0x02,
	BNO055_OPERATION_MODE_GYRONLY = 0x03,
	BNO055_OPERATION_MODE_ACCMAG = 0x04,
	BNO055_OPERATION_MODE_ACCGYRO = 0x05,
	BNO055_OPERATION_MODE_MAGGYRO = 0x06,
	BNO055_OPERATION_MODE_AMG = 0x07,  // 0x07
	// Fusion Mode
	BNO055_OPERATION_MODE_IMU = 0x08,
	BNO055_OPERATION_MODE_COMPASS = 0x09,
	BNO055_OPERATION_MODE_M4G = 0x0A,
	BNO055_OPERATION_MODE_NDOF_FMC_OFF = 0x0B,
	BNO055_OPERATION_MODE_NDOF = 0x0C  // 0x0C
} OPRMode_t;

typedef enum {
	NormalPwr = 0x00, LowPwr = 0x01, SuspendPwr = 0x02
} PWRMode_t;

/** Remap settings **/
typedef enum {
	REMAP_CONFIG_P0 = 0x21, REMAP_CONFIG_P1 = 0x24, // default
	REMAP_CONFIG_P2 = 0x24,
	REMAP_CONFIG_P3 = 0x21,
	REMAP_CONFIG_P4 = 0x24,
	REMAP_CONFIG_P5 = 0x21,
	REMAP_CONFIG_P6 = 0x21,
	REMAP_CONFIG_P7 = 0x24
} axis_remap_config_t;

/** Remap Signs **/
typedef enum {
	REMAP_SIGN_P0 = 0x04, REMAP_SIGN_P1 = 0x00, // default
	REMAP_SIGN_P2 = 0x06,
	REMAP_SIGN_P3 = 0x02,
	REMAP_SIGN_P4 = 0x03,
	REMAP_SIGN_P5 = 0x01,
	REMAP_SIGN_P6 = 0x07,
	REMAP_SIGN_P7 = 0x05
} axis_remap_sign_t;

enum Accg_range {
	R_2G = 0, R_4G, R_8G, R_16G
};

enum Acc_BandWidth {
	B_7hz = 0, B_15hz, B_31hz, B_62hz, B_125hz, B_250hz, B_500hz, B_1000hz
};

enum Acc_opr {
	acc_normal = 0,
	acc_suspend,
	acc_lowpower1,
	acc_standby,
	acc_lowpoer2,
	acc_deepsuspend
};

enum Gyro_range {
	R_2000, R_1000, R_500, R_250, R_125
};

enum Gyro_BandWidth {
	B_523hz, B_230hz, B_116hz, B_47hz, B_23hz, B_12hz, B_64hz, B_32hz
};

enum Gyro_opr {
	Gyro_normal,
	Gyro_FastPower,
	Gyro_DeepSuspend,
	Gyro_Suspend,
	Gyro_AdvancedPowerSaved,
};

enum DataOutputRate {
	MB_2hz, MB_6hz, MB_8hz, MB_10hz, MB_15hz, MB_20hz, MB_25hz, MB_30hz
};

enum Mag_opr {
	Mag_LowPwr, Mag_Regular, Mag_EnhancedRegular, Mag_HighAccuracy
};

enum Mag_pwrMode {
	Mag_Normal, Mag_Sleep, Mag_Suspend, Mag_ForceMode
};

void BNO_POST();
void BNO_Calib();
void BNO_init();
void SetMode(OPRMode_t mode);
void GetMode();
void SetPowerMode(PWRMode_t mode_p);
void readAccelData(int16_t *destination);
void readGyroData(int16_t *destination);
void readQuatData(int16_t *destination);
void readMagData(int16_t *destination);
void readEulData(int16_t *destination);
void BNO_setPage(uint8_t page);

#endif