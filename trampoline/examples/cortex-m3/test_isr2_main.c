#include "../os/tpl_os.h"
#include "tpl_os_generated_configuration.h"
#include "stm_regs.h"
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
 void	Init_Periphs(void);
#define TMP_CNT ((int)(7000.0/4.0/(0.219099-0.00028363)*0.1) )
void tempo(int ms)
{
	int nms,i;
	volatile int j;

	for(nms=0; nms < ms; nms++)
	{
		for(i=0;i<TMP_CNT;i++) j++;
	}
}
void InitApp(void)
{
	tempo(100);
	Init_Periphs();
}

int main (void)
{
	InitApp();
	StartOS(OSDEFAULTAPPMODE);
	return 1;
		
}



TASK(Tache1)
{

	tempo(2);

    TerminateTask();
}

TASK(Tache2)
{
	int i3 = 0;
	// corps de la t�che Tache2
//	Toggle_Led('2');
	//while (1) 
	 tempo(1);
	 i3++;
		
//	i1--;
    TerminateTask();
}
	  
ISR(EXTI0)
{
	// corps de l'ISR GSignal
	compteur ++;
//	Write_Integer_Lcd(compteur);
	
	
	EXTI->PR |= 1 ; //reset peripheral flag
	TerminateISR();
}
