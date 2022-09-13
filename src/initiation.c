/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:46:49 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/13 13:07:33 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static t_all	clear_init(void)
{
	t_all	pp;

	pp.env = NULL;
	pp.ac = -1;
	pp.av = NULL;
	pp.heredoc = 0;
	pp.fd_in = -1;
	pp.fd_out = -1;
	pp.pipe_fd = NULL;
	pp.nbr_cmds = -1;
	pp.child = -1;
	pp.pids = NULL;
	pp.cmd_op = NULL;
	pp.cmd_path = NULL;
	return (pp);
}

static void	create_pipes(t_all *pp)
{
	int	i;

	i = 0;
	while (i < pp->nbr_cmds - 1)
	{
		if (pipe(pp->pipe_fd + 2 * i) == -1)
			exit_error(er_msg("Could not create pepi", "", "", 1), pp);
		i++;
	}
}

t_all	lets_init(int ac, char **av, char **env)
{
	t_all	pp;

	pp = clear_init();
	pp.env = env;
	pp.ac = ac;
	pp.av = av;
	if (!ft_strncmp("here_doc", av[1], 9))
		pp.heredoc = 1;
	get_input(&pp);
	get_output(&pp);
	pp.nbr_cmds = ac - 3 - pp.heredoc;
	pp.pids = malloc(sizeof * pp.pids * pp.nbr_cmds);
	if (!pp.pids)
		exit_error(er_msg("PID error", strerror(errno), "", 1), &pp);
	pp.pipe_fd = malloc(sizeof * pp.pipe_fd * 2 * (pp.nbr_cmds - 1));
	if (!pp.pipe_fd)
		exit_error(er_msg("Pipe error", "", "", 1), &pp);
	create_pipes(&pp);
	return (pp);
}
