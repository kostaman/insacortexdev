#include "../sys/stm_regs.h" 

//=======================================================================================

// 	Auteur Periph Team
//  1 Sept 2010
//  Processeur : STM32F103RB
//  Logiciel dev : �Vision 4
//  Module qui configure les I/O
//
//  ________ Rappel sur les ressources __________________________________________________
// Broche : de 0 � 15 pour GPIOA, GPIOB, 
//		  : de 0 � 13 pour GPIOC 
//
//  ________ Comment utiliser la lib ? __________________________________________________
//   
//	1 - configurer la broche voulue Fct : char Port_IO_Init(char Port, char Broche, char Sens, char Techno);
//  2 - op�rer une �criture : void Port_IO_Set(char Port, char Broche) et void Port_IO_Clr(char Port, char Broche)
//  3 - op�rer une lecture : unsigned int Port_IO_Lire(char Port, char Broche);
//
//=======================================================================================
//=======================================================================================

#ifndef _Port_IO_H__
#define _Port_IO_H__

//__________________________________________________________________________________________
//
char Port_IO_Init( GPIO_TypeDef * Port, char Broche, char Sens, char Techno);
// Doc tech : STM32F103RM.pdf
// Port : Char A � C en majuscule ou minuscule
// Broche : de 0 � 15 pour GPIOA, GPIOB, 
//		  : de 0 � 13 pour GPIOC 
// Sens   : I pour entree, O pour sortie, en Majuscule ou minuscule

// Techno : 0 Analog						  / Output push-pull
//			1 Input floating				  / Output open-drain
//			2 Input-pull-down / up			  / Alternate function push-pull
//			3 reserved						  / Alternate function open-drain
// 	REMARQUE : Pour entree pull down/up, on choisit down en �crivant 0 en sortie
//				et up pour 1 en sortie (ODR)
// Retourne 0 si tout est OK, et 1 dans les cas suivant ou les param�tres sortent
// de l'intervalle sp�cifi�:
//__________________________________________________________________________________________
//




void Port_IO_Set(GPIO_TypeDef * Port, char Broche);
// Sp�cifier Port (A, B ou C)
// Sp�cifier le num�ro de broche (0 � 15)

//__________________________________________________________________________________________
//
void Port_IO_Clr(GPIO_TypeDef * Port, char Broche);
// Sp�cifier Port (A, B ou C)
// Sp�cifier le num�ro de broche (0 � 15)

//__________________________________________________________________________________________
//
unsigned int Port_IO_Lire(GPIO_TypeDef * Port, char Broche);
// Sp�cifier Port (A, B ou C)
// Sp�cifier le num�ro de broche (0 � 15)
// Renvoie l'�tat de la broche, 0 ou autre (si 1)
#endif
