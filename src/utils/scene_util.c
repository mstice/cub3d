/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:12:25 by ombatkam          #+#    #+#             */
/*   Updated: 2026/01/30 15:50:20 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//function that draws a pixel on the screen
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dest = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

//-----------------------------------------------------------------------------
//function that draws ceiling, walls, and floor
void	draw_all(t_room *game, t_raycast *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->img, x, y, game->all->ceiling);
		y++;
	}
	draw_walls(game, ray, game->all->txt, x);
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		put_pixel(&game->img, x, y, game->all->floor);
		y++;
	}
}
