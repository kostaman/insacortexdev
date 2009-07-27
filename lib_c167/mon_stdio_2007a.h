/* mon_stdio ****************************************************************
 *  permet d'utiliser stdio.h (printf,scanf etc.) avec diff�rentes solutions
 *  hardwares :
 *    STDIO_ASC_SIM => simule les transferts par la liason s�rie asynchrone ASC0
 *         visualisation en simul� sur la s�rial window UART0
 *    STDIO_ASC_REEL => transfert par la liason s�rie ASC0 (programm�e par le
 *         moniteur de Keil). Visualition 
 *
 ******************************************************************************
 ******************************************************************************
 * En mode r�el, UTILISEZ la cl� de compilation et d'assemblage MCB167NET.	  *
 * En mode  simul�, EFFACEZ cette cl�. (Onglets C166 et A166 du projet)		  *
 ******************************************************************************
 * void Init_IO_ASC(void) : il faut lancer cette fonction en premier afin de  *
 *			pouvoir b�n�ficier de la biblioth�que stdio et effectuer des E/S. *
 *				- Mode r�el : les E/S passent par la ligne ASC configur�e par *
 *                 le moniteur: On fait rien donc !                           *
 *				- Mode simul� : les E/S passent par la liasion s�rie ASC      *
 *						(visu sur fen�tre SERIAL #1 de KEIL).        		  *
 *																			  *
 ******************************************************************************/
#include <stdio.h>

void Init_Mon_Stdio (void);
