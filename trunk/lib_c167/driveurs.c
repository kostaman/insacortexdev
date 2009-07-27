// Librairie de gestion des PERIPHs
//+ Capsul�e par ACCO : Inclusion des LEDS et de lib__capcom (thierry v3_1) 
//+ Retouchee par Hugues le 21/12/2006. Rend le biblith�que de p�riph ind�pendante 
//de l'application 	=> la position est retourn�e en entier (on ne connait pas le pas)
//Fixe_Vitesse est en fait fixe courrant et la plage est donn�e entre +-1.


#include <c167cs.h>
// entr�es des codeurs incr�mentaux
sbit Opto_8=P2^8;
sbit Opto_9=P2^9;



//=================================================================================================
//
//       Commentaires  :   Version 3_1
//      
//
//  
//
// NB: les gestions de niveau d'IT seront faites dans le main !
// La position est maintenant g�r�e sans modulo.
//
//______________________________________________________________________
// Test effectu�s:
// init � 10m. Avanc�e de 9m environ, recul idem => aucun pas rat�, l'overflow se passe bien � priori
// init � 10m, avanc�e de 100m environ, recul idem, aucun probl�me
// init � 0m, avanc�e de 170mn recule de 170m, aucun pb.
// 
// NB: la pr�cision est due au pas estim�e de la roue ( 0.004254236)  , li� au diam�tre...


//___________________ADC___________________________________
//
// Voici la correspondance : [-12km/h  0km/h  +12km/h] = [-3.333.. m/s  0  +3.333..m/s] =>[0  2V5  5V]
// Test	(simu seule)
// Conforme pour les 3 valeurs de l'intervalle 
// La fonction Lire_Vitesse() dure 33us environ, dont 11us pour l'acquisition en scrutation
// et 22 us pour le calcul flottant.


//___________________PWM___________________________________
//
// Sur la voie 7.1 (simu)
// test� en simu. conforme pour des valeurs de -1.0 � +1.0 OK
// test� pour -50.0 et +50.0 (n'importe quoi !) ok, saturation correcte de la PWM
// dur�e de la fonction Fixe_vitesse(..) : 50us environ (du au calcul flottant vers int)

//__________________LEDS____________________________________
//Bibliotheque de gestion d'une LED pour la prise en main de tiny



//=================================================================================================
// unite Capcom, variables permanente globale � ce fichier______________________
// elles sont fig�es en RAM
int N_Pulse;




//=================================================================================================
//
//       Les sous-programmes
// 	
//=================================================================================================



//______________________________________________________________________________________________
//
//  Config_ADConverter 
//  r�gle le timing de l'�chantllonneur du c167 et prot�ge les voies 6 et 7 du bruit num�rique 
//  Ressources utilis�es :
// 	 
//   
//______________________________________________________________________________________________

//______________________________________________________________________________________________
//
//  Config_ADConverter 
//  place P5.5 en entr�e
// configure l'ADC Tconv #9.7us channel 5
// 	 
//   
//______________________________________________________________________________________________

void Config_ADConverter(void)
{
// P5.5 =>	

// deconnexion des circuits num�riques du port P5 (bruit, P5.5)
P5DIDIS=P5DIDIS | 0x0020;

// config de l'ADC:
// Mode simple,CAIN=33pF, Rsource # 1000 => charge OK � 5*RC = 165ns = ts.
// Configur� comme suit, � 20MHz => Tconv = tBC*8 + 40tBC + 2 tCPU 
//										  = 48*tCPU*4 + 2tCPU = 194/20Meg = 9,7 us
//										dont  ts = 8*tBC = 8*4/20M = 1,6us >> 165ns: OK
//

 
// ADCON = 0000 xxxx  xx00 0101
ADCON=ADCON|0x0005;
ADCON=ADCON&0x0FC5;
}


   



//______________________________________________________________________________________________
//
// float Lire_Vitesse();
// lit la valeur lue par l'ADC, en float : 
// [-12km/h  0km/h  +12km/h] = [-3.333.. m/s  0  +3.333..m/s] =>[0V  2V5  0V]
// 	 
//   
//______________________________________________________________________________________________

float Lire_Vitesse()
{
float Vitesse_Lue;
int Nbre;

// Start
ADST=1;
while(ADBSY)
	{};
Nbre=ADDAT & 0x03FF;
// [0V  5V] =>[0  1023]
Nbre=Nbre-512;
// [0V  5V] =>[-512  +511]

Vitesse_Lue=((float)Nbre)*0.00651042;
// [0V  5V] =>[-3.33sm/s  +3.326m/s] (=[-12km/h + 12km/h])

return(Vitesse_Lue);
}



//______________________________________________________________________________________________
//
//  
//   
//______________________________________________________________________________________________

void Config_Capture(void)
{

// initialisation  CAPCOM2
// utilisation des broches P2.8 et P2.9 en IT (cc8io et cc9io)
// fronts montant et descendants:  reg CCM2
// CCMOD8 = 011 (positive & negative edge)
// CCMOD9 = 011 (positive & negative edge)
// Acc8 = 0 => allou� � T7 arbitraire ! on se sert pas de la capture
// Acc9 = 0 => allou� � T7 arbitraire ! on se sert pas de la capture
//  => CCM2 = |xxxx,xxxx,0011,0011

CCM2=CCM2|0x0033;
CCM2=CCM2&0xFF33;  

// P2.8 et P2.9 en entr�e
DP2=DP2&0XFCFF;

// init des positions
N_Pulse=0;

}



//Temps d'ex�cution d'une interruption	457 cycles soit 23�s
//P�riode maxi = 1/750hz=1,3ms TpsExec/P=0.0177
void IT_CC8(void) interrupt 0x18
//			   	____	  ____
//  Opto_8 : __|    |____|    |__   : marche avant
//			   	  ____	    ____
//  Opto_9 :   __|    |____|    |__

// ou
//			   	____	  ____
//  Opto_8 : __|    |____|    |__   : marche arri�re
//		      ____	    ____
//  Opto_9 __|    |____|    |__
// 
{
	
if 	(Opto_8==1)	// c'est un front montant de Opto_8
	{
	if (Opto_9==0) // marche avant
		{
		N_Pulse=N_Pulse+1;
		// modulo 30 000
		if (N_Pulse>=30000)
			{
			 N_Pulse=0;
			}
		}
	else	   // marche arri�re
		{
		N_Pulse=N_Pulse-1;
		if (N_Pulse<=-30000)
			{
			 N_Pulse=0;
			
			}
		}
	}
else // c'est un front descendant
	{
	if (Opto_9==1) // marche avant
		{
		N_Pulse=N_Pulse+1;
		// modulo 30 000
		if (N_Pulse>=30000)
			{
			 N_Pulse=0;
			 
			}
		}
	else	   // marche arri�re
		{
		N_Pulse=N_Pulse-1;
		if (N_Pulse<=-30000)
			{
			 N_Pulse=0;
			}
		}
	}
}


void IT_CC9(void) interrupt 0x19

//			   	____	  ____
//  Opto_8 : __|    |____|    |__   : marche avant
//			   	  ____	    ____
//  Opto_9 :   __|    |____|    |__

// ou
//			   	____	  ____
//  Opto_8 : __|    |____|    |__   : marche arri�re
//		      ____	    ____
//  Opto_9 __|    |____|    |__
// 
{
	
if 	(Opto_9==1)	// c'est un front montant de Opto_9
	{
	if (Opto_8==1) // marche avant
		{
		N_Pulse=N_Pulse+1;
		// modulo 30 000
		if (N_Pulse>=30000)
			{
			 N_Pulse=0;
			
			}
		}
	else	   // marche arri�re
		{
		N_Pulse=N_Pulse-1;
		// modulo 30 000
		if (N_Pulse<=-30000)
			{
			 N_Pulse=0;
			 
			}
		}
	}
else // c'est un front descendant
	{
	if (Opto_8==0) // marche avant
		{
		N_Pulse=N_Pulse+1;
		// modulo 30 000
		if (N_Pulse>=30000)
			{
			 N_Pulse=0;
			
			}
		}
	else	   // marche arri�re
		{
		N_Pulse=N_Pulse-1;
		// modulo 30 000
		if (N_Pulse<=-30000)
			{
			 N_Pulse=0;
			 
			}
		}
	}
}

int Lire_Position(void)
{
	return N_Pulse;
}


void Init_Position(int Position_Initiale)
{
	N_Pulse=Position_Initiale;
}




//______________________________________________________________________________________________

void Config_PWM(void)	 // P7.1 
{
// PWM1 valid�e, Clk � 20MHz => si on prend un PT1=1024, on est � 20kHz de d�coupage
// 
// PWMCON0 = xxxx xx0x xx0x xx0x 
// PWMCON1 = xxx0 xxxx xx0x xx1x
PWMCON0=PWMCON0&0xFDDD;
PWMCON1=PWMCON1&0xEFDF;
PWMCON1=PWMCON1|0x0002;

PT1=0;	// le timer � 0
PW1=0;	// au depart, duty = 0
PP1=1024; // p�riode qui donnera environ 20k


/* Configuration PORT7.1 en sortie pushpull	*/	 
// ODP7.1 = 0, 
ODP7=ODP7&0XFFFD;
// DP7.1 =1, bit 1 du port7 en sortie
DP7=DP7|0X0002;

// P7.1 = 1, pour replacer la PWM en phase (inversion par XOR n�cessaire)
P7=P7|0X0002;

// demarrage timer PWM1 
PTR1=1;


}

void Fixe_Rapport(float Sigma)
{
float valeur;
int valeur_entiere;

valeur = (512.0*Sigma);
// -512.0 � +511.0
valeur_entiere = (int) valeur;
valeur_entiere = valeur_entiere+512;
if (valeur_entiere>1023) valeur_entiere=1023;
if (valeur_entiere<1) valeur_entiere=1;
PW1=valeur_entiere;
}

//_________________________________________LEDS__________________
// initLED avant la premi�re utilisation (inite les LEDS �teintes)
// puis  appel de modifierLed1 ou 2 pour changer son �tat

 void initLED(void){
   	DP2=0x03;
	ODP2=0x0;
	P2 =   P2 & 0xF8;
}
void modifierLed1(void){
	P2=P2 ^ 0x01;
}

void modifierLed2(void){
	P2=P2 ^ 0x02;
}	 

//______________________________________________________________________________________________



