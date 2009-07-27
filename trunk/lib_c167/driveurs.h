#ifndef _DRIVEURS_H
#define _DRIVEURS_H


// !!!!!Les autorisations d'IT sont � faire dans le main (gestion priorit�, autorisation
// individuelle, autorisation globale !!!


//=================================================================================================
 
// auteur: T.Rocacher
// date : 26 sept 06
// processeur: C167
// Enseignement : 5TRS - Trottinettes en serie
// Langage : C
//
// Bilioth�que qui permet de commander la trottinette (PWM1), de lire la vitesse (ADC P5.5)
// et de lire la position (deux optocoupleurs en quadrature  sur P2.8 et P2.9)
//
//=================================================================================================



void Config_ADConverter(void);
//________________________________________________________________
// ROLE : R�gle l'ADC en single, sur la voie P5.5, r�gle l'aquisition  
//		  aux evirons de 10us.
// DUREE : non mesur�e, pas important
// TEST (r�sum�) : voir fonction suivante
//________________________________________________________________

float Lire_Vitesse();
//________________________________________________________________
// ROLE : renvoie la vitesse en m/s (float). ADC en scrutation
// DUREE : 33us environ
// TEST (r�sum�) : SIMU seule. Test�e pour 0V, 2.5V et 5V
//________________________________________________________________


void Config_Capture(void);
//________________________________________________________________
// ROLE : initialise l'unit� CAPCOM sur les voies P2.8 et P2.9
//		  En interne 2 fonctions d'interruption g�rent les captures CC8 et CC9
//		   !! g�rer compl�tement les IT dans le main !!
// DUREE : non mesur�e, pas important
// TEST (r�sum�) : voir fonction suivante
//________________________________________________________________


int Lire_Position(void);
//________________________________________________________________
// ROLE :  permettent de lire position en nbr de pas. Elle est 
//         donn�e modulo 30000 pas 	
//        1 pas vaut 2.PI/96 d'angle de roue soit environ 4.25mm  pour une roue de 13cm de diametre.
// DUREE : 23us	
// TEST (r�sum�) : SIMU seule, test2.ini pour les stimuli d'optocoupleur, 
//			opto() pour le sens up
//			optorev() pour le sens down. Pour plus d'info sur les tests voir directement 
//			les commentaires du .c.
//________________________________________________________________


void Init_Position(int Position_Initiale);
//________________________________________________________________
// ROLE : Positionne la trottinette, valeur en pas obligatoirement positive et < 30000
//        1 pas vaut environ 4.25mm  .
//		  Si la valeur n'est pas dans ce cadre, on proc�de � une saturation (0 et 30000) 
// DUREE : 67us	
// TEST (r�sum�) : SIMU seule, fonctionne correctement, pour plus s'infos voir directement 
//			      les commentaires du .c.
//________________________________________________________________


void Config_PWM(void);
//________________________________________________________________
// ROLE : Configure l'unit� PWM 1  (P7.1 ), � 20kHz, PWM de 1 � 1023 inclus
// DUREE : non mesur�e, pas important	
// TEST (r�sum�) : Voir fonction suivante 
//________________________________________________________________



void Fixe_Rapport(float Sigma);
//________________________________________________________________
// ROLE : donne la consigne de courrant � la trottinette [-1 � +1]
// 		  saturation non g�r�e sur le float. La saturation de sortie est g�r�e [1 1023] 
//        L'arret de la tritinnette est command� par "Fixe_Courrant(0);"
// DUREE : 50us environ (du au calcul flottant vers int)
// TEST (r�sum�) :test� en simu. conforme pour des valeurs de -1 � +1 OK
// test� pour -50.0 et +50.0 (n'importe quoi !) ok, saturation correcte de la PWM 
//________________________________________________________________



void initLED(void);
//________________________________________________________________
// ROLE : Initialise le port 2 pour les 2 LEDS. Les 2 LEDs sont 
//   �teintes au d�part
// DUREE : ?
//________________________________________________________________

void modifierLed1(void);
void modifierLed2(void);
//________________________________________________________________
// ROLE : Change l'�tat de la LED 1 ou 2 du port 2
// DUREE : ?
//________________________________________________________________



//=================================================================================================
//
//       Commentaires th�oriques (rapport entre tr/min, m.s, km/h opto....
//
//=================================================================================================
 

//___________________Capture___________________________________
//
// calcul th�orique
//------------------
// La fr�quence maximale des pulses issus des opto est d�finie de la mani�re suivante :
// diam�tre de la roue # 13cm.
// nombre de pas : 24 lignes noires, 24 balanches => 24 p�riodes.
//                 r�solution * 4 en prenant tous les fronts, sur les 2 signaux
//					= 96 pulses par tours
// vitesse maxi = 12km/h
// 
// => Froue = Om�ga/2pi = Vlin/(2.pi.Droue/2)= Vlin/(pi.Droue)
// et Vlin (m/s) = V(km/h). 1000/3600 = V(km/h)/3.6
// => Froue = Vlin(km/h)/(pi.Droue.3,6) 
// AN � 12km/h, Froue = 8,16 Hz.
//
// Le nombre de pas �tant 96, la fr�quence du signal issu des opto vaut 784Hz environ.
// Cela signifie qu'� plein vitesse, il s'�coule 1/784 = 1,275 ms entre deux pulses.
//
// Un pulse correspond � une avanc�e de pi.D/96 = 4,25mm.
// Le comptage d'impulsion se fera modulo 30 000 (127,6m)

// valeurs � pr�ciser sur les pas

// La mesure se fait sur IT fronts desc et montant de P2.8 et P2.9.






#endif