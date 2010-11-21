/*
 * Projet: Reseau de capteur
 *
 * R�le: Gestion du timer (SYSTICK) et temporisation
 * Version: 4.0
 */
#ifndef __TIME_H__
#define __TIME_H__

#include <stm32f10x_lib.h>

/* 
 * Creation du type TIME_CALLBACK pour typer le parametre de la fonction TIMEInit 
 */
typedef void (*TIME_CALLBACK) (void);

/*
 * Variables export�es (publiques)
 */
extern int TIMEEnabled; /* Active ou desactive le timer periodique (10 ms)
                             0 (defaut): Le timer periodique est d�sactiv�
							 1 : Le timer focntionne */

/*
 * Fonctions export�es (publiques)
 */
void TIMEInit(TIME_CALLBACK callback);
int TIME10ms(void);
void TIMEWaitxms(int ms);

#endif /* __TIME_H__ */
