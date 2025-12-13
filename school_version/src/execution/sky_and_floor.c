/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_and_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:47:28 by mtice             #+#    #+#             */
/*   Updated: 2025/12/13 14:03:37 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

void	draw_sky(t_data *all)
{
	int		x;
	int		y;

	y = 1;
	while (y < WIN_START - 1)
	{
		x = 0;
		while (x < WIN_WIDTH - 1)
		{
			my_mlx_pixel_put(all, x, y, BLUE);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_data *all)
{
	int		x;
	int		y;

	y = WIN_END - 1;
	while (y < WIN_HEIGHT - 1)
	{
		x = 0;
		while (x < WIN_WIDTH - 1)
		{
			my_mlx_pixel_put(all, x, y, BROWN);
			x++;
		}
		y++;
	}
}
