#include "MPU6050Lib.h"

MPU6050Lib::MPU6050Lib() : mpu() {}

void MPU6050Lib::begin() {
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed");
        while (1);
    }
}

void MPU6050Lib::readSensor(float &ax, float &ay, float &az, float &gx, float &gy, float &gz) {
    int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;
    mpu.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
    ax = ax_raw / 16384.0;
    ay = ay_raw / 16384.0;
    az = az_raw / 16384.0;
    gx = gx_raw / 131.0;
    gy = gy_raw / 131.0;
    gz = gz_raw / 131.0;
}
