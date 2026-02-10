/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:29:21 by mtice             #+#    #+#             */
/*   Updated: 2025/12/12 16:23:51 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//frees a 2d array
void	free_double_char(char **arr)
{
	int	j;

	j = 0;
	while (arr[j] != NULL)
		free(arr[j++]);
	free(arr);
}

//-----------------------------------------------------------------------------
//frees elements stored in t_data struct
static void	free_t_data(t_data *all)
{
	if (all->map)
		free_double_char(all->map);
	if (all->north)
		free(all->north);
	if (all->south)
		free(all->south);
	if (all->east)
		free(all->east);
	if (all->west)
		free(all->west);
	if (all->txt && all->txt->txt_address)
	{
		free(all->txt->txt_address[0]);
		free(all->txt->txt_address[1]);
		free(all->txt->txt_address[2]);
		free(all->txt->txt_address[3]);
		free(all->txt->txt_address);
	}
	if (all->txt)
		free(all->txt);
}

//-----------------------------------------------------------------------------
//frees elements stored in the t_room struct
static void	free_t_room(t_room *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_image(game->mlx, game->img.img_tmp);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

//-----------------------------------------------------------------------------
void	free_all(t_data *all)
{
	if (all->game)
		free_t_room(all->game);
	free_t_data(all);
}
