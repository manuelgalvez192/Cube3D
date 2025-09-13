/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:33:27 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/13 17:45:09 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// Muestra el mapa en consola (para debug)
void	show_map(t_config *config)
{
	int	i;

	i = 0;
	printf("Mapa (%d filas, %f angle,:\n",
		config->map_rows, config->player_angle);
	while (i < config->map_rows)
	{
		printf("%s", config->map[i]);
		i++;
	}
}

#include "cube.h"

bool check_extension(const char *arg, const char *extension)
{
	const char *base = arg;
	const char *p = arg;
	size_t base_len;
	size_t ext_len = ft_strlen(extension);

	if (!arg || !*arg)
		return (true);
	while (*p)
	{
		if (*p == '/')
			base = p + 1;
		p++;
	}
	base_len = ft_strlen(base);
	if (base[0] == '.')
    	return (true);
	if (base_len <= ext_len)
		return (true);
	if (ft_strncmp(base + base_len - ext_len, extension, ext_len) != 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	int			fd;

	if (argc != 2)
		return (error_msg("Error\nNumero de argumentos invalido\n", NULL), 1);
	if (check_extension(argv[1], ".cub"))
		return (error_msg("Error\nExtension de archivo invalida\n", NULL), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("Error\nNo se pudo abrir el archivo\n", NULL), 1);
	config = ft_calloc(1, sizeof(t_config));
	if (!config)
		return (error_msg("Error\nFallo al asignar de memoria\n", config), 1);
	config->file_path = ft_strdup(argv[1]);
	if (!config->file_path)
		return (error_msg("Error\nFallo al asignar de memoria\n", config), 1);
	parse_file(config, fd);
	show_map(config);
	close(fd);
	run_game(config);
	free_config(&config);
	return (0);
}
