# C-essionProjectc

Etape 1 : générer l'application à l'aide de la commande "make" dans le répertoire "C-essionPc". 

Etape 2 : lancer l'application. 2 choix s'offre alors à vous:
- Lancement en tant qu'administrateur vous avez le choix entre 2 commandes :
 
    1) ./bin/traitement -admin : celle-ci permet de renseigner le nom d'utilisateur et le mot de passe d'un administrateur. Cette         commande est accessible sans droit à la première utilisation. Après la première utilisation, vous devrez disposer de droits         pour lancer cette commande.

    2) ./bin/traitement -conf <chemin du fichier de conf> + <option utilisateur (-matrix)> : Celle-ci permet de renseigner les         machines distantes qui serviront à lancer les modules paires et impaires. Attention ce fichier devra avoir une         structure         bien précise : 
    ligne 1: <adresse IP de la première machine>:<port>
    ligne 2: <adresse IP de la deuxième machine>:<port>. 
    Cette commande est protégée par des droits. Si cette option n'est pas renseigné, l'application se lancera en local.


- Lancement en tant qu'utilisateur. Vous avez le choix entre 2 commandes :

    1) ./bin/traitement -matrix <chemin du fichier de l'echiquier> : cette commande permet de rentrer directement l'echiquier de départ.         Attention le contenu du fichier devra avoir une structure bien précise, de la forme :
    XXXX
    XXXX
    XXXX
    Cette matrice devra être placé le plus en haut à gauche dans le fichier.
    Toutes les lignes doivent être de la même taille et toutes les colonnes doivent également être de la même taille. Lorsque cette     commande est entrée, l'interface propose de renseigner les règles manuellement. 


    2) ./bin/traitement -matrix <chemin du fichier de l'echiquier> -rules <chemin du fichier de règles> : cette commande permet de         rentrer, en plus de l'echiquier de départ, une liste de règles. Attention le contenu du fichier de règle devra avoir une structure         bien précise de la forme :
    XXX
    XXXX
    XX
    Ces lignes devront être placées le plus en haut à gauche dans le fichier.


