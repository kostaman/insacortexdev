/* mon_stdio ****************************************************************
 *  permet d'utiliser stdio.h (printf,scanf etc.) avec diff�rentes solutions
 *  hardwares d�finies par STDIO_MODE:
 *    STDIO_ASC_SIM => simule les transferts par la liason s�rie asynchrone ASC0
 *         visualisation en simul� sur la s�rial window UART0
 *    STDIO_ASC_REEL => transfert par la liason s�rie ASC0 (programm�e par le
 *         moniteur de Keil). Visualition
 *
 * En mode r�el, UTILISEZ la cl� de compilation et d'assemblage MCB167NET qui 
 *    va forcer STDIO_MODE dans le mode STDIO_ASC_REEL	                      *
 * En mode  simul�, EFFACEZ cette cl� MCB167NET. (Onglets C166 et A166 du projet)
 *    qui va forcer STDIO_MODE dans le mode STDIO_ASC_SIM  		  *
 *
 * Dans tousq les cas Visualisation sur la fen�tre SERIAL #1 de KEIL  		  *
 ******************************************************************************
 * void Init_Mon_Stdio(void) : il faut lancer cette fonction en premier afin de  *
 *			pouvoir b�n�ficier de la biblioth�que stdio et effectuer des E/S. *
 *																			  *
 ******************************************************************************/
#include <stdio.h>
#define STDIO_ASC_SIM 1
#define STDIO_ASC_REEL 2

#ifdef MCB167NET
#define STDIO_MODE STDIO_ASC_REEL
#else
#define STDIO_MODE STDIO_ASC_SIM
#endif

void Init_Mon_Stdio (void);
