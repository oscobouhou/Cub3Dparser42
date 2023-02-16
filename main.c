/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:44:28 by pgros             #+#    #+#             */
/*   Updated: 2023/02/16 07:38:04 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dparser.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(int fd, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar_fd(fd, str[i]);
}

t_cub	*init_game(void)
{
	t_cub	*init;

	init = malloc(sizeof(t_cub));
	if (!init)
		return (NULL);
	init->extract = malloc(sizeof(t_extract));
	if (!init->extract)
		return (NULL);
	init->extract->map_width = 0; 
	init->extract->map_height = 0;
	init->extract->map = NULL;
	init->extract->textures[0] = NULL;
	init->extract->textures[1] = NULL;
	init->extract->textures[2] = NULL;
	init->extract->textures[3] = NULL;
	init->extract->parser = malloc(sizeof(t_parse));
	if (!init->extract->parser)
		return (NULL);
	init->extract->parser->check_prm = 0;
	init->extract->parser->charfile = NULL;
	return (init);
}

int	ft_char_cmp(char cmp1, char cmp2)
{
	return (cmp1 - cmp2);
}

// dprintf(2, "ext: %c    ---    input: %c\n", cmp1[len], cmp2[start]);
int	ft_reverse_cmp(char *cmp1, char *cmp2, int len)
{
	int	start;

	start = ft_strlen(cmp2) - 1;
	while (len + 1)
	{
		if (ft_char_cmp(cmp1[len], cmp2[start]))
			return (1);
		start--;
		len--;
	}
	return (0);
}

int	ft_check_arg(char **av, int ac)
{
	if (!(ac == 2))
	{
		ft_putstr_fd(2, "Error\n");
		ft_putstr_fd(2, "cub3d: invalid number of arguments\n");
		return (FAIL);
	}
	if (ft_reverse_cmp(".cub", av[1], 3))
	{
		ft_putstr_fd(2, "Error\n");
		ft_putstr_fd(2, "cub3d: argument doesn't terminate with '.cub'\n");
		return (FAIL);
	}
	return (SUCCESS);
}

char	*bufcat(char *buf, char **str)
{
	char	*new;
	int		i[2];

	if (!(*str))
	{
		new = malloc(sizeof(char) * 2);
		if (!new)
			return (NULL);
		new[0] = buf[0];
		new[1] = '\0';
		return (new);
	}
	i[0] = ft_strlen((*str));
	i[1] = 1;
	new = malloc(sizeof(char) * (i[0] + i[1] + 1));
	if (!new)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while ((*str)[i[0]])
	{
		new[i[1]] = (*str)[i[0]];
		i[0]++;
		i[1]++;
	}
	i[0] = 0;
	while (buf[i[0]])
	{
		new[i[1]] = buf[i[0]];
		i[0]++;
		i[1]++;
	}
	new[i[1]] = '\0';
	free((*str));
	return (new);
}

int	open_file(int *fd, char **av)
{
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd(2, "Error\n");
		ft_putstr_fd(2, "cub3d: 'open' ");
		ft_putstr_fd(2, strerror(errno));
		ft_putchar_fd(2, '\n');
		return (FAIL);
	}
	return (SUCCESS);
}

int	extract_map_info(t_cub *cub, char *buf, int fd)
{
	char	*str;

	str = NULL;
	while (1)
	{
		if (!read(fd, buf, 1))
			break ;
		str = bufcat(buf, &str);
	}
	cub->extract->parser->charfile = str;
	return (SUCCESS);
}

int	fill_rgb_params(t_cub *cub, int *i, int param)
{
	(void)i;
	(void)cub;
	(void)param;
	return (SUCCESS);
}

int	fill_cardinal_params(t_cub *cub, int *i, int param)
{
	int	tmp;

	tmp = *i;
	(*i)++;
	(*i)++;
	while (cub->extract->parser->charfile[*i] && (cub->extract->parser->charfile[*i] == ' ' \
		|| (cub->extract->parser->charfile[*i] >= 9 && cub->extract->parser->charfile[*i] <= 13)))
			(*i)++;
	while (cub->extract->parser->charfile[*i] != ' ' && (!(cub->extract->parser->charfile[*i] >= 9 \
		&& cub->extract->parser->charfile[*i] <= 13)))
		(*i)++;
	cub->extract->parser->game_infos[param] = malloc(sizeof(char) * (*i - tmp + 1));
	if (!cub->extract->parser->game_infos[param])
		return (FAIL);
	dprintf(2, "%d --- %d\n", *i, tmp);
	while (tmp < *i)
	{
		cub->extract->parser->game_infos[param][tmp] = cub->extract->parser->charfile[tmp];
		tmp++;
	}
	cub->extract->parser->game_infos[param][tmp] = '\0';
	dprintf(2, "game_infos: %s\n", cub->extract->parser->game_infos[param]);
	cub->extract->parser->check_prm++;
	return (SUCCESS);
}

int	check_info(t_cub *cub, int *i)
{
	if (cub->extract->parser->charfile[*i] == 'N' && cub->extract->parser->charfile[*i + 1] && cub->extract->parser->charfile[*i + 1] == 'O')
		fill_cardinal_params(cub, i, 0);
	else if (cub->extract->parser->charfile[*i] == 'S' && cub->extract->parser->charfile[*i + 1] && cub->extract->parser->charfile[*i + 1] == 'O')
		fill_cardinal_params(cub, i, 1);
	else if (cub->extract->parser->charfile[*i] == 'W' && cub->extract->parser->charfile[*i + 1] && cub->extract->parser->charfile[*i + 1] == 'E')
		fill_cardinal_params(cub, i, 2);
	else if (cub->extract->parser->charfile[*i] == 'E' && cub->extract->parser->charfile[*i + 1] && cub->extract->parser->charfile[*i + 1] == 'A')
		fill_cardinal_params(cub, i, 3);
	// else if (cub->extract->parser->charfile[*i] == 'F' && cub->extract->parser->charfile[*i + 1] && cub->extract->parser->charfile[*i + 1] == ' ')
	// 	fill_rgb_params(cub, i, 4);
	// else if (cub->extract->parser->charfile[*i] == 'C' && cub->extract->parser->charfile[*i + 1] && cub->extract->parser->charfile[*i + 1] == ' ')
	// 	fill_rgb_params(cub, i, 5);
	return (SUCCESS);
}

int	map_params(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->extract->parser->charfile[i])
	{
		if (!check_info(cub, &i))
			return (FAIL);
		else
			i++;
		if (cub->extract->parser->check_prm == 4)
			break ;
	}
	return (SUCCESS);
}

int	file_extractor(t_cub *cub, char **av)
{
	char	buf[1];
	int 	fd;

	if (!open_file(&fd, av))
		return (FAIL);
	if (!extract_map_info(cub, buf, fd))
		return (FAIL);
	if (!map_params(cub))
		return (FAIL);
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_cub	*cub;

	if (!ft_check_arg(av, ac))
		return (FAIL);
	cub = init_game();
	file_extractor(cub, av);
	(void)ac;
	return (0);
}

// FONCTIONS AUTORISEES
/*

open, close, read, write,
printf, malloc, free,
perror, strerror, exit
• Toutes les fonctions de
la lib math (-lm man man 3
math) */
