/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:03:56 by mtice             #+#    #+#             */
/*   Updated: 2025/12/13 13:59:17 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//a function which finds the optimal values for the x translation
//for the y translation, for the zoom and for the elevation
void	position_image(t_data *all)
{
	all->zoom = 20;
	all->elev = 10;
	all->x_translate = 100;
	all->y_translate = 100;
	transform_map2d(all);
}

//-----------------------------------------------------------------------------
//function which opens the window and creates an image
//position_image first moves all the x and y coordinates to the middle of the window
//draw_sky and draw_floor draw the sky and the floor
//draw() draws the map
void	render(t_data *all)
{
	all->mlx_ptr = mlx_init();
	all->win_ptr = mlx_new_window(all->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	all->img1 = mlx_new_image(all->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	all->addr = mlx_get_data_addr(all->img1,
			&all->bits_per_pixel, &all->line_length, &all->endian);
	position_image(all);
	//draw_sky(all);
	//draw_floor(all);
	draw(all);
	mlx_put_image_to_window(all->mlx_ptr, all->win_ptr, all->img1, 0, 0);
	mlx_hook(all->win_ptr, ON_KEYDOWN, 1L << 0, on_key_down, all);
	mlx_hook(all->win_ptr, ON_DESTROY, 0L, mlx_loop_end, all->mlx_ptr);
	mlx_loop(all->mlx_ptr);
	mlx_loop_end(all->mlx_ptr);
	free_all(all);
	exit(EXIT_SUCCESS);
}
