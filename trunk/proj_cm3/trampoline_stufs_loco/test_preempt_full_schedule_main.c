#include "../os/tpl_os.h"
#include "../../lib_user/uart.h"
#include "../../lib_user/lcd.h"
#include "../../lib_user/lib_trajectoire_2009a.h"
#include "tpl_os_generated_configuration.h"
#include "../../system/STM32_Init.h"
#include "../../lib_user/led.h"
#include "../../lib_cm3/Metro_Librairie_Version2009d.h"

/*Test selon le mail de peh

  Un syst�me avec deux t�ches, l''une T1 de p�riode 10 ms et de dur�e 7 ms (� ajuster avec une boucle),
 la seconde T2 de p�riode 2 ms et de dur�e 1 ms avec d�marrage synchrone (m�me valeur de ALARMTIME).
  Les deux t�ches doivent avoir une valeur pour ACTIVATION de 1 (pas de m�morisation des activations). 
  La p�riode de T2 sup�rieure � T1.

 Premi�re version les deux t�ches FULL pour SCHEDULE (voir fichier archi_appli_1.oil).
  Normalement T1 devrait rater une activation sur 2. 
  De plus tu devrais observer plusieurs pr�emptions de T1 par T2 (tu verras si le changement de contexte se fait bien).
*/

int compteur = 0;

#define TMP_CNT ((int)(7000.0/4.0/(0.219099-0.00028363)*0.1) )



void InitApp(void)
{

	stm32_Init ();
	Init_Periphs();

	//lcd_init();
	   initGenerateur(20, 800, 1000);
}

int main (void)
{
	InitApp();
	StartOS(OSDEFAULTAPPMODE);
	return 1;
		
}



TASK(Tache1)
{

	if (getPhase())
	{
		initTrajectoire(5600);
	}
	else
	{
		calculConsigneSuivante();
	}

    TerminateTask();
}

TASK(Tache2)
{

	Etat cons;
	cons= lireConsigne();
	
	Fixe_Rapport(cons.Vit);

    TerminateTask();
}
