clear all ;
close all;

Te=1E-3; % temps d'échantillonnage

%% Valeurs des N modèles
N=3;
Kmli = 1.8*2; %% Gain trottinette
sigma_K = Kmli/10;
K=(randn(N,1)*sigma_K)+Kmli;
%K(3)=K(3)*1;


Vmax = 12 *1000 /60/60; %% 3.33 m/s
Ktach = 2.5/Vmax;
Tm=33.5E-3; %% Chez thierry Kmli*Ktach/Inertie = 1/Tm
%% Vit(p) = Kmli /(1+Tm p )

Inertie=Kmli*Ktach*Tm;
sigma_Ig=Inertie/10;
Ig=(randn(N,1)*sigma_Ig)+Inertie;
%Ig(3) = 5*Ig(3);

if (N>1) 
    M_ecart=[eye(N-1) zeros(N-1,1)]-[zeros(N-1,1) eye(N-1)];
else
    M_ecart=0;
end;


[Kr,S,E,Kry,Sy,Ey]=calcul_retour_etat(Kmli,Inertie,Ktach,N);
dim=3;
Ki=Kr(:,1:dim:dim*N)*(dim-2)
Ka=Kr(:,dim-1:dim:dim*N)
Kv=Kr(:,dim:dim:dim*N)


L=20;
Delta=0.1;
sim n_trotinettes_crash_discret;
Puissance_LQ = sum(commandes_courant.*commandes_courant)/length(commandes_courant)
Puissance_Tot_LQ = sum(Puissance_LQ)/N
visu_crash;


%plot(temps,ecarts);
hold on;
pause;
close all;
hold off;
Ki=Kry(:,1:dim:dim*N)*(dim-2)
Ka=Kry(:,dim-1:dim:dim*N)
Kv=Kry(:,dim:dim:dim*N)
sim n_trotinettes_crash_discret;
Puissance_LQY = sum(commandes_courant.*commandes_courant)/length(commandes_courant)
Puissance_Tot_LQY = sum(Puissance_LQY)/N

%plot(temps,ecarts,'--')
visu_crash