#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

/* =========================================================
   1. Khai bao cac ham
   ========================================================= */
void GPIO_Config(void);
void LED_Blink(uint16_t pin, float frequency);

void Task_LED1(void *pvParameters);
void Task_LED2(void *pvParameters);
void Task_LED3(void *pvParameters);


/* =========================================================
   2. Ham main
   - Khoi tao GPIO
   - Tao 3 task
   - Khoi dong FreeRTOS
   ========================================================= */
int main(void)
{
    GPIO_Config();

    /* LED PA0 nhap nhay 0.1 Hz */
    xTaskCreate(Task_LED1, "LED1", 128, NULL, 1, NULL);

    /* LED PA1 nhap nhay 1 Hz */
    xTaskCreate(Task_LED2, "LED2", 128, NULL, 1, NULL);

    /* LED PA2 nhap nhay 10 Hz */
    xTaskCreate(Task_LED3, "LED3", 128, NULL, 1, NULL);

    /* Khoi dong bo lap lich FreeRTOS */
    vTaskStartScheduler();

    while (1);
}


/* =========================================================
   3. Khoi tao GPIO
   PA0, PA1, PA2 duoc cau hinh Output Push-Pull
   ========================================================= */
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Cap clock cho GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Chon 3 chan dieu khien LED */
    GPIO_InitStruct.GPIO_Pin =
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Tat ca LED luc khoi dong */
    GPIO_ResetBits(GPIOA,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
}


/* =========================================================
   4. Ham nhap nhay LED dung chung

   pin       : chan LED
   frequency : tan so nhap nhay (Hz)

   Vi LED phai ON va OFF trong 1 chu ky:
        delay = T/2 = 1/(2*f)

   Doi sang ms:
        delay = 500/frequency
   ========================================================= */
void LED_Blink(uint16_t pin, float frequency)
{
    uint32_t delay_ms;

    /* Tinh nua chu ky */
    delay_ms = (uint32_t)(500.0f / frequency);

    /* Dao trang thai LED */
    GPIO_WriteBit(
        GPIOA,
        pin,
        (BitAction)!GPIO_ReadOutputDataBit(GPIOA, pin)
    );

    /* Delay FreeRTOS - Task khac van duoc chay */
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}


/* =========================================================
   5. TASK 1
   LED PA0 - tan so 0.1 Hz
   Toggle moi 5 giay
   ========================================================= */
void Task_LED1(void *pvParameters)
{
    while (1)
    {
        LED_Blink(GPIO_Pin_0, 0.1f);
    }
}


/* =========================================================
   6. TASK 2
   LED PA1 - tan so 1 Hz
   Toggle moi 500 ms
   ========================================================= */
void Task_LED2(void *pvParameters)
{
    while (1)
    {
        LED_Blink(GPIO_Pin_1, 1.0f);
    }
}


/* =========================================================
   7. TASK 3
   LED PA2 - tan so 10 Hz
   Toggle moi 50 ms
   ========================================================= */
void Task_LED3(void *pvParameters)
{
    while (1)
    {
        LED_Blink(GPIO_Pin_2, 10.0f);
    }
}