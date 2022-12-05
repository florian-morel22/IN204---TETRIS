La class Game est celle qui représente le déroulement du jeu. 

Elle contient :
L'attribut _running qui est un booléen indiquant true lorsque la partie est en route.
L'attribut window pour afficher la fenêtre;
Les attributs grid_view, menu_view pour afficher la grille et le menu dans la fenêtre. 
Les attributs bgGrid, bgMenu qui sont les fonds d'écran des vues. (Ce sont des rectangles)
Une grille grid.
Un pointeur sur un block.
Une horloge clock.
Un flottant fps_grid qui représente le FPS de la descente du bloc.
Des fonctions Initialize(), Shutdown() et Frame() pour initialiser, éteindre et actualiser le jeu. 


Run() pour jouer.
Des fonctions set et get pour actualiser et récupérer des attributs. 
Une fonction generate_new_block() pour générer un nouveau block une fois que le bloc actuel ne peut plus descendre. 

Une fonction Input_handler qui ne fait pas partie de la classe mais qui est appelée en continue dans le Frame() car elle prend en charge les entrées clavier pour jouer au Tetris. 