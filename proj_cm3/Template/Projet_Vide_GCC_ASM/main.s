/* 
 * Fichier main, en assembleur 
 */
	
	.section ".text"
	.align	2

	.global	main
	.type	main, %function

main:
/* Debut de la routine main */
	
/* 
 * Code de l'appli a mettre ici 
 */

/*
 * Boucle infinie, pour ne pas sortir de la routine main
 */

	B		.  

/*
 * Constantes utilis�es par main	
 * Stock�es en section .text, apr�s la routine
 */
	/* .align	2 inutile, normalement */
	.section ".text"	
main_constants:
	/* Constantes a mettre ici */
	
	.end
