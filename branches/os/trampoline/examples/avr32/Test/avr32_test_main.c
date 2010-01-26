#include "tpl_os.h"
#include "tpl_os_generated_configuration.h"
#include <avr32/io.h>

/*Test selon le mail de peh

  Un syst�me avec deux t�ches, l'une T1 de p�riode 10 ms et de dur�e 7 ms (� ajuster avec une boucle),
 la seconde T2 de p�riode 2 ms et de dur�e 1 ms avec d�marrage synchrone (m�me valeur de ALARMTIME).
  Les deux t�ches doivent avoir une valeur pour ACTIVATION de 1 (pas de m�morisation des activations).
  La p�riode de T2 sup�rieure � T1.

 Premi�re version les deux t�ches FULL pour SCHEDULE (voir fichier archi_appli_1.oil).
  Normalement T1 devrait rater une activation sur 2.
  De plus tu devrais observer plusieurs pr�emptions de T1 par T2 (tu verras si le changement de contexte se fait bien).
*/

u32 compteur_tache_1 = 0;
u32 compteur_tache_2 = 0;

#define TMP_CNT ((int)(7000.0/4.0/(0.219099-0.00028363)*0.1) )

void InitApp(void)
{
	/*Init_Periphs();*/
	/* Initialisation du timer OS */
}

int main (void)
{
	InitApp();

	StartOS(OSDEFAULTAPPMODE);

	return 1;
}

TASK(Tache1)
{

    TerminateTask();
}

TASK(Tache2)
{

    TerminateTask();
}

