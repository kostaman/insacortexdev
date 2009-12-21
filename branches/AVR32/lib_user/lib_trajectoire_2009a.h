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

#ifndef _LIB_AUTOM_
#define _LIB_AUTOM_



typedef struct {
	signed int Pos ;
	signed int Vit ;
	signed int I_Pos ;
} Etat;

/**
   Initialisation des param�tres du g�n�rateur
   	- p�riode en ms
   	- temps de mont�e en ms
	- vitesse max en pas/s
**/
void initGenerateur(int periodeGenerateurParam, int tempsMonteeParam, int vitesseMaxParam);

/**
 	Initialisation des param�tres pour une trajectoire
		- distance � parcourir en nombre de pas
**/
void initTrajectoire(unsigned int distanceAParcourir);

/**
   Calcul la consigne suivante de la trajectoire
**/
unsigned char calculConsigneSuivante(void);

/**
	Retourne la consigne calcul�e sous forme d'un �tat
**/
Etat lireConsigne(void);

/**
   Retourne le num�ro du pas de calcul de la trajectoire
**/
unsigned int GetCompteurTrajectoire (void);

 /**
   Retourne l'�tat du g�n�rateur
   		1 : g�n�rateur en attente
		0 : g�n�rateur en cours de calcul de trajectoire
**/
unsigned int getPhase (void);

#endif