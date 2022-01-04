/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:25:39 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 16:31:22 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "pipex.h"
#include "utils/utils.h"

int	ft_perror(char *type)
{
	perror(type);
	return (1);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_printerr(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	ft_genfile(int fd, char *cmd)
{
	if (write(fd, "#!/bin/bash\n", 12) < 0)
		return (1);
	else if (write(fd, cmd, ft_strlen(cmd)) < 0)
		return (1);
	else if (write(fd, "\n", 1) < 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_pipes		*pipes;

	if (argc != 5)
		return (ft_printerr("Error: Invalid number of input"));
	pipes = ft_new_pipes(argc - 1);
	(void)argv;
	if (!pipes)
		return (ft_perror("malloc"));
}
