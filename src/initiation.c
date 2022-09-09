/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:46:49 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/09 16:38:46 by lleiria-         ###   ########.fr       */
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

t_all	lets_init(int ac, char **av, char **env)
{
	t_all	pp;
	
	pp = clear_init();
	pp.env = env;
	pp.ac = ac;
	pp.av = av;
	if (!ft_strncmp("here_doc", av[1], 9))
		pp.heredoc = 1;
	
}