/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:12 by ombatkam          #+#    #+#             */
/*   Updated: 2026/01/30 16:16:43 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-ROT_SPEED)
		- player->dir_y * sin(-ROT_SPEED);
	player->dir_y = old_dir_x * sin(-ROT_SPEED)
		+ player->dir_y * cos(-ROT_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-ROT_SPEED)
		- player->plane_y * sin (-ROT_SPEED);
	player->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ player->plane_y * cos(-ROT_SPEED);
}

void	rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(ROT_SPEED)
		- player->dir_y * sin(ROT_SPEED);
	player->dir_y = old_dir_x * sin(ROT_SPEED)
		+ player->dir_y * cos(ROT_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(ROT_SPEED)
		- player->plane_y * sin (ROT_SPEED);
	player->plane_y = old_plane_x * sin(ROT_SPEED)
		+ player->plane_y * cos(ROT_SPEED);
}
