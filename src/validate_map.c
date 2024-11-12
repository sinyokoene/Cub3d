/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:54 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/09 00:18:37 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* Function to validate all characters in the map */
void	validate_map_characters(t_data *data, int *player_count)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			validate_map_character(data, x, y, player_count);
			x++;
		}
		y++;
	}
}

/* Function to check if a '0' tile is properly surrounded by walls */
void	check_map_wall(t_data *data, size_t x, size_t y)
{
	if (data->map[y][x] != '0')
		return ;
	if (y == 0 || x == 0 || y == data->map_height - 1
		|| x == ft_strlen(data->map[y]) - 1)
	{
		fprintf(stderr, "Error\nMap is not closed/surrounded by walls.\n");
		terminate(data);
	}
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
		|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
	{
		fprintf(stderr, "Error\nMap is not closed/surrounded by walls.\n");
		terminate(data);
	}
}

/* Function to validate the walls in the map */
void	validate_map_walls(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			check_map_wall(data, x, y);
			x++;
		}
		y++;
	}
}

/* Function to validate the player starting position */
void	validate_player_position(int player_count, t_data *data)
{
	if (player_count != 1)
	{
		fprintf(stderr,
			"Error\nThere must be exactly one player starting position.\n");
		terminate(data);
	}
}

/* Main function to validate the entire map */
void	validate_map(t_data *data)
{
	int	player_count;

	player_count = 0;
	validate_map_characters(data, &player_count);
	validate_map_walls(data);
	validate_player_position(player_count, data);
}
