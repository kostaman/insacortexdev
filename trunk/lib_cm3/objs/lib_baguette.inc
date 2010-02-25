;/*****************************************************************************/
;/* Fichier "include" pour les fonctions de lib_baguette                      */
;/*****************************************************************************/


;________________________________________________________________________________________
; void Init_Baguette(void);
 EXTERN Init_Baguette [CODE]
; IN: 	Rien
; OUT: 	Rien
; REG. ALT. : R0-R2, R14, R15
;________________________________________________________________________________________
;
; Initialise le syst�me et les p�riph�riques li�s � la baguette :
;  - initialise les horloges  du coeur et des p�riphs 
;     + coeur � 40 MHz cadenc� par le quartz ext�rieur (8MHz) multipli� par PLL interne
;	 + low speed p�riph APB1 � 20MHz, high speed APB2 � 40MHz
;	 + ADC � 5MHz
;  - initialise les p�riph�riques reli�s � l'�cran LCD de la carte MCBSTM32
;  	 + IO_Ports du PORT C broches 0,1,2,3 et 10,11,12 : not� PC.0-3 et PC.10-12
;  - liaison s�rie 	(utilis�e en simul�e pour mimer l'�cran LCD)
;  	 + USART1 � 9600 bauds en mode POLLING sur broches PA.9 PA.10
;  - ADC pour mesure analogique des acc�l�ros (baguette)  et potentiom�tre de saisie (MCBSTM32)
;     + ADC1 en conversion continue de la s�quence AIN1 (pot) , AIN14(acc�l X), AIN15(accel Y)
;	 + DMA1 channel 1, r�cup�re les conversion ADC et stocke dans buffer tournant en continu
;	 + ADC1 Analog watchdog du canal AIN14 et g�n�ration d'interruption sur passage de seuil de AIN14
;  - init timers pour cadencer clignottements mesures etc. par interruptions	et niveau des handlers d'interruption
;  	 + systick timer (core) : p�riode de 800ns, timer arr�t�, interruption  "SysTick_Handler" de niveau 13
;	 			pour cadencer le clignottement des diodes
;	 + Analog watchdog interruption "ADC_IRQHandler" de niveau 14
;	 			pour rep�rer les phase d'aller/retour du mouvement de secousse de baguette
;	 + TIM1 (APB2) 	: p�riode 100ms, timer arr�t�, interruption "TIM1_UP_IRQHandler" de niveau 15
;	  			pour autres taches si besoin est...
;   - init des IO ports pour allumer les LEDs de la baguette reli�es aux leds de la carte MCBSTM32
;     + broche du port B : PB8 � PB15 en sorties push/pull  (diodes MCB allum�es par un 1, diodes baguettes �teintes)
;   - init des IO ports pour recevoir l'appuis des bouton poussoirs TAMP et WKUP de MCBSTM32
;     + bouton TAMP utilis� en tant que bouton Valider : PA.1 en entr�e	  (re�oit un 0 pour appuy� et 1 sinon)
;	 + bouton WKUP utilis� en tant que bouton Effacer : PC.13 en entr�e	  (re�oit un 0 pour appuy� et 1 sinon)
;_______________
;  TOUJOURS appeler cette fonction en d�but de programme (1 seule fois) 
;     avant d'utiliser les autres fonctions de cette librairie.
;
;________________________________________________________________________________________


;________________________________________________________________________________________
BOUTON_EFFACER equ 1
BOUTON_VALIDER equ 2
; int Lire_Touche(int button);
 EXTERN Lire_Touche [CODE]
; IN: 
;              R0: Bouton � lire
;                      1 = Bouton Effacement (BOUTON_EFFACER)
;                      2 = Bouton Validation (BOUTON_VALIDER)
; OUT: 	Rien
;              R0: Etat du bouton
;                      0 = Bouton appuy�
;                      Different de 0 = Bouton relach�
; REG. ALT. : R0-R2, R14, R15
;________________________________________________________________________________________
;  Lecture de l'�tat d'une touche de la carte MCBSTM32 
;   PC.13 (TAMP) -> Validation 
;   PA.0  (WKUP) -> RAZ 
;  Attention renvoie 0 pour "bouton appuy�" (cabl�ge inverse sur MCBSTM32)
;________________________________________________________________________________________



;________________________________________________________________________________________
;void Ecrit_LED(int val);
 EXTERN Ecrit_LED [CODE]
; IN: 
;     R0.0-R0.7: Valeur � envoyer sur les diodes
; OUT: 	Rien
; REG. ALT. : R1-R2, R14, R15
;________________________________________________________________________________________
;   Copy en octet en sortie sur port PB.8-PB.15
;      ATTENTION, un 1 logique allume les diodes de MCBSTM32 
;                              mais etteind celles de la baguette  (montage inverse)
;________________________________________________________________________________________





;________________________________________________________________________________________
; void Acquite_ADC(void);
 EXTERN Acquite_ADC [CODE]
; IN:  rien
; OUT: 	Rien
; REG. ALT. : R15
;________________________________________________________________________________________
;	Acquite la drapeau d'interuption Analog Watchdog (AWD) de l'ADC
;________________________________________________________________________________________



;/* 
; * Fonction: 	Demarre_SYSTICK
; * Role: 		Lance le timer SYSTICK ( pour le clignotement des led )
; * Entr�e: 		Rien
; * Sortie: 		Rien
; */
 EXTERN Demarre_Systick

;/* 
; * Fonction: 	Arrete_SYSTICK
; * Role: 		Arrete le timer SYSTICK ( pour le clignotement des led )
; * Entr�e: 		Rien
; * Sortie: 		Rien
; */
 EXTERN Arrete_Systick

;/* 
; * Fonction: 	Demarre_Timer1
; * Role: 		Lance le timer 1 (pour le rafraichissement de l'interface)
; * Entr�e: 		Rien
; * Sortie: 		Rien
; */
 EXTERN Demarre_Timer1

;/* 
; * Fonction: 	Arrete_Timer1
; * Role: 		Arrete le timer 1 (pour le rafraichissement de l'interface)
; * Entr�e: 		Rien
; * Sortie: 		Rien
; */
 EXTERN Arrete_Timer1

;/ * Fonction: 	Acquite_Timer1
; * Role: 		Acquite la drapeau d'interuption du timer 1 
; * Entr�e: 		Rien
; * Sortie: 		Rien
; */
 EXTERN Acquite_Timer1

;/* 
; * Fonctions pour la gestion de l'ecran LCD 
; */

;/* 
; * Fonction: 	Efface_Ecran
; * Role: 		Efface l'ecran LCD
; * Entr�e: 		Rien
; * Sortie: 		Rien
; */
 EXTERN Efface_Ecran

;/* 
; * Fonction:	Ecrit_Ecran
; * Role: 		Ecrit un caractere sur l'ecran LCD
; * Entr�e: 
; *		R0: Octet de poids faible contient l'octet a ecrire
; * Sortie: 		Rien
; */
 EXTERN Ecrit_Ecran

;/* 
; * Fonction:	Ecrit_Chaine_Ecran
; * Role: 		Ecrit d'une chaine de caractere l'ecran LCD
; * Entr�e: 
; *		R0: @ de la chaine (la chaine se termine par un caractere NULL (0x00))
; * Sortie: 		Rien
; */
 EXTERN Ecrit_Chaine_Ecran

;/* 
; * Fonction: 	Position_Curseur
; * Role: 		Positionne le curseur sur l'ecran LCD
; * Entr�e: 
; *      R0: contient l'offset sur une ligne (coordonn�e X), entre 0 et 19
; *      R1: contient l'identifiant de ligne (coordonn�e Y), entre 0 et 1
; * Sortie: 		Rien
; */
 EXTERN Position_Curseur

;/* 
; * Fonctions pour la gestion de l'ADC 
; */

;/* 
; * Definition (EQU) a utiliser avec Lire_ADC
; */
ADC_POTENTIOMETRE 	EQU		0
ADC_X				EQU		1
ADC_Y 				EQU		2

;/* 
; * Fonction: 	Lire_ADC
; * Role: 		Lecture de la valeur d'un canal de l'ADC
; * Entr�e: 		
; *		R0:	Canal ADC � lire.
; *			0 = Potentiometre
; *			1 = Accelerometre voie X
; *			2 = Accelerometre voie Y
; * Sortie: 
; *		R0: Valeur ADC (12 bits de poids faible)
; */
 EXTERN Lire_ADC
 EXTERN Analog_Dog_Watch_For_Higher_Than [CODE]
 EXTERN Analog_Dog_Watch_For_Lower_Than [CODE]

 END