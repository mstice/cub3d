/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:21:46 by mtice             #+#    #+#             */
/*   Updated: 2025/12/02 13:50:40 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
//
// void init_all(t_data *all)
// {
// 	all->map3d = NULL;
// 	all->map2d = NULL;
// 	all->libx = NULL;
// }
//
int	main(int argc, char *argv[])
{
	t_data	all;
	// t_libx	libx;
	//
	//init_all(&all);
	// is_map_valid();
	// all.map3d = map_3d_map();
	// all.map2d = map_2d_map();
	if (argc != 2)
		ft_exit(ERR_USAGE, EXIT_FAILURE);
	init_t_data(&all);
	if (parsing(&all, argv[1]))
		return (FAILURE);
	// render(&libx);
	printf("Map is valid!\n");
	return (SUCCESS);
}
