/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:21:46 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 15:10:11 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_data	all;

	if (argc != 2)
		ft_exit(&all, ERR_USAGE);
	init_t_data(&all);
	if (parsing(&all, argv[1]))
		return (FAILURE);
	// render(&libx);
	printf("Map is valid!\n");
	free_all(&all);
	return (SUCCESS);
}
