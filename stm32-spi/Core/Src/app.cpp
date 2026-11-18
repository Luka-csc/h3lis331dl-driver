#include "app.h"
#include "h3lis331dl.h"

constexpr uint8_t H3LIS_CTRL1_CONFIG = H3LIS_PM_NORMAL | H3LIS_DR_50HZ | H3LIS_AXES_XYZ;

static void fail(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // keep led on if check fails

    while(1) {}
}

void app_main(void) {
    uint8_t data;
    HAL_StatusTypeDef check;

    int32_t x_data, y_data, z_data;

    check = h3lis_write_reg(H3LIS_REG_CTRL_REG1, H3LIS_CTRL1_CONFIG);
    if (check != HAL_OK) fail();

    check = h3lis_read_reg(H3LIS_REG_CTRL_REG1, &data);
    if (check != HAL_OK) fail();
    if (data != H3LIS_CTRL1_CONFIG) fail();

    HAL_Delay(50);

    while(1) {
        check = h3lis_read_accel_mg(&x_data, &y_data, &z_data);
        if (check != HAL_OK) fail();

        if (z_data >= 1300 && z_data <= 1800) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            HAL_Delay(150);
        } else {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            HAL_Delay(1000);
        }
    }
}