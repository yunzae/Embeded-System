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

#define GPIOC_CRL ((volatile unsigned *)(GPIOC_Base + GPIOx_CRL_ADDR_OFFSET)) //입출력 사용
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

void delay(){
  int i;
  for(i=0;i<10000000;i++){}
}

int main()
{
  *RCC_APB2 |= RCC_APB2_IOPCEN | RCC_APB2_IOPDEN;
  *GPIOC_CRL &= ~0x00F00F00;
  *GPIOC_CRL |= 0x00800800;
  *GPIOD_CRH &= ~0xF0F0F000;
  *GPIOD_CRH |= 0x30308000;
  *GPIOD_BRR |= (BIT_15|BIT_13);
  
  int i = 0;
  while(1) {
        //8번 셋
    if(!(*GPIOC_IDR & BIT_5))
          i=1;
    if(!(*GPIOC_IDR & BIT_2))
          i=2;
    if(!(*GPIOD_IDR & BIT_11)) 
          i=3;
    switch(i)
    {
    case 1:
     *GPIOD_BRR |= 0x2000;     //13번 리셋
      *GPIOD_BSRR |= 0x8000;     //15번 셋
      break;
    case 2:     //시계
     *GPIOD_BRR |= 0x8000;     //15번 리셋
      *GPIOD_BSRR |= 0x2000;     //13번 셋
      break;
    case 3:     //정지
     *GPIOD_BSRR |= 0xa000;     //13, 15번 리셋
      break;
    }
  }
 }
