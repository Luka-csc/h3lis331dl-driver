#include "h3lis331dl.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_gpio.h"

extern SPI_HandleTypeDef hspi1;

constexpr uint8_t H3LIS_CMD_READ_ACCEL = H3LIS_REG_OUT_X_L | H3LIS_SPI_READ | H3LIS_SPI_AUTO_INC;

HAL_StatusTypeDef h3lis_read_reg(uint8_t reg_addr, uint8_t *data) {
    uint8_t tx[2] = {static_cast<uint8_t>(reg_addr | H3LIS_SPI_READ), 0x0};
    uint8_t rx[2] = {0};
    HAL_StatusTypeDef check;

    HAL_GPIO_WritePin(H3LIS_CS_PORT, H3LIS_CS_PIN, GPIO_PIN_RESET); // set CS low
    check = HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, 100);
    HAL_GPIO_WritePin(H3LIS_CS_PORT, H3LIS_CS_PIN, GPIO_PIN_SET); // set CS high

    if (check == HAL_OK) {
        *data = rx[1];
    } 
    return check;
}

HAL_StatusTypeDef h3lis_write_reg(uint8_t reg_addr, uint8_t data) {
    uint8_t tx[2] = {static_cast<uint8_t>(reg_addr & 0x3F), data};
    HAL_StatusTypeDef check;

    HAL_GPIO_WritePin(H3LIS_CS_PORT, H3LIS_CS_PIN, GPIO_PIN_RESET); // set CS low
    check = HAL_SPI_Transmit(&hspi1, tx, 2, 100);
    HAL_GPIO_WritePin(H3LIS_CS_PORT, H3LIS_CS_PIN, GPIO_PIN_SET); // set CS high

    return check;
}

HAL_StatusTypeDef h3lis_read_accel_mg(int32_t *x_data, int32_t *y_data, int32_t *z_data) {
    HAL_StatusTypeDef check;

    uint8_t tx[7] = {H3LIS_CMD_READ_ACCEL};
    uint8_t rx[7] = {0};

    HAL_GPIO_WritePin(H3LIS_CS_PORT, H3LIS_CS_PIN, GPIO_PIN_RESET); // set CS low
    check = HAL_SPI_TransmitReceive(&hspi1, tx, rx, 7, 100);
    HAL_GPIO_WritePin(H3LIS_CS_PORT, H3LIS_CS_PIN, GPIO_PIN_SET); // set CS high

    if (check != HAL_OK) return check;

    int16_t x_raw = static_cast<int16_t>((rx[2] << 8) | rx[1]) >> 4;
    int16_t y_raw = static_cast<int16_t>((rx[4] << 8) | rx[3]) >> 4;
    int16_t z_raw = static_cast<int16_t>((rx[6] << 8) | rx[5]) >> 4;

    *x_data = x_raw * H3LIS_SENS_100G_MG;
    *y_data = y_raw * H3LIS_SENS_100G_MG;
    *z_data = z_raw * H3LIS_SENS_100G_MG;

    return check;
}