/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:37:45 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/12 20:55:30 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h" // Your get_next_line header
# include "MLX42/MLX42.h"                    // Include MLX42 header
# include "libft.h"                          // Your libft header
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 1200

// Keycodes for MLX42 (using GLFW key codes)
# define KEY_ESC GLFW_KEY_ESCAPE
# define KEY_W GLFW_KEY_W
# define KEY_A GLFW_KEY_A
# define KEY_S GLFW_KEY_S
# define KEY_D GLFW_KEY_D
# define KEY_LEFT GLFW_KEY_LEFT   // Left arrow key
# define KEY_RIGHT GLFW_KEY_RIGHT // Right arrow key

# define TOTAL_KEYS 349

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	int				frame_count;
	double			fps;
	double			last_time;
	int				key_states[TOTAL_KEYS];
	char			*north_texture_path;
	char			*south_texture_path;
	char			*west_texture_path;
	char			*east_texture_path;
	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_west;
	mlx_texture_t	*texture_east;
	t_color			floor_color;
	t_color			ceiling_color;
	char			**map;
	size_t			map_width;
	size_t			map_height;
	t_player		player;
}					t_data;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
}					t_ray;

typedef struct s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef struct s_minimap
{
	t_coords		center;
	int				tile_size;
	int				radius;
	int				minimap_radius;
	int				corners_within_circle;
	uint32_t		wall_color;
	uint32_t		player_color;
	uint32_t		border_color;
	uint32_t		background_color;
}					t_minimap;

typedef struct s_line
{
	t_coords		start;
	t_coords		end;
	t_coords		dir;
	t_coords		step;
	int				err;
	uint32_t		color;
	mlx_image_t		*image;
}					t_line;

// Minimap Constants
# define MM_TILE_SIZE 10 // Size of each tile on the minimap in pixels
# define MM_RADIUS 10 // Radius of the minimap in tiles
# define MM_POS_X 20 // X position of the minimap on the screen
# define MM_POS_Y 20 // Y position of the minimap on the screen
# define MM_DIAMETER_PIXELS (MM_RADIUS * 2 * MM_TILE_SIZE) // Diameter in pixels
# define MM_MID (MM_DIAMETER_PIXELS / 2) // Center of the minimap in pixels
# define MM_PLAYER_SIZE 5 // Size of the player marker
# define MM_BORDER_COLOR 0x888888FF // Color for the minimap border
# define MM_WALL_COLOR 0xFFFFFF // Color for walls on the minimap
# define MM_PLAYER_COLOR 0xFF0000 // Color for the player on the minimap
# define MM_DIR_COLOR 0x00FF00 // Color for player direction indicator

// Type Definitions
typedef struct s_ivector2
{
	int				x;
	int				y;
}					t_ivector2;

typedef struct s_vector2
{
	float			x;
	float			y;
}					t_vector2;
// Function prototypes
void				init_game(t_data *data);
void				load_textures(t_data *data);
void				parse_map(char *map_file, t_data *data);
void				validate_map(t_data *data);
void				hook_functions(t_data *data);
void				render(t_data *data);
void				terminate(t_data *data);
void				key_hook(mlx_key_data_t keydata, void *param);
void				loop_hook(void *param);
uint32_t			rgb_to_hex(t_color color);
uint32_t			get_texture_pixel(mlx_texture_t *texture, int x, int y);
void				set_player(t_data *data, int x, int y, char dir);
void				print_map(char **map);

// Utility functions in map_utils.c
void				ft_free_str_array(char **array);
int					ft_str_array_len(char **array);
size_t				ft_strcspn(const char *s1, const char *s2);
void				parse_color(char *line, t_color *color, t_data *data);

// Line processing functions in process_line.c
void				process_texture_line(char *line, t_data *data,
						int *handled);
void				process_color_line(char *line, t_data *data, int *handled);
void				process_map_line(char *line, t_list **map_lines,
						int *in_map, int *handled);
void				handle_invalid_line(char *line, int handled, t_data *data);
void				process_line(char *line, t_data *data, t_list **map_lines,
						int *in_map);

// Map reading functions in map_reader.c
void				open_map_file(char *map_file, int *fd, t_data *data);
void				read_map_lines(int fd, t_data *data, t_list **map_lines);
void				validate_map_lines(t_list *map_lines, t_data *data);
void				allocate_map(t_data *data, t_list *map_lines);
void				copy_map_lines(t_data *data, t_list *map_lines);

// Map parsing and dimension calculation functions in parse_map.c
void				calculate_map_dimensions(t_data *data);
void				parse_map(char *map_file, t_data *data);

void				clear_screen(t_data *data);
void				draw_floor_ceiling(t_data *data, uint32_t floor_color,
						uint32_t ceiling_color);
void				calculate_ray(t_data *data, int x, t_ray *ray);
void				calculate_step_initial_side_dist(t_data *data, t_ray *ray);
void				perform_dda(t_data *data, t_ray *ray);
void				calculate_perp_wall_dist(t_data *data, t_ray *ray);
void				calculate_line_dimensions(t_ray *ray);
mlx_texture_t		*select_texture(t_data *data, t_ray *ray);
void				calculate_texture_coordinates(t_data *data, t_ray *ray,
						mlx_texture_t *texture);
void				draw_vertical_line(t_data *data, int x, t_ray *ray,
						mlx_texture_t *texture);

// Rendering functions in render.c
void				clear_screen(t_data *data);
void				draw_floor_ceiling(t_data *data, uint32_t floor_color,
						uint32_t ceiling_color);
void				draw_vertical_line(t_data *data, int x, t_ray *ray,
						mlx_texture_t *texture);
void				render(t_data *data);
void				draw_minimap(t_data *data);
void				draw_fps(t_data *data);

// Minimap functions in render_minimap.c
void				draw_tile(t_data *data, t_coords map, t_minimap *minimap);
void				draw_minimap_tiles(t_data *data, t_minimap *minimap);
void				draw_circle(mlx_image_t *image, t_coords center, int radius,
						uint32_t color);
void				draw_player_icon(t_data *data, t_minimap *minimap);
void				init_minimap(t_minimap *minimap);

// Line drawing functions in render_utils.c
void				init_line_direction(t_line *line);
void				update_line_coords(t_line *line);
void				mlx_draw_line(mlx_image_t *image, t_coords start,
						t_coords end, uint32_t color);
void				mlx_draw_rectangle(mlx_image_t *image, t_coords pos,
						t_coords size, uint32_t color);

int				check_tile_within_circle(t_coords screen, t_minimap *minimap);

// Raycasting functions in raycasting.c
void				calculate_ray(t_data *data, int x, t_ray *ray);
void				calculate_step_initial_side_dist(t_data *data, t_ray *ray);
void				perform_dda(t_data *data, t_ray *ray);
void				calculate_perp_wall_dist(t_data *data, t_ray *ray);
void				calculate_line_dimensions(t_ray *ray);

// Movement functions in update_movement.c
void				update_move_forward(t_data *data);
void				update_move_backward(t_data *data);
void				update_strafe_left(t_data *data);
void				update_strafe_right(t_data *data);

// Rotation functions in update_rotation.c
void				update_rotate_left(t_data *data);
void				update_rotate_right(t_data *data);

void				validate_map_character(t_data *data, size_t x, size_t y,
						int *player_count);

#endif
