 PRESERVE8
 THUMB
 IMPORT |Lib$$Request$$armlib| ; assure l'initialisation des variables apr�s un reset
;___________________________________________________________________________________________________
;                  fichier dummy.s servant d'exemple de TD asm 
; voir sujet http://www.lesia.insa-toulouse.fr/~acco/acco_wiki/
;___________________________________________________________________________________________
;  Cr�� par P. ACC0
; 
;___________________________________________________________________________________________________

;___________________________________________________________________________________________________
;_______________________________CONSTANTES ETIQUETTES_______________________________________________
CHAR_FIN equ 'Z'
TAILLE 	equ  15            
;___________________________________________________________________________________________________
;______________________________VARIABLES initialis�es_______________________________________________           			
  AREA    DummyVars, DATA, READWRITE
Caracteres		DCB 	'B','A',"BA",41
Nombre			DCW		0xFFFE,-1,128
Copy_Texte		SPACE   TAILLE
;___________________________________________________________________________________________________
;______________________________CONSTANTES MEMOIRE___________________________________________________            			
				
  AREA     DummyConsts, DATA, READONLY
Texte 			DCB 	"Salut les geeks",CHAR_FIN
Taille_Texte	DCW 	TAILLE  
ID_PUCE			SPACE	15



;___________________________________________________________________________________________________
;____________________________CODE___________________________________________________________________           
 AREA    |.textDummy|, CODE, READONLY, ALIGN=2





;_________________________
dummy_asm	PROC
;_________________________
 	EXPORT dummy_asm   
; fonction myst�rieuse pour TD assembleur          	
; IN :  rien
; OUT : R0 : somme des caract�res
; REGS ALTERES : R0-R1, R6-R8, R15(PC)
;_________________________

	LDR R6,=Texte
	LDR R8,=Copy_Texte
	LDR R0,=0

|Pas_Fini|

		LDR R1,= CHAR_FIN
		LDRB R7,[R6],#1
		STRB R7,[R8],#1
		ADD R0,R0,R7

	CMP R1,R7
	BNE |Pas_Fini|

	BX LR  ;retour � l'envoyeur

;_________________________
 ENDP  ; dummy_asm
;_________________________



 END ; module asm
;___________________________________________________________________________________________________

 Ici on peut �crire de la p��sie par exemple :-)

