/*
_______________________________________________________________________________
			             G�n�rateur de trajectoires
_______________________________________________________________________________

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

*/

#ifndef _LIB_TRAJ_
#define _LIB_TRAJ_

#include "standard_types.h"	  


typedef struct {
	u16 Pos ;
	u16 Vit ;
} Une_Consigne;

/**
   Initialisation des param�tres du g�n�rateur
   	- p�riode en ms
   	- temps de mont�e en ms
	- vitesse max en pas/s
**/
void initGenerateur(u16 periodeGenerateurParam, u16 tempsMonteeParam, u16 vitesseMaxParam);

/**
 	Initialisation des param�tres pour une trajectoire
		- distance � parcourir en nombre de pas
**/
void initTrajectoire(u16 distanceAParcourir);

/**
   Calcul la consigne suivante de la trajectoire
**/
u8 calculConsigneSuivante(void);

/**
	Retourne la consigne calcul�e sous forme d'un �tat
**/
Une_Consigne lireConsigne(void);

/**
   Retourne le num�ro du pas de calcul de la trajectoire
**/
u16 getCompteurTrajectoire (void);

 /**
   Retourne l'�tat du g�n�rateur
   		1 : g�n�rateur en attente
		0 : g�n�rateur en cours de calcul de trajectoire
**/
u8 getPhase (void);




#endif