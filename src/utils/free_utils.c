/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:29:21 by mtice             #+#    #+#             */
/*   Updated: 2025/12/02 17:32:51 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_double(void **content, int	size)
{
	while (size--)
		free(content++);
	free(content);
}

void	free_all(t_data *all)
{
	if (all->raw_map)
		free_double((void *)all->raw_map, all->height);
	if (all->map3d)
		free_double((void *)all->map3d, all->height);
	if (all->map2d)
		free_double((void *)all->map2d, all->height);
}
