/*************************************************************************************
** Titre:STRUCT_DONNEES.H				     		                   				**
** Auteurs: Claire DUBOIS, Denis DESMAELE, S�bastien DARDONVILLE, Katia ROULLET	    **
** Date:31/10/2007									                   				**
** Sujet: d�fini une structure de donn�es                              				**
**************************************************************************************/

#ifndef __STRUCT_DONNEES_H__
#define __STRUCT_DONNEES_H__

/*****************************************************************************
**				Structure donn�es de l'�tat trottinette    					**
** La structure comprend:													**
** 	- Position de la rame par rapport � sa position initiale				**
**	- Vitesse de la rame													**
******************************************************************************/

typedef struct {
	int position;
	float vitesse;
	}Etat_Trottinette;

#endif