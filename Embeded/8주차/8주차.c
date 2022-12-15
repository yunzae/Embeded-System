#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "touch.h"
#include "lcd.h"


int color[12] = {WHITE, CYAN, BLUE, RED, MAGENTA, LGRAY, GREEN, YELLOW, BROWN, BRRED, GRAY};
uint16_t value = 100;

/* function prototype */
void RCC_Configure(void);
void GPIO_Configure(void);
void NVIC_Configure(void);

//---------------------------------------------------------------------------------------------------

void RCC_Configure(void)
{
   /* Alternate Function IO clock enable */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE); // ADC1, port C RCC ENABLE
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
   // ������ LCD�� �ʿ��� ��Ʈ���� lcd.c���� Ȱ��ȭ �ȴ�.
}

void GPIO_Configure(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // �Ƴ��α� �Է� ����
   GPIO_Init(GPIOC, &GPIO_InitStructure);        // C0��Ʈ Ȱ��ȭ, ���������� PC0�� ������ ��ȹ
}

void ADC_Configure(void)
{
   // Analog to Digital Converter
   ADC_InitTypeDef ADC_InitStruct;

   // ADC_StructInit(&ADC_InitStruct);
   ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                  // slave-master�� ���� ���� ADC
   ADC_InitStruct.ADC_ScanConvMode = DISABLE;                       // ����ä���̹Ƿ� ��Ȱ��ȭ
   ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                  // �� ���� Ʈ���ŷ� �� ä���� ���ø� ����
   ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // �ܺ� �Է��ɿ� ���� Ʈ���� ��Ȱ��ȭ
   ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;              // Default
   ADC_InitStruct.ADC_NbrOfChannel = 1;                             // ä���� �ϳ�

   ADC_Init(ADC1, &ADC_InitStruct); // �� ������ ADC1�� ����

   ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_28Cycles5); // ä�� �켱���� ����, 10ä�� �ܵ����

   // ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE); // ���к��� �ڵ鷯 ȣ�� ������ ���� �ּ�ó��

   ADC_Cmd(ADC1, ENABLE); // ADC1 Ȱ��ȭ

   // Calibration reset & start
   ADC_ResetCalibration(ADC1);

   while (ADC_GetResetCalibrationStatus(ADC1))
      ;

   ADC_StartCalibration(ADC1);

   while (ADC_GetCalibrationStatus(ADC1))
      ;

   ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void NVIC_Configure(void)
{

   NVIC_InitTypeDef NVIC_InitStructure;

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

   NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn; // ADC IRQ ���ͷ�Ʈ Ȱ��ȭ
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}

void ADC1_2_IRQHandler(void)
{
   // printf("Handle\n");
   if (ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET)
   {                                        // End Of Conversion, ADC��ȯ�� ��������,
      value = ADC_GetConversionValue(ADC1); // value�� �������� �� �Է�
      ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
   }
}

int main(void)
{

   SystemInit();
   RCC_Configure();
   GPIO_Configure();
   ADC_Configure();
   NVIC_Configure();

   //-----------------

   LCD_Init();            // LCD �ʱ�ȭ
   Touch_Configuration(); // ��ġ ����
   Touch_Adjust();        // ȭ�� ��ġ ���� ���߱�
   LCD_Clear(WHITE);      // LCD ��� �ʱ�ȭ

   //-----------------

   uint16_t pos_temp[2]; // x, y��ǥ�� ���� �迭

   while (1)
   {
      LCD_ShowString(40, 40, "WED_Team10", MAGENTA, WHITE); // ���� ���

      Touch_GetXY(&pos_temp[0], &pos_temp[1], 1);                        // ��ġ ��ǥ �޾Ƽ� �迭�� �Է�
      Convert_Pos(pos_temp[0], pos_temp[1], &pos_temp[0], &pos_temp[1]); // ���� ��ǥ�� LCD ũ�⿡ �°� ��ȯ
      Draw_Big_Point(pos_temp[0], pos_temp[1]);                          // ���� ��ǥ�� ū ���� ����Ѵ�. �̶� touch.c�� Draw_Big_Point�Լ��� �����Ͽ� �̿��ߴ�.

      LCD_ShowNum(40, 60, (u32)pos_temp[0], 3, BLUE, WHITE); // x��ǥ ���
      LCD_ShowNum(40, 80, (u32)pos_temp[1], 3, BLUE, WHITE); // y��ǥ ���

      ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); // ADC ��ȯ�� �������� ���ͷ�Ʈ �߻�
      LCD_ShowNum(40, 100, value, 4, BLUE, WHITE);
      ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE); // ���к��� ���ͷ�Ʈ ������ ���� ��Ȱ��ȭ
   }
   return 0;
}
