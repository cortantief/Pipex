/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:47:05 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 11:41:54 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 128
#define IFILE ".exec1"
#define OFILE ".exec2"

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

void	ft_printerr(char *str)
{
	write(2, str, ft_strlen(str));
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

int	ft_main(int pfd[2], pid_t pid, char *path)
{
	char	*parms[3];
	char	*envs[1];
	char	buffer[BUFFER_SIZE];
	int		rt;
	int		fd;

	*envs = NULL;
	parms[2] = NULL;
	if (pid == 0)
	{
		*parms = "/bin/bash";
		parms[1] = IFILE;
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return (ft_perror("open"));
		while ((dup2(pfd[1], STDOUT_FILENO) == -1) && errno == EINTR)
			puts("lol");
		close(pfd[1]);
		/*while ((dup2(fd, STDIN_FILENO) == -1) && errno == EINTR)
			puts("mdr");
		*/execve(*parms, parms, envs);
		close(fd);
	}
	else
	{
		puts("qsd");
		fd = open(path, O_CREAT | O_WRONLY, 0600);
		if (fd < 0)
			return (ft_perror("open"));
		while (1)
		{
			rt = read(pfd[0], buffer, BUFFER_SIZE);
			if (rt < 0)
			{
				close(fd);
				return (ft_perror("read"));
			}
			write(fd, buffer, rt);
			if(rt < BUFFER_SIZE)
				break ;
		}
		close(fd);
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (argc < 5)
	{
		ft_printerr("Not enough arguments gived\n");
		return (1);
	}
	if (ft_init(argv[2], argv[3]))
	{
		ft_clean(pipe_fd);
		return (1);
	}
	if (pipe(pipe_fd) == -1)
		return (ft_perror("pipe"));
	pid = fork();
	if (pid == -1)
	{
		ft_clean(pipe_fd);
		return (ft_perror("fork"));
	}
	ft_main(pipe_fd, pid, pid == 0 ? argv[0] : argv[4]);
	ft_clean(pipe_fd);
}
