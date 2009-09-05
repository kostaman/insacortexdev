#ifndef _LIB_AUTOM_
#define _LIB_AUTOM_

#define TE (0.002) // p�riode d'�chantillonage du calcul d'int�grale
#define I_Max (1.0)
#define I_Min (-1.0)

typedef struct {
	signed int Pos ;
	signed int Vit ;
	signed int I_Pos ;
} Un_Etat;

// Lis l'�tat des p�riphs
Un_Etat Lire_Etat_Absolu(void);

Un_Etat Calculer_Etat_Relatif( Un_Etat );
// Lis l'�tat des p�riph et mets � jour l'int�grale de Pos
// ATTENTION il faut un appel p�riodique tout les TE secondes de cette fonction !


void Reinit_Etat(int Longueur_Trajet);

#endif