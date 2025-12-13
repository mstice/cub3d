/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:02:25 by mtice             #+#    #+#             */
/*   Updated: 2025/12/13 11:03:17 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	on_key_down(int keycode, t_data *all)
{
	if (keycode == ESC_KEY)
		mlx_hook(all->win_ptr, ON_DESTROY, 0L, mlx_loop_end, all->mlx_ptr);
	return (0);
}
