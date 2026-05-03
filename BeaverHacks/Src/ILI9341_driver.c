#include <stdint.h>
#include "SPI_driver.h"
#include "ILI9341_driver.h"
#include "Delay.h"
#include "main.h"

#define GPIOA_Base 0x40020000
#define GPIOA_MODER *((volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_ODR *((volatile uint32_t*)(GPIOA_Base + 0x14))

static void DC_Command(){
    GPIOA_ODR &= ~(1<<1); // Pull PA1 LOW for Commands
}

static void DC_Data(){
    GPIOA_ODR |= (1<<1);  // Pull PA1 HIGH for Data
}

// pin A2
static void RST_LOW(){
    GPIOA_ODR &= ~(1<<2);
}

// pin A2
static void RST_HIGH(){
    GPIOA_ODR |= (1<<2);
}

static void WriteCommand(uint8_t cmd){
    DC_Command();
    CS_enable();
    spi1_send(&cmd, 1);
    CS_disable();
}

static void WriteData(uint8_t data){
    DC_Data();
    CS_enable();
    spi1_send(&data, 1);
    CS_disable();
}

void ILI9341_Init(){

    // config for SPI
    spi1_gpioinit();
    spi1_config();
    
    // initilize P1,2 for output
    GPIOA_MODER &= ~((3<<10)|(3<<12));
    GPIOA_MODER |= (1<<2)|(1<<4);

    // begining init sequence for LCD
    RST_LOW();
    delay_SysTick(1, system_frequency);
    RST_HIGH();

    WriteCommand(0x01); // Software Reset
    delay_SysTick(120, system_frequency);

    WriteCommand(0x11); // Sleep Out
    delay_SysTick(5, system_frequency);
    
    WriteCommand(0x3A); // Pixel Format Set
    WriteData(0b01010101); // 16bits/pixel

    WriteCommand(0x36); // Memory Access Control
    WriteData(0); //! Change to rearagne display

    WriteCommand(0x29); // Display ON
}