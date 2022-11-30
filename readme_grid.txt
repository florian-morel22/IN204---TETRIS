Grid est une classe représentant la grille du Tetris.

Elle a comme attributs nb_lines et nb_columns qui représentent le nombre de lignes et de colonnes de notre grilles. %%(Le mettre sous forme de vecteur pour être en accord avec get_size()??)

Elle a aussi un tableau d'entier **grid qui représente les endroits vides ou non de la grille (grid[i][j]==0 <=> La position (i,j) de la grille est libre).

Une fonction initialize_grid(l,c) qui représente le constructeur de la grille. %%(à changer)
Une fonction clean_grid qui réinitialise la grille comme vide <=> (pour tout (i,j) grid[i][j]=0).

Une fonction display_grid() qui permet d'afficher seulement la grille dans le terminal.
Une fonction display_block(Block &b) qui permet d'afficher le bloc qui descend sur la grille. 

Une fonction set_case_value(i,j,newValue) qui permet de mettre à jour l'état de la case (i,j).
Une fonction get_case_value() qui permet de récupérer la valeur sur la grille à la position (i,j).
Une fonction get_size() qui renvoie un vecteur (nb_lines,nb_columns) de la grille. 

Une fonction Free_grid qui représente le destructeur de grid. %%à changer ~Grid()

