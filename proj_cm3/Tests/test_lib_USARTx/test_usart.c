/*----------------------------------------------------------------------------
 * Name:    test_usart.c
 * Purpose: USART usage for STM32 with stdio.h
 * Version: V1.00
 *----------------------------------------------------------------------------
 * ACCO [28 Juillet 2009] cr�ation et test en simul� sur USART 1,2 et 3 
 *     c'est une d�rive du projet boards/keil/stm32/USART_pol
 *  utilise seulement des includes de la microlib.
 * 
 *----------------------------------------------------------------------------*/


#include <stdio.h>
//#include ""
int	printf(const char *fmt, ...) ;
FILE __stdin ;

#include "lib_usartx.h"

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {

                                 
  setup_usart();

  printf ("Polling mode Serial I/O Example\r\n\r\n");

  while (1) {                                     // Loop forever
    unsigned char c;

    printf ("Press a key. ");
    c = fgetc(& __stdin);
    printf ("\r\n");
    printf ("You pressed '%c'.\r\n\r\n", c);
  } // end while
} // end main

/* a supprimer 
void _sbrk_r (void)
{
}

void _write_r (void)
{
}

void _close_r (void)
{
}
void _lseek_r (void)
{
}
void _read_r (void)
{
	
}
void _fstat_r (void)
{
}
void _isatty_r (void)
{
}
*/