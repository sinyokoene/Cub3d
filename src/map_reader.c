/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 23:28:39 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/08 23:29:30 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	open_map_file(char *map_file, int *fd, t_data *data);
void	read_map_lines(int fd, t_data *data, t_list **map_lines);
void	validate_map_lines(t_list *map_lines, t_data *data);
void	allocate_map(t_data *data, t_list *map_lines);
void	copy_map_lines(t_data *data, t_list *map_lines);

void	open_map_file(char *map_file, int *fd, t_data *data)
{
	*fd = open(map_file, O_RDONLY);
	if (*fd < 0)
	{
		fprintf(stderr, "Error\nFailed to open map file.\n");
		terminate(data);
	}
}

void	read_map_lines(int fd, t_data *data, t_list **map_lines)
{
	char	*line;
	int		in_map;

	in_map = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(line, data, map_lines, &in_map);
		line = get_next_line(fd);
	}
	close(fd);
}

void	validate_map_lines(t_list *map_lines, t_data *data)
{
	if (!map_lines)
	{
		fprintf(stderr, "Error\nMap data is missing.\n");
		terminate(data);
	}
}

void	allocate_map(t_data *data, t_list *map_lines)
{
	data->map_height = ft_lstsize(map_lines);
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
	{
		fprintf(stderr, "Error\nMemory allocation failed.\n");
		terminate(data);
	}
}

void	copy_map_lines(t_data *data, t_list *map_lines)
{
	t_list	*current;
	int		i;
	t_list	*temp;

	current = map_lines;
	i = 0;
	while (current)
	{
		data->map[i++] = ft_strdup(current->content);
		free(current->content);
		temp = current;
		current = current->next;
		free(temp);
	}
	data->map[i] = NULL;
}
