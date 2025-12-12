/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reformats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:50:50 by mtice             #+#    #+#             */
/*   Updated: 2025/12/12 16:40:00 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//reformats the map to be able to overcome empty lines and spaces
int	reformat_raw_map(t_data *all)
{
	int	j;
	int	i;

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
				if (i > 0 && i < ft_strlen(all->raw_map[j])
					&& all->raw_map[j][i - 1] == '0'
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

//-----------------------------------------------------------------------------
static int map3d_map(t_data *all)
{
	t_three	*line_coords;
	int		i;
	int		j;

	all->map3d = malloc(sizeof(t_three *) * (all->height + 1));
	if (!all->map3d)
		ft_exit(all, ERR_MALLOC);
	j = 0;
	while (j < all->height)
	{
		line_coords = ft_calloc(sizeof(t_three), all->width);
		if (!line_coords)
			ft_exit(all, ERR_MALLOC);
		i = 0;
		while (i < all->width)
		{
			line_coords[i].x = i;
			line_coords[i].y = j;
			line_coords[i].z = all->raw_map[j][i] - '0';
			line_coords[i].colour = RED;
			i++;
		}
		all->map3d[j] = line_coords;
		j++;
	}
	all->map3d[j] = NULL;
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
static int map_2d_map(t_data *all)
{
	t_two	*line_coords;
	int		i;
	int		j;

	all->map2d = malloc(sizeof(t_two *) * (all->height + 1));
	if (!all->map2d)
		ft_exit(all, ERR_MALLOC);
	j = 0;
	while (j < all->height)
	{
		line_coords = ft_calloc(sizeof(t_two), all->width);
		if (!line_coords)
			ft_exit(all, ERR_MALLOC);
		i = 0;
		while (i < all->width)
		{
			line_coords[i].x = all->map3d[j][i].x;
			line_coords[i].y = all->map3d[j][i].y;
			line_coords[i].colour = RED;
			i++;
		}
		all->map2d[j] = line_coords;
		j++;
	}
	all->map2d[j] = NULL;
	return (SUCCESS);
}

//-----------------------------------------------------------------------------

int	map_reformats(t_data *all)
{
	if (map3d_map(all))
		return (FAILURE);
	else if (map_2d_map(all))
		return (FAILURE);
	return (SUCCESS);
}
