# multiTerm

## but du projet
Le projet multiTerm a pour but d'offrir une interface graphique en QT permettant de lancer des connexion sur des serveur distant en mode ssh

## Fonctionnement
une fois l'application lancée, un arbre des connexions disponibles apparait ; il suffit de déployer les différents noeuds jusqu'a trouver la feuille décrivant la connexion que vous voulez utiliser

## Fonctions disponibles
Les différentes fonctions disponibles pour chaque item de l'arbres sont
* Edition d'une connexion   
* Création d'une connexion  
* Supprimer une connexion  
* Lance connexion  
* échange clé ssh  
* création d'un groupe  

## fichier de configuration
la configuration de multiTerm est stockée dans un fichier "multiTerm.cfg" localisé dans le même répertoire que l'exécutable de l'application.Les paramètres de configuration sont modifiables via le menu "Aide/édit configuration"
les paramètres disponibles sont :  
* Home dir  
* nom du fichier de configuration  
* option de forwarding X11  
* Liste des applications terminal disponibles  

## fichier de description des connexions
le fichier est compose de blocs inclus entre { et }
un bloc peut être de 2 types différents :  
- groupeConnexion  
- Connexion  

### description d'un groupe de connexions
le groupe de connexion est un bloc entre { et } qui commence par l'instruction  
groupeConnexion = < nom du groupe >  
sur les lignes suivantes, on trouvera des blocs tels groupeConnexion ou connexion


### description d'une connexion
une connexion est un bloc entre { et } qui décrit l'ensemble des paramètres nécessaire a l'établissement d'une connexion ssh vers un serveur distant  
Le groupe connexion commence par l'instruction   
connexion = < nom de la connexion >  
ensuite haque paramètres est sur une ligne distincte


### trello de suivi des developpements
https://trello.com/b/reJ40MV7
