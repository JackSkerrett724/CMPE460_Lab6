
/**
 * ******************************************************************************
 * @file    : main.c
 * @brief   : Main run loop
 *
 * @author  : Wil Salus
 * @date    : 9/2/26
 * ******************************************************************************
*/

#include <stdint.h>
#include <stdio.h>
#include <ti/devices/msp/msp.h>
#include "lab2/uart.h"
#include "lab1/leds.h"
#include "lab6/timers.h"
#include "lab5/switches.h"

void delay_ms(uint32_t ms)
{
    // Simple delay loop    
    for (uint32_t i = 0; i < ms * 10000; i++) {
        __NOP();
    }
}

//*****************************************
//*****************PART 1******************
//*****************************************
// int main(void)
// {
//     // Initialize both PWM channels:
//     // 100 us period = nominally 10 kHz
//     TIMA0_PWM_init(0, 100, 0, 0.0);
//     TIMA0_PWM_init(1, 100, 0, 0.0);

//     while (1)
//     {
//         // Forward: 0% -> 100%
//         TIMA0_PWM_DutyCycle(1, 0.0); //make sure the other channel is off before starting the first channel

//         for (int d = 0; d <= 100; d++) 
//         {
//             TIMA0_PWM_DutyCycle(0, d / 100.0);
//             delay_ms(10);
//         }

//         // Forward: 100% -> 0%
//         for (int d = 100; d >= 0; d--) {
//             TIMA0_PWM_DutyCycle(0, d / 100.0);
//             delay_ms(10);
//         }

//         TIMA0_PWM_DutyCycle(0, 0.0);//make sure the other channel is off before starting the next channel
//         delay_ms(10);

//         // Reverse: 0% -> 100%
//         TIMA0_PWM_DutyCycle(1, 0.0); 

//         for (int d = 0; d <= 100; d++) {
//             TIMA0_PWM_DutyCycle(1, d / 100.0);
//             delay_ms(10);
//         }

//         // Reverse: 100% -> 0%
//         for (int d = 100; d >= 0; d--) {
//             TIMA0_PWM_DutyCycle(1, d / 100.0);
//             delay_ms(10);
//         }

//         TIMA0_PWM_DutyCycle(1, 0.0);
//         delay_ms(10);
//     }
// }

//**********************************************
//**************PART 2**************************
//**********************************************

// int main(void)
// {
//     // Configure PB6, PB7, PB0, PB16 for GPIO function
//     IOMUX->SECCFG.PINCM[IOMUX_PINCM23] = IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM23_PF_GPIOB_DIO06;

//     IOMUX->SECCFG.PINCM[IOMUX_PINCM24] = IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM24_PF_GPIOB_DIO07;

//     IOMUX->SECCFG.PINCM[IOMUX_PINCM12] = IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM12_PF_GPIOB_DIO00;

//     IOMUX->SECCFG.PINCM[IOMUX_PINCM33] = IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM33_PF_GPIOB_DIO16;

//     // Configure PB6, PB7, PB0, PB16 as outputs
//     GPIOB->DOESET31_0 |= GPIO_DOESET31_0_DIO6_SET;
//     GPIOB->DOESET31_0 |= GPIO_DOESET31_0_DIO7_SET;
//     GPIOB->DOESET31_0 |= GPIO_DOESET31_0_DIO0_SET;
//     GPIOB->DOESET31_0 |= GPIO_DOESET31_0_DIO16_SET;

//     int forward = 1;
//     int phase = 0;

//     while (1)
//     {
//         // Turn off all coils
//         GPIOB->DOUTCLR31_0 = (GPIO_DOUTCLR31_0_DIO6_CLR |
//                               GPIO_DOUTCLR31_0_DIO7_CLR |
//                               GPIO_DOUTCLR31_0_DIO0_CLR |
//                               GPIO_DOUTCLR31_0_DIO16_CLR);

//         if (forward)
//         {
//             if (phase == 0) {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO6_SET; // A: PB6
//                 phase++;
//             }
//             else if (phase == 1) {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO7_SET; // B: PB7
//                 phase++;
//             }
//             else if (phase == 2) {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO0_SET; // C: PB0
//                 phase++;
//             }
//             else {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO16_SET; // D: PB16
//                 phase = 0;
//             }
//         }
//         else
//         {
//             if (phase == 0) {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO16_SET; // D: PB16
//                 phase++;
//             }
//             else if (phase == 1) {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO0_SET; // C: PB0
//                 phase++;
//             }
//             else if (phase == 2) {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO7_SET; // B: PB7
//                 phase++;
//             }
//             else {
//                 GPIOB->DOUTSET31_0 = GPIO_DOUTSET31_0_DIO6_SET; // A: PB6
//                 phase = 0;
//             }
//         }

//         delay_ms(10);
//     }
// }


//***********************************************
//***************PART 3**************************
//***********************************************

int main(void)
{
    // Channel 0, 20 ms period (50 Hz), 1.5 ms pulse (7.5%)
    TIMA1_PWM_init(0, 20000, 0, 0.075);

    while (1)
    {
        // TIMA1 generates the PWM continuously in hardware.
    }
}