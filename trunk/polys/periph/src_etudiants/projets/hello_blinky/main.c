//__________________________________________________________
// projet/hello_blinky/      MAIN.C
// Tentaive de faire clignoter une diode
// BINOME :
// ETAT : ni compil� ni test�
// TODO : lire la doc, configurer, compiler, deboguer
//   Quand vous serrez grands vous pourrez enlever les
// commentaires //REMARQUES qui sont � but p�dagogiques
// et inutile pour les geeks
//__________________________________________________________

//____ registres de p�riph�riques du stm_32
#include "stm_regs.h"
//REMARQUES
//  si le fichier n'est pas visible faites :
//     Project->options for target
//     onglet C/C++ remplir "include paths"
//      pour rendre visible le r�pertoire sys

//___ pilote de l'arbre d'horloges
#include "../../pilotes/stm_clock.h"
//REMARQUES
// ATTENTION c'est une librairie statique :
// il faut qu'un fichier stm_clock_config.h soit dans
// le r�pertoire projet et qu'il soit visible (ajouter
// le r�pertoire du projet � l'include path des option C/C++)
// Normalement c'est le cas et le fichier non modifi�
// r�gle les fr�quences �
//   SYSCLK = 40MHz = 8 (HSE quartz) * 5 (PLL)
//    SYSCLK est l'horloge du coeur qui est
//    issue du quartz externe "HSE" � 8MHz qui arrive 
//    direct sur une Phase Locked Loop PLL qui 
//    multiplie la fr�quence par 5.
// 	PCLK1 = SYSCLK / 2(prescaler PRE1) = 20 MHz  
//   sortie de l'APB1 "low speed" pour p�riph lents.
//  PCLK2 = SYSCLK / 1 (prescaler PRE2)= 40 MHz
//   sortie de l'APB2 "high speed" pour p�riph press�s.
    

int main (void)
{
	//___ initialise les horloges SYSCLK,PCLK1,PCLK2
	Init_Clock_System() ; 
	//REMARQUES
	// Attention si vous oubliez cette ligne, il n'y a pas de 
	// configuration : le processeur reste sur une horloge interne
	// � la puce (oscillateur RC nomm� High Speed Internal clock)
	// c'est oscillateur oscille vaguement aux alentours de 8MHz !
	 
	//___ validation de l'horloge des ports GPIOA GPIOB et GPIOC	
 	(RCC->APB2ENR)|= RCC_IOPAEN | RCC_IOPBEN | RCC_IOPCEN;
 	//REMARQUES
	// en effet le bridge APB2 am�ne une horloge � 40MHz 
	// aux p�riph�riques tels que ces GPIO. Par d�faut les 
	// p�riph�riques sont �tteints pour ne pas consommer de
	// courant. Cette initialisation permet d'allumer l'horloge
	// de chaque p�riph�riques. Soyez TRES VIGILENTS car sans
	// cette ligne de validation lors d'un acc�s � un registre,
	//  par exemple GPIOA->ODR = ..., le programme compile, 
	//  s'ex�cute mais comme le registre GPIOA_ODR ne re�oit pas
	//  d'horloge il ne m�morise pas la valeur d�sir�e et rien
	//  ne marche malgr� les apparences... 
	// Bon courage les futurs geeks
	GPIOB->CRH = 0x44444474;
	GPIOB->CRL = 0x44484444;
	while(1)
	{
		GPIOB->ODR ^=(1<<9);
	}
	//__ configuration du port PB.8 � PB.15 pour faire blinky
	// sur une ou plusieurs diodes de la carte MCBSTM32
	
	return 0;
}
