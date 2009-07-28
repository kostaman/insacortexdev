#ifndef _LIB_AUTOM_
#define _LIB_AUTOM_

#define TE (2) // en ms ! : p�riode d'�chantillonage du calcul d'int�grale
#define TT (20) // en ms ! :  p�riode d'�chantillonnage du g�n�rateur de trajectoire
#define I_MAX (1.0)
#define I_MIN (-1.0)

//#define Tc  PERIODE_GENERER_TRAJECTOIRE //p�riode des tics du g�n�rateur de trajectoires [tics du Tourniquet]
               // 20[ms] = 20*1ms = 20[tics fu Tourniquet] 



#define TEMPS_MONTEE (200) // en ms ! : temps de mont�e/descente � Vmax [tics du g�n�rateur]
#define VMAX  (800) // Vitesse de croisi�re en pas/s
#define AVEC_APPROCHE // Valide la marche d'approche
//#define SANS_APPROCHE
#define VAPP (35) // Vitesse d'approche de la station en pas/s

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

void Reinit_Etat(int);


unsigned char Iterer_Trajectoire(void);

Un_Etat Lire_Consigne(void);

unsigned int Compteur_Trajectoire (void);
void Init_Trajectoire(unsigned int );


#endif
