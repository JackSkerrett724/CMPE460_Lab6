/**
 * ******************************************************************************
 * @file    : main.c
 * @brief   : Main run loop
 * 
 * @author  : Wil Salus
 * @date 		: 9/2/26
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

//int main(void)
//{
//		//TIMA0_PWM_init(2, 100, 0, 0.20);
//    // Initialize at 10 kHz (100 us period)
//    TIMA0_PWM_init(0, 100, 0, 0.0);
//	TIMA0_PWM_init(1, 100, 0, 0.0);
//	TIMA0_PWM_DutyCycle(1, 0.0);
//	TIMA0_PWM_DutyCycle(0, 0.0);

//    while (1)
//    {
//			delay_ms(10);
//        // 0% to 100% forward
//        for (double d = 0.0; d <= 1.0; d += 0.01) {
//            TIMA0_PWM_DutyCycle(0, d);
//            delay_ms(10);
//        }
//        // 100% to 0% forward
//        for (double d = 1.0; d >= 0.0; d -= 0.01) {
//            TIMA0_PWM_DutyCycle(0, d);
//            delay_ms(10);
//        }
//				delay_ms(10);
//				
//				// 0% to 100% forward
//        for (double d = 0.0; d <= 1.0; d += 0.01) {
//            TIMA0_PWM_DutyCycle(1, d);
//            delay_ms(10);
//        }
//        // 100% to 0% forward
//        for (double d = 1.0; d >= 0.0; d -= 0.01) {
//            TIMA0_PWM_DutyCycle(1, d);
//            delay_ms(10);
//        }
//    }
//}

//**********************************************
//**************PART 2**************************
//**********************************************

// int main(void)
// { 
//	 	if (!(GPIOB->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK)){
//		//Peripheral reset control
//		GPIOB->GPRCM.RSTCTL |= (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETASSERT_ASSERT | GPIO_RSTCTL_RESETSTKYCLR_CLR);
//		GPIOB->GPRCM.PWREN |= (GPIO_PWREN_ENABLE_ENABLE | GPIO_PWREN_KEY_UNLOCK_W);
//	}
//     // Configure PB6, PB7, PB0, PB16 for GPIO function
//     IOMUX->SECCFG.PINCM[IOMUX_PINCM23] |= (IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM23_PF_GPIOB_DIO06);

//     IOMUX->SECCFG.PINCM[IOMUX_PINCM24] |= (IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM24_PF_GPIOB_DIO07);

//     IOMUX->SECCFG.PINCM[IOMUX_PINCM12] |= (IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM12_PF_GPIOB_DIO00);

//     IOMUX->SECCFG.PINCM[IOMUX_PINCM33] |= (IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM33_PF_GPIOB_DIO16);

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

// int main(void)
// {
//     // Channel 0, 20 ms period (50 Hz), 1.5 ms pulse (7.5%) //.078 is 100% duty cycle. Mult by whatever duty cycle required to get
//     //TIMA1_PWM_init(0, 20000, 0, .2);
//		TIMA1_PWM_init(0, 20000, 15, 0.075);

//     while (1)
//     {
//			 	  delay_ms(1000);
//	  TIMA1_PWM_DutyCycle(0, 0.05);
//    delay_ms(1000);
//	 	TIMA1_PWM_DutyCycle(0, 0.0);
//		 delay_ms(1000);
//		TIMA1_PWM_DutyCycle(0, 0.1);
//         //shouldnt need anything here as the hardware does all the works
//     }
// }


//***********************************************
//***************PART 4**************************
//***********************************************

 int main(void)
 {
     // DC motor ; 100 us period = 10 kHz ; 30% duty cycle
     TIMA0_PWM_init(0, 100, 0, 0.30);

     // Servo ; 20,000 us period = 50 Hz ; 1.5 ms pulse = 7.5% duty cycle
     TIMA1_PWM_init(0, 20000, 15, 0.05);

    while (1)
    {
			delay_ms(10);
        // 0% to 100% forward
        for (double d = 0.05; d <= .10; d += 0.01) {
            TIMA1_PWM_DutyCycle(0, d);
            delay_ms(500);
        }
        // 100% to 0% forward
        for (double d = .10; d >= 0.05; d -= 0.01) {
            TIMA1_PWM_DutyCycle(0, d);
            delay_ms(500);
        }
				delay_ms(500);
         //shouldnt need anything here as the hardware does all the works
     }
 }