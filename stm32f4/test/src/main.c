/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2023-10-03

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
#include "Driver_LCD.h"
#include "Drive_Timer.h"

/* Private macro */
/* Private variables */
unsigned int writeIndex, readIndex,cmp_3_inter = 0;
int LectureCommandeFlag = 0;
char reception;
char fifo[20];
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

void UART4_IRQHandler(void) {
	//Plus besoin de fonction ReadUART
	UART4->SR &= ~BIT5;
	fifo[writeIndex++] = UART4->DR;
	writeIndex %= 20;
	cmp_3_inter++;
	if (cmp_3_inter == 3) {//cmp_3_inter == 3
		LectureCommandeFlag = 1;
	}
	cmp_3_inter %= 3;
}

void InitUart(void){
	//p62, PA0 connect� � tx et PA1 a rx (colonne AF8)
	RCC->AHB1ENR |= BIT0; //Enable clk for gpioA

	GPIOA->MODER |= BIT1 | BIT3;
	GPIOA->AFR[0] |= BIT7 | BIT3;//Fonction altenative 8 pour les 2 broches PA0 et PA1 (colone AF8)

	RCC->APB1ENR |= BIT19; //Enable clk for UART

	UART4->CR1 |= BIT3 | BIT2 | BIT5; //Interrupt when TDR register has been transfered into the  shift register, BIT5, RXNEIE : Interrupt on read data register not empty, BIT3 Transmitter enable, BIT2 Reception enable

	NVIC->ISER[1] |= BIT20;

	//UART4->BRR = 7.29*16;//13.44Mhz feed au UART, on multiplie par 16 pour faire un bit shift pour prendre les 4 bits dans la partie fract et les mettres en entier
				  //Voir page 978 ref manual 30.3.4. On cherche USARTDIV, on trouve USARTDIV = 7.29. over8 est � 0 et clk est � 13.44Mhz
	//Pour un baud rate de 115200. brr = fclkUart"13.44Mhz"/(8*2*115200), on multiplie par 16 pour avoir une partie fractionnaire sur 4 bits

	UART4->BRR = 43.75*16;

	UART4->CR1 |= BIT13;//enable
}

void writeByte(char p_byte){
	while(!(UART4->SR & BIT7)){}// Tant que les donn�es n'ont pas �t� transf�r�es au shift register, on attend

	UART4->DR = p_byte;
}

void writeUart(const char * p_str){
	int i =0;
	while(p_str[i] != '\0'){ // Tant que la transmission n'est pas compl�t�e
		writeByte(p_str[i++]);
	}
	//writeByte('\0');
	//writeByte('\n');
}

char receiveByteUart(){

	while(!(UART4->SR & BIT5)){

	}// Tant que les donn�es n'ont pas �t�es transf�r�es dans le data register, on attend

	return UART4->DR;
}

void LectureCommande(char commande, char param, char checksum){
	volatile char trueCKS = commande + param + checksum;
	if (trueCKS != 0) {
		return;
	}
	switch(commande){
		case (0x41):
		//Changer l'�tat de la LED
		if(param == 0x31) {
			GPIOD->ODR |= BIT12;
		}
		else if(param == 0x30) {
			GPIOD->ODR &= ~BIT12;
		}
		break;
		case (0x42):
		//Effacer la 2e ligne
				ClearLCD();
		  	  	CursorHome();
		  	  	writeStringLCD("SMI_EE_WG                               ");
		break;
		case (0x43):
				writeByteLCD(param);
		//Ajouter le param�tre � la 2e ligne
		break;
		default:
		break;
	}
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~BIT0; //pour clear le flag
	BoucleDAttente(9999);
}

void BoucleDAttente(short nombre_microsecondes_dattente) {
	for (volatile int i = 0; i > nombre_microsecondes_dattente; i++) {
	}
}

int main(void)
{
  volatile int compteurRetourDebutLaLigne = 0;//garde en memoire la position du curseur
  	//char reception;
  InitUart();
  //NVIC->ISER[0] |= BIT28;
  //TIM2->SR |= BIT0;
  configureAndStartSystick(8);//frequence a laquelle on lit le clavier (10Hz)
  configLCD();// GPIO pour le lcd
  WriteControl();// instructions pour initialiser le lcd
  ClearLCD();
  CursorHome();
  writeStringLCD("SMI_EE_WG                               ");
  Gpio_key_Init();
  ConfigTimer2(5);

  /* TODO - Add your application code here */

  /* Infinite loop */
  while (1)
  {
	  //writeUart("Hello World");
	  //reception = receiveByteUart();
	  if(LectureCommandeFlag) {
		  LectureCommandeFlag = 0;
		  LectureCommande(fifo[readIndex], fifo[(readIndex+1)%20], fifo[(readIndex+2)%20]);
		  readIndex++;
		  readIndex++;
		  readIndex++;
		  readIndex %=20;
	  }
	  //writeByte(reception);
  }
}
