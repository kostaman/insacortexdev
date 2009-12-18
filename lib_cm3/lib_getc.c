/*----------------------------------------------------------------------------
 * Name:    getc.c
 * Purpose: fonction getc sur liaison serie
 * Version: V1.00
 *----------------------------------------------------------------------------
 * SDM [28 Juillet 2009] cr�ation et test en simul� sur USART 2 
 *     test� sous GCC (aucun interet sur ARMCC)
 *----------------------------------------------------------------------------*/

#include "stdio.h"				// import FILE type

FILE __stdout;
FILE __stdin;

/* Remarque: le fichier lib_cm3.h fait une redefinition de getchar en lgetchar */
int getc(FILE *f)
{
	return (fgetc(__stdin));
} 