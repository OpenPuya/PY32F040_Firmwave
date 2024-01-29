/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define  PERIOD_VALUE       (uint32_t)(50 - 1)
#define  PULSE1_VALUE       10
#define  PULSE2_VALUE       20
#define  PULSE3_VALUE       30
#define  PULSE4_VALUE       40

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef sConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief  Main program
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Configure Systemclock */
  APP_SystemClockConfig(); 

  TimHandle.Instance = TIM1;                                                  /* Select TIM1 */
  TimHandle.Init.Period            = 50;                                      /* Auto reload value */
  TimHandle.Init.Prescaler         = 800 - 1;                                 /* Prescaler：800-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  /* Clock division: tDTS=tCK_INT */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      /* CounterMode:Up */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                   /* repetition counter value:1-1 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          /* TIM1_ARR register is not buffered */
  /* Initializes the TIM PWM Time Base */
  if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig.OCMode       = TIM_OCMODE_PWM1;                                     /* Set as PWM1 mode */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 /* OC channel active high */
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;                                  /* Output Compare fast disable */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                /* OCN channel active high */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              /* OC1N channel idle state is low level */
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                               /* OC1 channel idle state is low level */

  sConfig.Pulse = PULSE1_VALUE;                                               /* TIM1_CCR1 value:10，duty cycle:10/50=20% */
  /* Initializes the TIM PWM channel 1 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  sConfig.Pulse = PULSE2_VALUE;                                               /* TIM1_CCR2 value:20,duty cycle:20/50=40% */
  /* Initializes the TIM PWM channel 2 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  sConfig.Pulse = PULSE3_VALUE;                                               /* TIM1_CCR3 value:30,duty cycle:30/50=60% */
  /* Initializes the TIM PWM channel 3 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    APP_ErrorHandler();
  }
  sConfig.Pulse = PULSE4_VALUE;                                               /* TIM1_CCR4 value:40,duty cycle:40/50=80% */
  /* Initializes the TIM PWM channel 4 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_4) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Starts the all channel PWM signal generation. */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_4) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief   Configure systemclock
  * @param   None
  * @retval  None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef  OscInitstruct = {0};
  RCC_ClkInitTypeDef  ClkInitstruct = {0};
  
  OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | 
                                  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
  OscInitstruct.HSEState        = RCC_HSE_OFF;                              /* HSE OFF */
/* OscInitstruct.HSEFreq         = RCC_HSE_16_32MHz; */                     /* HSE clock range 16~32MHz */
  OscInitstruct.HSI48MState     = RCC_HSI48M_OFF;                           /* Disable HSI48M clock */
  OscInitstruct.HSIState        = RCC_HSI_ON;                               /* HSI ON */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                              /* LSE OFF */
/* OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH; */                    /* LSE high drive capability */
  OscInitstruct.LSIState        = RCC_LSI_OFF;                              /* LSI OFF */
  OscInitstruct.PLL.PLLState    = RCC_PLL_OFF;                              /* PLL OFF */
/* OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE; */                    /* HSE oscillator clock selected as PLL clock entry */
/* OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL6; */                         /* PLLVCO = PLL clock entry x 6 */
  /* Initialize the RCC Oscillators */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_HSI;                 /* Select HSI as system clock */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* SYSCLK not divided: HCLK=SYSCLK */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* HCLK not divided: PCLK1=HCLK */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* HCLK divided by 2: PCLK2=HCLK/2 */
  /* Set clock source */
  if(HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Error handling function
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file：Pointer to the source file name
  * @param  line：assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add His own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
