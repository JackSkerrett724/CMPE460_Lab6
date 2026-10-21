/**
 * ******************************************************************************
 * @file    : timers.c
 * @brief   : Timers module file
 * @details : Timers initialization and interaction
 * 
 * @author 
 * @date 
 * ******************************************************************************
*/

#include <stdint.h>
#include <sysctl.h>
#include <ti/devices/msp/msp.h>
#include <ti/devices/msp/peripherals/hw_gptimer.h>
#include "lab6/timers.h"

void TIMG0_init(uint32_t period, uint32_t prescaler)
{
    if (!(TIMG0->GPRCM.PWREN & GPTIMER_PWREN_ENABLE_MASK))
    {
        // Peripheral reset control
        TIMG0->GPRCM.RSTCTL |=
            (GPTIMER_RSTCTL_KEY_UNLOCK_W |
             GPTIMER_RSTCTL_RESETASSERT_ASSERT |
             GPTIMER_RSTCTL_RESETSTKYCLR_CLR);

        TIMG0->GPRCM.PWREN |=
            (GPTIMER_PWREN_KEY_UNLOCK_W |
             GPTIMER_PWREN_ENABLE_ENABLE);
    }

    // Select BUSCLK
    TIMG0->CLKSEL |= GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE;

    // Clock divider = 1
    TIMG0->CLKDIV |= GPTIMER_CLKDIV_RATIO_DIV_BY_1;

    // Prescaler
    TIMG0->COMMONREGS.CPS |= prescaler;

    // Enable timer clock
  //  TIMG0->COMMONREGS.CCLKCTL |= GPTIMER_CCLKCTL_CLKEN_ENABLED;

    // Disable timer
    TIMG0->COUNTERREGS.CTRCTL = GPTIMER_CTRCTL_EN_DISABLED;

    // Repeat mode
    TIMG0->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CM_MASK;

    TIMG0->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_REPEAT_REPEAT_1;

    TIMG0->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CVAE_MASK;

    // Set timer period
    uint32_t clk = SYSCTL_SYSCLK_getMCLK();
    uint32_t load = period*(clk/(1000000*(prescaler+1))*(TIMG0->CLKDIV+1));
    TIMG0->COUNTERREGS.LOAD = load;

  //  __disable_irq();

    // Clear Zero event interrupt
    // TIMG0->CPU_INT.ICLR = GPTIMER_CPU_INT_ICLR_Z_CLR;

    // // Enable Zero event interrupt
    // TIMG0->CPU_INT.IMASK |= GPTIMER_CPU_INT_IMASK_Z_SET;

    TIMG0->COMMONREGS.CCLKCTL |= GPTIMER_CCLKCTL_CLKEN_ENABLED;


    // Enable TIMG0 interrupt
   // NVIC_EnableIRQ(TIMG0_INT_IRQn);

  //  __enable_irq();

}


void TIMG6_init(uint32_t period, uint32_t prescaler){

	if (!(TIMG6->GPRCM.PWREN & GPTIMER_PWREN_ENABLE_MASK)){
		//Peripheral reset control
	TIMG6->GPRCM.RSTCTL |= (GPTIMER_RSTCTL_KEY_UNLOCK_W | GPTIMER_RSTCTL_RESETASSERT_ASSERT | GPTIMER_RSTCTL_RESETSTKYCLR_CLR);
  TIMG6->GPRCM.PWREN  |= (GPTIMER_PWREN_KEY_UNLOCK_W  | GPTIMER_PWREN_ENABLE_ENABLE);
	}
	
	TIMG6->CLKSEL |= GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE;
	TIMG6->CLKDIV |= GPTIMER_CLKDIV_RATIO_DIV_BY_1; 
	TIMG6->COMMONREGS.CPS |= prescaler;
	//TIMG6->COMMONREGS.CCLKCTL |= GPTIMER_CCLKCTL_CLKEN_ENABLED; 
	TIMG6->COUNTERREGS.CTRCTL = GPTIMER_CTRCTL_EN_DISABLED;
	
	TIMG6->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CM_MASK;
	TIMG6->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_REPEAT_REPEAT_1;  
	TIMG6->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CVAE_MASK;

	
	//uint64_t load = (((32000000*period)/((prescaler+1)*(1000000)))-1);
  // Convert period from microseconds to timer ticks
  uint32_t clk = SYSCTL_SYSCLK_getMCLK();
  uint32_t load = period*(clk/(1000*(prescaler+1))*(TIMG6->CLKDIV+1));
	TIMG6->COUNTERREGS.LOAD = load;
	
	//	__disable_irq();
  
	// TIMG6->CPU_INT.ICLR |= GPTIMER_CPU_INT_ICLR_Z_CLR;
	// TIMG6->CPU_INT.IMASK |= GPTIMER_CPU_INT_IMASK_Z_SET;
  // TIMG6->COMMONREGS.CCLKCTL |= GPTIMER_CCLKCTL_CLKEN_ENABLED;
	 TIMG6 ->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_EN_ENABLED;
	//NVIC_ClearPendingIRQ(TIMG6_INT_IRQn);
	//NVIC_EnableIRQ(TIMG6_INT_IRQn);
	//__enable_irq();

}


void TIMG12_init(uint32_t period){
	if (!(TIMG12->GPRCM.PWREN & GPTIMER_PWREN_ENABLE_MASK)) {
	TIMG12->GPRCM.RSTCTL |= (GPTIMER_RSTCTL_KEY_UNLOCK_W | GPTIMER_RSTCTL_RESETASSERT_ASSERT | GPTIMER_RSTCTL_RESETSTKYCLR_CLR);
  	TIMG12->GPRCM.PWREN  |= (GPTIMER_PWREN_KEY_UNLOCK_W  | GPTIMER_PWREN_ENABLE_ENABLE);
  	}
	
	TIMG12->CLKSEL = GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE;
	TIMG12->COMMONREGS.CCLKCTL |= GPTIMER_CCLKCTL_CLKEN_ENABLED ;
	TIMG12->COUNTERREGS.CTRCTL = GPTIMER_CTRCTL_EN_DISABLED;
	
	TIMG12->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CM_MASK;
	TIMG12->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_REPEAT_REPEAT_1;  
	TIMG12->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CVAE_MASK;
	
	//uint64_t load = (((32000000*period)/(1000000))-1);
	TIMG12->COUNTERREGS.LOAD = (uint32_t) period;
	
	//__disable_irq();
	// TIMG12->CPU_INT.ICLR  |= GPTIMER_CPU_INT_ICLR_Z_CLR;
  // TIMG12->CPU_INT.IMASK |= GPTIMER_CPU_INT_IMASK_Z_SET;
	 TIMG12->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_EN_ENABLED;
	
  	//NVIC_EnableIRQ(TIMG12_INT_IRQn);
	//__enable_irq();
}





void TIMA0_PWM_init(uint8_t channel, uint32_t period, uint32_t prescaler, double percentDutyCycle)
{
	if (!(TIMA0->GPRCM.PWREN & GPTIMER_PWREN_ENABLE_MASK))
	{
		//Peripheral reset control
		TIMA0->GPRCM.RSTCTL |= (GPTIMER_RSTCTL_KEY_UNLOCK_W | GPTIMER_RSTCTL_RESETASSERT_ASSERT | GPTIMER_RSTCTL_RESETSTKYCLR_CLR);
		TIMA0->GPRCM.PWREN  |= (GPTIMER_PWREN_KEY_UNLOCK_W  | GPTIMER_PWREN_ENABLE_ENABLE);
	}


	TIMA0->CLKSEL |= GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE;
	TIMA0->CLKDIV |= GPTIMER_CLKDIV_RATIO_DIV_BY_1; 
	TIMA0->COMMONREGS.CPS |= prescaler;


	TIMA0->COMMONREGS.CCLKCTL |= 1;
	TIMA0->COUNTERREGS.CTRCTL = GPTIMER_CTRCTL_EN_DISABLED; 
	
	TIMA0->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CM_MASK;
	TIMA0->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_REPEAT_REPEAT_1;  
	TIMA0->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CVAE_MASK;

	
	//uint64_t load = (((32000000*period)/((prescaler+1)*(1000000)))-1);

	//convert to load assuming period is in microseconds
 	uint32_t clk = SYSCTL_SYSCLK_getMCLK();
  	uint32_t load = period*(clk/(1000000*(prescaler+1))*(TIMA0->CLKDIV+1));
	TIMA0->COUNTERREGS.LOAD = load;




	if(channel == 0 || channel == 1)
	{
		

		//Set duty cycle
		TIMA0->COUNTERREGS.CC_01[channel] = (uint32_t) (load * (1-percentDutyCycle));

		//Set compare mode
		TIMA0->COUNTERREGS.CCCTL_01[channel] |= GPTIMER_CCCTL_01_COC_COMPARE;


		//Action on Load - high, Action on Compare - low
		TIMA0->COUNTERREGS.CCACT_01[channel] |= (GPTIMER_CCACT_01_LACT_CCP_HIGH | GPTIMER_CCACT_01_CDACT_CCP_LOW );

		//Set output mode to for singal generator output
		TIMA0->COUNTERREGS.OCTL_01[channel] = (GPTIMER_OCTL_01_CCPO_FUNCVAL |
											   GPTIMER_OCTL_01_CCPOINV_NOINV |
												 GPTIMER_OCTL_01_CCPIV_LOW);
							
		

		if(channel == 0)
		{
			// Set IOMUX for GPIOB DIO12 to be connected to TIMA0 CCP0
			IOMUX->SECCFG.PINCM[IOMUX_PINCM25] |= (	IOMUX_PINCM25_PF_TIMA0_CCP0 | 
												IOMUX_PINCM_PC_CONNECTED);
			
			TIMA0->COMMONREGS.CCPD |= GPTIMER_CCPD_C0CCP0_OUTPUT;

		}





		else if(channel == 1)
		{
			// Set IOMUX for GPIOB DIO12 to be connected to TIMA0 CCP1
			IOMUX->SECCFG.PINCM[IOMUX_PINCM29] |= (	IOMUX_PINCM29_PF_TIMA0_CCP1 | 
												IOMUX_PINCM_PC_CONNECTED);
  
			TIMA0->COMMONREGS.CCPD |= GPTIMER_CCPD_C0CCP1_OUTPUT;
		}


	}

	else if(channel == 2 || channel == 3)
	{

		TIMA0->COUNTERREGS.CC_23[channel - 2] = (uint32_t) (load * (1-percentDutyCycle));

		//Set compare mode
		TIMA0->COUNTERREGS.CCCTL_23[channel - 2] |= GPTIMER_CCCTL_23_COC_COMPARE;


		//Action on Load - high, Action on Compare - low
		TIMA0->COUNTERREGS.CCACT_23[channel - 2] |= (GPTIMER_CCACT_23_LACT_CCP_HIGH | GPTIMER_CCACT_23_CDACT_CCP_LOW );

		//Set output mode to for singal generator output
		TIMA0->COUNTERREGS.OCTL_23[channel - 2] = (GPTIMER_OCTL_23_CCPO_FUNCVAL |
											   GPTIMER_OCTL_23_CCPOINV_NOINV |
												 GPTIMER_OCTL_23_CCPIV_LOW);

		if(channel == 2)
		{
			// Set IOMUX for GPIOB DIO12 to be connected to TIMA0 CCP2
			IOMUX->SECCFG.PINCM[IOMUX_PINCM43] |= (	IOMUX_PINCM43_PF_TIMA0_CCP2 | 
												IOMUX_PINCM_PC_CONNECTED);
			
			TIMA0->COMMONREGS.CCPD |= GPTIMER_CCPD_C0CCP2_OUTPUT;

		}



		else if(channel == 3)
		{
			// Set IOMUX for GPIOB DIO13 to be connected to TIMA0 CCP1
			IOMUX->SECCFG.PINCM[IOMUX_PINCM30] |= (	IOMUX_PINCM30_PF_TIMA0_CCP3 | 
												IOMUX_PINCM_PC_CONNECTED);

			TIMA0->COMMONREGS.CCPD |= GPTIMER_CCPD_C0CCP3_OUTPUT;
		}


	}
			// Enable timer
		TIMA0->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_EN_ENABLED;

}




void TIMA1_PWM_init(uint8_t channel, uint32_t period, uint32_t prescaler, double percentDutyCycle)
{
    if (!(TIMA1->GPRCM.PWREN & GPTIMER_PWREN_ENABLE_MASK))
    {
        TIMA1->GPRCM.RSTCTL |= (GPTIMER_RSTCTL_KEY_UNLOCK_W | GPTIMER_RSTCTL_RESETASSERT_ASSERT | GPTIMER_RSTCTL_RESETSTKYCLR_CLR);

        TIMA1->GPRCM.PWREN |= (GPTIMER_PWREN_KEY_UNLOCK_W |  GPTIMER_PWREN_ENABLE_ENABLE);
    }

    TIMA1->CLKSEL |= GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE;
    TIMA1->CLKDIV |= GPTIMER_CLKDIV_RATIO_DIV_BY_1;
    TIMA1->COMMONREGS.CPS |= prescaler;

    TIMA1->COMMONREGS.CCLKCTL |= GPTIMER_CCLKCTL_CLKEN_ENABLED;
    TIMA1->COUNTERREGS.CTRCTL = GPTIMER_CTRCTL_EN_DISABLED;

    TIMA1->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CM_MASK;
    TIMA1->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_REPEAT_REPEAT_1;
    TIMA1->COUNTERREGS.CTRCTL &= ~GPTIMER_CTRCTL_CVAE_MASK;

    uint32_t clk = SYSCTL_SYSCLK_getMCLK();
	// Microseconds to timer ticks conversion
    uint32_t load = period * (clk / (1000000 * (prescaler + 1)) * (TIMA1->CLKDIV + 1));

    TIMA1->COUNTERREGS.LOAD = load;

    if (channel == 0)
    {
        TIMA1->COUNTERREGS.CC_01[channel] = (uint32_t)(load * (1.0 - percentDutyCycle));

        TIMA1->COUNTERREGS.CCCTL_01[channel] |= GPTIMER_CCCTL_01_COC_COMPARE;

        TIMA1->COUNTERREGS.CCACT_01[channel] |= (GPTIMER_CCACT_01_LACT_CCP_HIGH |
            							   GPTIMER_CCACT_01_CDACT_CCP_LOW);

        TIMA1->COUNTERREGS.OCTL_01[0] =
            (GPTIMER_OCTL_01_CCPO_FUNCVAL |
             GPTIMER_OCTL_01_CCPOINV_NOINV |
             GPTIMER_OCTL_01_CCPIV_LOW);

        // Configure PB4 as TIMA1 CCP0 output
		IOMUX->SECCFG.PINCM[IOMUX_PINCM17] = (IOMUX_PINCM17_PF_TIMA1_CCP0 |
    										  IOMUX_PINCM_PC_CONNECTED);

        TIMA1->COMMONREGS.CCPD |=
            GPTIMER_CCPD_C0CCP0_OUTPUT;
    }

    TIMA1->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_EN_ENABLED;
}




void TIMA0_PWM_DutyCycle(uint8_t channel, double percentDutyCycle)
{
    uint32_t load = TIMA0->COUNTERREGS.LOAD;
    uint32_t compareVal = (uint32_t)(load * (1.0 - percentDutyCycle));

    if (channel == 0 || channel == 1)
    {
        TIMA0->COUNTERREGS.CC_01[channel] = compareVal;
    }
    else if (channel == 2 || channel == 3)
    {
        TIMA0->COUNTERREGS.CC_23[channel - 2] = compareVal;
    }
}



void TIMA1_PWM_DutyCycle(uint8_t channel, double percentDutyCycle)
{
    uint32_t load = TIMA1->COUNTERREGS.LOAD;

    uint32_t compareVal = (uint32_t)(load * (1.0 - percentDutyCycle));

    if (channel == 0)
    {
        TIMA1->COUNTERREGS.CC_01[channel] = compareVal;
    }
}