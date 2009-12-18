//anim.h	Librairie de communication avec Matlab pour stocker les donn�es
#include <structDonnees.h>


// Le type de la variable contenant l'angle
#define TYPE int

// Le genre d'animation
// 1 -> Affichage sur une ligne / valeurs
// 2 -> 1 Chariot par ligne et roues qui tournent (scrolling obligatoire)
// 3 -> Tout sur une lige avec espacements variables
#define GENRE 1

#define LARGEUR (80) //largeur de l'�cran � ne pas trop d�passer
#define ECART_MAX (500) //�crat � partir l'affichage d�connerait
#define UNITEES ((ECART_MAX*NB_TROT)/LARGEUR)

// SCROLLING=1 => l'affichage est d�roulant \n
// SCROLLING=0 => affichage sur la ligne \r
#define SCROLLING 0

extern void Choix_signal(void); 
extern int EcrireMatInt (char *,int , int *);

//Envoie des entiers a Matlab
//Le premier parametre correspond au nombre d'entier envoy�s
//Le deuxi�me parametres est la tableau d'entiers a envoyer
extern void EnvoyerEchantillonPosition(int ,int * );

//Demande la distance entre la station courrante et la station suivante
//Retourne la distance � parcourir en pas
extern int DemanderDistanceProchaineStation(void);