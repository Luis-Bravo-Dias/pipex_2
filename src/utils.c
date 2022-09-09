/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:48:32 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/09 12:35:07 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	er_msg(char *str1, char *str2, char *str3, int erno)
{
	ft_putstr_fd("pipex ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
	return (erno);
}

static void	close_pipe_fds(t_all *pp)
{
	int	i;
	
	i = 0;
	while (i < (pp->nbr_cmds - 1) * 2)
	{
		close(pp->pipe_fd[i]);
		i++;
	}
}

void	close_fds(t_all *pp)
{
	if (pp->fd_in != -1)
		close(pp->fd_in);
	if (pp->fd_out != -1)
		close(pp->fd_out);
	close_pipe_fds(pp);
}

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i]);
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	exit_error(int status, t_all *pp)
{
	if (pp)
	{
		close_fds(pp);
		if (pp->pipe_fd != NULL)
			free(pp->pipe_fd);
		if (pp->pids != NULL)
			free(pp->pids);
		if (pp->cmd_op != NULL || pp->cmd_path != NULL)
			free_strs(pp->cmd_path, pp->cmd_op);		
	}
	if (pp->heredoc == 1)
		unlink(".heredoc.tmp");
	exit(status);
}