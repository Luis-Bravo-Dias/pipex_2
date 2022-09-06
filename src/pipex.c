/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:08:42 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/06 12:42:08 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pipex(char **av, char **env)
{
	pid_t	child1;
	pid_t	child2;
	int		end[2];
	int		fd_in;
	int 	fd_out;
	char	*cmd1_path;
	char	*cmd2_path;

	if (pipe(ends) == -1)
		return (ERROR);
	child1 = fork ();
	if (child1 == -1)
		return (ERROR);
	if (child1 == 0)
	{
		fd_in = open(infile, O_RDONLY);
		if (!fd_in)
			return (ERROR);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (ERROR);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			return (ERROR);	
		cmd1_path = get_cmd(av[2], env);
		execve(cmd1_path, av[2], env);
	}
		
}