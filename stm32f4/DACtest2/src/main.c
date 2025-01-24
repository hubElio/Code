#include "stm32f4xx.h"
#include "macros_utiles.h"

#define NS  128


volatile uint32_t outValue;

volatile uint32_t Triangle[NS] = {
		0, 64, 129, 193, 258, 322, 387, 451, 516, 580,
		 645, 709, 774, 838, 903, 967, 1032, 1096, 1161, 1225,
		 1290, 1354, 1419, 1483, 1548, 1612, 1677, 1741, 1806, 1870,
		 1935, 1999, 2064, 2128, 2193, 2257, 2322, 2386, 2451, 2515,
		 2580, 2644, 2709, 2773, 2837, 2902, 2966, 3031, 3095, 3160,
		 3224, 3289, 3353, 3418, 3482, 3547, 3611, 3676, 3740, 3805,
		 3869, 3934, 3998, 4063, 4063, 3998, 3934, 3869, 3805, 3740,
		 3676, 3611, 3547, 3482, 3418, 3353, 3289, 3224, 3160, 3095,
		 3031, 2966, 2902, 2837, 2773, 2709, 2644, 2580, 2515, 2451,
		 2386, 2322, 2257, 2193, 2128, 2064, 1999, 1935, 1870, 1806,
		 1741, 1677, 1612, 1548, 1483, 1419, 1354, 1290, 1225, 1161,
		 1096, 1032, 967, 903, 838, 774, 709, 645, 580, 516,
		 451, 387, 322, 258, 193, 129, 64, 0
};

volatile uint32_t Sinus[NS] = {
		2048, 2149, 2250, 2350, 2450, 2549, 2646, 2742, 2837, 2929, 3020, 3108, 3193, 3275, 3355,
		3431, 3504, 3574, 3639, 3701, 3759, 3812, 3861, 3906, 3946, 3982, 4013, 4039, 4060, 4076,
		4087, 4094, 4095, 4091, 4082, 4069, 4050, 4026, 3998, 3965, 3927, 3884, 3837, 3786, 3730,
		3671, 3607, 3539, 3468, 3394, 3316, 3235, 3151, 3064, 2975, 2883, 2790, 2695, 2598, 2500,
		2400, 2300, 2199, 2098, 1997, 1896, 1795, 1695, 1595, 1497, 1400, 1305, 1212, 1120, 1031,
		944, 860, 779, 701, 627, 556, 488, 424, 365, 309, 258, 211, 168, 130, 97,
		69, 45, 26, 13, 4, 0, 1, 8, 19, 35, 56, 82, 113, 149, 189,
		234, 283, 336, 394, 456, 521, 591, 664, 740, 820, 902, 987, 1075, 1166, 1258
};

volatile uint32_t Sinc[NS] = {
		4095, 4060, 3958, 3793, 3578, 3323, 3045, 2758, 2479, 2222,
		 2000, 1822, 1694, 1618, 1594, 1616, 1677, 1766, 1874, 1988,
		 2097, 2191, 2264, 2310, 2326, 2315, 2277, 2219, 2148, 2071,
		 1996, 1930, 1879, 1847, 1837, 1848, 1878, 1924, 1981, 2043,
		 2103, 2155, 2195, 2219, 2225, 2213, 2185, 2143, 2093, 2039,
		 1987, 1942, 1908, 1889, 1886, 1900, 1928, 1968, 2016, 2067,
		 2116, 2157, 2187, 2203, 2203, 2187, 2157, 2116, 2067, 2016,
		 1968, 1928, 1900, 1886, 1889, 1908, 1942, 1987, 2039, 2093,
		 2143, 2185, 2213, 2225, 2219, 2195, 2155, 2103, 2043, 1981,
		 1924, 1878, 1848, 1837, 1847, 1879, 1930, 1996, 2071, 2148,
		 2219, 2277, 2315, 2326, 2310, 2264, 2191, 2097, 1988, 1874,
		 1766, 1677, 1616, 1594, 1618, 1694, 1822, 2000, 2222, 2479,
		 2758, 3045, 3323, 3578, 3793, 3958, 4060, 4095
};

void initDAC() {

	RCC->AHB1ENR |= BIT0; //enable clock gpioA

	GPIOA->MODER |= BIT7;//alternate function pour PA4
	GPIOA->AFR[0] |= BIT15 +BIT14+BIT13+BIT12; // dac pour PA4

    // Enable the DAC clock
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;

    DAC->CR &= ~DAC_CR_EN1;

    // Configure DAC channel 1, PA4 alternate function DAC1_out
    DAC->CR &= ~DAC_CR_BOFF1; // Enable buffer pour DAC channel 1 DAC_CR_BOFF1
    //DAC->CR |= BIT12 |BIT5 |BIT2;//EN DMA, bit5 pour utiliser timer2 et bit 2 pour enable les triggers du timer 2
    DAC->CR |= DAC_CR_EN1;   // Enable DAC channel 1
}

void setDACValue(uint16_t value) {
    // 12-bit range (0 to 4095)
    value &= 0x0FFF;

    //ecrit la valeur digitale au dac
    DAC->DHR12R1 = value;
}


void configureDMA(void){
	RCC->AHB1ENR |= BIT22;//clock enable DMA p250

	DMA2_Stream0->CR &=~BIT0;

	DMA2_Stream0->CR |=BIT25 |BIT26 |BIT27; // choix du chanel 7 car il est lié à l'adc
	DMA2_Stream0->CR |=BIT14;//bit Memorysize a config en word(32 bits) p328
	//DMA2_Stream0->CR |=BIT12;
	DMA2_Stream0->CR |=BIT11;//taille memoire peripherique (le registre DAC->DHR12R1 pour le dac 12 bits) sur 16 bits
	DMA2_Stream0->CR |=BIT10;//il faut incrementer l@ ou on ecrit a chaque transfert pour pas ecraser.
	//DMA2_Stream0->CR |=BIT9;// peripheral memory increment
	DMA2_Stream0->CR |=BIT8;//Quand le tableau est rempli, une interruption se fait et on reecrit au depart du tableau
	//DMA2_Stream0->CR |=BIT7;//direction memoire a memoire
	DMA2_Stream0->CR |=BIT6;//Memory to peripheral
	DMA2_Stream0->CR |=BIT4;//creation interruption quand un transfert est fait

	DMA2_Stream0->CR |=BIT2;//transfer interrupt enabled

	DMA2_Stream0->NDTR =  NS;//nombre de transferts a faire NS
	DMA2_Stream0->PAR = (int)Triangle;//adresse de depart
	DMA2_Stream0->M0AR = (int)(DAC->DHR12R1);//destination, registre sortie du dac

	NVIC->ISER[1]|= BIT24; //voir la position de la table
}


void startDMA(void){
	DMA2_Stream0->CR |=BIT0;//start le transfert
}
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

void generationSignal(int SignalChoisi,int frequence) {

	if(SignalChoisi == 1){
		for(volatile int j = 0;j<NS;j++){// on envoi toutes les valeures du tableau à L'adc
			setDACValue(Sinus[j]);
			for(volatile int i = 0;i<frequence;i++);// fréquence du signal périodique divisé par 3.33, donc ici on à un signal à 333Hz (dépend de NS, de l'horloge du dac)
		}
	}
	else if(SignalChoisi == 2){
		for(volatile int j = 0;j<NS;j++){// on envoi toutes les valeures du tableau à L'adc
			setDACValue(Triangle[j]);
			//setDACValue(Sinc[j]);
			for(volatile int i = 0;i<frequence;i++);// fréquence du signal périodique divisé par 3.33, donc ici on à un signal à 333Hz (dépend de NS, de l'horloge du dac)
		}
	}
	else if(SignalChoisi == 3){
		for(volatile int j = 0;j<NS;j++){// on envoi toutes les valeures du tableau à L'adc
			setDACValue(Sinc[j]);
			for(volatile int i = 0;i<frequence;i++);// fréquence du signal périodique divisé par 3.33, donc ici on à un signal à 333Hz (dépend de NS, de l'horloge du dac)
		}
	}
	else{
		printf("error Mauvaise valeur\n");
	}

}

int main(void) {
    // Initialize the DAC
	volatile uint32_t debug;
    initDAC();
    //ConfigTimer2(100);
    //configureDMA();
    //startDMA();
    while (1) {

    	generationSignal(2,100);//parametre1= 1,2,3 pour sinus,triangle,sinc et parametre2 pour la fréquence
    }
}

void DMA2_Stream0_IRQHandler(){
	DMA2->LIFCR|=BIT5;//p327 pour clear le flag pour le canal0
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~BIT0; //pour clear le flag
	//GPIOD->ODR ^= BIT12|BIT15;
}
