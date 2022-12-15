#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "lcd.h"
#include "touch.h"

int color[12] = {WHITE,CYAN,BLUE,RED,MAGENTA,LGRAY,GREEN,YELLOW,BROWN,BRRED,GRAY};
uint16_t value;
int ledCount = 0;

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
uint16_t prescale;

/* function prototype */
void RCC_Configure(void);
void GPIO_Configure(void);
void NVIC_Configure(void);
void TIM_Configure(void);
void NVIC_Configure(void);
void TIM2_IRQHandler(void);
void delay(void);



//---------------------------------------------------------------------------------------------------

void RCC_Configure(void)
{
    // TODO: Enable the APB2 peripheral clock using the function 'RCC_APB2PeriphClockCmd'
    /* LED */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // Port D
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
}

void GPIO_Configure(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void NVIC_Configure(void) {

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* Enable TIM2 Global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
       
}

void TIM_Configure(void) {

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  int prescale = (uint16_t)(SystemCoreClock / 10000) - 1;
  TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = prescale;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}


void delay()
{
  int i;
  for(i = 0; i < 5000000; ++i) {}
}

uint16_t pos_temp[2]; // x, y좌표를 담을 배열
int led2 = 0;
int led3 = 0;
int cnt = 0;
int isOnOff = 0;
   
   
void TIM2_IRQHandler()
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET ) {
    if(isOnOff) {
      led2 = !led2;
      led3++;
    }
    
    if(led2) {
      GPIO_SetBits(GPIOD, GPIO_Pin_2);
    }
    else {

      GPIO_ResetBits(GPIOD, GPIO_Pin_2);

    }
    if(led3%5==0) {

      if(led3 == 5) {

        GPIO_SetBits(GPIOD, GPIO_Pin_3);
      }
      else if(led3 == 10){

        GPIO_ResetBits(GPIOD, GPIO_Pin_3);

        led3 = 0;
      }
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


int main()
{
   SystemInit();
   RCC_Configure();
   GPIO_Configure();
   TIM_Configure();
   NVIC_Configure();

   //-----------------

   LCD_Init();            // LCD 초기화
   Touch_Configuration(); // 터치 설정
   Touch_Adjust();        // 화면 터치 초점 맞추기
   LCD_Clear(WHITE);      // LCD 배경 초기화

   //-----------------

  char msg_Team[] = "WED_Team10";
  LCD_ShowString(0, 0, msg_Team, color[2], color[0] );

  char msgOn[] = "ON ";
  char msgOff[] = "OFF";

  char msgBtn[] = "BUT";
  
  LCD_DrawRectangle(16, 64, 64, 112);
  LCD_ShowString(32, 76, msgBtn, color[3], color[0] );
   
  

   while (1)
   {
         if (isOnOff)
         {
            LCD_ShowString(0, 32, msgOn, color[3], color[0] );
         }
         else
         {
             LCD_ShowString(0, 32, msgOff, color[3], color[0] );
         }
         
          Touch_GetXY(&pos_temp[0], &pos_temp[1], 1);
          Convert_Pos(pos_temp[0], pos_temp[1], &pos_temp[0], &pos_temp[1]);
          if( pos_temp[0]>= 16 && pos_temp[0] <= 64 && pos_temp[1]>= 64 && pos_temp[1] <= 112) {
          isOnOff = !isOnOff;
      }
   }
   
   return 0;
   
}

