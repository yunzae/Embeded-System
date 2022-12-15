
/*Base Address*/
#define RCC_Base_APB2 0x40021000
#define GPIOC_Base 0x40011000
#define GPIOD_Base 0x40011400

/*RCC*/
#define RCC_APB2_OFFSET 0x18
#define RCC_APB2 ((volatile unsigned *)(RCC_Base_APB2 + RCC_APB2_OFFSET)) //clock
#define RCC_APB2_IOPCEN 0x00000010
#define RCC_APB2_IOPDEN 0x00000020

#define GPIOx_CRL_ADDR_OFFSET 0x00
#define GPIOC_CRL ((volatile unsigned *)(GPIOC_Base + GPIOx_CRL_ADDR_OFFSET)) //입출력 사용
#define GPIOD_CRL ((volatile unsigned *)(GPIOD_Base + GPIOx_CRL_ADDR_OFFSET))

#define GPIOx_BSRR_OFFSET 0x10
#define GPIOx_BRR_OFFSET 0x14
#define GPIOD_BSRR ((volatile unsigned *)(GPIOD_Base + GPIOx_BSRR_OFFSET))//bit set
#define GPIOD_BRR  ((volatile unsigned *)(GPIOD_Base + GPIOx_BRR_OFFSET)) //bit reset
#define BIT_2 0x00000004
#define BIT_3 0x00000008
#define BIT_4 0x00000010
#define BIT_5 0x00000020
#define BIT_7 0x00000080

#define GPIOx_IDR_OFFSET 0x08
#define GPIOC_IDR ((volatile unsigned *)(GPIOC_Base + GPIOx_IDR_OFFSET)) //high low



int main()
{
  *RCC_APB2 |= RCC_APB2_IOPCEN | RCC_APB2_IOPDEN;
  *GPIOC_CRL &= ~0x00FFFF00;
  *GPIOC_CRL |= 0x00888800;
  *GPIOD_CRL &= ~0xF00FFF00;
  *GPIOD_CRL |= 0x30033300;
  *GPIOD_BRR |= (BIT_2|BIT_3|BIT_4|BIT_7); // problem part

  int i = 0;
  while(1) {
    if(!(*GPIOC_IDR& BIT_2))
          i=1;
    if(!(*GPIOC_IDR& BIT_3))
          i=2;
    if(!(*GPIOC_IDR& BIT_4))
          i=3;
    if(!(*GPIOC_IDR& BIT_5))
          i=4;

    switch(i)
    {
    case 1:
      *GPIOD_BSRR |= 0xc;   //d1,d2 on 1000 0100
      break;
    case 2:
      *GPIOD_BRR |= 0x90;   //d3,d4 off 0001 1000
      break;
    case 3:
      *GPIOD_BRR |= 0xc;   //d1,d2 off
      break;
    case 4:
      *GPIOD_BSRR |= 0x90;   //d3,d4 on
      break;
    }
  }
 }
