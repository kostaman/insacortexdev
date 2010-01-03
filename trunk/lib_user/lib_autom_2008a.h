#ifndef _LIB_AUTOM_
#define _LIB_AUTOM_
#include "standard_types.h"	 

typedef struct {
	s32 I_Pos ;
	s32 Pos ;
	s32 Vit ;
} Un_Etat;


#define TE (0.002) // p�riode d'�chantillonage du calcul d'int�grale


// Lis l'�tat des p�riphs
Un_Etat Lire_Etat_Absolu(void);

Un_Etat Calculer_Etat_Relatif( Un_Etat );
// Lis l'�tat des p�riph et mets � jour l'int�grale de Pos
// ATTENTION il faut un appel p�riodique tout les TE secondes de cette fonction !


void Reinit_Etat(int Longueur_Trajet);

#endif