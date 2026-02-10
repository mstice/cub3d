/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:21:46 by mtice             #+#    #+#             */
/*   Updated: 2026/01/30 16:44:36 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	render_game(t_room *game)
{
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_hook(game->win, KeyPress, KeyPressMask, on_key_down, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_game, game);
	mlx_loop(game->mlx);
	mlx_loop_end(game->mlx);
}

int	main(int argc, char *argv[])
{
	t_data	all;
	t_room	game;

	if (argc != 2 || !argv[1] || !(*argv[1]))
		ft_exit(NULL, ERR_USAGE, 0);
	init_t_data(&all);
	parsing(&all, argv[1]);
	init_game(&all, &game);
	render_game(&game);
	free_all(&all);
	return (SUCCESS);
}
