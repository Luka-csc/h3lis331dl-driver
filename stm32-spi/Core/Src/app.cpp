#include "app.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"

extern SPI_HandleTypeDef hspi1;

void app_main(void) {
    uint8_t transmit_buffer[2] = {0x8F, 0x00};
    uint8_t receive_buffer[2] = {0};
    HAL_StatusTypeDef check;
    
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // set CS low
    check = HAL_SPI_TransmitReceive(&hspi1, transmit_buffer, receive_buffer, 2, 100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // set CS high

    if (check == HAL_OK) {
        while(1) {
            if (receive_buffer[1] == 0x32) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                HAL_Delay(150);
            } else {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                HAL_Delay(1000);
            }
        }
    } else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // keep led on if check fails
    }
}