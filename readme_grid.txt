Grid est une classe représentant la grille du Tetris.

Elle a comme attributs :
_ nb_lines et nb_columns qui représentent le nombre de lignes et de colonnes de notre grilles. 
_ un tableau d'entier **grid qui représente les endroits vides ou non de la grille (grid[i][j]==0 <=> La position (i,j) de la grille est libre)
_ un tableau de carrés (sf::RectangleShape) **grid_drawn qui représente les cases de la grille affichés sur l'écran
_ un vecteur de couleur (sf::Color) list_color_block qui contient les couleurs des block tels que si list_color_block[B.value] est la couleur du Block B


Une fonction initialize_grid(l,c) qui représente le constructeur de la grille. %%(à changer)
Une fonction clean_grid qui réinitialise la grille comme vide <=> (pour tout (i,j) qui n'est pas au bord de la grille, grid[i][j]=0).
Une fonction clean_grid_with_borders qui réinitialise toute la grille y compris les bords.

Une fonction display_grid() qui permet d'afficher seulement la grille dans le terminal.

Une fonction draw_grid() 

Une fonction set_case_value(i,j,newValue) qui permet de mettre à jour l'état de la case (i,j).
Une fonction get_case_value() qui permet de récupérer la valeur value sur la grille à la position (i,j).
Une fonction get_case_value_drawn() qui permet de récupérer le sf::rectangleshape sur la grille à la position (i,j).

Une fonction get_size() qui renvoie un vecteur (nb_lines,nb_columns) de la grille. 

Une fonction set_color_block(index i, color c) qui permet modifier les couleurs de liste list_color_block. 
Une fonction get_color_bloc(index i) qui renvoie la couleur à l'indice i de list_color_block.

Une fonction Free_grid qui représente le destructeur de grid. %%à changer ~Grid()

