#include "app.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
constexpr uint8_t H3LIS_REG_WHO_AM_I = 0x0F;
constexpr uint8_t H3LIS_WHO_AM_I_EXPECTED = 0x32;

HAL_StatusTypeDef h3lis_read_reg(uint8_t reg_addr, uint8_t *data) {
    uint8_t tx[2] = {static_cast<uint8_t>(0x80 | reg_addr), 0x0};
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

void app_main(void) {
    uint8_t data;
    HAL_StatusTypeDef check;

    check = h3lis_read_reg(H3LIS_REG_WHO_AM_I, &data);

    if (check == HAL_OK) {
        while(1) {
            if (data == H3LIS_WHO_AM_I_EXPECTED) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                HAL_Delay(150);
            } else {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                HAL_Delay(1000);
            }
        }
    } else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // keep led on if check fails

        while(1) {}
    }
}