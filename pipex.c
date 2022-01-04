/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:47:05 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 15:55:40 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_init(char *cmd1, char *cmd2)
{
	int	fd[2];

	fd[0] = open(IFILE, O_CREAT | O_RDWR, 0600);
	fd[1] = open(OFILE, O_CREAT | O_WRONLY, 0600);
	if (fd[1] < 0 || fd[0] < 0)
	{
		ft_close_pipe(fd);
		return (ft_perror("open"));
	}
	puts("init done");
	if (ft_genfile(fd[0], cmd1))
		return (1);
	if (ft_genfile(fd[1], cmd2))
		return (1);
	ft_close_pipe(fd);
	return (0);
}

void	ft_clean(int pipe_fd[2])
{
	unlink(IFILE);
	unlink(OFILE);
	ft_close_pipe(pipe_fd);
}

static int	first_part(int pfd, int fd, char *exec)
{
	char	*params[3];
	char	*envs[1];

	*envs = NULL;
	params[0] = "/bin/bash";
	params[1] = exec;
	params[2] = NULL;
	while ((dup2(pfd, STDOUT_FILENO) == -1) && errno == EINTR)
		;
	close(pfd);
	while ((dup2(fd, STDIN_FILENO) == -1) && errno == EINTR)
		;
	close(fd);
	execve(*params, params, envs);
	return (0);
}

static int	second_part(int pfd, char *path)
{
	int		rt;
	int		fd;
	char	*buffer[BUFFER_SIZE];

	fd = open(path, O_CREAT | O_WRONLY, 0600);
	if (fd < 0)
		return (ft_perror("open"));
	while (1)
	{
		rt = read(pfd, buffer, BUFFER_SIZE);
		if (rt < 0)
		{
			close(fd);
			return (ft_perror("read"));
		}
		if (write(fd, buffer, rt) < 0)
		{
			close(fd);
			return (ft_perror("write"));
		}
		if (rt < BUFFER_SIZE)
			break ;
	}
	close(fd);
	return (0);
}

int	ft_main(int pfd[2], pid_t pid, char *path)
{
	int fd;
	//int	npfd[2];

	if (pid == 0)
	{
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return (ft_perror("open"));
		first_part(pfd[1], fd, IFILE);
		exit(0);
	}
	return (second_part(pfd[0], path));
}
