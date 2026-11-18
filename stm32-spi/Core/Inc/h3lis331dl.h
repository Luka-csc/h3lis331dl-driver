#ifndef H3LIS331DL_H
#define H3LIS331DL_H

#include "main.h"

static GPIO_TypeDef* const H3LIS_CS_PORT = GPIOA;
constexpr uint16_t H3LIS_CS_PIN = GPIO_PIN_4;

constexpr uint8_t H3LIS_REG_WHO_AM_I = 0x0F;
constexpr uint8_t H3LIS_WHO_AM_I_EXPECTED = 0x32;
constexpr uint8_t H3LIS_REG_CTRL_REG1 = 0x20;

constexpr uint8_t H3LIS_PM_NORMAL = 0b001 << 5;
constexpr uint8_t H3LIS_DR_50HZ = 0b00 << 3;
constexpr uint8_t H3LIS_AXES_XYZ = 0b111;

constexpr uint8_t H3LIS_REG_OUT_X_L = 0x28;
constexpr uint8_t H3LIS_SPI_READ = 1 << 7;
constexpr uint8_t H3LIS_SPI_AUTO_INC = 1 << 6;
constexpr int32_t H3LIS_SENS_100G_MG = 49;

HAL_StatusTypeDef h3lis_read_reg(uint8_t reg_addr, uint8_t *data);
HAL_StatusTypeDef h3lis_write_reg(uint8_t reg_addr, uint8_t data);
HAL_StatusTypeDef h3lis_read_accel_mg(int32_t *x_data, int32_t *y_data, int32_t *z_data);

#endif