/* ========================================
*
* Copyright YOUR COMPANY, THE YEAR
* All Rights Reserved
* UNPUBLISHED, LICENSED SOFTWARE.
*
* CONFIDENTIAL AND PROPRIETARY INFORMATION
* WHICH IS THE PROPERTY OF your company.
*
* ========================================
*/
#include "project.h"
#include <stdlib.h>
#include <stdio.h>
#include <max30102.h>
#include <algorithm.h>
double temp, temp1, temp_frac;
#define MAX_BRIGHTNESS 255

int main(void)
{
    CyGlobalIntEnable;
    char str[15];
    uint32_t aun_red_buffer[500];
    uint32_t aun_ir_buffer[500];
    int32_t n_ir_buffer_length; //data length
    int32_t n_sp02;             //SPO2 value
    int8_t ch_spo2_valid;       //indicator to show if the SP02 calculation is valid
    int32_t n_heart_rate;       //heart rate value
    int8_t ch_hr_valid;         //indicator to show if the heart rate calculation is valid
    uint8_t uch_dummy;

    I2C_Start();
    UART_1_Start();
    uint32_t un_min, un_max, un_prev_data;
    int32_t n_brightness;
    float f_temp;

    max_Reset();
    CyDelay(1000);

    int i;
    max_ReadReg(0, &uch_dummy);
    while (UART_1_GetChar() == 0)
    {
        sprintf(str, "Press any key to start conversion\n\r");
        UART_1_PutString(str);
        CyDelay(100);
    }
    uch_dummy = getchar();
    un_min = 0x3FFFF;
    un_max = 0;
    n_brightness = 0;
    maxim_max30102_init();

    n_ir_buffer_length = 500;
    for (i = 0; i < n_ir_buffer_length; i++)
    {

        while (MaxINT_Read() == 1)
            ;
        max_Read_FIFO((aun_red_buffer + i), (aun_ir_buffer + i));
        if (un_min > aun_red_buffer[i])
            un_min = aun_red_buffer[i]; //update signal min
        if (un_max < aun_red_buffer[i])
            un_max = aun_red_buffer[i];
        sprintf(str, "red %lu ", (unsigned long)aun_red_buffer[i]);
        UART_1_PutString(str);
        sprintf(str, "ir %lu\r\n", (unsigned long)aun_ir_buffer[i]);
        UART_1_PutString(str);
    }
    un_prev_data = aun_red_buffer[i];
    maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
    //max_Temperature();
    for (;;)
    {
        i = 0;
        un_min = 0x3FFFF;
        un_max = 0;

        //dumping the first 100 sets of samples in the memory and shift the last 400 sets of samples to the top
        for (i = 100; i < 500; i++)
        {
            aun_red_buffer[i - 100] = aun_red_buffer[i];
            aun_ir_buffer[i - 100] = aun_ir_buffer[i];

            //update the signal min and max
            if (un_min > aun_red_buffer[i])
                un_min = aun_red_buffer[i];
            if (un_max < aun_red_buffer[i])
                un_max = aun_red_buffer[i];
        }

        //take 100 sets of samples before calculating the heart rate.
        for (i = 400; i < 500; i++)
        {
            un_prev_data = aun_red_buffer[i - 1];
            while (MaxINT_Read() == 1)
                ;
            max_Read_FIFO((aun_red_buffer + i), (aun_ir_buffer + i));

            if (aun_red_buffer[i] > un_prev_data)
            {
                f_temp = aun_red_buffer[i] - un_prev_data;
                f_temp /= (un_max - un_min);
                f_temp *= MAX_BRIGHTNESS;
                n_brightness -= (int)f_temp;
                if (n_brightness < 0)
                    n_brightness = 0;
            }
            else
            {
                f_temp = un_prev_data - aun_red_buffer[i];
                f_temp /= (un_max - un_min);
                f_temp *= MAX_BRIGHTNESS;
                n_brightness += (int)f_temp;
                if (n_brightness > MAX_BRIGHTNESS)
                    n_brightness = MAX_BRIGHTNESS;
            }

            //send samples and calculation result to terminal program through UART
            sprintf(str, "red=%lu ", (unsigned long)aun_red_buffer[i]);
            UART_1_PutString(str);
            sprintf(str, "ir=%lu ", (unsigned long)aun_ir_buffer[i]);
            UART_1_PutString(str);
            sprintf(str, "HR=%lu ", (unsigned long)n_heart_rate);
            UART_1_PutString(str);
            sprintf(str, "HRvalid=%lu ", (unsigned long)ch_hr_valid);
            UART_1_PutString(str);
            sprintf(str, "SpO2=%lu ", (unsigned long)n_sp02);
            UART_1_PutString(str);
            sprintf(str, "SPO2Valid=%lu \n\r", (unsigned long)ch_spo2_valid);
            UART_1_PutString(str);
        }
        maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
    }
}