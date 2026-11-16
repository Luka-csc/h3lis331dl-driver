#include "app.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
constexpr uint8_t H3LIS_REG_WHO_AM_I = 0x0F;
constexpr uint8_t H3LIS_WHO_AM_I_EXPECTED = 0x32;
constexpr uint8_t H3LIS_REG_CTRL_REG1 = 0x20;

constexpr uint8_t H3LIS_PM_NORMAL = 0b001 << 5;
constexpr uint8_t H3LIS_DR_50HZ = 0b00 << 3;
constexpr uint8_t H3LIS_AXES_XYZ = 0b111;
constexpr uint8_t H3LIS_CTRL1_CONFIG = H3LIS_PM_NORMAL | H3LIS_DR_50HZ | H3LIS_AXES_XYZ;

static void fail(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // keep led on if check fails

    while(1) {}
}

HAL_StatusTypeDef h3lis_read_reg(uint8_t reg_addr, uint8_t *data) {
    uint8_t tx[2] = {static_cast<uint8_t>(reg_addr | 0x80), 0x0};
    uint8_t rx[2] = {0};
    HAL_StatusTypeDef check;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // set CS low
    check = HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, 100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // set CS high

    if (check == HAL_OK) {
        *data = rx[1];
    } 
    return check;
}

HAL_StatusTypeDef h3lis_write_reg(uint8_t reg_addr, uint8_t data) {
    uint8_t tx[2] = {static_cast<uint8_t>(reg_addr & 0x3F), data};
    HAL_StatusTypeDef check;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // set CS low
    check = HAL_SPI_Transmit(&hspi1, tx, 2, 100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // set CS high

    return check;
}

void app_main(void) {
    uint8_t data;
    HAL_StatusTypeDef check;

    check = h3lis_write_reg(H3LIS_REG_CTRL_REG1, H3LIS_CTRL1_CONFIG);
    if (check != HAL_OK) fail();

    check = h3lis_read_reg(H3LIS_REG_CTRL_REG1, &data);
    if (check != HAL_OK) fail();

    while(1) {
        if (data == H3LIS_CTRL1_CONFIG) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            HAL_Delay(150);
        } else {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            HAL_Delay(1000);
        }
    }
}