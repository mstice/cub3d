/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:39:58 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 14:30:35 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//ONLY TO BE USED IN CASE OF EXIT_FAILURE!
//function that displays error message, and frees before exiting with FAILURE
void	ft_exit(t_data *all, char *err_msg)
{
	if (err_msg)
	{
		ft_putendl_fd(ERR, 2);
		ft_putendl_fd(err_msg, 2);
	}
	free_all(all);
	exit(EXIT_FAILURE);
}
