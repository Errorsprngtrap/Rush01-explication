/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bblondin <bblondin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:30:33 by tbaricau          #+#    #+#             */
/*   Updated: 2025/09/07 08:08:38 by bblondin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

void	display_tab(int *tab, int size) // affiche le tableau sous forme de "grille",tab c est notre tableau de int qu on affiche est size c est la taille du dit tableau 
{
	int		i; // index pour parcourir le tableau
	char	c; // char pour convertir l int en char

	i = -1;
	while (++i < size * size) // on boucle dans le tableau
	{
		c = '0' + tab[i];  // on convertit l int en char
		write(1, &c, 1); // on ecrit le char
		if (i % size != size - 1) // si on n est pas a la fin d une ligne on ecrit un espace
			write(1, " ", 1); 
		else // sinon on ecrit un retour a la ligne
			write(1, "\n", 1);
	}
	return ; // on retourne rien
}
