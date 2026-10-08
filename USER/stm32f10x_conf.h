#ifndef __STM32F10X_CONF_H
#define __STM32F10X_CONF_H

/* Thu vien Standard Peripheral Library can dung */
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

/* Kiem tra tham so */
#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line);

#define assert_param(expr) \
    ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))

#else

#define assert_param(expr) ((void)0)

#endif

#endif /* __STM32F10X_CONF_H */