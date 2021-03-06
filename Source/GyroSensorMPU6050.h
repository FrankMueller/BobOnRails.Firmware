// Copyright 2017 Frank Mueller
#ifndef SOURCE_GYROSENSORMPU6050_H_
#define SOURCE_GYROSENSORMPU6050_H_

#include <stdint.h>
#include "Vector3.h"
#include "GyroSensor.h"

namespace BobOnRails {
namespace Firmware {

class GyroSensorMPU6050 : public GyroSensor {
 public:
    enum AccelerationResolutions { AccLow = 16, AccMedium = 8, AccHigh = 4, AccVeryHigh = 2 };

    enum GyroResolutions { GyroLow = 2000, GyroMedium = 1000, GyroHigh = 500, GyroVeryHigh = 250 };

    GyroSensorMPU6050();

    ~GyroSensorMPU6050();

    /** @inheritdoc */
    int connect();

    /** @inheritdoc */
    int measure(Vector3* acceleration, Vector3* gyration, float* temperature);

    /**
       Gets the resolution of the gyration data set on the device.

       @return zero if the operation succeeded; otherwise an error code.
     */
    int getGyrationResolution(GyroResolutions* resolution);

    int setGyrationResolution(GyroResolutions resolution);

    int getAccelerationResolution(AccelerationResolutions* resolution);

    int setAccelerationResolution(AccelerationResolutions resolution);


 private:
    int deviceHandle;
    float temperatureOffset;
    float temperatureGain;
    float accelerationGain;
    float gyrationGain;

    int readFromMPU6050(uint8_t command, uint8_t* buffer, uint8_t size);

    int writeToMPU6050(uint8_t command, uint8_t value);

    float decodeRawValue(uint8_t msb, uint8_t lsb);

    struct MPU6050RawData {
        uint8_t acceleration_x_high;
        uint8_t acceleration_x_low;
        uint8_t acceleration_y_high;
        uint8_t acceleration_y_low;
        uint8_t acceleration_z_high;
        uint8_t acceleration_z_low;
        uint8_t temperature_high;
        uint8_t temperature_low;
        uint8_t gyration_x_high;
        uint8_t gyration_x_low;
        uint8_t gyration_y_high;
        uint8_t gyration_y_low;
        uint8_t gyration_z_high;
        uint8_t gyration_z_low;
    };
};
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_GYROSENSORMPU6050_H_
