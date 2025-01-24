#include "stm32f4xx.h"
#include "macros_utiles.h"

void ConfigTimer2(int p_freq)
{
	const int peripheral_clk = 53760000/2; //
	const int prescaller = 499;

	//registre RCC_ APB1ENR Reg

	RCC->APB1ENR |= BIT0;

	//Rien a config dans le registre TIM2_CR1 et TIM2_CR2
	//registre TIM2_DIER pour les interrruptions a chaque fois remise a 0, interruption avec le bit 0;
	TIM2->DIER |= BIT0; //registre TIM2_DIER pour les interrruptions a chaque fois remise a 0, interruption avec le bit 0;
	TIM2->PSC = prescaller;
	TIM2->ARR = (peripheral_clk/prescaller)/p_freq;//autoreload register

	//il faut enable le systic pour les interruptions dans le cortexm4 user guide dans le nvic, il faut apres aller voir la table des vecteurs d'interruptions dans le startup_stm32f40xx.s et notre periph timer est a la place 28 (ligne 183), il faut mettre le bit 28 a 1
	NVIC->ISER[0] |= BIT28;

	TIM2->CR1 |= BIT0; //enable le timer2
}
