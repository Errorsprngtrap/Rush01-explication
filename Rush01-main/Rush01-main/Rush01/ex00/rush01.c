/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaricau <tbaricau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:25:35 by tbaricau          #+#    #+#             */
/*   Updated: 2025/09/06 13:12:38 by tbaricau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
//#include <unistd.h>

int		solve(int *tab, int *views, int size, int i); // prototype de la fonction solve
void	display_tab(int *tab, int size); // prototype de la fonction display_tab

int	read_size(char *str) // tableau de strinvg 
{
	int	result;

	result = 0;
	while (*str) // on boucle dans le tableau 
	{
		if ('0' <= *str && *str <= '9')
			result = result * 10 + (*str++) - '0'; // on convertit le char en int
		else
			return (0); // si pas un nombre on retourne 0
	}
	return (result); // on retourne la taille du tableau
}

int	*read_views(char *str, int size) 
{
	int	*views;
	int	i; // index pour parcourir le string
	int	j; // index pour parcourir le tableau des vues

	views = malloc(sizeof(int) * size * 4); // on alloue de la memoire pour le tableau
	i = 0;
	j = 0;
	while (str[i])
	{
		if (j < size * 4 && i % 2 == 0 && '0' <= str[i] && str[i] <= '9')
			views[j++] = str[i++] - '0'; // on convertit le char en int et on l ajoute au tableau
		else if (i % 2 == 1 && str[i] == ' ')
			i++; // on ignore les espaces
		else
		{
			free(views);
			return (NULL); // en cas d erreur on libere la memoire et on retourne NULL
		}
	}
	return (views); // on retourne le tableau de int
}

int	*init_tab(int size) // initialise le tableau a 0
{
	int	*tab; //tableau de int
	int	i;

	tab = malloc(sizeof(int) * size * size); // on alloue de la memoire pour le tableau
	i = 0;
	while (i < size * size) // temps aue i n est pas egal a size par lui meme sa boucle
		tab[i++] = 0; // on initialise le tableau a 0
	return (tab); // on retourne le tableau
}

void	run(int *tab, int *views, int size) // lance le solveur et affiche le resultat
{
	int	found;

	found = solve(tab, views, size, 0); // on lance le solveur
	if (found)
		display_tab(tab, size); // si on a trouve une solution on l affiche
	else
		write(1, "Error\n", 6); // sinon on affiche une erreur
	free(views); // on libere la memoire
	free(tab); // on libere la memoire
	return ;
}

int	main(int argc, char **argv) //programme principale argc et argv
{
	int	*views; // poinjteur de tableau de int  
	int	size; // taille du tableau 

	if (argc == 2 || argc == 3) // marche aue si 2 ou 3 argument
	{
		if (argc == 3) // si un tableau a une taille particuliere 
			size = read_size(argv[2]);  // onm prend la taille en argument
		else
			size = 4; // la teille aui est hardcoder
		if (size > 0) // verifie si plus grand que 0
		{
			views = read_views(argv[1], size);  //on assigne a vue le retour de read_views
			if (views)
			{
				run(init_tab(size), views, size);
				return (0); // on finit le code si sa marche
			}
		}
	}
	write(1, "Error\n", 6); //  erreur en cas de mauvaise entrée
	return (0); // fin du programme en cas d erreur
}
