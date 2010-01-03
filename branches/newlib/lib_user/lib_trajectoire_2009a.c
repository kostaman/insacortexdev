/*
	Auteur : Pascal Acco
	Date : 15/01/2009
	Description : Librairire de generation d'une trajectoire en rampe
	Modifications : 
		- PEH 7/12/09 suppression des m�thodes qui ne font pas partie
	du g�n�rateur de trajectoire 
		- PEH 7/12/09 Suppression de la m�thode d'approche
*/

#include "lib_trajectoire_2009a.h"
//#include "driveurs_2008a.h"

/**
   Constante du g�n�rateur
**/
int tic ;  // en ms :  p�riode d'�chantillonnage du g�n�rateur de trajectoire
int tM ; // en ms : temps de mont�e/descente � vMax
int vMax ;  // Vitesse de croisi�re en pas/s

/**
   Variables de calcul du g�n�rateur
**/
u8 phase = 1;
u16 indexPas ; // nombre de pas de calcul fait par le g�n�rateur
u16 Dist; // en pas : distance du parcours � effectuer
u16 iFM ; // index � partir duquel la mont�e est termin�e
u16 iDF; // index � partir duquel il faut commencer � freiner
u16 iFin; // index auquel le generateur doit terminer sa trajectoire
u16 dV; // Incr�ment/d�cr�ment de vitesse dans les phases de mont�e et descente
float  positionCourante; // Consigne de position
float dP ; // coef d'int�gration de la position
u16 vitesseCourante; // Consigne de vitesse

/**
   Retourne la consigne en position et en vitesse calcul�e par le g�n�rateur
**/
Etat lireConsigne(void)
{	
	Etat consigne;
	consigne.I_Pos = 999;
 	consigne.Pos = (u16) positionCourante;
	consigne.Vit = (u16) (vitesseCourante);
	return consigne;
}

/**
   Initialisation des param�tres du g�n�rateur
**/
void initGenerateur( u16 ticParam,
					 u16 tMParam,
					 u16 vitesseMaxParam) {

	tic = ticParam ; // en ms
	tM = tMParam ; // en ms
	vMax  = vitesseMaxParam ; // Vitesse de croisi�re en pas/s
}

/**
 	Initialisation des param�tres pour une trajectoire
**/
void initTrajectoire(u16 distanceStation)
{
	
	indexPas = 0;

	Dist = distanceStation;

	// Le nombre de pas de calcul en d�pend pas des temps de mont�e !
//	indexFinal = (unsigned int)(((long unsigned int)(Dist)*1000L)/(long unsigned int)(vMax*tic));

	iFM = (u16)(tM/tic);
	dV = vMax/iFM;  //incr�ment de vitesse par p�riode du g�n�rateur pour la rampe

	iDF = (u16) ( ((u32)Dist * (u32)1000UL) / ((u32)vMax*(u32)tic) );

	iFin = iDF + iFM ;
	dP=((float)tic) / 2000.0;
	
	vitesseCourante=0;
	positionCourante=0.0;

	phase = 0;
}

 /**
   Retourne le num�ro du pas de calcul de la trajectoire
**/
u16 GetCompteurTrajectoire (void)
{
   return indexPas;
}

 /**
   Retourne l'�tat du g�n�rateur
   		1 : g�n�rateur en attente
		0 : g�n�rateur en cours de calcul de trajectoire
**/
u8 getPhase (void)
{
   return phase;
}

/**
   Calcul le pas suivant de la trajectoire
**/
unsigned char calculConsigneSuivante(void)
{
	u16 Vitesse_Precedente=vitesseCourante;
	phase = 0;

	indexPas++;
		
	if (indexPas <= iFM)
	{
		vitesseCourante = vitesseCourante + dV;
	}
	else if (indexPas <= iDF)
	{		
		vitesseCourante = vMax;
	}
	else if (indexPas <= iFin)
	{		
		vitesseCourante = vitesseCourante - dV;
	}
	else
	{
		vitesseCourante = 0;
		phase = 1;
	}
	
	if (phase == 0) 
	{
		positionCourante = positionCourante + (float)(vitesseCourante+Vitesse_Precedente)*dP;
	}
	else 
	{
		positionCourante = Dist;
	}

	return phase;			
}



