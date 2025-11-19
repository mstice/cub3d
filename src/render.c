/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:39:22 by mtice             #+#    #+#             */
/*   Updated: 2025/11/19 10:59:18 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "../minilibx-linux/mlx.h"

static void	my_mlx_pixel_put(t_libx *libx, int x, int y, int colour)
{
	char	*dst;

	dst = libx->addr + (y * libx->line_length + x * (libx->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

static void	draw(t_libx *libx, int x, int y)
{
	int	n;

	n = 50;
	while (n-- > 0)
		my_mlx_pixel_put(libx, x--, y--, WHITE);
}

static int	on_key_down(int keycode, t_libx *libx)
{
	if (keycode == ESC)
		mlx_hook(libx->win_ptr, ON_DESTROY, 0L, mlx_loop_end, libx->mlx_ptr);
	return (0);
}

void	render(t_libx *libx)
{
	libx->mlx_ptr = mlx_init();
	libx->win_ptr = mlx_new_window(libx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	libx->img1 = mlx_new_image(libx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	libx->addr = mlx_get_data_addr(libx->img1, &libx->bits_per_pixel, &libx->line_length, &libx->endian);
	draw(libx, 200, 200);
	mlx_put_image_to_window(libx->mlx_ptr, libx->win_ptr, libx->img1, 0, 0);
	mlx_hook(libx->win_ptr, ON_KEYDOWN, 1L << 0, on_key_down, libx);
	mlx_hook(libx->win_ptr, ON_DESTROY, 0L, mlx_loop_end, libx->mlx_ptr);
	mlx_loop(libx->mlx_ptr);
	mlx_loop_end(libx->mlx_ptr);
	exit(EXIT_SUCCESS);
}
