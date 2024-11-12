/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:37:58 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/12 18:12:20 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* Function to free texture paths */
void	free_texture_paths(t_data *data)
{
	free(data->north_texture_path);
	free(data->south_texture_path);
	free(data->west_texture_path);
	free(data->east_texture_path);
}

/* Function to free the map */
void	free_map(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

/* Function to terminate the program gracefully */
void	terminate(t_data *data)
{
	if (data->texture_north)
		mlx_delete_texture(data->texture_north);
	if (data->texture_south)
		mlx_delete_texture(data->texture_south);
	if (data->texture_west)
		mlx_delete_texture(data->texture_west);
	if (data->texture_east)
		mlx_delete_texture(data->texture_east);
	free_texture_paths(data);
	free_map(data);
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	if (data->mlx)
		mlx_terminate(data->mlx);
	exit(EXIT_SUCCESS);
}

/* Function to initialize MLX and create a new image */
void	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!data->mlx)
	{
		fprintf(stderr, "Error\nMLX42 initialization failed.\n");
		exit(EXIT_FAILURE);
	}
	data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->image)
	{
		fprintf(stderr, "Error\nFailed to create MLX42 image.\n");
		terminate(data);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
	{
		fprintf(stderr, "Error\nFailed to put image to window.\n");
		terminate(data);
	}
}

/* Main function */
int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 2 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		fprintf(stderr, "Error\nInvalid number of arguments.\n");
		fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	initialize_mlx(&data);
	parse_map(argv[1], &data);
	load_textures(&data);
	init_game(&data);
	hook_functions(&data);
	mlx_loop(data.mlx);
	terminate(&data);
	return (EXIT_SUCCESS);
}
