/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:21:46 by mtice             #+#    #+#             */
/*   Updated: 2025/12/11 12:41:20 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_data	all;

	if (argc != 2)
		ft_exit(NULL, ERR_USAGE);
	init_t_data(&all);
	if (parsing(&all, argv[1]))
		return (free_all(&all), FAILURE);
	// else if (execution(&all))
	// 	return (free_all(&all), FAILURE);
	printf("Map is valid!\n");
	render(&all);
	free_all(&all);
	return (SUCCESS);
}
