clear all ;
close all;
clc;


Te=2E-3; % p�riode d'�chantillonnage de la commande


Delta=10; %% �cart initial entre les loco au d�marrage

%% Initialisation du g�n�rateur de trajectoire
%   G�n�re des consignes de position et de vitesse coh�rentes selon le profil 
%   de vitesse suivant
% 
% Vitesse
%   /\         Vmax ----> _______________________________
%    |                  / I                             I\
%    |                 /  I                             I \
%    |                /	  I                             I  \
%    |			     /	  I                             I   \
%    |		  	    /	  I 							I	 \
%    |   __________/	  I                             I     \____________
%    |_____________I______I_____________________________I___________________\ temps
%                  |       |_                           |<---->|_          /
%                  |		 \_                         |		  \_
%                  |           \_                       |		    \_
%                  |<----------->|                      |<----------> |
%                  |  tpsm   					   	    |      tpsm 
%                 tda                                   tdd
%
% L'int�grale de ce profil de vitesse donne une position qui doit se
% terminer � la valeur Dist d�sir�e
%   Surface = Position finale = Dist = (tdd-tda)*Vmax

Dist=32000; % distance � parcourir
tda=0.5;    %temps d�but d'acc�l�ration (s)
tpsm=2;     %temps de mont�e (s)
Vmax=1000;  % Vitesse Maximale (pas/s)
tdd=tda+Dist/Vmax; % temps d�but de descente
Amax = Vmax/tpsm;  % acc�l�ration maximale (pas/s/s)
L=tdd+tpsm+2;   % horizon de simulation

Vitmax = 1200 %% pas/s


%% Valeurs des N mod�les de locomotive
% Vit(p)          K
% _______  =  ____________
%  Com(p)      1 + Tau . p

N=3; % nombre de loco simul�es

%% initialise N gains K autour de la valeur nominale
Knom = 0.4979;          % Gain nominal
sigma_K = Knom/100;     % 1% devariance de K sur l'univers probabiliste des diff�rentes locos
K=(randn(N,1)*sigma_K)+Knom; % Vecteur des N gains K de chaque loco simul�e
K(end)=K(end)*1;   


%% initialise N constante Tu autour de la valeur nominale
Taunom=3E-2; % constante de temps d'une loco 
sigma_Tau=Taunom/10; % forte variance de 10% car il peut y avoir
                     % beaucoup de monde dans une voiture de m�tro
Tau=(randn(N,1)*sigma_Tau)+Taunom; % Vecteur des N constante de temps Tau des locos
Tau(end) = 1*Tau(end);


[Kr,S,E,Kry,Sy,Ey]=calcul_retour_etat(Knom,Taunom,N);
dim=3;
Ki=Kr(:,1:dim:dim*N)*(dim-2)
Ka=Kr(:,dim-1:dim:dim*N)
Kv=Kr(:,dim:dim:dim*N)



sim n_metro_discret;
Puissance_LQ = sum(commandes.*commandes)/length(commandes)
Puissance_Tot_LQ = sum(Puissance_LQ)/N
visu_crash;

pause;
close all;
hold off;
Ki=Kry(:,1:dim:dim*N)*(dim-2)
Ka=Kry(:,dim-1:dim:dim*N)
Kv=Kry(:,dim:dim:dim*N)
sim n_metro_discret;
Puissance_LQY = sum(commandes.*commandes)/length(commandes)
Puissance_Tot_LQY = sum(Puissance_LQY)/N

 visu_crash