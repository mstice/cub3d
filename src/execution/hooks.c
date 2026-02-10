/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:02:25 by mtice             #+#    #+#             */
/*   Updated: 2026/01/30 13:57:03 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//swaps image1 with image2 during movement
static void	swap_images(t_room *game)
{
	void	*tmp_img;
	char	*tmp_addr;

	tmp_img = game->img.img;
	game->img.img = game->img.img_tmp;
	game->img.img_tmp = tmp_img;
	tmp_addr = game->img.addr;
	game->img.addr = game->img.addr_tmp;
	game->img.addr_tmp = tmp_addr;
}

//-----------------------------------------------------------------------------
int	ft_render_frame(t_room *game)
{
	if (!game->render_in_progress)
		return (0);
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	swap_images(game);
	game->render_in_progress = 0;
	return (0);
}

//-----------------------------------------------------------------------------
int	close_game(t_room *game)
{
	mlx_loop_end(game->mlx);
	free_all(game->all);
	exit(SUCCESS);
	return (0);
}

//-----------------------------------------------------------------------------
int	on_key_down(int keycode, t_room *game)
{
	if (keycode == XK_Escape)
		close_game(game);
	else if (keycode == XK_Up || keycode == XK_w)
		move_forward(&game->player, game->map);
	else if (keycode == XK_Down || keycode == XK_s)
		move_back(&game->player, game->map);
	else if (keycode == XK_Right)
		rotate_right(&game->player);
	else if (keycode == XK_Left)
		rotate_left(&game->player);
	else if (keycode == XK_d)
		move_right(&game->player, game->map);
	else if (keycode == XK_a)
		move_left(&game->player, game->map);
	game->render_in_progress = 1;
	ft_render_frame(game);
	return (0);
}
