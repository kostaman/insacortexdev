


//=======================================================================================

// 	Auteur T.R.
//  12 Mai 2010
//  Processeur : STM32F103RB
//  Logiciel dev : �Vision 4
//  Module qui configure l'ADC en mode DMA
//
//  ________ Rappel sur les ressources __________________________________________________
//
//  - 2ADC 16 canaux
//  - Les broches :
//		- ADC_In0  	PA0
//		- ADC_In1	PA1
//		- ADC_In2	PA2
//		- ADC_In3	PA3
//		- ADC_In4	PA4
//		- ADC_In5 	PA5
//		- ADC_In6	PA6
//		- ADC_In7	PA7
//		- ADC_In8	PB0
//		- ADC_In9	PB1
//		- ADC_In10	PC0
//		- ADC_In11	PC1
//		- ADC_In12	PC2
//		- ADC_In13	PC3
//		- ADC_In14	PC4
//		- ADC_In15	PC5
//
// 	-  ADCck Maxi = 14MHz
//
//  ________ Comment utiliser la lib ? __________________________________________________
// 	
// Fonction d'init de l'ADC
// float ADC_Init(char Nb_Canaux, char Seq_Canaux[], unsigned int *Start_Adress, float T_samp_us, float  Freq_ADC_kHz)
//
//	Configur� en DMA, mode continu. Les datas sont align�es � droite
//  La fonction renvoie la valeur recalcul�e de la p�riode d'�chantillonnage Te
//  Une fois la fonction lanc�e, l'ADC tourne en boucle. A l'utilisateur de venir
//  Chercher les variables en RAM, en �vitant un sur�chantillonnage qui fausserait la r�alit�.
//  ATTENTION !! configurer les ports IO en entr�e analogique (cf Port_IO.h)
//
//	- Nb_Canaux : de 1 � 16, c'est le nombre de canaux scann�s
//	- Seq_Canaux[] Table qui doit avoir la taille Nb_Canaux.
//		- Seq_Canaux[0] = 0 � 15 c'est le rang du scan pour la voie 0
//		- Seq_Canaux[n] = 0 � 15 c'est le rang du scan pour la voie n
///	- T_samp_us : Temps de fermeture de l'IT (echantillonnage de la capa ADC) en �s
//	- Freq_ADC_kHz : fr�quence d'attaque de l'ADC en MHz, maxi 14 MHz
//
// Fonction de lecture : vu16 ADC_Lire(char Voie);
//	- Voie de 0 � 15 num�ro de la voie ADC � lire
// Renvoie la valeur 16 bits par lecture en RAM (remplie par DMA via ADC)
// Ainsi, la fonction ne lance pas l'ADC, elle se contente de lire un zone RAM
//
//__________ Exemple de configuration : _________________________________________________
//
// *****d�claration******
//vu16 Main_Tab_Resu_ADC[6]; // table de r�sultat � remplir par une s�rie de lecture
//float Periode_us;		   // r�sultat en us de la p�riode Te
//char Sequencement_ADC[6];  // table � remplir avant l'init de l'ADC. Doit contenir
						   // les ordres de scan (0 � 15) 0 en premier, 15 en dernier
//
//  **** ex�cution ******
//Sequencement_ADC[0]=0;
//Sequencement_ADC[1]=1;
//Sequencement_ADC[2]=2;
//Sequencement_ADC[3]=3;
//Sequencement_ADC[4]=4;
//Sequencement_ADC[5]=5;
//Periode_us = ADC_Init(6, Sequencement_ADC, 5.0, 4000.0);
//                      6 canaux, @ table se s�quencement , Tsample = 5�s, Freq_ADC=4MHz)
//
// .....
// // remplissage de la table par lecture des divers canaux.
//Main_Tab_Resu_ADC[0]=ADC_Lire(0);
//Main_Tab_Resu_ADC[1]=ADC_Lire(1);
//Main_Tab_Resu_ADC[2]=ADC_Lire(2);
//Main_Tab_Resu_ADC[3]=ADC_Lire(3);
//Main_Tab_Resu_ADC[4]=ADC_Lire(4);
//Main_Tab_Resu_ADC[5]=ADC_Lire(5);



//
//=======================================================================================
 
//=======================================================================================



#ifndef _ADC_H__
#define _ADC_H__


float ADC_Init(char Nb_Canaux, char Seq_Canaux[], float T_samp_us, float  Freq_ADC_kHz);
//	- Nb_Canaux : de 1 � 16, c'est le nombre de canaux scann�s
//	- Seq_Canaux[] Table qui doit avoir la taille Nb_Canaux.
//		- Seq_Canaux[0] = 0 � 15 c'est le rang du scan pour la voie 0
//		- Seq_Canaux[n] = 0 � 15 c'est le rang du scan pour la voie n
///	- T_samp_us : Temps de fermeture de l'IT (echantillonnage de la capa ADC) en �s
//	- Freq_ADC_kHz : fr�quence d'attaque de l'ADC en MHz, maxi 14 MHz
//  - La fonction renvoie la valeur recalcul�e de la p�riode d'�chantillonnage Te en us

vu16 ADC_Lire(char Voie);
//	- Voie de 0 � 15 num�ro de la voie ADC � lire


#endif
