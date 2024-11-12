/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:34 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/12 18:12:29 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calculate_map_dimensions(t_data *data);
void	parse_map(char *map_file, t_data *data);

void	calculate_map_dimensions(t_data *data)
{
	size_t	line_length;
	int		j;

	j = 0;
	data->map_width = 0;
	while (data->map[j])
	{
		line_length = ft_strlen(data->map[j]);
		if (line_length > data->map_width)
			data->map_width = line_length;
		j++;
	}
}

void	parse_map(char *map_file, t_data *data)
{
	int		fd;
	t_list	*map_lines;

	map_lines = NULL;
	open_map_file(map_file, &fd, data);
	read_map_lines(fd, data, &map_lines);
	validate_map_lines(map_lines, data);
	allocate_map(data, map_lines);
	copy_map_lines(data, map_lines);
	calculate_map_dimensions(data);
	print_map(data->map);
	validate_map(data);
}
