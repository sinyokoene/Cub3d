/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 20:49:41 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/12 20:53:14 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_minimap(t_minimap *minimap)
{
	minimap->tile_size = 15;
	minimap->radius = 10;
	minimap->center = (t_coords){20 + minimap->radius * minimap->tile_size, 60
		+ minimap->radius * minimap->tile_size};
	minimap->minimap_radius = minimap->radius * minimap->tile_size;
	minimap->wall_color = 0xFFFFFF;
	minimap->player_color = 0xFF0000;
	minimap->border_color = 0x000000;
	minimap->background_color = 0xF5F5F5F5;
	minimap->corners_within_circle = 0;
}

void	init_line_direction(t_line *line)
{
	line->dir.x = abs(line->end.x - line->start.x);
	line->dir.y = -abs(line->end.y - line->start.y);
	if (line->start.x < line->end.x)
		line->step.x = 1;
	else
		line->step.x = -1;
	if (line->start.y < line->end.y)
		line->step.y = 1;
	else
		line->step.y = -1;
	line->err = line->dir.x + line->dir.y;
}

void	update_line_coords(t_line *line)
{
	int	e2;

	e2 = 2 * line->err;
	if (e2 >= line->dir.y)
	{
		line->err += line->dir.y;
		line->start.x += line->step.x;
	}
	if (e2 <= line->dir.x)
	{
		line->err += line->dir.x;
		line->start.y += line->step.y;
	}
}

void	mlx_draw_line(mlx_image_t *image, t_coords start, t_coords end,
		uint32_t color)
{
	t_line	line;

	line.image = image;
	line.start = start;
	line.end = end;
	line.color = color;
	init_line_direction(&line);
	while (1)
	{
		if (line.start.x >= 0 && line.start.x < (int)line.image->width
			&& line.start.y >= 0 && line.start.y < (int)line.image->height)
		{
			mlx_put_pixel(line.image, line.start.x, line.start.y,
				line.color);
		}
		if (line.start.x == line.end.x && line.start.y == line.end.y)
			break ;
		update_line_coords(&line);
	}
}

int	check_tile_within_circle(t_coords screen, t_minimap *minimap)
{
	int		corner_dx;
	int		corner_dy;
	int		corner_x;
	int		corner_y;
	float	corner_distance;

	minimap->corners_within_circle = 0;
	corner_dx = 0;
	while (corner_dx <= minimap->tile_size)
	{
		corner_dy = 0;
		while (corner_dy <= minimap->tile_size)
		{
			corner_x = screen.x + corner_dx;
			corner_y = screen.y + corner_dy;
			corner_distance = sqrtf((corner_x - minimap->center.x) * (corner_x
						- minimap->center.x) + (corner_y - minimap->center.y)
					* (corner_y - minimap->center.y));
			if (corner_distance <= minimap->minimap_radius)
				minimap->corners_within_circle++;
			corner_dy += minimap->tile_size;
		}
		corner_dx += minimap->tile_size;
	}
	return (minimap->corners_within_circle == 4);
}
