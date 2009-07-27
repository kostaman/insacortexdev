#include "lib_autom_2008a.h"
#include "driveurs_2008a.h"

float Vieux_I_Pos = 0.0;



Un_Etat Lire_Etat_Absolu(void)
{
	Un_Etat Courant;
	Courant.Pos=Lire_Position();
	Courant.Vit=Lire_Vitesse();
	Courant.I_Pos = 666;

   return Courant;
}

Un_Etat Calculer_Etat_Relatif(Un_Etat Etat_Cons)
{
	Un_Etat Courant;
	Courant.Pos= Etat_Cons.Pos - Lire_Position();
	Courant.Vit= Etat_Cons.Vit -  Lire_Vitesse();
	Vieux_I_Pos = (float)(Courant.Pos) * TE + Vieux_I_Pos ;
	if (Vieux_I_Pos > I_MAX) Vieux_I_Pos = I_MAX;
	if (Vieux_I_Pos < I_MIN) Vieux_I_Pos = I_MIN;

	Courant.I_Pos = (signed int)(Vieux_I_Pos);
   	return Courant;
}

void Reinit_Etat(int Longueur_Trajet)
{
	Init_Position(Lire_Position()-Longueur_Trajet);
	Vieux_I_Pos = 0.0;
}


/*
_______________________________________________________________________________
			T�che du       G�n�rateur de trajectoires
_______________________________________________________________________________
P�riode = Tc*Ttourniquet 

IN :    SIGNAL -> d�clenche la synth�se de la trajactoire
		Position_Voulue : float globale => position d�sir�e [m] � la fin de la trajectoire

OUT:   Consigne_Vitesse : float globale=> consigne de vitesse (p�riodique � Tc)
       Consigne_Position : float globale=> consigne de position li�e (Tc)

Vitesse
  /\         Vmax ----> _______________________________
   |                  / I                             I\
   |                 /  I							  I \
   |                /	I						 	  I  \
   |			   /	I							  I   \
   |		  	  /	    I 							  I	   \
   |   __________/	    I							  I     \____________
   |_____________I______I_____________________________I___________________\ temps
                 |       |_                            |<---->|_           /
                 |		   \_						   |		\_
				 |           \_ 					   |		  \_
				 |<----------->|					   |<---------->|
				 |  TM   						       |      TM 
                 |------------------------------------>|
                                  Tstop

Pour que la position finale soit Position_Voulue[m] il faut calculer le 
                                                               Tstop(Vmax,TM,Position_Voulue)
	          Position_Voulue
	Tstop = __________________   surprenant mais vrai ! ind�pendant des rampes de mont�e...
	              Vmax
	Tstop = Npas * Tc (on �chantillone la trajectoire � la p�riode Tc

*/

struct {
	unsigned int Count;
	unsigned char Phase;
	unsigned int Position_Finale;
	unsigned int Tfrein;
	unsigned int Tend ;
	unsigned int Delta_V;
	float  Position;
	unsigned int Vitesse;
} E;

#define TM ((unsigned int)(TEMPS_MONTEE/TT))
void Init_Trajectoire(unsigned int Position_Station)
{
			E.Position_Finale = Position_Station;
			E.Count = 0;
//			E.Phase = 'M';
			E.Tfrein = (unsigned int)(((long unsigned int)(E.Position_Finale)*1000L)/(long unsigned int)(VMAX*TT)); //T2 (en multiples de Tc)
			E.Tend = TM+E.Tfrein;
			E.Delta_V = (VMAX*TT)/TEMPS_MONTEE;  //incr�ment de vitesse par p�riode du g�n�rateur pour la rampe
			E.Vitesse=0;
			E.Position=0.0;
}

unsigned int Compteur_Trajectoire (void)
{
   return E.Count;
}

Un_Etat Lire_Consigne(void)
{	
	Un_Etat Consigne;
	Consigne.I_Pos = 999;
 	Consigne.Pos = (unsigned int) E.Position;
 	Consigne.Vit = (unsigned int) ((float)E.Vitesse*KD);

	return Consigne;
}
//const int Position_Voulue = (int)33.0/PAS;

unsigned char Iterer_Trajectoire(void)
{
	signed int DV = 0;
	unsigned int VV;

		E.Count++;	
	   	VV=E.Vitesse;
			
		if (E.Count<TM)
		{
			E.Vitesse = E.Vitesse+E.Delta_V;
		}
#ifdef AVEC_APPROCHE
		else if (E.Count<E.Tfrein)
#else
		else if (E.Count<=E.Tfrein)
#endif
		{		
			E.Vitesse = VMAX;
		}
#ifdef AVEC_APPROCHE
		else if ((E.Position_Finale-(int)E.Position-1)>(VAPP*TT/1000))
		{
			E.Vitesse = E.Vitesse -  E.Delta_V;
			if (E.Vitesse < VAPP)
			{
				E.Delta_V=0; 
			 	E.Vitesse = VAPP;
			 }
		}
#else
		else if (E.Vitesse>E.Delta_V)
		{
			E.Vitesse = E.Vitesse -  E.Delta_V;
		}
#endif
		else
		{
				E.Vitesse = 0;
#ifdef AVEC_APPROCHE
				E.Position = E.Position_Finale;
#endif

		return 1;
		}

		E.Position = E.Position + (float)((E.Vitesse+VV)*TT)/2000.0;

		return 0;
		//Envoyer_Msg(NUM_MO_CONTROLEUR,Consigne);

		//Consigne.Position=Position_Voulue;
		//Envoyer_Msg(NUM_MO_CONTROLEUR,Consigne);
		//os_wait(K_IVL,500,0);
		//Envoyer_Mode_Rame(MODE_A_L_ARRET);
			
}



