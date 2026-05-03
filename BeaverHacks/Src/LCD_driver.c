
#include <stdint.h>
#include "SPI_driver.h"
#include "LCD_driver.h"

#define GPIOA_Base 0x40020000
#define GPIOA_ODR  *((volatile uint32_t*)(GPIOA_Base + 0x14))

// Rough delay function for initialization
void delay_ms(volatile uint32_t ms) {
    ms *= 16000; // Adjust this multiplier if your delay is too fast/slow
    while(ms--) { __NOP(); }
}

void DC_Command() {
    GPIOA_ODR &= ~(1<<1); // Pull PA1 LOW for Commands
}

void DC_Data() {
    GPIOA_ODR |= (1<<1);  // Pull PA1 HIGH for Data
}

void ILI9341_WriteCommand(uint8_t cmd) {
    DC_Command();
    CS_enable();
    spi1_send(&cmd, 1);
    CS_disable();
}

void ILI9341_WriteData(uint8_t data) {
    DC_Data();
    CS_enable();
    spi1_send(&data, 1);
    CS_disable();
}

void ILI9341_Init() {
    // 1. Software Reset
    ILI9341_WriteCommand(0x01);
    delay_ms(10); // wait after a reset

    // 2. Power Control A, Power Control B, VCOM, etc. 
    // (Often you can skip the deep power tweaks for basic functionality, 
    // but the following are strictly required)

    // 3. Memory Access Control (MADCTL) - Sets screen rotation & color order
    ILI9341_WriteCommand(0x36); 
    ILI9341_WriteData(0x48); // 0x48 = Landscape mode, BGR color order

    // 4. Pixel Format Set (COLMOD) - Tells screen we are using 16-bit colors
    ILI9341_WriteCommand(0x3A); 
    ILI9341_WriteData(0x55); // 0x55 = 16-bit RGB565

    // 5. Sleep Out - Wake up the display!
    ILI9341_WriteCommand(0x11); 
    delay_ms(120); // MUST wait at least 120ms for the power supply to stabilize

    // 6. Display ON
    ILI9341_WriteCommand(0x29); 
}