La class Game est celle qui représente le déroulement du jeu. 

Elle contient :
L'attribut _running qui est un booléen indiquant true lorsque la partie est en route.
L'attribut window pour afficher la fenêtre;
Les attributs grid_view, menu_view pour afficher la grille et le menu dans la fenêtre. 
Les attributs bgGrid, bgMenu qui sont les fonds d'écran des vues. (Ce sont des rectangles)
Une grille grid.
Un pointeur sur un block.
Un flottant fps_grid qui représente le FPS de la descente du bloc.
Des fonctions Initialize(), Shutdown() et Frame() pour initialiser, éteindre et actualiser le jeu. 


Run() pour jouer.
Des fonctions set et get pour actualiser et récupérer des attributs. 

