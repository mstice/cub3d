/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:24:27 by ombatkam          #+#    #+#             */
/*   Updated: 2026/01/30 16:49:27 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_new_pos(t_player new, t_player *player, char **map)
{
	if (map[(int)player->pos_y][(int)new.pos_x] != '1')
		player->pos_x = new.pos_x;
	if (map[(int)new.pos_y][(int)player->pos_x] != '1')
		player->pos_y = new.pos_y;
}

void	move_forward(t_player *player, char **map)
{
	t_player	new;

	new.pos_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new.pos_y = player->pos_y + player->dir_y * MOVE_SPEED;
	update_new_pos(new, player, map);
}

void	move_back(t_player *player, char **map)
{
	t_player	new;

	new.pos_x = player->pos_x - player->dir_x * MOVE_SPEED;
	new.pos_y = player->pos_y - player->dir_y * MOVE_SPEED;
	update_new_pos(new, player, map);
}

void	move_right(t_player *player, char **map)
{
	t_player	new;

	new.pos_x = player->pos_x + player->plane_x * MOVE_SPEED;
	new.pos_y = player->pos_y + player->plane_y * MOVE_SPEED;
	update_new_pos(new, player, map);
}

void	move_left(t_player *player, char **map)
{
	t_player	new;

	new.pos_x = player->pos_x - player->plane_x * MOVE_SPEED;
	new.pos_y = player->pos_y - player->plane_y * MOVE_SPEED;
	update_new_pos(new, player, map);
}
