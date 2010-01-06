/*
________________________________________________________________________________________
	Generation de trajectoire pour le BE M�tro
	lib_trajectoire_2009a.c
    GPL licensed code (P.E. Hladik and P. Acco)
________________________________________________________________________________________
USAGE
	inlude lib_trajectoire_2009a.h in your application
________________________________________________________________________________________
REVS
	[PEH 7/12/09] suppression des m�thodes qui ne font pas partie
	du g�n�rateur de trajectoire 
	[PEH 7/12/09 ]Suppression de la m�thode d'approche
	[PAC 3/1/10 ] Passage � des types standards u16 u32 etc...
	[Acco 06/01/2010] finalisation et commentaires de la premi�re version
		Test�e en r�el et simul�
________________________________________________________________________________________
TODO 
	version simplifi�e en float
	version en s32
___________________________________________________________________________________
  G�n�re des consignes de position et de vitesse coh�rentes selon le profil 
  de vitesse suivant

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
				 |  tempsMontee   						  |      tempsMontee 

La position en fin de trajectoire est celle sp�cifi�e
*/

#ifndef _LIB_TRAJ_
#define _LIB_TRAJ_

#include "standard_types.h"	  

// Type renvoy� par lireConsigne()
typedef struct {
	u16 Pos ;	//Position en pas (attention pas de position n�gative)
	u16 Vit ;	//Vitesse en pas/s (attention pas de vitesse n�gative)
} Une_Consigne;


//_________________________________________________________________________________________
void initGenerateur(u16 periodeGenerateurParam, u16 tempsMonteeParam, u16 vitesseMaxParam);
// Initialisation des param�tres du g�n�rateur
//
//   periodeGenerateurParam : p�riode en ms de rafraichissement de la valeur de consigne
//   tempsMonteeParam : temps de mont�e en ms  (tempsMont�e du sch�ma)
//	 vitesseMaxParam : vitesse max en pas/s	  (Vmax du sch�ma)
// Appelez cette fonction avant toute autre fonction de cette lib
//_________________________________________________________________________________________

//_________________________________________________________________________________________
void initTrajectoire(u16 distanceAParcourir);
// 	Initialisation des param�tres pour le calcul d'une 
//   une trajectoire alant de 0 pas � distance_a_parcourir pas
//  en respectant le profil de vitesse
//  Appelez cette fonction apr�s initGenerateur et avant calculConsigneSuivante
//_________________________________________________________________________________________


//_________________________________________________________________________________________
u8 calculConsigneSuivante(void);
//   Calcul la consigne suivante de la trajectoire
//   ATTENTION   Appelez cette fonction PERIODIQUEMENT
//      toutes les 	"periodeGenerateurParam" ms (voir initGenerateur)
//   Elle met � jour la valeur de consigne qui peut �tre lue avec lireConsigne()
//   La fonction renvoie l'�at du g�n�rateur de trajectoire
//	 	1 : g�n�rateur en attente
//		0 : g�n�rateur en cours de calcul de trajectoire
// Le premier appel de cette fonction fait passer l'�tat � 0
// Si la fonction calcule la derni�re valeur de consigne (position finale)
// l'�tat passe � 1
//_________________________________________________________________________________________


//_________________________________________________________________________________________
Une_Consigne lireConsigne(void);
//	Retourne la derni�re consigne calcul�e par calculConsigneSuivantesous
//_________________________________________________________________________________________


//_________________________________________________________________________________________
u16 getCompteurTrajectoire (void);
//   Retourne le num�ro du pas de calcul de la trajectoire
//  � utiliser pour Debug normalement
//_________________________________________________________________________________________


//_________________________________________________________________________________________
u8 getPhase (void);
//   Retourne l'�tat du g�n�rateur
//   		1 : g�n�rateur en attente
//		0 : g�n�rateur en cours de calcul de trajectoire
//_________________________________________________________________________________________

//_________________________________________________________________________________________
#define TRAJECTOIRE_TERMINEE (getPhase())
// vrai lorsque le generateur est � l'arr�t (position 0 avant d�part) ou (position finale)
//_________________________________________________________________________________________

//_________________________________________________________________________________________
#define TRAJECTOIRE_EN_COURS (~getPhase())
// vrai lorsque le generateur est en train de piloter la consigne
//_________________________________________________________________________________________




#endif