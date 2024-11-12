/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_minimap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 20:45:14 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/12 20:55:56 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_filled_circle(mlx_image_t *image, t_coords center, int radius,
		uint32_t color)
{
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_put_pixel(image, center.x + x, center.y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_tile(t_data *data, t_coords map, t_minimap *minimap)
{
	t_coords	screen;

	screen.x = minimap->center.x + (map.x - (int)data->player.x)
		* minimap->tile_size;
	screen.y = minimap->center.y + (map.y - (int)data->player.y)
		* minimap->tile_size;
	if (check_tile_within_circle(screen, minimap)
		&& data->map[map.y][map.x] == '1')
	{
		mlx_draw_rectangle(data->image, screen, (t_coords){minimap->tile_size,
			minimap->tile_size}, minimap->wall_color);
	}
}

void	draw_minimap_tiles(t_data *data, t_minimap *minimap)
{
	int	player_map_x;
	int	player_map_y;
	int	map_y;
	int	map_x;

	player_map_x = (int)data->player.x;
	player_map_y = (int)data->player.y;
	map_y = player_map_y - minimap->radius;
	while (map_y <= player_map_y + minimap->radius)
	{
		map_x = player_map_x - minimap->radius;
		while (map_x <= player_map_x + minimap->radius)
		{
			if (map_x >= 0 && map_x < (int)data->map_width && map_y >= 0
				&& map_y < (int)data->map_height)
			{
				draw_tile(data, (t_coords){map_x, map_y}, minimap);
			}
			map_x++;
		}
		map_y++;
	}
}

void	draw_player_icon(t_data *data, t_minimap *minimap)
{
	int			player_size;
	int			line_length;
	t_coords	line_start;
	t_coords	line_end;

	player_size = minimap->tile_size / 2;
	line_length = minimap->tile_size * 2;
	line_start = minimap->center;
	line_end.x = minimap->center.x + (int)(data->player.dir_x * line_length);
	line_end.y = minimap->center.y + (int)(data->player.dir_y * line_length);
	mlx_draw_rectangle(data->image, (t_coords){minimap->center.x - player_size
		/ 2, minimap->center.y - player_size / 2}, (t_coords){player_size,
		player_size}, minimap->player_color);
	mlx_draw_line(data->image, line_start, line_end, minimap->player_color);
}

void	draw_minimap(t_data *data)
{
	t_minimap	minimap;

	init_minimap(&minimap);
	draw_filled_circle(data->image, minimap.center, minimap.minimap_radius + 5,
		minimap.border_color);
	draw_filled_circle(data->image, minimap.center, minimap.minimap_radius,
		minimap.background_color);
	draw_minimap_tiles(data, &minimap);
	draw_player_icon(data, &minimap);
}
