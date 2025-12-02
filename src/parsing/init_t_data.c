/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:21:51 by mtice             #+#    #+#             */
/*   Updated: 2025/12/02 17:35:30 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_t_data(t_data *all)
{
	all->raw_map = NULL;
	all->map_3d = NULL;
	all->map_2d = NULL;
	all->height = 0;
	all->width = 0;
	all->libx = NULL;
}
