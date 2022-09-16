/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:08:42 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/16 15:01:29 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_heredoc(t_all *pp)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	tmp_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	stdin_fd = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		exit_error(er_msg("here_doc", ": ", strerror(errno), 1), pp);
	line = "";
	while (1)
	{
		ft_putstr_fd("here_doc < ", 1);
		line = get_next_line(stdin_fd);
		if (line == NULL)
			break ;
		if (ft_strlen(pp->av[2]) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, pp->av[2], ft_strlen(pp->av[2] + 1)))
			close(stdin_fd);
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
}

void	get_input(t_all *pp)
{
	if (pp->heredoc == 1)
	{
		get_heredoc(pp);
		pp->fd_in = open(".heredoc.tmp", O_RDONLY);
		if (pp->fd_in == -1)
			exit_error(er_msg("here_doc", ": ", strerror(errno), 1), pp);
	}
	else
	{
		pp->fd_in = open(pp->av[1], O_RDONLY, 644);
		if (pp->fd_in == -1)
			er_msg(strerror(errno), ": ", pp->av[1], 1);
	}
}

void	get_output(t_all *pp)
{
	if (pp->heredoc == 1)
		pp->fd_out = open(pp->av[pp->ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pp->fd_out = open(pp->av[pp->ac -1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pp->fd_out == -1)
		er_msg(strerror(errno), ": ", pp->av[pp->ac - 1], 1);
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