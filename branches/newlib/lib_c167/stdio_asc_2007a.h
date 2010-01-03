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

void Init_IO_ASC (void);
