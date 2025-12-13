/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:49:25 by mtice             #+#    #+#             */
/*   Updated: 2025/12/13 14:03:37 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *all, int x, int y, int colour)
{
	char	*dst;

	dst = all->addr + (y * all->line_length + x * (all->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

float	get_fmax(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}


void	bresenham(t_data *all, t_two point1, t_two point2)
{
	int		max;
	float	x_step;
	float	y_step;

	x_step = point2.x - point1.x;
	y_step = point2.y - point1.y;
	max = get_fmax(fabsf(x_step), fabsf(y_step));
	x_step = x_step / max;
	y_step = y_step / max;
	if (((int)point1.x < 0 || (int)point1.x > WIN_WIDTH)
		&& ((int)point2.x < 0 || (int)point2.x > WIN_WIDTH))
		return ;
	else if (((int)point1.y < 0 || (int)point1.y > WIN_HEIGHT)
		&& ((int)point2.y < 0 || (int)point2.y > WIN_HEIGHT))
		return ;
	while ((int)(point1.x - point2.x) || (int)(point1.y - point2.y))
	{
		if (((int)point1.x > 0 && (int)point1.x < WIN_WIDTH)
			&& ((int)point1.y > 0 && (int)point1.y < WIN_HEIGHT))
		{
			my_mlx_pixel_put(all, (int)point1.x, (int)point1.y, point1.colour);
			all->bounds += 1;
		}
		point1.x += x_step;
		point1.y += y_step;
	}
}

void	draw(t_data *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < all->height)
	{
		x = 0;
		while (x < all->width)
		{
			if (x < all->width - 1)
				bresenham(all, all->map2d[y][x], all->map2d[y][x + 1]);
			if (y < all->height - 1)
				bresenham(all, all->map2d[y][x], all->map2d[y + 1][x]);
			x++;
		}
		y++;
	}
	if (all->bounds == 0)
		ft_exit(all, ERR_BOUNDS);
}
