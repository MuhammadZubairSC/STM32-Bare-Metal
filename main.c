#include "stm32f1xx.h"
#include <stdio.h>


void delayMs(int delay);
/*
    - USER PB   : connected to PA0
    - LED       : connected to PA5
*/



int main(void){
	RCC->APB2ENR |= (1U<<2);
		//Clearing only bit 16
	GPIOA->CRL &= 0xFF0FFFFF;
	GPIOA->CRL |= 0x00200000;
	while(1){
		GPIOA->ODR |= (1U<<5);
		delayMs(500);
		GPIOA->ODR &=~(1U<<5);
		delayMs(500);
	}

}

void delayMs(int delay){
	volatile int i;  // try to stop optimisation removing loops
	for(; delay>0; delay--){
		for (i=0; i<3195;i++) ;
	}
}
