/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:43:47 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/18 21:31:36 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

void	err(char *str)
{
	while (*str)
		write (2, str++, 1);
}

int	cd(char **av, int i)
{
	if (i != 2)
		return (err("error: cd: bad arguments\n"), 1);
	if (chdir(av[1]) == -1)
		return (err("error: cd: cannot change directory to "),
			err(av[1]), err("\n"), 1);
	return (0);
}

void	set_pipe(int is_pipe, int *fd, int end)
{
	if (is_pipe)
	{
		if (dup2(fd[end], end) == -1 || close(fd[0]) == -1
			|| close(fd[1]) == -1)
		{
			err("error: fatal\n");
			exit(1);
		}
	}
}

void	check_pipe(int is_pipe, int *fd)
{
	if (is_pipe && pipe(fd) == -1)
	{
		err("error: fatal\n");
		exit(1);
	}
}

void	check_pid(int pid)
{
	if (pid == -1)
	{
		err("error: fatal\n");
		exit(1);
	}
}

int	exec(char **av, char **env, int i)
{
	int	status;
	int	pid;
	int	fd[2];
	int	is_pipe;

	is_pipe = av[i] && !strcmp(av[i], "|");
	if (!is_pipe && !strcmp(*av, "cd"))
		return (cd(av, i));
	check_pipe(is_pipe, fd);
	pid = fork();
	check_pid(pid);
	if (!pid)
	{
		av[i] = 0;
		set_pipe(is_pipe, fd, 1);
		if (!strcmp(*av, "cd"))
			exit (cd(av, i));
		execve(av[0], av, env);
		err("error: cannot execute ");
		err(av[0]);
		err("\n");
		exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(is_pipe, fd, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	int	status;
	int	i;

	(void)ac;
	status = 0;
	i = 0;
	while (av[i])
	{
		av += i + 1;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (i)
			status = exec(av, env, i);
	}
	return (status);
}
