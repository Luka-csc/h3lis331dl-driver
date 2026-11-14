# H3LIS331DL Driver notes

## Goal
Want to get sparkfun H3LIS331Dl breakbaord driver working for basic operations

## Log 
### Arduino Uno + I2C 
- Was able to find address 0x19 through the scanner
- Uno's internal pull-up resistors pulled up the I2C lines to 5v. Turning them off worked.
- SPI lines are actively driven high to 5V and software cannot change this. So SPI on the Uno would put 5V into a 3.6V chip, Blue Pill fixes this.

### STM32 Blue Pill + SPI
- tools: CubeMX, VS Code + ST extension, ST-Link V2
- CubeMX setting and WHY:
  - CPOL: High 
    - SPC idles high when CS is high (no transfer)
  - CPHA: 2 Edge 
    - data captured on rising edge, which is 2nd edge since CPOL is high
  - SPI CLK: 4 MHz 
    - under the 10 MHz max of h3lis331dl 
  - PA4: GPIO_Output, High
    - this is CS | High = sensor not selected
    - pull low to start each SPI transaction, back high to end it 
  - PC13: GPIO_Output
    - onboard LED (active-low: LOW = on)
    - blinking to prove toolchain 

## Open Questions
- What is the HAL doing underneath 
- What exactly does a driver do, where does it sit between my code and the hardware
- How do SPI and I2C differ in more detail, and why does one chip support both 

