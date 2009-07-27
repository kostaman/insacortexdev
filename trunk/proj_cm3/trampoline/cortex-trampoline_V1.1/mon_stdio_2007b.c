/* STDIO_ASC.c ****************************************************************
 *	Entr�es-Sorties s�rie via le port asynchrone ASC en simu et en r�el       *
 *  stdio.h est donc utilisable (printf etc.) et visualisables sur la         *
 *  "serial windows #1" de Keil.
 *   Septembre 2007 pascal Acco												  *
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

#include <c167cs.h>
#include <intrins.h>
#include "mon_stdio_2007b.h"

#define Trappe_Logicielle 0x50

  
void Init_Mon_Stdio (void)
	{
#if(STDIO_MODE==STDIO_ASC_SIM)
//# MODE SIMULE # MODE SIMULE # MODE SIMULE # MODE SIMULE # MODE SIMULE # MODE
	P3 = P3 | 0x0400;		/* La bascule 10 de sortie du port P3 doit �tre � '1'
				car elle est combin�e par un ET avec la fonction alternative.
						 							(User's Manual, p. 7-7) */
	DP3 = DP3 | 0x0400;		// ligne P3.10 en sortie - TxD
	_nop_();				// pipe-line !   (User's Manual, p. 4-8)
	DP3 = DP3 & 0xF7FF;		// ligne P3.11 en entr�e - RxD
	_nop_();				// pipe-line !
	S0TIC = 0x0080;			// pr�t � �mettre, sans IT.
	S0RIC = 0;				// rien re�u, sans IT itou.
	S0BG  = 0x0040;			// vitesse : 9600 bauds.

/*  S0CON : voir User's Manual, pp. 11-2 et 11-3.
	  S0R	1   G�n�rateur de bauds en marche			S0CON.15
	  S0LB	0   Usage normal, sans rebouclage			S0CON.14
	  S0BRS	0   Vitesse d�finie par S0BG.				S0CON.13
	  S0ODD	0   Parit�.									S0CON.12
	   ---  0	--										S0CON.11
	  S0OE	0   RAZ du drapeau d'erreur de d�bordement	S0CON.10
	  S0FE	0   RAZ du drapeau d'erreur de trame		S0CON.9
	  S0PE	0   RAZ du drapeau d'erreur de parit�		S0CON.8
	  S0OEN	0   Ignore les d�bordements					S0CON.7
	  S0FEN	0   Ignore les erreurs de trame				S0CON.6
	  S0PEN	0   Ignore la parit�						S0CON.5
	  S0REN	1   RECEPTEUR EN MARCHE !					S0CON.4
	  S0STP	0   Trame avec 1 bit de stop				S0CON.3
	  S0M	001 Trame avec 8 bits de donn�es, async.	S0CON.2-0
	---------------
	c'est-�-dire  S0CON <-- 1000 0000 0001 0001b = 8011h
 */
 	S0CON = 0x8011;
#else
	_nop_ ();
	// Tout est configur� par le moniteur !!!
#endif
//# ENDIF # ENDIF # ENDIF # ENDIF # ENDIF # ENDIF # ENDIF # ENDIF # ENDIF # END
}
