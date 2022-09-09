/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:08:42 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/09 17:00:14 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_input(t_all *pp)
{
	if (pp->heredoc == 1)
	{
		
	}
}

/*void	pipex(char **av, char **env)
{
	pid_t	child1;
	pid_t	child2;
	int		end[2];
	int		fd_in;
	int 	fd_out;
	char	*cmd1_path;
	char	*cmd2_path;
	int		status;

	if (pipe(ends) == -1)
		return (ERROR);
	child1 = fork ();
	if (child1 == -1)
		return (ERROR);
	if (child1 == 0)
	{
		fd_in = open(av[1], O_RDONLY);
		if (!fd_in)
			return (ERROR);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (ERROR);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			return (ERROR);	
		cmd1_path = get_cmd(av[2], env);
		execve(cmd1_path, av[2], env);
	}
	else if (child1 > 0)
	{
		child2 = fork();
		if (child2 == -1)
			return (ERROR);
		else if (child2 == 0)
		{
			fd_out = open(av[4], O_RDONLY);
			if (!fd_out)
				return (ERROR);
			if (dup2(end[0], STDIN_FILENO) == -1)
				return (ERROR);
			if (dup2(end[1], STDOUT_FILENO) == -1)
				return (ERROR);
			cmd2_path = get_cmd(av[3], env);
			execve(cmd2_path, av[3], env);
		}
		else if (child2 > 0)
		{
			close(end[0]);
			close(end[1]);
			close(fd_in);
			close(fd_out);
			waitpid(child1, &status, 0);
			waitpid(child2, &status, 0);
		}
	}
		
}*/