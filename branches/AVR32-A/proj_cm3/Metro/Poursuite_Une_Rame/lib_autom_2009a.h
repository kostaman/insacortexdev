/*
________________________________________________________________________________________
 Petites fonctions de calcul de retour d'�tat pour le BE 5TRS locomotives 
 	lib_autom_2009a[_TEMPLATE].h
    GPL licensed code (P. Acco)
________________________________________________________________________________________
USAGE

	copy /lib_users/lib_autom_2009a_TEMPLATE.h as ./lib_autom_2009a.h 
	    in your project directory
	configure the local .H

	add include "./lib_autom_2009a.h in your application
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
__________________________________________________________________________________
  Calcule l'int�grale de l'erreur de position par rapport � la consigne (variable statique)
  Fournit des fonctions de r�init de l'�tat de la rame de m�tro en utilisant
    la librairie de p�riph�riques
  Fournit une fonction de calcul de retour d'�tat de la voiture

*/

#ifndef _LIB_AUTOM_
#define _LIB_AUTOM_


#include "standard_types.h"	 

// CONFIGURE the line below
#define LIB_DRIVEURS "stm_metro_v1.h"
//Librairie offrant les primitives
// Set_Position(pos), Lire_Position(), Lire_Vitesse()
// RAPPORT_MAX
// RAPPORT_MIN

//CONFIGURE the line below
#define TE (0.002) // p�riode d'�chantillonage du calcul de la commande
				// et donc de l'int�gration d'erreur de position


// Limitation du windup de l'int�grateur d'erreur de position
// Une bonne valeur est Max_Commande/Max_Ki o� Ki est le gain d'int�grale
#define I_MAX (RAPPORT_MAX/100.0) //Limite SUP de l'int�grateur
#define I_MIN (-RAPPORT_MIN/100.0)//Limite SUP de l'int�grateur


// Vecteur d'�tat relatif d'une rame de m�tro
typedef struct {
	s32 Pos ;	// Position en pas (sign�e)
	s32 Vit ;   // Vitesse en pas/s (sign�e)
	s32 I_Pos ;	// Int�grale de l'�rreur de position (pas.s)  (sign�e)
} Etat;



//_____________________________________________________________
void reinitEtat(u16 longueurTrajet)	  ;
//	Initialise l'�tat en fin d'une poursuite de trajectoire
//  longueurTrajet : position finale en pas donn�e au g�n�rateur 
//                    de trajectoire
// cette fonction agit directement sur la librairie 
//      de p�riph�riques
// ATTENTION : appelez cette fonction avant de reg�n�rer la trajectoire
// ATTENTION : Lors de la premi�re trajectoire il convient de faire un 
// Set_Position(longueurTrajet); puis un reinitEtat(longueurTrajet);
// de mani�re � initialiser la position � 0 comme si une
// trajectoire avait parfaitement �t� suivie
//______________
//		position <- longueurTrajet - position courante (Lire_Position())
//		vitesse <- 0
//		I position <-0	
//_____________________________________________________________


//_____________________________________________________________
Etat calculerEtatRelatif(s32 pos, s32 vit)	  ;
// pos : valeur de la consigne de position
// vit : valeur de la vitesse de consigne
//
// Lis l'�tat via les p�riphs, calcul les erreur de position et vitesse 
//  et l'int�grale de l'erreur de Pos (backward euler)
// ATTENTION il faut un appel p�riodique tout les TE secondes de 
//   cette fonction !  sinon le calcul est fauss�
// La valeur de l'int�grateur est born�e par I_MAX et I_MIN
//_____________________________________________________________


//_____________________________________________________________
 float calculerCommande(Etat rame, float gains[3]);
// rame : un �tat contenant l'erreur d'�tat d'une voiture par rapport 
//     � la consigne
// gains : un vecteur des gains de commande {Ki Kp Kv}
// renvoie la valeur de la commande en float
// com = Ki * Err_Integrale_Pos + Kp * Err_Pos + Kv*Err_Vit
//_____________________________________________________________

#endif