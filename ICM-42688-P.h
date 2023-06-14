/*
 * ICM-42688-P.h
 *
 *  Created on: Jun 10, 2023
 *  Author: Gabriel Felipe
 *  email: gabriel.felipe@ufu.br
 *
 *  -Based on MPU6050.h by leech001 - https://github.com/leech001/MPU6050-
 *
 *  This library is focused on defining the ICM-42688 registers,
 *  reading gyroscope and accelerometer data and defining the interrupt 0 parameters
 *  to be used in STM32
 *
 */

#ifndef ICM_42688_P_H_
#define ICM_42688_P_H_

#include <stdint.h>
#include "main.h"

#define ICM42688_ADDRESS 0x68	//Address 0x0011110 AP_AD0 = GND

/*
 *	Register Defines for Bank set default, BANK 0 Register 0x76 = 0 (default)
 */

#define		DEVICE_CONFIG 			0x11
#define		DRIVE_CONFIG 			0x13
#define 	INT_CONFIG				0x14
#define 	FIFO_CONFIG				0x16
#define		TEMP_DATA1				0x1D
#define		TEMP_DATA0				0x1E
#define		ACCEL_DATA_X1 			0x1F
#define		ACCEL_DATA_X0			0x20
#define		ACCEL_DATA_Y1			0x21
#define		ACCEL_DATA_Y0			0x22
#define		ACCEL_DATA_Z1			0x23
#define		ACCEL_DATA_Z0			0x24
#define		GYRO_DATA_X1			0x25
#define		GYRO_DATA_X0 			0x26
#define		GYRO_DATA_Y1 			0x27
#define		GYRO_DATA_Y0			0x28
#define		GYRO_DATA_Z1 			0x29
#define		GYRO_DATA_Z0			0x2A
#define		TMST_FSYNCH 			0x2B
#define		TMST_FSYNCL 			0x2C
#define		INT_STATUS				0x2D
#define		FIFO_COUNTH 			0x2E
#define		FIFO_COUNTL				0x2F
#define		FIFO_DATA				0x30
#define		APEX_DATA0				0x31
#define		APEX_DATA1				0x32
#define		APEX_DATA2				0x33
#define		APEX_DATA3				0x34
#define		APEX_DATA4				0x35
#define		APEX_DATA5 				0x36
#define		INT_STATUS2				0x37
#define		INT_STATUS3				0x38
#define		SIGNAL_PATH_RESET		0x4B
#define		INTF_CONFIG0			0x4C
#define		INTF_CONFIG1			0x4D
#define		PWR_MGMT0				0x4E
#define		GYRO_CONFIG0			0x4F
#define		ACCEL_CONFIG0 			0x50
#define		GYRO_CONFIG1 			0x51
#define		GYRO_ACCEL_CONFIG0 		0x52
#define		ACCEL_CONFIG1 			0x53
#define		TMST_CONFIG 			0x54
#define		APEX_CONFIG0 			0x56
#define		SMD_CONFIG 				0x57
#define		FIFO_CONFIG1 			0x5F
#define		FIFO_CONFIG2 			0x60
#define		FIFO_CONFIG3 			0x61
#define		FSYNC_CONFIG 			0x62
#define		INT_CONFIG0  			0x63
#define		INT_CONFIG1  			0x64
#define		INT_SOURCE0  			0x65
#define		INT_SOURCE1  			0x66
#define		INT_SOURCE3  			0x68
#define		INT_SOURCE4 			0x69
#define		FIFO_LOST_PKT0  		0x6C
#define		FIFO_LOST_PKT1 			0x6D
#define		SELF_TEST_CONFIG 		0x70
#define		WHO_AM_I  				0x75
#define		REG_BANK_SEL 			0x76

/*
 * ICM-42688 structure
*/

typedef struct {

    int16_t Accel_X;
    int16_t Accel_Y;
    int16_t Accel_Z;
    int16_t Gyro_X;
    int16_t Gyro_Y;
    int16_t Gyro_Z;


} ICM42688_t;

/*
 * Functions Definitions for I2C Communication with Register Bank Default
 */

extern I2C_HandleTypeDef hi2c;

uint8_t ICM42688_INIT(I2C_HandleTypeDef *I2Cx);
void ICM42688_READ_GYRO(I2C_HandleTypeDef *I2Cx, ICM42688_t *DataStruct);
void ICM42688_READ_ACCEL(I2C_HandleTypeDef *I2Cx, ICM42688_t *DataStruct);

#endif /* ICM_42688_P_H_ */
