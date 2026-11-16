#!/bin/bash
set -e
cd "$(dirname "$0")"
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/Debug/stm32-spi.elf verify reset exit"
