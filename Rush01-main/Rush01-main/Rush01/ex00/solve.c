/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaricau <tbaricau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:29:58 by tbaricau          #+#    #+#             */
/*   Updated: 2025/09/06 13:29:32 by tbaricau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_row(int *tab, int *views, int size, int i) // droite a gauche 
{
	int	j;
	int	max_left;  // plus haut bâtiment vu depuis la gauche
	int	max_right;  // plus haut bâtiment vu depuis la droite
	int	n_left;  // plus bas bâtiment vu depuis la gauche
	int	n_right;  // plus bas  bâtiment vu depuis la droite

	//initialisation
	max_left = 0;
	max_right = 0;
	n_left = 0;
	n_right = 0;
	j = -1; // on commence à -1 pour l'incrémenter dans la boucle
	while (++j < size) 
	{
		if (tab[i / size * size + j] > max_left && ++n_left) // Depuis la gauche : si bâtiment plus haut trouvé, l’ajssigner a max left
			max_left = tab[i / size * size + j];
		if (tab[i / size * size + size - j - 1] > max_right && ++n_right) // Depuis la droite : si bâtiment plus haut trouvé, l’ajssigner a max_right
			max_right = tab[i / size * size + size - j - 1];
	}
	// Comparer avec les contraintes dans views si c est bon on renvoye true sinon false donc 1 ou 0
	return (n_left == views[size * 2 + i / size]
		&& n_right == views[size * 3 + i / size]);
}

int	check_column(int *tab, int *views, int size, int i) // bas en haut
{
	int	j;
	int	max_top;     // plus haut bâtiment vu depuis le haut
	int	max_bottom;  // plus haut bâtiment vu depuis le bas
	int	n_top;       // nombre de bâtiments visibles depuis le haut
	int	n_bottom;    // nombre de bâtiments visibles depuis le bas

	//initialisation
	max_top = 0;
	max_bottom = 0;
	n_top = 0;
	n_bottom = 0;
	j = -1;
	// ++j veut dire incremementer j avant de l utiliser
	while (++j < size) // tant que j plus petit que size size
	{
		// Depuis le haut : si bâtiment plus haut trouvé, on l’ajssigne a max_top
		if (tab[size * j + i % size] > max_top && ++n_top) //??
			max_top = tab[size * j + i % size];
		// Depuis le bas : si bâtiment plus haut trouvé, on l’ajssigne a max_bottom
		if (tab[size * (size - j - 1) + i % size] > max_bottom && ++n_bottom)
			max_bottom = tab[size * (size - j - 1) + i % size];
	}

	// Comparer avec les contraintes dans views si c est bon on renvoye true sinon false donc 1 ou 0
	return (n_top == views[i % size]
		&& n_bottom == views[size + i % size]);
}

int	solve(int *tab, int *views, int size, int i) //i = 0
{
	int	n; 
	int	j;

	// Si i == size * size on a rempli tout le tableau donc on retourne 1
	if (i == size * size)
		return (1);
	n = 0;
	// Essayer toutes les valeurs possibles pour la case courante
	while (++n <= size)
	{
		j = -1;
		while (++j < size)
			if (tab[i / size * size + j] == n || tab[size * j + i % size] == n)
				j = size + 1; // doublon trouvé → valeur invalide donc on incremente j
		if (j == size) 	// Si pas de doublon, on peut placer la valeur
		{
			tab[i] = n; // placer la valeur
			// Vérifier les contraintes si fin de ligne ou de colonne atteinte
			if ((i % size != size - 1 || check_row(tab, views, size, i))
				&& (i / size != size - 1 || check_column(tab, views, size, i))
				&& solve(tab, views, size, i + 1))  // continuer récursivement à la case suivante
				return (1); //  dans le cas ou on a trouve une solution on retourne 1
		}
	}
	tab[i] = 0; 
	return (0); // en cas d echec on retourne 0
}
