//__________________________________________________________
// projet/TP_GPIO/      MAIN.C
// Tentative de faire clignoter une diode
// BINOME :
// ETAT : compil� et test�
//__________________________________________________________

/** TODO : Compiler ce fichier. Ex�cuter le en simulation puis passer irl. Constatez ce qui se passe.
**/

/** TODO : Lire le code et faire les TODO pr�sents dans le code
**/

/** TODO : Ajouter la configuration en entr�e du port PA.0 qui est cabl� au bouton WKUP et allumer la diode PB13 quand le 
** bouton est maintenu appuy�.
**/

/** TODO : Ecrire une fonction qui permet de configurer une broche d'un port en output push-pull.
**			Le prototype de la fonction sera : char Port_IO_Init_Output( GPIO_TypeDef * Port, char Broche)
**/

/** TODO : Ecrire une fonction qui permet de configurer une broche d'un port en input floating.
**			Le prototype de la fonction sera : char Port_IO_Init_Input( GPIO_TypeDef * Port, char Broche)
**/

/** TODO : Ecrire une fonction qui permet de mettre � 1 une broche d'un port
** 			Le prototype de la fonction sera :void Port_IO_Set(GPIO_TypeDef * Port, char Broche)
**/
/** TODO : Ecrire une fonction qui permet de mettre � 0 une broche d'un port
** 			Le prototype de la fonction sera :void Port_IO_Reset(GPIO_TypeDef * Port, char Broche)
*/
/** TODO : Ecrire une fonction qui inverse l'�tat d'une broche
** 			Le prototype de la fonction sera :void Port_IO_Blink(GPIO_TypeDef * Port, char Broche)
*/
/** TODO : Ecrire une fonction qui permet de lire l'�tat d'une broche d'un port
**			Le prototype de la fonction sera : unsigned int Port_IO_Read(GPIO_TypeDef * Port, char Broche)
**/
/** TODO : Cr�er un fichier gpio.c qui contient ces fonctions et un fichier d'en-t�te gpio.h et les placer dans le 
** r�pertoire ../../pilotes/gpio  Modifier Test_GPIO.c pour faire dispara�tre tout ce qui est directement
** en lien avec le p�riph. Vous ne pouvez que faire appel � vos nouvelles fonctions.
**/


//____ registres de p�riph�riques du stm_32
#include "stm_regs.h"
//REMARQUES
//  si le fichier n'est pas visible faites :
//     Project->options for target
//     onglet C/C++ remplir "include paths"
//      pour rendre visible le r�pertoire sys


int main (void)
{
	char flipflop = 1;
	
 	// Cette ligne est n�cessaire pour le bon fonctionnement de la carte, pour l'instant oubliez l� !
 	(RCC->APB2ENR)|= RCC_IOPAEN | RCC_IOPBEN | RCC_IOPCEN;

	// CRH = 1111 1111 : 1111 1111 : 1111 1111 : 1111 1111 
	GPIOB->CRH = 0xFFFFFFFF;
	//__ configuration du port PB.9 en sortie (output push-pull)
	// CRH = xxxx xxxx : xxxx xxxx : xxxx xxxx : 0001 xxxx 	
	GPIOB->CRH = (0x01 << 4);
	// TODO : Qu'est-ce que veut dire (x << y) ?
	// TODO : Pour ne pas toucher aux autres bits que le 9 du registre CRH, il faut faire un masque. Faites le ! 
	 
	// Faire clignoter la diode sur le port PB.9
	while(1)
	{
		if (flipflop == 1) {
		// ODR = xxxx xxxx : xxxx xxxx : xxxx xx1x : xxxx xxxx 
			GPIOB->ODR = (0x01 << 9); 
			// TODO : Comment faire pour ne changer que le bit 9 ?
			flipflop = 0;
			// TODO : Comment faier pour se passer du flipflop en utilisant directement la valeur de ODR ?
		} else {
		// ODR=xxxx xxxx | xxxx xxxx | xxxx xx0x |xxxx xxxx 
			GPIOB->ODR = 0x00; 
			flipflop = 1;
		}
	}

	return 0;
}

