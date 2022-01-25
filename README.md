# Projet IA 2022

## Nqueens :
Le problème des Nqueens consiste à positionner les N reines sur un échiquier NxN sans qu’aucune ne s’attaquent.

Pour lancer notre jeu il suffit de faire la commande suivante:

make;./nqueens <opt> 
	
<opt> peut prendre trois valeurs : -b pour bfs; -d pour dfs; -u pour ucs;

## Knights:
Pour résoudre ce problème, on veut chercher le plus court chemin reliant le cavalier en position (0,0) pour aller en position (N-1,N-1) sur un échiquier de taille NxN.

Pour lancer notre jeu il suffit de faire la commande suivante:
	
make;./knights <opt> 
	
<opt> peut prendre trois valeurs : -b pour bfs; -d pour dfs; -u pour ucs;

## Taquin:

Sur un plateau de 9 cases, il faut replacer, en les glissant, 8 cases dans le bon ordre avec le moins de mouvements possibles.
 Le bon ordre ici est:
	
		      123
		      456
		      780	
	
Où 0 indique la case vide.

### Trois niveaux différents :
#### EASY :
		      125
		      304
		      786
#### MEDIUM :
		      748
		      256
		      310
#### Difficult :
		      807
		      561
		      324

Pour lancer notre jeu il suffit de faire la commande suivante:
	
make;./taquin <opt> 
	
<opt> peut prendre quatre valeurs : -b pour bfs; -d pour dfs; -u pour ucs ; -a pour astar;

