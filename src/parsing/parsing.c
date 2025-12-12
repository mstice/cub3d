/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:18:52 by mtice             #+#    #+#             */
/*   Updated: 2025/12/07 16:50:23 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(t_data *all, char *map_name)
{

	if (file_checks(all, map_name))
		return (FAILURE);
	if (map_checks(all, map_name))
		return (FAILURE);
	if (map_reformats(all))
		return (FAILURE);
	if (DEBUG)
	{
		int	i = -1;
		printf("----------AFTER REFORMAT----------------\n");
		while (all->raw_map[++i] != NULL)
			printf("line[%2d]: %s\n", i, all->raw_map[i]);
		printf("----------MAP ELEMENTS------------------\n");
		printf("floor: %X\n", all->floor);
		printf("ceiling: %X\n", all->ceiling);
		printf("north: %s\n", all->north);
		printf("south: %s\n", all->south);
		printf("east: %s\n", all->east);
		printf("west: %s\n", all->west);
		printf("player: %c\n", all->player);
		printf("-----------MAP IS VALID!----------------\n");
	}
	return (SUCCESS);
}
