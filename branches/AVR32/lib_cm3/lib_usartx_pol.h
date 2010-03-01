/*----------------------------------------------------------------------------
 * Name:    lib_usartx_pol
 * Purpose: USART usage for STM32 with stdio.h
 *  
 * Version: V1.00
 *----------------------------------------------------------------------------
 * ACCO [28 Juillet 2009] cr�ation et test en simul� sur USART 1,2 et 3 
 *     c'est une d�rive du projet boards/keil/stm32/USART_pol
 *  utilise seulement des includes de la microlib.
 * ACCO 
 *----------------------------------------------------------------------------
  USAGE :
  	1\ include the lib_usartx_pol.c in project
	2\ include the lib_usartx_pol.h in main program
	3\ edit lib_usartx_pol.h to config USART to use and BAUDRATE
	4\ call usartx_setup()	 before  any use of stdlib functions !

 	5\ when running connect terminal with 
		matching BAUDRATE
	 	8bits DATA
		1bit Stop
		NO PARITY check
		NO flow control
	______________________________________________________________________
	TODO :
	-	tester en r�el
		+ 9600 bauds OK avec zeegbee
		- 19200 bauds marche pas ! 
		   sur l'hyperterm � 9600 passage de zegbee � 19200 avec
		   +++[CR] r�ponse OK
		   ATBD4[CR] r�ponse OK
		   ATCN[CR]
		   ouverture de l'hterm � 19200 bauds
		   c'est bien 19200 car  +++[CR] r�pondes OK ! (je fais ATCN[CR] pour sortir)
		   compil du projet avec la lib � 19200 bauds + tests => CARACTERES BIZARRES
		   sans doute un probl�me de data rate...
	- 	voir la compatibilit� avec le noyau TR
	-   clarifier l'histoire du //#pragma import(__use_no_semihosting_swi) 
 */



// USART config
//#define NUM_USART	1   // choose to use USART1
//#define NUM_USART	2   // choose to use USART2
#define NUM_USART	3   // choose to use USART3

//choose baudrate among following values
#define BAUDRATEx   9600      // OK avec zigbee
//#define BAUDRATEx   14400 
//#define BAUDRATEx   19200 
//#define BAUDRATEx   28800 
//#define BAUDRATEx   38400 
//#define BAUDRATEx   56000 
//#define BAUDRATEx   57600 
//#define BAUDRATEx   115200 

void setup_usart(void);