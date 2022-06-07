#include "stm32f1xx.h"
#include <stdio.h>

#define RCC_APB2ENR_USART1EN	(1U<<14)
#define UART1_TX_Pin	PA9
#define Clk				72000000
#define BaudRate_UART1	115200


void GPIO_config(void);
void USART_config(void);
void SendChar(int ch);

int __io_putchar(int ch){
	SendChar(ch);
	return ch;
}

int main(void){

	GPIO_config();
	USART_config();
	while(1){
		printf("Hello from STM32F1......\n\r");
	}
}


void GPIO_config(void){
	/* Configure UART port Pin (GPIO Pin) */
	//enabling clock to GPIOA
	RCC->APB2ENR |= (1U<<2);
	//configuring GPIOA pin to be TX
	//                FEDCBA98
	GPIOA->CRH   &= 0xFFFFFF0F;  // PA9 => USART1_TX, AF, PP, 50MHz
	GPIOA->CRH   |= 0x000000B0;
}

void USART_config(void){
	/* Configure UART module*/
	//Enabling clock to the UART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	//Configuring baudRate
	//uart_set_baudRate(USART1, Clk, BaudRate_UART1);
	USART1->BRR = 0x0271; //BaudRate 115200
	//configure transfer direction for TX
	USART1->CR1  &=  ~USART_CR1_M;      // Word length = 8 bits
	USART1->CR1  &=  ~USART_CR1_PCE;    // No parity
	USART1->CR1  |=   USART_CR1_TE; // Transmitter enable
	USART1->CR1  |=   USART_CR1_UE; // USART enable
}

void SendChar(int ch){
  while (!(USART1->SR & USART_SR_TXE)){} // wait until TXE = 1
  USART1->DR = ch & 0xFF; // Send the character
}

