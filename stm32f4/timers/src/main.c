/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2023-09-12

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "macros_utiles.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
volatile int counter = 0;
volatile int counter2 = 0;
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
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


void Gpio_LED_Init(){
	RCC->AHB1ENR |= BIT3 ;//RCC, clock enabled for gpioD(BIT3)
	GPIOD->MODER |= (BIT24 + BIT26 + BIT28+ BIT30); //Mise sur output des pins 12,13,14,15 (code 01 dans le registre)
}

void configureAndStartSystick(int p_freq){//hologe du processeur est 53.73Mhz, l'autre est 53.73Mhz/8
	const int systick_clk = 53760000/8;// on doit utiliser l'horloge du processeur pour pouvoir utiliser des insterruptions(trop rapide)
	SysTick->LOAD = systick_clk/p_freq;//on compte jusqu'a 1
	SysTick->CTRL |= BIT0 |BIT1;//BIT0 pour Enable et BIT1 pour Enable SysTick exception request
	SysTick->VAL = systick_clk/p_freq;//lire ou ecrire en tout temps la valeur du compteur
}

int main(void)
{
//#pragma pack // pour enlever l'alignement de la prochaine variable
  Gpio_LED_Init();
  configureAndStartSystick(2000); //f = 2kHz soit T = 0.5 ms
  ConfigTimer2(2); //  f = 2Hz soit T = 0.5s

  while (1)
  {
	  if(counter2 == 3)
	  {
		  counter2 = 0;
		  GPIOD->ODR &= ~(BIT13|BIT14); // si le bit est a 0 le met a 1 et inversement
	  }
	  if(counter == 3)
	  {
		  counter = 0;
		  GPIOD->ODR &= ~(BIT12|BIT15); // si le bit est a 0 le met a 1 et inversement
	  }

  }
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~BIT0; //pour clear le flag
	counter++;
	GPIOD->ODR |= BIT12|BIT15; // si le bit est a 0 le met a 1 et inversement
	//GPIOD->ODR ^= BIT12|BIT15;
}

void SysTick_Handler(void) {
	counter2++;
	GPIOD->ODR |= BIT13|BIT14; // si le bit est a 0 le met a 1 et inversement
	//GPIOD->ODR ^= BIT13|BIT14;
}
