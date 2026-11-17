#include "h3lis331dl.h"

extern SPI_HandleTypeDef hspi1;

HAL_StatusTypeDef h3lis_read_reg(uint8_t reg_addr, uint8_t *data) {
    uint8_t tx[2] = {static_cast<uint8_t>(reg_addr | 0x80), 0x0};
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