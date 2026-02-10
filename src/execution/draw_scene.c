/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:36:10 by ombatkam          #+#    #+#             */
/*   Updated: 2026/01/30 14:03:18 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//init raycasting
static void	init_raycaster(t_room *game, t_raycast *ray, int x)
{
	ray->camera_x = 2.0 * x / WIN_WIDTH - 1.0;
	ray->raydir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->raydir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->raydir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}

//-----------------------------------------------------------------------------
//direction conditions used for DDA
static void	ft_dir_cond(t_room *game, t_raycast *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_y;
	}
}

//-----------------------------------------------------------------------------
//DDA algorithm
static void	dda(t_room *game, t_raycast *ray)
{
	while (!ray->hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

//-----------------------------------------------------------------------------
//calculates the distance of the ray to the wall, to know how tall wall is
//this is the shortest distance between the camera and the wall
static void	recalc_distance(t_room *game, t_raycast *ray)
{
	if (ray->side == 0)
		ray->dist = (ray->map_x - game->player.pos_x + (1 - ray->step_x) / 2)
			/ ray->raydir_x;
	else
		ray->dist = (ray->map_y - game->player.pos_y + (1 - ray->step_y) / 2)
			/ ray->raydir_y;
	if (ray->dist <= 0)
		ray->dist = 1e-6;
	ray->line_h = (int)(WIN_HEIGHT / ray->dist);
	ray->draw_start = -ray->line_h / 2 + WIN_HEIGHT / 2;
	ray->draw_end = ray->line_h / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->dist * ray->raydir_y;
	else
		ray->wall_x = game->player.pos_x + ray->dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
}

//-----------------------------------------------------------------------------
//initialises the raycaster, sets the conditions, calculates and draws
void	draw_scene(t_room *game)
{
	t_raycast	ray;
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_raycaster(game, &ray, x);
		ft_dir_cond(game, &ray);
		dda(game, &ray);
		recalc_distance(game, &ray);
		draw_all(game, &ray, x);
		x++;
	}
}
