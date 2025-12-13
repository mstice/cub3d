/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:56:15 by mtice             #+#    #+#             */
/*   Updated: 2025/12/13 14:03:34 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//zooms the image
void	zoom(t_data *all, t_two *point)
{
	point->x *= all->zoom;
	point->y *= all->zoom;
}

//-----------------------------------------------------------------------------
//increases the height of the walls
void	elevate(t_data *all, int *z)
{
	*z *= all->elev;
}

//-----------------------------------------------------------------------------
//moves the image to the center of the window
void	translate(t_data *all, t_two *point)
{
	point->x += all->x_translate;
	point->y += all->y_translate;
}

//-----------------------------------------------------------------------------
//converts degrees into radians
double	rad(int degrees)
{
	double	radians;

	radians = degrees * 0.01745329251;
	return (radians);
}

//-----------------------------------------------------------------------------
//rotating the map depending on the player starting position
void	rotate(t_two *point, t_spawn player)
{
	if (player == NORTH)
		point->x *= -1;
}

//-----------------------------------------------------------------------------
//applies all the transformations to the x and y coordinates
void	transform_map2d(t_data *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < all->height)
	{
		x = 0;
		while (x < all->width)
		{
			zoom(all, &all->map2d[y][x]);
			elevate(all, &all->map3d[y][x].z);
			//rotate(&all->map2d[y][x], all->player);
			translate(all, &all->map2d[y][x]);
			x++;
		}
		y++;
	}
}
