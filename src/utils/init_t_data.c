/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:21:51 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 15:29:12 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_t_data(t_data *all)
{
	all->map = NULL;
	all->height = 0;
	all->width = 0;
	all->map_start = 0;
	all->player = NOPLAYER;
	all->north = NULL;
	all->south = NULL;
	all->east = NULL;
	all->west = NULL;
	all->floor = -1;
	all->ceiling = -1;
	all->game = NULL;
	all->txt = ft_calloc(1, sizeof(t_txt));
}
