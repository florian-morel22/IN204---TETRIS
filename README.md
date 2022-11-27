# IN204_Tetris
Projet C++ : Faire un Tetris 

Le dossier "src" contient tous les .cpp

Le dossier "inc" contient tous les .hpp

Les autres dossiers sont claires

Ce qu'il faut faire pour adapter votre dossier build :

 - Créer un dossier qui contiendra tout le projet (le miens s'appelle "project")
 
 - Lui mettre dedans les dossiers "build" et "repository"
 

 - Dans CMakeCach.txt et cmake_install.cmake : ctr+F pour trouver tous les chemins contenant IN204 et les modifier pour que ça corresponde à votre répertoire.
 
 - ouvrir un terminal, aller dans le dossier build et lancer la commande : >>cmake ../repository (cette commande est à lancer à chaque fois qu'on ajoute ou supprime un fichier dans le repository.)
 
 #### La config du make est terminée ####
 
 - Pour compiler : en restant dans le dossier build, lancer la commande : >>make
 
 - Pour executer : >>./sfml-app (toujours dans le build)
 