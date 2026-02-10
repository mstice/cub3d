/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:51:10 by mtice             #+#    #+#             */
/*   Updated: 2026/01/12 17:39:05 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_t_room(t_data *all, t_room *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_exit(all, ERR_MALLOC, 0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.len, &game->img.endian);
	game->img.img_tmp = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr_tmp = mlx_get_data_addr(game->img.img_tmp, &game->img.bpp,
			&game->img.len, &game->img.endian);
	game->map = all->map;
	game->render_in_progress = 0;
	game->all = all;
	all->game = game;
}

static void	init_t_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = FOV;
	player->rotate = 0;
}

static void	init_t_txt(t_room *game, t_txt *txt)
{
	txt->txt_address = ft_calloc(sizeof(unsigned int *), 4);
	txt->txt_address[0] = get_txt_address(game, game->all->north);
	txt->txt_address[1] = get_txt_address(game, game->all->east);
	txt->txt_address[2] = get_txt_address(game, game->all->south);
	txt->txt_address[3] = get_txt_address(game, game->all->west);
	txt->y = 0;
	txt->x = 0;
	txt->pos = 0;
	txt->step = 0;
}

void	init_game(t_data *all, t_room *game)
{
	init_t_room(all, game);
	init_t_player(&game->player);
	set_direction_south_north(all->player, &game->player);
	set_direction_east_west(all->player, &game->player);
	set_player_pos(all, &game->player);
	init_t_txt(game, all->txt);
}
