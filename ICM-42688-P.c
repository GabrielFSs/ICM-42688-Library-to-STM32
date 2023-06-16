/*
 * ICM-42688-P.c
 *
 *     Created on: Jun 10, 2023
 *     Author: Gabriel Felipe
 */

#include "ICM-42688-P.h"
#include <stdint.h>

const uint16_t i2c_timeout = 10;

uint8_t ICM42688_INIT(I2C_HandleTypeDef *I2Cx)
{
    uint8_t check;
    uint8_t Data;

    HAL_I2C_Mem_Read(I2Cx, ICM42688_ADDRESS, WHO_AM_I_G, 1, &check, 1, i2c_timeout);

    if (check == 104)  // Verify if the address is 0x68
        {
            // Set the parameters about the PWR_MGM0 register 0x4E to 0x1111 to able Accelerometer and Gyroscope
            Data = 0xF;
            HAL_I2C_Mem_Write(I2Cx, ICM42688_ADDRESS, PWR_MGMT0, 1, &Data, 1, i2c_timeout);

            // Set the parameters about the INT_CONFIG1 register 0x4D to 0x00 to use RC oscillator clock
            Data = 0xF;
            HAL_I2C_Mem_Write(I2Cx, ICM42688_ADDRESS, PWR_MGMT0, 1, &Data, 1, i2c_timeout);

            // Set the configuration about the interruption 1 (INT1) generator to MPU, INT_CONFIG 0x14
            // 001 to Active High, 010 to set Push Pull, BIT 2 = 0 to set Latched mode
            Data = 0x3;
            HAL_I2C_Mem_Write(I2Cx, ICM42688_ADDRESS, INT_CONFIG, 1, &Data, 1, i2c_timeout);

            // Set the configuration about when the INT1 is generate, INT_STATUS 0x2D
            // 0x100 to Active when DATA READY
            Data = 0x3;
            HAL_I2C_Mem_Write(I2Cx, ICM42688_ADDRESS, INT_STATUS, 1, &Data, 1, i2c_timeout);

            // Set accelerometer configuration to 0x50
            // ACCEL_FS_SEL = 0000011 -> 2g, ACCEL_ODR = 0110 -> 1kHz (default)
            Data = 0x66;
            HAL_I2C_Mem_Write(I2Cx, ICM42688_ADDRESS, ACCEL_CONFIG0, 1, &Data, 1, i2c_timeout);

            // Set accelerometer configuration to 0x4F
            // GYRO_FS_SEL = 011 -> 250dps, GYRO_ODR = 0110 -> 1kHz (default)
            Data = 0x66;
            HAL_I2C_Mem_Write(I2Cx, ICM42688_ADDRESS, GYRO_CONFIG0, 1, &Data, 1, i2c_timeout);
            return 0;
        }
    return 1;
}

void ICM42688_READ_ACCEL(I2C_HandleTypeDef *I2Cx, ICM42688_t *DataStruct)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from ACCEL_DATA_X1 register, 0x1F

    HAL_I2C_Mem_Read(I2Cx, ICM42688_ADDRESS, ACCEL_DATA_X1, 1, Rec_Data, 6, i2c_timeout);

    DataStruct->Accel_X = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

    DataStruct->Ax = DataStruct->Accel_X/ 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y/ 16384.0;
    DataStruct->Az = DataStruct->Accel_Z/ 16384.0;
}


void ICM42688_READ_GYRO(I2C_HandleTypeDef *I2Cx, ICM42688_t *DataStruct)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, ICM42688_ADDRESS, GYRO_DATA_X1, 1, Rec_Data, 6, i2c_timeout);

    DataStruct->Gyro_X = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Gyro_Y = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Gyro_Z = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

    DataStruct->Gx = DataStruct->Gyro_X/ 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y/ 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z / 131.0;
}



