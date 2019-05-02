#include "project.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define I2C_ADDRESS 0X57
#define I2C_WRITE_ADDR 0x57
#define I2C_READ_ADDR 0x57

//register addresses
#define REG_INTR_STATUS_1 0x00
#define REG_INTR_STATUS_2 0x01
#define REG_INTR_ENABLE_1 0x02
#define REG_INTR_ENABLE_2 0x03
#define REG_FIFO_WR_PTR 0x04
#define REG_OVF_COUNTER 0x05
#define REG_FIFO_RD_PTR 0x06
#define REG_FIFO_DATA 0x07
#define REG_FIFO_CONFIG 0x08
#define REG_MODE_CONFIG 0x09
#define REG_SPO2_CONFIG 0x0A
#define REG_LED1_PA 0x0C
#define REG_LED2_PA 0x0D
#define REG_PILOT_PA 0x10
#define REG_MULTI_LED_CTRL1 0x11
#define REG_MULTI_LED_CTRL2 0x12
#define REG_TEMP_INTR 0x1F
#define REG_TEMP_FRAC 0x20
#define REG_TEMP_CONFIG 0x21
#define REG_PROX_INT_THRESH 0x30
#define REG_REV_ID 0xFE
#define REG_PART_ID 0xFF

bool max_WriteReg(uint8_t Reg, uint8_t Value);
bool maxim_max30102_init();
bool max_ReadReg(uint8_t Reg, uint8_t *Value);
bool max_Reset(void);
void max_Temperature();
bool max_Read_FIFO(uint32_t *pun_red_led, uint32_t *pun_ir_led);