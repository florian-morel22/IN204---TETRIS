La classe Block est une classe abstraite, classe mère de tous les blocs.

Elle est composée d'un vecteur position _pos indiquant la position du coin haut gauche du rectangle encadrant la figure. 
D'une valeur "value" qui indique la couleur du bloc.
Height et width étant sont la hauteur et la largeur du bloc.
D'une liste de vecteurs position des emplacements pris par le bloc.

(Height et width pourraient être supprimés dans le futur ?)

Des fonctions get_pos(), set_pos(i,j) pour obtenir et indiquer la position.
Des fonctions get_height, get_width, get_value, get_list_squares pour obtenir la hauteur, la largeur, la couleur et les vecteurs positions du bloc. 

Des fonctions go_down(), go_right(), go_left(), rotate() pour déplacer, tourner le bloc.

