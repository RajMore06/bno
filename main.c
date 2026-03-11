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
#include "bno.h"

int main() {
    if (i2c_init("/dev/i2c-1", BNO055_ADDRESS) < 0) {
        return 1;
    }
    msleep(1000);
    BNO_POST();
    // Step 2: Verify chip ID
    // uint8_t chip_id;
    // if (i2c_read(BNO055_CHIP_ID, &chip_id, 1) == 0) {
    //     printf("BNO055 Chip ID: 0x%02X\n", chip_id);
    // } else {
    //     printf("Failed to read chip ID\n");
    //     i2c_close();
    //     return 1;
    // }
    msleep(800);
    BNO_setPage(0);
    // Step 3: Configure units and operation mode
    i2c_write(BNO055_UNIT_SEL, 0x01);   // set units
    SetMode(BNO055_OPERATION_MODE_CONFIG);
    SetPowerMode(NormalPwr);
    SetMode(BNO055_OPERATION_MODE_NDOF);
    GetMode();
    msleep(25); // wait 25ms for mode switch
    BNO_Calib();

    // Step 4: Loop to read quaternion data
    while (1) {
        uint8_t rawData[8];
        if (i2c_read(BNO055_QUA_DATA_W_LSB, rawData, 8) == 0) {
            int16_t quat[4];
            quat[0] = ((int16_t)rawData[1] << 8) | rawData[0]; // W
            quat[1] = ((int16_t)rawData[3] << 8) | rawData[2]; // X
            quat[2] = ((int16_t)rawData[5] << 8) | rawData[4]; // Y
            quat[3] = ((int16_t)rawData[7] << 8) | rawData[6]; // Z

            // Convert to float
            float q0 = quat[0] / 16384.0f;
            float q1 = quat[1] / 16384.0f;
            float q2 = quat[2] / 16384.0f;
            float q3 = quat[3] / 16384.0f;

            // Compute yaw (heading)
            float yaw = -atan2f(2.0f*(q0*q3 + q1*q2), 1.0f - 2.0f*(q2*q2 + q3*q3));
            float yaw_deg = yaw * (180.0f / M_PI);

            printf("Quaternion: W=%.3f, X=%.3f, Y=%.3f, Z=%.3f | Yaw=%.2f°\n",
                   q0, q1, q2, q3, yaw_deg);
        } else {
            printf("Failed to read quaternion data\n");
        }
    }
    // Step 5: Close I2C (never reached in this loop, but good practice)
    i2c_close();
    return 0;
}