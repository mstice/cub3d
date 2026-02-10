/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 23:16:06 by ombatkam          #+#    #+#             */
/*   Updated: 2026/01/12 17:39:06 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_direction_south_north(t_spawn direction, t_player *player)
{
	if (direction == SOUTH)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -FOV;
		player->plane_y = 0;
	}
	else if (direction == NORTH)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = FOV;
		player->plane_y = 0;
	}
}

void	set_direction_east_west(t_spawn direction, t_player *player)
{
	if (direction == EAST)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = FOV;
	}
	else if (direction == WEST)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -FOV;
	}
}

void	set_player_pos(t_data *all, t_player *player)
{
	int	i;
	int	j;

	j = 0;
	while (all->map[j])
	{
		i = 0;
		while (all->map[j][i])
		{
			if (all->map[j][i] == (char)all->player)
			{
				player->pos_x = i + 0.5;
				player->pos_y = j + 0.5;
				return ;
			}
			i++;
		}
		j++;
	}
	ft_exit(all, ERR_POS_NOEXIST, 0);
}
