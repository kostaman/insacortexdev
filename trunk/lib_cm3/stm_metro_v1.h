/*
________________________________________________________________________________________
	STM32 peripherals lib for use with INSA subway project
	stm_metro_v1.h
________________________________________________________________________________________
USAGE
	??? is the name of the library i.e. stm_metro_v1
	RELPATH is the relative path from your projetc directory to lib_cm3 directory	
	
   	include RELPATH/lib_cm3/???.c file in your makefile
	copy    RELPATH/lib_cm3/???_config_TEMPLATE.h in your project directory	(noted ./)
	rename  ./???_config_TEMPLATE.h as ./???_config.h in your project directory
	edit    ./???_config.h file for your project (lines with //CONF tags)  
	ensure that ./ path is visible in CC compiler options 
	add "#include "RELPATH/lib_cm3/???.h" in app. code 
	add a call to "Init_???();" at initialisation step of your APP
________________________________________________________________________________________
REVS
	[Acco 06/01/2010] finalisation et commentaires de la premi�re version
_______________________________________________________________________________________
TODO
	+ Mesure courant ADC avec DMA 
	+ config fr�aquence mesure de courant
	Am�liorer la fr�quence de mesure de la vitesse pour les basse vitesses
______________________________________________________________________________________
*/
#ifndef __STM_METRO
#define __STM_METRO

#include "stm_metro_v1_config.h"


//__________________________________________________________
extern void Init_Periphs(void);	
// Appelez cette fonction avant toute utilisation de p�riph
// 	Initialise les clocks selon stm_clock
//  Initialise les periphs 
//  	Position = 0
//  	PWM � l'arret
// 		Vitesse = 0 (Arr�t de mesure)
//      Mesure de courant en boucle  
//__________________________________________________________




#ifdef USE_POSITION
	//__________________________________________________________
	extern  s16 Lire_Position(void);
	// utilise le TIMER 3 en mode encod incremental-3 (compte et d�compte)
	// pour mesurer la position relative. Codeurs branch�s sur PORTA.6 et PORTA.7
	// s16 nombre de pas relatifs en sign�  -32535 � 32536 max !!!
	// Pas de signalement d'overload ! 
 	//__________________________________________________________

	//__________________________________________________________
	extern void Set_Position(s16 pos) ;
	// Initialise le compteur de pas � la valeur pos
	// pos nombre de pas relatifs en sign�  -32535 � 32536 max !!!
	//__________________________________________________________

	//_________________________________________________________
	// Nombre de pas dans la boucle du circuit en salle 113
	// valeur donn�e une incertitude de +-5mm	
	#define NB_PAS_BOUCLE (27792)  
	 	
#endif

#ifdef USE_SPEED
	//__________________________________________________________
	extern  u16 Lire_Vitesse(void);	
	// Utilse le TIMER 4 et les interruptions sur front haut de PORTA.6
	// des entr�es du codeur incr�mental pour mesurer la vitesse.
	// Frequence du Timer4 configur�e dans ./stm_metro_v1_config.h	
	// ATTENTION la valeur est positive quelque soit le sens de d�placement
	// 			u16 = |vitesse| en pas/s
	// ATTENTION la vitesse est mise � jour uniquement sur front haut de
	// PORTA.6 (tout les 4 pas). La mesure peut donc �tre assez vieille
	// 	si la locomotive se d�place lentement : 
	//  		Freq mesure = vitesse[pas/s]/4
	// ATTENTION la vitesse est d�clar�e nulle sur deuxi�me overload de
	//  Timer 4 soit environ au bout 0.3 secondes sans front montant
	//__________________________________________________________

#endif

#ifdef USE_PWM
	//__________________________________________________________
	extern void Fixe_Rapport(s16);
	// commande le rapport cyclique du PWM de commande du moteur
	// TIMER 2 en mode PWM edge aligned pr�cision de 12 bits
	// Frequence configur�e dans ./stm_metro_v1_config.h
	//___
	// PWM bipolaire : 12V ou 0V en sens direct, 0V ou -12V en sens inverse
	// s16 > 0 => TIM_CH2 (sens direct) => PWM sur  PA.1  LED_AVANCE allum�e
	// s16 < 0 => TIM_CH3 (sens inverse)=> PWM sur  PA.2  LED RECULE allum�e
	// s16 = 0 => TIM2 arr�t� => PA.1 et PA.2 � 0  LEDs �teintes.
	//___ 
	// s16 doit �tre entre [-0x0FFF 0 0x0FFF] soit [-4095 0 4095] 
	// sinon la valeur est satur�e dans l'intervalle
	//  valeur = min(4095,max(-4095,s16))
	// Vmoteur = valeur/0x0FFF * 12 Volts
	// Utilisez les RAPPORT_MAX etc. ci-dessous pour vos calculs
	//__________________________________________________________

	#define RAPPORT_MAX (0x0FFF)
	#define RAPPORT_MIN (-0x0FFF)
	#define RAPPORT_ARRET (0)
#endif

#ifdef USE_ADC 
	//__________________________________________________________
	extern  u16 Lire_courant(void);
	// Retourne le courant mesur� par r�sistance chunt de 6 Ohms
	// filtre analog passe bas R=12kOhms et C=47nF
	// Mesure par PORTC.2/ADC_IN12 (ADC interruptif)
	// Attention la mesure est toujours positive quelque 
	// soit le sens de passage du courant
	// ADC 12 bit, align� � droite, 3.3V en pleine �chelle
	// u16 = I*6 *0x0FFF / 3.3  
	//__________________________________________________________
#endif

#endif
