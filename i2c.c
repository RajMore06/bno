#include "i2c.h"

static int file_i2c = -1;

uint8_t i2c_init(const char *device, int addr) {
    file_i2c=open(device, O_RDWR);
    if(file_i2c<0) {
        perror("Failed to open the i2c bus");
        return -1;
    }
    if(ioctl(file_i2c, I2C_SLAVE,addr)<0) {
        perror("Failed to acquire bus access to slave");
        close(file_i2c);
        file_i2c=-1;
        return -1;
    }
    return 0;
}

uint8_t i2c_close() {
    if(file_i2c>=0) {
        close(file_i2c);
        file_i2c=-1;
    }
}

uint8_t i2c_write(uint8_t reg, uint8_t val) {
    uint8_t buf[2] = {reg,val};
    if(write(file_i2c,buf,2)!=2) {
        perror("I2C Write Error");
        return -1;
    }
    return 0;
}

uint8_t i2c_read(uint8_t reg, uint8_t *buf, size_t len) {
    if(write(file_i2c,&reg,1)!=1) {
        perror("Failed to set register address");
        return -1;
    }

    if(read(file_i2c,buf,len)!=(ssize_t)len) {
        perror("Failed to read from i2c device");
        return -1;
    }
    return 0;
}