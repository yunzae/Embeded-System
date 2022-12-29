#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#include "stdlib.h"

#include "stdio.h"

#include "stm32f10x.h"

#include "core_cm3.h"

#include "misc.h"

#include "stm32f10x_gpio.h"

#include "stm32f10x_rcc.h"

#include "stm32f10x_exti.h"

#include "stm32f10x_usart.h"

#include "stm32f10x_tim.h"



typedef int bool;

#define true 1;

#define false 0;

//��������=========================================================

bool orderFlag=false;

bool madeFlag=false;

bool drinkArrivalFlag=false;

char orderBuf[255] = "test";



//�������=========================================================

void RCC_Configure_bluetooth(void);

void GPIO_Configure_bluetooth(void);

void USART1_Init(void);

void USART2_Init(void);

void NVIC_Configure_bluetooth(void);

void bluetoothInit(void);

void sendStringUsart(USART_TypeDef* USARTx, char* msg);





void RCC_Configure_bluetooth(void)

{

  /* UART TX/RX port clock enable */

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Alternate Function IO clock enable */

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* USART1 clock enable */

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);



  /* USART2 clock enable */

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

}



void GPIO_Configure_bluetooth(void)

{

  //--Enable GPIOA--

  GPIO_InitTypeDef GPIOA_InitStructure;



  /* UART1 pin setting     �޴���*/

  //TX a9

  GPIO_InitTypeDef GPIO_InitStructure1;

  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_9;

  GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;

  GPIO_Init(GPIOA, &GPIO_InitStructure1);



  //RX a10

  GPIO_InitTypeDef GPIO_InitStructure2;

  GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_10;

  GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure2.GPIO_Mode = (GPIO_Mode_IPD) | (GPIO_Mode_IPU);

  GPIO_Init(GPIOA, &GPIO_InitStructure2);



  /* UART2 pin setting -  �������  �κ�*/

  //TX a2

  GPIO_StructInit(&GPIOA_InitStructure);

  GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_2;

  GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

  GPIO_Init(GPIOA, &GPIOA_InitStructure);



  //RX a3

  GPIO_StructInit(&GPIOA_InitStructure);

  GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_3;

  GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIOA_InitStructure.GPIO_Mode = (GPIO_Mode_IPD) | (GPIO_Mode_IPU);

  GPIO_Init(GPIOA, &GPIOA_InitStructure);

}



void USART1_Init(void)

{

  // Enable the USART1 peripheral

  USART_Cmd(USART1, ENABLE);



  // TODO: Initialize the USART using the structure 'USART_InitTypeDef' and the function 'USART_Init'

  USART_InitTypeDef USART1_InitStructure;

  USART1_InitStructure.USART_BaudRate = 9600;                      // Baud Rate 9600

  USART1_InitStructure.USART_WordLength = USART_WordLength_8b;     // word length 8bit

  USART1_InitStructure.USART_StopBits = USART_StopBits_1;          // stop bit 1bit

  USART1_InitStructure.USART_Parity = USART_Parity_No;             // no parity bits

  USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // rx&tx mode

  USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  USART_Init(USART1, &USART1_InitStructure); // USART1



  // TODO: Enable the USART1 RX interrupts using the function 'USART_ITConfig' and the argument value 'Receive Data register not empty interrupt'

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

}



void USART2_Init(void)

{

  // Enable the USART2 peripheral

  USART_Cmd(USART2, ENABLE);



  // TODO: Initialize the USART using the structure 'USART_InitTypeDef' and the function 'USART_Init'

  USART_InitTypeDef USART2_InitStructure;

  USART2_InitStructure.USART_BaudRate = 9600;                      // Baud Rate 9600

  USART2_InitStructure.USART_WordLength = USART_WordLength_8b;     // word length 8bit

  USART2_InitStructure.USART_StopBits = USART_StopBits_1;          // stop bit 1bit

  USART2_InitStructure.USART_Parity = USART_Parity_No;             // no parity bits

  USART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // rx&tx mode

  USART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  USART_Init(USART2, &USART2_InitStructure); // USART2



  // TODO: Enable the USART2 RX interrupts using the function 'USART_ITConfig' and the argument value 'Receive Data register not empty interrupt'

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

}



void NVIC_Configure_bluetooth(void)

{



  NVIC_InitTypeDef NVIC_InitStructure;



    // UART1

    // 'NVIC_EnableIRQ' is only required for USART setting

    NVIC_EnableIRQ(USART1_IRQn);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    //

    // // UART2

    NVIC_EnableIRQ(USART2_IRQn);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);





 }







void bluetoothInit(void)

{

  RCC_Configure_bluetooth();

  GPIO_Configure_bluetooth();

  NVIC_Configure_bluetooth();

  USART1_Init();

  USART2_Init();



}



//���÷κ��� �޼����� �޾��� ��(�ֹ�)

int bufi = 0;



void USART1_IRQHandler() {
    printf("bluetooth start\n\n");
    
   int word;

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
          printf("check\n");

         // the most recent received data by the USART1 peripheral

         if(!orderFlag){

           word = USART_ReceiveData(USART1);
           //word = USART1_receive();
           printf("%c     sdfdsfdfdfds\n",word);
           printf("%d     sdfdsfdfdfds\n",word);
           USART_SendData(USART1, word);
           if (word == '0') printf("this is 0\n");
           else if (word == 0) printf("this is number 0 (or null )\n");
           if (word == '/'){

              bufi = 0;

              orderFlag=true;

              printf("orderFlag True" );
              

            }else{

              orderBuf[bufi] = word;

              bufi++;
              printf("bufi=%d\n",bufi );
              
            }
           

          // clear 'Read data register not empty' flag

          USART_ClearITPendingBit(USART1,USART_IT_RXNE);

        }
        
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
        

    }
    else printf("no text sended\n");

}

//�ڵ����κ��� �޼����� �޾��� ��(��� �Ϸ�)

void USART2_IRQHandler() {

   char word;

    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){

      if(madeFlag){

         // the most recent received data by the USART2 peripheral

          word = USART_ReceiveData(USART2);

          if (word == '\n'){

              sendStringUsart(USART1,"ENJOY!\n");

              printf("ENJOY!" );

              orderFlag=false;

              printf("orderFlag False" );

              madeFlag=false;

              printf("madeFlag False" );

              drinkArrivalFlag=false;

              printf("drinkArrivalFlag False" );


          }

      }

      else{

        word = USART_ReceiveData(USART2);

        if (word == '\n'){

            drinkArrivalFlag=true;

            printf("drinkArrivalFlag True" );

        }



      }

      // clear 'Read data register not empty' flag

      USART_ClearITPendingBit(USART2,USART_IT_RXNE);

    }

}



void sendStringUsart(USART_TypeDef* USARTx, char* msg) {

  char *tmp = &msg[0];

  while (*tmp != '\0') {

    USART_SendData(USARTx, *tmp);

    /* Wait till TC is set */

    while ((USARTx->SR & USART_SR_TC) == 0);

    tmp++;

  }

}





//��������===============================================================
void startPump1();
void stopPump();

/*Base Address*/
#define RCC_Base_APB2 0x40021000 
#define GPIOC_Base 0x40011000
#define GPIOD_Base 0x40011400
#define GPIOA_Base 0x40010800
/*RCC*/
#define RCC_APB2_OFFSET 0x18
#define RCC_APB2 ((volatile unsigned *)(RCC_Base_APB2 + RCC_APB2_OFFSET)) //clock
#define RCC_APB2_IOPCEN 0x00000010
#define RCC_APB2_IOPDEN 0x00000020


#define GPIOx_CRL_ADDR_OFFSET 0x00
#define GPIOx_CRH_ADDR_OFFSET 0x04

#define GPIOC_CRL ((volatile unsigned *)(GPIOC_Base + GPIOx_CRL_ADDR_OFFSET)) //����� ���
#define GPIOD_CRL ((volatile unsigned *)(GPIOD_Base + GPIOx_CRL_ADDR_OFFSET))
#define GPIOA_CRH ((volatile unsigned *)(GPIOA_Base + GPIOx_CRH_ADDR_OFFSET))
#define GPIOD_CRH ((volatile unsigned *)(GPIOD_Base + GPIOx_CRH_ADDR_OFFSET))

#define GPIOx_BSRR_OFFSET 0x10 
#define GPIOx_BRR_OFFSET 0x14
#define GPIOD_BSRR ((volatile unsigned *)(GPIOD_Base + GPIOx_BSRR_OFFSET))//bit set
#define GPIOD_BRR  ((volatile unsigned *)(GPIOD_Base + GPIOx_BRR_OFFSET)) //bit reset
#define GPIOA_BSRR ((volatile unsigned *)(GPIOA_Base + GPIOx_BSRR_OFFSET))//bit set
#define GPIOA_BRR  ((volatile unsigned *)(GPIOA_Base + GPIOx_BRR_OFFSET)) //bit reset

#define BIT_2 0x00000004
#define BIT_3 0x00000008
#define BIT_4 0x00000010
#define BIT_5 0x00000020
#define BIT_7 0x00000080
#define BIT_8 0x00000100
#define BIT_9 0x00000200
#define BIT_10 0x00000400
#define BIT_11 0x00000800
#define BIT_12 0x00001000
#define BIT_13 0x00002000
#define BIT_15 0x00008000

#define GPIOx_IDR_OFFSET 0x08
#define GPIOC_IDR ((volatile unsigned *)(GPIOC_Base + GPIOx_IDR_OFFSET)) //high low
#define GPIOD_IDR ((volatile unsigned *)(GPIOD_Base + GPIOx_IDR_OFFSET)) //high low




  

void RCC_Configure_motor(void);

void GPIO_Configure_motor1(void);

void motorInit(void);



void RCC_Configure_motor(void)

{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

}



void GPIO_Configure_motor1(void)

{

  //--Enable GPIOE--

  GPIO_InitTypeDef GPIOD_InitStructure;



  //����

  GPIO_StructInit(&GPIOD_InitStructure);

  GPIOD_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;

  GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_Init(GPIOD, &GPIOD_InitStructure);



}






void motorInit(void)

{

  RCC_Configure_motor();

  GPIO_Configure_motor1();

  printf("MOTOR INIT\n");
  GPIO_SetBits(GPIOD, GPIO_Pin_4);
  GPIO_SetBits(GPIOD, GPIO_Pin_5);
  GPIO_SetBits(GPIOD, GPIO_Pin_6);
  GPIO_SetBits(GPIOD, GPIO_Pin_7);


}




void delayTime(uint32_t msTime);
uint32_t usTime = 0; //pin setȮ���ϰ� �����


void startPump1(){

  uint8_t val = RESET;
  uint32_t prev=0;
   delayTime(200);
  GPIO_ResetBits(GPIOD, GPIO_Pin_4);
  printf("start pump1!!\n");
  

}
void startPump2(){

  uint8_t val = RESET;
  uint32_t prev=0;
   delayTime(200);
  GPIO_ResetBits(GPIOD, GPIO_Pin_5);
  printf("start pump2!!\n");
  


}
void startPump3(){

  uint8_t val = RESET;
  uint32_t prev=0;
   delayTime(200);
  GPIO_ResetBits(GPIOD, GPIO_Pin_6);
  printf("start pump3!!\n");
  


}
void startPump4(){
  uint8_t val = RESET;
  uint32_t prev=0;
   delayTime(200);
  GPIO_ResetBits(GPIOD, GPIO_Pin_7);
  printf("start pump4!!\n");
  


}





//������ �۵��ѰŸ� ������Ŵ, ��Ȯ�� �� ��ž��Ű���� stop1,2,3,4 ���θ������� , �ٵ� ���⼭�� ���ص� ����

void stopPump1(){

  delayTime(200);
  printf("stop pump1!!!!!!!!!!!!!!!!!\n");
  GPIO_SetBits(GPIOD, GPIO_Pin_4);

  delayTime(500);

}


void stopPump2(){
  
  delayTime(200);
  printf("stop pump2!!!!!!!!!!!!!!!!!\n");
  GPIO_SetBits(GPIOD, GPIO_Pin_5);
  delayTime(500);

}

void stopPump3(){
  

  delayTime(200);
  printf("stop pump3!!!!!!!!!!!!!!!!!\n");
  GPIO_SetBits(GPIOD, GPIO_Pin_6);
  delayTime(500);

}

void stopPump4(){
  

  delayTime(200);
  printf("stop pump4!!!!!!!!!!!!!!!!!\n");
  GPIO_SetBits(GPIOD, GPIO_Pin_7);
  delayTime(500);

}

//�����ĸ� ���� Ÿ�̸�=====================================================================

void TIM2_Configure(void) ;

void TIM2_IRQHandler();

//uint32_t usTime = 0; //�ּ������ؾ���



void RCC_Configure_timer(void){

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

}



void NVIC_Configure_timer(void){

    NVIC_InitTypeDef NVIC_InitStructure;

    //Ÿ�̸�

    NVIC_EnableIRQ(TIM2_IRQn);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // �켱������ ���� ����.

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

}



void TIM2_Configure(void) {

  // ª�� �ð� ���� ������ �ʿ��ϹǷ� 1us�� ����ٰ� ����

  TIM_TimeBaseInitTypeDef TIM_InitStructure;

  TIM_InitStructure.TIM_Prescaler = 72;

  TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_InitStructure.TIM_Period = 1;

  TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

  TIM_TimeBaseInit(TIM2, &TIM_InitStructure);



  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  TIM_Cmd(TIM2, ENABLE);

}



void timerInit(void){

      RCC_Configure_timer();

      NVIC_Configure_timer();

      TIM2_Configure();

    }



void TIM2_IRQHandler() {

  //printf("Time\n");

  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {

    //printf("in if:%d\n",usTime);

    usTime++; // 1us���� Interrupt�� �ɸ����� �����صξ����� usTime�� �����ϴ� ����

  }

  //printf("out %d\n",usTime);

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

}







void delayTime(uint32_t msTime){
 
    uint32_t prev_time = usTime;

   // printf("delay: %d\n",usTime);

    while(1){

      if(usTime - prev_time > 500*msTime) break;

    }

}



//������=======================================================================

#define PORT_ULTRA GPIOB
#define PIN_TRIG GPIO_Pin_15
#define PIN_ECHO GPIO_Pin_13



void RCC_Configure_ultra(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}
void GPIO_Configure_ultra(void){
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = PIN_TRIG; // TRIG
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // ������ �߻�
     GPIO_Init(PORT_ULTRA, &GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = PIN_ECHO; // Echo
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // input pull down ������ �ޱ�
     GPIO_Init(PORT_ULTRA, &GPIO_InitStructure);

}
void ultraInit(void){
      RCC_Configure_ultra();
      GPIO_Configure_ultra();
    }


int readDistance(uint16_t GPIO_PIN_TRIG, uint16_t GPIO_PIN_ECHO){
    printf("distance\n");
    sendStringUsart(USART1,"distance\n");
  //uint8_t val = GPIO_ReadInputDataBit(GPIOE, GPIO_PIN_ECHO);
  uint8_t val = RESET;
  uint32_t prev=0;
  
  GPIO_ResetBits(GPIOB, PIN_TRIG);
  printf("test wave_trig input 0?: %x\n", GPIO_ReadInputDataBit(GPIOB, PIN_TRIG));
  delayTime(2);
  GPIO_SetBits(GPIOB, PIN_TRIG);
  printf("test wave_trig input 1?: %x\n", GPIO_ReadInputDataBit(GPIOB, PIN_TRIG));
  delayTime(10);
  GPIO_ResetBits(GPIOB, PIN_TRIG);
  
  prev = usTime;
  while (!GPIO_ReadInputDataBit(GPIOB, GPIO_PIN_ECHO)) {
    if(usTime - prev >= 1000000) 
    {
      printf("timeout\n"); 
      return -1;
    }
  }
  
  prev = usTime;
  while (GPIO_ReadInputDataBit(GPIOB, GPIO_PIN_ECHO)) {
    //printf("test wave input 1?: %x\n", GPIO_ReadInputDataBit(GPIOB, GPIO_PIN_ECHO));
    if(usTime - prev >= 5000) break;
  }
  
  // float distance = (usTime-prev)*34/1000;
  float distance = (usTime-prev)*58.0; 
  printf("distance: %f\n",distance);
 
   return distance; // �ٽ� SET -> RESET�� �ɶ����� �ð� (usTime -prev)���� distance����ؼ� ��ȯ.
  

  
  
  //---------------------------
  
  
  
    printf("1\n");
    //uint32_t prev = 0;
    printf("2\n");
    GPIO_SetBits(PORT_ULTRA, GPIO_PIN_TRIG);
    printf("3\n");
    GPIO_ResetBits(PORT_ULTRA, GPIO_PIN_ECHO);
    printf("4\n");
    delayTime(10);
    printf("5\n");
    GPIO_ResetBits(PORT_ULTRA, GPIO_PIN_TRIG);
    printf("6\n");
    //uint8_t val = GPIO_ReadInputDataBit(GPIOE, GPIO_PIN_ECHO);

    /* ����Ʈ �߻� ���� ���ڴ� HIGH ������ ������.
    ���� ����Ʈ�� �߻��ߴ��� �˱� ���� while���� ����
    ���ڰ� LOW ����(RESET)�� ���� ��(����Ʈ �߻� X)�� �ݺ����� �ӹ��� �ϰ�
    ���ڰ� HIGH ����(SET)�� ���� ��(����Ʈ �߻�)�� �ݺ����� Ż���Ѵ�.*/
    printf("before\n");
    while(GPIO_ReadInputDataBit(PORT_ULTRA, GPIO_PIN_ECHO) == RESET);
    printf("after\n");
    // �ݺ����� Ż���� ���Ŀ� �ð� ������ ���� prev ������ ���� �ð��� �����Ѵ�.
    prev = usTime;

    /* ���ڿ� ����Ʈ�� �ٽ� ������ ���ڴ� LOW ������ ������.
    ���� ���ڰ� HIGH ����(SET)�� ������ ���� ����Ʈ�� ���� ���� ���� �Ŵϱ�
    �ݺ����� �ӹ��� �ϰ� ���ڰ� LOW ������ ������ �� ����Ʈ�� ���Դٴ�
    �ǹ̴ϱ� �ݺ����� Ż���� �Ÿ��� ����Ѵ�.*/
    while(GPIO_ReadInputDataBit(PORT_ULTRA, GPIO_PIN_ECHO) != RESET);

    // �Ÿ��� (����Ʈ �պ��Ÿ�) / 2 / 0.034cm/us �� ��������.
    int d = (usTime - prev)*34/1000;
    printf("distance: %d\n",d);
    return d; //cm
}





//��뺯��,�Լ�=================================================================

double ratio[4]; //[���ֺ���,��п��ͺ���,��,��]

double fullTime = 20000; // ������ ���� ����ä��µ� �ɸ��� �ð�

void selectMenu(){
  printf("\nselect Menu() call");
    printf("\n % s\n",orderBuf);
    //printf("%s",type(orderBuf));
    
    sendStringUsart(USART1,"Call selectMenu()\n");
    sendStringUsart(USART1,orderBuf);

        switch (orderBuf[0]) {
    case '0':
      ratio[0] = 1.0;
      ratio [1] = 0.0;
      ratio [2] = 0.0;
      ratio [3] = 0.0;
      break;
    case '1':
      ratio[0] = 0.0;
      ratio [1] = 1.7;
      ratio [2] = 0.0;
      ratio [3] = 0.0;
      break;
    case '2': 
      ratio[0] = 0.4;
      ratio [1] = 1.2;
      ratio [2] = 0.0;
      ratio [3] = 0.0;
      break;
    case '3':
      ratio[0] = 0.3;
      ratio [1] = 0.4;
      ratio [2] = 0.3;
      ratio [3] = 0.3;
      break;
    }
    /*
    char* orders=strtok(orderBuf,","); //orderBuf="0.3,0.7,0,0"

    int i=0;

    while(orders!=NULL){

        ratio[i]=atof(orders);
        printf("%dth recipe->%d",i,ratio[i]);
        orders=strtok(NULL,",");
        i++;

    }
*/

}





void startDrive(){

    sendStringUsart(USART2, "1\n") ;

    printf("gogogo car" );

    /*

    while(1){

        USART_SendData(USART2, data[i]); // �κ����� �޼��� ����

        if(data[i]=='\n') break;

        i++;

    }

    */



}





int arrivalAlert(){

  int distance=8;

  printf("Arrival Start\n");
  

    while ( 1 ) {

         distance= readDistance(PIN_TRIG, PIN_ECHO);
         printf("%d\n",distance);
          
    
         if (distance<7 && drinkArrivalFlag) {

           break;

         }

    }

    printf("arrival!\n" );

    sendStringUsart(USART1, "making start!\n") ;

    printf("making start" );
    return distance;

}







void makeHappyPotion(){
  sendStringUsart(USART1,"make happy potion!\n");
  
  delayTime(3000);

  //pump1 �۵�

  startPump1();

  printf("pump1 start\n" );

  //delayTime(300);
  delayTime(fullTime*ratio[0]);

  stopPump1();

  printf("pump1 stop\n" );
  
  //pump2 �۵�
  
  startPump2();

  printf("pump2 start\n" );

  //delayTime(300);
  delayTime(fullTime*ratio[1]);

  stopPump2();

  printf("pump2 stop\n" );
  
  //pump3 �۵�
    startPump3();

  printf("pump3 start\n" );

  //delayTime(300);
  delayTime(fullTime*ratio[2]);

  stopPump3();

  printf("pump3 stop\n" );

  //pump4 �۵�
    startPump4();

  printf("pump4 start\n" );

  //delayTime(300);
  delayTime(fullTime*ratio[3]);

  stopPump4();

  printf("pump4 stop\n" );


  sendStringUsart(USART1, "making complete!\n") ;

  printf("making complete" );

  sendStringUsart(USART2, "2\n");

  madeFlag=true;
  orderFlag=false;

}

//����======================================================================



int main(void)

{
    *GPIOD_CRH &= ~0xF0F0F000;
    
    
    printf("main start\n");



    SystemInit();

    /* NVIC�� Priority Group Config�� ��� ������ ����� */

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /*������� ����*/

    bluetoothInit();

    /*��������*/
    motorInit();

    /*Ÿ�̸�*/

    timerInit();

    /*������*/

    ultraInit();
  

    //sendStringUsart(USART2, "ATD\n");

    readDistance(PIN_TRIG, PIN_ECHO);

    while(1){
        GPIO_SetBits(GPIOD, GPIO_Pin_4);
        GPIO_SetBits(GPIOD, GPIO_Pin_5);
        GPIO_SetBits(GPIOD, GPIO_Pin_6);
        GPIO_SetBits(GPIOD, GPIO_Pin_7);

      //sendStringUsart(USART2, "ATD\n");

      //printf("Start\n");

      if(orderFlag){

        selectMenu(); //�޴��Է�, �޴������� ����� ���� �����

      //startDrive(); //�κ��� ��� ��ȣ ����
      //while(1){
        
       
        while (readDistance(PIN_TRIG, PIN_ECHO) > 7000 );
      //}
      //}
       // if (arrivalAlert()) // �κ��� ���漭�� �������� �� �޴������� �˸�����
      //  {  
       makeHappyPotion(); // �ֹ��� �°� �� ����
      //  }

        //while(orderFlag){} //��� �Ϸ���� ���, ���ͷ�Ʈ����

      //}


      }

    }

}
//USART1_IRQHandler
//startPump11
//readDistance