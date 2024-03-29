clear;
pack;  %Netoyage par le vide
Reinit_com;   % nettoyage des communications existantes
% configuration de la communication
s = serial('COM3');  
set(s,'DataTerminalReady','off');
set(s,'Terminator','LF/CR');
s.BytesAvailableFcn = @callread; % routine d'interuption sur reception de caract�res sur Com2
fopen(s); % ouverture de la communication
s.userdata = 0;
s.timeout = 1000  ;    % avoir le temps de debug
disp('Connection �tablie - Lancer la cible ');
fprintf(s,'Ecriture pour rien car si lecture en premier la liaison plante')

Finir  = 0;  % Flag de validit� de la communication

while (Finir == 0 ) 
    
    disp('boucle');

    while (s.userdata == 0) % on est en mode normal
        r = input('\n==>','s');
        if (s.userdata == 0)
            fprintf(s,r);
            fwrite(s,10);
        end
    end
    if (s.userdata == 1)  % On a re�u une demande de fin ($) de communication
        Finir = 1;
        disp('Au revoir');
        fclose(s);
        delete(s);
        freeserial
    elseif(s.userdata == 2) % On est dans dans le mode "t�l�chargement" (on a re�u #i)
        disp('On est dans dans le mode "t�l�chargement" (on a re�u #i)');
        fprintf(s,num2str(0));   % Envoie l'accord 
        disp('1');
        prem = fread(s,3);  %reprend l'�cho
        disp('2');
        % lecture du nom : c'est une chaine de caract�re toout va bien
        NomMat = fgetl(s);  

        %Lecture de la taille : c'est un entier cod� en chaine de caract�re
        % Taille = fscanf(s,'%d',1) devrait fonctionner mais ce n'est pas
        % le cas...??? On d�compose donc : lecture d'une chaine puis conversion
        % en nombre
        Taille_chaine = fgetl(s);
        Taille=str2num(Taille_chaine);

        % lecture de "Taille" entiers cod�s en chaine de caract�re. 
        % L� encoire n�cessit� de d�composer la lecture.
        for LireEntier = 1 : Taille
            Rentier_chaine = fgetl(s);
            Matrice(LireEntier)= str2num(Rentier_chaine);
        end
        eval([NomMat,' = Matrice;']); %  affectation des donnes au nom matlab
        disp('a');
        fprintf(s,num2str(0)); % libere la routine de telechargement en C
        disp('b');
        sec = fread(s,3);   % R�cup�ration de l'�cho  
        disp('c');
        s.BytesAvailableFcn = @callread;  % revalide l'IT
        disp('d');
        s.userdata = 0 ;  % fait retomber le drapeau global poure repasser en mode "normal"     
        disp('e');
    
   elseif(s.userdata == 3) % On est dans dans le mode "t�l�chargement" (on a re�u %i)
        disp('On est dans dans le mode "t�l�chargement binaire" (on a re�u %i)');
        fprintf(s,num2str(0));   % Envoie l'accord 
        disp('1');
        prem = fread(s,3);  %reprend l'�cho
        disp('2');
        % lecture du nom : c'est une chaine de caract�re toout va bien
        NomMat = fgetl(s);  

        %Lecture de la taille : c'est un entier cod� en chaine de caract�re
        % Taille = fscanf(s,'%d',1) devrait fonctionner mais ce n'est pas
        % le cas...??? On d�compose donc : lecture d'une chaine puis conversion
        % en nombre
        Taille_chaine = fgetl(s);
        Taille=str2num(Taille_chaine);

        % lecture de "Taille" entiers cod�s en chaine de caract�re. 
        % L� encoire n�cessit� de d�composer la lecture.
        Rentier_chaine = fgetl(s);
        for LireEntier = 1 : Taille
            Matrice(LireEntier)= ascii(Rentier_chaine(2*(LireEntier-1))) + ascii(Rentier_chaine(2*LireEntier));
        end
        eval([NomMat,' = Matrice;']); %  affectation des donnes au nom matlab
        disp('a');
        fprintf(s,num2str(0)); % libere la routine de telechargement en C
        disp('b');
        sec = fread(s,3);   % R�cup�ration de l'�cho  
        disp('c');
        s.BytesAvailableFcn = @callread;  % revalide l'IT
        disp('d');
        s.userdata = 0 ;  % fait retomber le drapeau global poure repasser en mode "normal"     
        disp('e');

    end            
end

