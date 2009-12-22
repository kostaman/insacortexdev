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
int periodeGenerateur ;  // en ms :  p�riode d'�chantillonnage du g�n�rateur de trajectoire
int tempsMontee ; // en ms : temps de mont�e/descente � vitesseMaximale
int vitesseMaximale ;  // Vitesse de croisi�re en pas/s

/**
   Variables de calcul du g�n�rateur
**/
unsigned int phase = 1;
unsigned int indexPas ; // nombre de pas de calcul fait par le g�n�rateur
unsigned int distanceDuParcours; // en pas : distance du parcours � effectuer
unsigned int indexFinMontee ; // index � partir duquel la mont�e est termin�e
unsigned int indexDebutFreinage; // index � partir duquel il faut commencer � freiner
unsigned int indexFinTrajectoire; // index auquel le generateur doit terminer sa trajectoire
unsigned int incrementVitesse; // Incr�ment/d�cr�ment de vitesse dans les phases de mont�e et descente
float  positionCourante; // Consigne de position
unsigned int vitesseCourante; // Consigne de vitesse

/**
   Retourne la consigne en position et en vitesse calcul�e par le g�n�rateur
**/
Etat lireConsigne(void)
{	
	Etat consigne;
	consigne.I_Pos = 999;
 	consigne.Pos = (unsigned int) positionCourante;
 	//consigne.Vit = (unsigned int) ((float)vitesseCourante*KD);
	consigne.Vit = (unsigned int) (vitesseCourante);
	return consigne;
}

/**
   Initialisation des param�tres du g�n�rateur
**/
void initGenerateur(int periodeGenerateurParam,
					 int tempsMonteeParam,
					 int vitesseMaxParam) {

	periodeGenerateur = periodeGenerateurParam ; // en ms
	tempsMontee = tempsMonteeParam ; // en ms
	vitesseMaximale  = vitesseMaxParam ; // Vitesse de croisi�re en pas/s
}

/**
 	Initialisation des param�tres pour une trajectoire
**/
void initTrajectoire(unsigned int distanceStation)
{
	
	int indexFinal;

	indexPas = 0;

	distanceDuParcours = distanceStation;

	// Le nombre de pas de calcul en d�pend pas des temps de mont�e !
	indexFinal = (unsigned int)(((long unsigned int)(distanceDuParcours)*1000L)/(long unsigned int)(vitesseMaximale*periodeGenerateur));

	indexFinMontee = ((unsigned int)(tempsMontee/periodeGenerateur));

//	indexFinal = (unsigned int)(((long unsigned int)(distanceDuParcours-(indexFinMontee*periodeGenerateur*vitesseMaximale))*1000L)/(long unsigned int)(vitesseMaximale*periodeGenerateur));

	indexDebutFreinage = indexFinal - indexFinMontee ;	

	indexFinTrajectoire = indexFinal ;
	
	incrementVitesse = vitesseMaximale/indexFinMontee;  //incr�ment de vitesse par p�riode du g�n�rateur pour la rampe
	vitesseCourante=0;
	positionCourante=0.0;

	phase = 0;
}

 /**
   Retourne le num�ro du pas de calcul de la trajectoire
**/
unsigned int GetCompteurTrajectoire (void)
{
   return indexPas;
}

 /**
   Retourne l'�tat du g�n�rateur
   		1 : g�n�rateur en attente
		0 : g�n�rateur en cours de calcul de trajectoire
**/
unsigned int getPhase (void)
{
   return phase;
}

/**
   Calcul le pas suivant de la trajectoire
**/
unsigned char calculConsigneSuivante(void)
{
	unsigned int Vitesse_Precedente=vitesseCourante;
	phase = 0;

	indexPas++;
		
	if (indexPas < indexFinMontee)
	{
		vitesseCourante = vitesseCourante + incrementVitesse;
	}
	else if (indexPas <= indexDebutFreinage)
	{		
		vitesseCourante = vitesseMaximale;
	}
	else if (indexPas <= indexFinTrajectoire)
	{		
		vitesseCourante = vitesseCourante - incrementVitesse;
	}
	else
	{
		vitesseCourante = 0;
		phase = 1;
	
	}
	
	if (phase == 0) 
	{
		positionCourante = positionCourante + (float)((vitesseCourante+Vitesse_Precedente)*periodeGenerateur)/2000.0;
	}
	else 
	{
		positionCourante = distanceDuParcours;
	}

	return phase;			
}



