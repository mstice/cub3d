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
	bool debug = true;

	if (file_checks(all, map_name))
		return (FAILURE);
	if (map_checks(all, map_name))
		return (FAILURE);
	if (debug)
	{
		int j = -1;
		printf("-----------RAW_MAP----------------------\n");
		while (++j < all->height)
			printf("line[%d]: %s\n", j, all->raw_map[j]);
	}
	if (map_reformats(all))
		return (FAILURE);
	//else if (position_image(all))
		//return (FAILURE);
	if (debug)
	{
		int	i = -1;
		printf("----------AFTER REFORMAT----------------\n");
		while (all->raw_map[++i] != NULL)
			printf("line[%2d]: %s\n", i, all->raw_map[i]);
		printf("----------MAP ELEMENTS------------------\n");
		printf("floor: %X\n", all->floor);
		printf("ceiling: %X\n", all->ceiling);
		printf("north: %s\n", all->north_text);
		printf("south: %s\n", all->south_text);
		printf("east: %s\n", all->east_text);
		printf("west: %s\n", all->west_text);
		printf("player: %c\n", all->player);
		printf("-----------MAP IS VALID!----------------\n");
	}
	return (SUCCESS);
}
