/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reformats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:50:50 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 14:30:31 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//reformats the map to be able to overcome empty lines and spaces
static int	reformat_raw_map(t_data *all)
{
	int	j;
	int	i;
	bool wall;

	wall = false;
	j = 0;
	while (all->raw_map[j] != NULL)
	{
		i = 0;
		while (all->raw_map[j][i] != '\0')
		{
			if (all->raw_map[j][i] == ' ')
			{
				if (i == 0 || i == all->width - 1)
					all->raw_map[j][i] = '1';
				if (all->raw_map[j][i - 1] == '0'
					&& all->raw_map[j][i + 1] == '0')
					all->raw_map[j][i] = '0';
				else
					all->raw_map[j][i] = '1';
			}
			i++;
		}
		j++;
	}
	return (SUCCESS);
 }

int	map_reformats(t_data *all)
{
	printf("----------BEFORE REFORMAT-------------\n");
	int	i;
	i = 0;
	while (all->raw_map[i] != NULL)
	{
		printf("line[%d]: %s\n", i, all->raw_map[i]);
		i++;
	}
	if (reformat_raw_map(all))
		return (FAILURE);
	printf("----------AFTER REFORMAT--------------\n");
	i = 0;
	while (all->raw_map[i] != NULL)
	{
		printf("line[%d]: %s\n", i, all->raw_map[i]);
		i++;
	}

	// else if (map_3d_map(all))
	// 	return (FAILURE);
	// else if (map_2d_map(all))
	// 	return (FAILURE);
	return (SUCCESS);
}
