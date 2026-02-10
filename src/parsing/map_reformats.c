/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reformats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:50:50 by mtice             #+#    #+#             */
/*   Updated: 2025/12/13 14:03:33 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
int	check_fd(t_data *all, char *map_name)
{
	int	fd;

	fd = file_no_exist(map_name);
	if (fd == -1)
		ft_exit(all, ERR_FILE_NOEXIST, 0);
	return (fd);
}

//-----------------------------------------------------------------------------
//stores a copy of the inputted map
void	create_map(t_data *all, char *map_name)
{
	int			j;
	char		*line;
	const int	fd = check_fd(all, map_name);

	all->map = ft_calloc(sizeof(char *), all->height + 1);
	if (!all->map)
		ft_exit(all, ERR_MALLOC, fd);
	while (all->map_start-- > 0)
		free(get_next_line(fd));
	j = 0;
	while (j < all->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		all->map[j] = ft_strtrim(line, "\n");
		if (!all->map[j] || !(*all->map[j]))
		{
			free(all->map[j]);
			continue ;
		}
		j++;
	}
	all->map[j] = NULL;
	close(fd);
}

//-----------------------------------------------------------------------------
static char	**alloc(t_data *all)
{
	char	**new_map;
	int		j;

	new_map = ft_calloc(sizeof(char *), all->height + 1);
	if (!new_map)
		ft_exit(all, ERR_MALLOC, 0);
	j = -1;
	while (++j < all->height)
	{
		new_map[j] = ft_calloc(sizeof(char), all->width + 1);
		if (!new_map[j])
		{
			free(new_map);
			ft_exit(all, ERR_MALLOC, 0);
		}
	}
	new_map[j] = NULL;
	return (new_map);
}

//-----------------------------------------------------------------------------
//reformats the map to be able to overcome empty lines and spaces
//map becomes rectangular
int	reformat_map(t_data *all)
{
	int		j;
	int		i;
	char	**new_map;

	new_map = alloc(all);
	j = -1;
	while (++j < all->height)
	{
		i = -1;
		while (++i < all->width)
		{
			new_map[j][i] = '1';
			if (i < ft_strlen(all->map[j]) && all->map[j][i] == ' ')
			{
				if (i == 0 || i == all->width - 1)
					new_map[j][i] = '1';
				else if (i && all->map[j][i - 1] == '0'
					&& all->map[j][i + 1] == '0')
					new_map[j][i] = '0';
			}
			if (i < ft_strlen(all->map[j]) && is_open(all->map[j][i]))
				new_map[j][i] = all->map[j][i];
		}
	}
	return (free_double_char(all->map), all->map = new_map, SUCCESS);
}
