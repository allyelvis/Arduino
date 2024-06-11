#ifndef MPU6050LIB_H
#define MPU6050LIB_H

#include <Wire.h>
#include <MPU6050.h>

class MPU6050Lib {
public:
    MPU6050Lib();
    void begin();
    void readSensor(float &ax, float &ay, float &az, float &gx, float &gy, float &gz);

private:
    MPU6050 mpu;
};

#endif
