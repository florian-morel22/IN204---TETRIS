La classe Block est une classe abstraite, classe mère de tous les blocs.


D'une valeur "value" qui indique la couleur du bloc.
D'une valeur "rotate_value" qui indique la position radiale du bloc.
D'une liste de vecteurs position des emplacements pris par le bloc.

Des fonctions get_value, get_list_squares pour obtenir la couleur et les vecteurs positions du bloc. 

Une fonction display_block(Grid&) pour afficher le block sur la grille.
Une fonction hide_block(Grid&) pour supprimer le block sur la grille. 

Des fonctions go_down(), go_right(), go_left(), rotate() pour déplacer, tourner le bloc.

