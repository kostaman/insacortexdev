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
Vmax=2000;  % Vitesse Maximale (pas/s)
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
sigma_K = Knom*5/100;     % 1% devariance de K sur l'univers probabiliste des diff�rentes locos
K=(randn(N,1)*sigma_K)+Knom; % Vecteur des N gains K de chaque loco simul�e
K(end)=K(end)*1;   


%% initialise N constante Tu autour de la valeur nominale
Taunom=3E-2; % constante de temps d'une loco 
sigma_Tau=Taunom*10/100; % forte variance de 10% car il peut y avoir
                     % beaucoup de monde dans une voiture de m�tro
Tau=(randn(N,1)*sigma_Tau)+Taunom; % Vecteur des N constante de temps Tau des locos
Tau(end) = 0.5*Tau(end);


%% Calcul de la commande


dim=3;

Ai = [0 1 0 ; 0 0 1; 0 0 -1/Taunom];
Bi = [0; 0;  Knom/Taunom] ;
Ci = eye(3,3);



R=eye(1)*1;
Q=eye(3,3)*1;
Q(1,1)=10
Q(2,2)=100
Q(3,3)=100;

nvoit=ss(Ai,Bi,Ci,0);
[KLQ,S,E]=lqrd(Ai,Bi,Q,R,Te);

Ki=KLQ(1)*eye(3,3);
Kp=KLQ(2)*eye(3,3);
Kv=KLQ(3)*eye(3,3);


%% visualisation de la simulation
sim n_metro_discret;
Puissance_LQ = sum(commandes.*commandes)/length(commandes)
Puissance_Tot_LQ = sum(Puissance_LQ)/N
visu_crash;

