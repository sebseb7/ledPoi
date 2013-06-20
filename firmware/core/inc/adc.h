/****************************************************************************
 *   $Id:: adc.h 4088 2010-07-31 01:31:48Z nxp28433                         $
 *   Project: NXP LPC13Uxx ADC example
 *
 *   Description:
 *     This file contains ADC code header definition.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __ADC_H 
#define __ADC_H

#define ADC_INTERRUPT_FLAG    1	/* 1 is interrupt driven, 0 is polling */
#define BURST_MODE            1 /* Burst mode works in interrupt driven mode only. */
#define ADGINTEN              0	/* global DONE flag generate interrupt */
#define TENBIT_MODE           0	/* 10-bit mode */
#define LOWPWR_MODE           0	/* Low-power mode */
#define ADC_DEBUG             1
#define ADC_DEBUG_CLEAR_CNT   (100) /* Number of samples until statistics are cleared */
#define ADC_DEBUG_UPDATE_CNT  (5000) /* Number of samples until statistics are cleared */

#define ADC_OFFSET            0x10
#define ADC_INDEX             4

#define ADC_DONE              0x80000000
#define ADC_OVERRUN           0x40000000
#define ADC_ADINT             0x00010000

#define ADC_NUM               8			/* for LPC13Uxx */
//#define ADC_CLK               4000000		/* set to 4.0Mhz - Pass at 24MHz */
//#define ADC_CLK               6000000		/* set to 6.0Mhz - Pass at 36MHz */
//#define ADC_CLK               8000000		/* set to 8.0Mhz - Pass at 48MHz */
//#define ADC_CLK               10000000		/* set to 10.0Mhz - Pass at 60MHz */
#define ADC_CLK               12000000		/* set to 12.0Mhz - Pass at 72MHz */

extern void ADC_IRQHandler( void );
extern void ADCInit( uint32_t ADC_Clk );
extern uint32_t ADCRead( uint8_t channelNum );
extern void ADCBurstRead( void );
#endif /* end __ADC_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
