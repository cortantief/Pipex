/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:47:05 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 12:56:26 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!(str && *str))
		return (len);
	while (str[len])
		len++;
	return (len);
}

int	ft_perror(char *type)
{
	perror(type);
	return (errno);
}

int	ft_printerr(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	ft_close_pipe(int pipe[2])
{
	close(pipe[1]);
	close(pipe[0]);
}

int	ft_genfile(int fd, char *str)
{
	if (write(fd, "#!/bin/bash\n", 12) == -1)
		return (ft_perror("write"));
	if (write(fd, str, ft_strlen(str)) == -1)
		return (ft_perror("write"));
	if (write(fd, "\n", 1) == -1)
		return (ft_perror("write"));
	return (0);
}
