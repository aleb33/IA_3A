# Projet IA 2022 👾

### Members:
- [Aloïs Bozon](https://github.com/Alois-B)
- [Alexandre Bousquet](https://github.com/aleb33)


## Nqueens ♟ :
Le problème des Nqueens consiste à positionner les N reines sur un échiquier NxN sans qu’aucune ne s’attaquent.

Pour lancer notre nqueens il suffit de faire la commande suivante:

make;./nqueens -opt 
	
-opt peut prendre trois valeurs : -b pour bfs; -d pour dfs; -u pour ucs;

## Knights ♟ :
Pour résoudre ce problème, on veut chercher le plus court chemin reliant le cavalier en position (0,0) pour aller en position (N-1,N-1) sur un échiquier de taille NxN.

Pour lancer notre knights il suffit de faire la commande suivante:
	
make;./knights -opt
	
-opt peut prendre trois valeurs : -b pour bfs; -d pour dfs; -u pour ucs;

## Taquin 🧩:

Sur un plateau de 9 cases, il faut replacer, en les glissant, 8 cases dans le bon ordre avec le moins de mouvements possibles.
 Le bon ordre ici est:
	
| 1 | 2 | 3 |
|---|---|---|
| 4 | 5 | 6 |
| 7 | 8 |   |	
	
Où 0 indique la case vide.

### Trois niveaux différents :
#### EASY :

| 1 | 2 | 5 |
|---|---|---|
| 3 |   | 4 |
| 7 | 8 | 6 |   

#### MEDIUM :

| 7 | 4 | 8 |
|---|---|---|
| 2 | 5 | 6 |
| 3 | 1 |   | 

#### Difficult :

| 8 |   | 7 |
|---|---|---|
| 5 | 6 | 1 |
| 3 | 2 | 4 | 

Pour lancer notre taquin il suffit de faire la commande suivante :
	
make;./taquin -opt 
	
-opt peut prendre quatre valeurs : -b pour bfs; -d pour dfs; -u pour ucs ; -a pour astar;

#### Nota Bene: 
On peut modifier les tailles des échiquiers ainsi que le taille du taquin dans board.h
