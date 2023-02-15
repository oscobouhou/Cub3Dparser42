/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:44:28 by pgros             #+#    #+#             */
/*   Updated: 2023/02/15 17:16:28 by oboutarf         ###   ########.fr       */
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
	return (init);
}
int	file_extractor(t_cub *cub, char **av)
{
	
	(void)cub;
	(void)av;
	return (SUCCESS);
}

int	ft_char_cmp(char cmp1, char cmp2)
{
	return (cmp1 - cmp2);
}

int	ft_reverse_cmp(char *cmp1, char *cmp2, int len)
{
	int	start;

	start = ft_strlen(cmp2) - 1;
	while (len)
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
		ft_putstr_fd(2, "cub3d: argument doesn't terminal with '.cub'\n");
		return (FAIL);
	}
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

/* open, close, read, write,
printf, malloc, free,
perror, strerror, exit
• Toutes les fonctions de
la lib math (-lm man man 3
math) */