/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:20:10 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/15 17:51:03 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	pipex(t_all *pp)
{
	int	exit_code;
	
	if (pipe(pp->pipe_fd) == -1)
		exit_error(er_msg("pipe", ": ", strerror(errno), 1), pp);
	pp->child = 0;
	while (pp->child < pp->nbr_cmds)
	{
		pp->cmd_op = ft_split(pp->av[pp->child + 2 + pp->heredoc], '');
		if (!pp->cmd_op)
			exit_error(er_msg("unexpected error", "". "", 1), pp);
		pp->cmd_path = get_cmd(pp->cmd_op[0], pp);
	}
}

int	main(int ac, char **av, char **env)
{
	t_all	pp;
	int		exit_code;

	if (ac < 5)
	{
		if (ac > 2 && !ft_strncmp("here_doc", av[1], 9))
			return (er_msg("Use format: ",
					"./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.",
					"", 1));
		return (er_msg("Use format: ",
				"./pipex file1 cmd1 cmd2 ... cmdn file2.", "", 1));
	}
	else if (ac < 6 && !ft_strncmp("here_doc", av[1], 9))
		return (er_msg("Use format: ",
				"./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.", "", 1));
	if (!env || env[0][0] == '\0')
		exit_error(er_msg("Unexpected error.", "", "", &pp));
	pp = lets_init(ac, av, env);
	exit_code =
}

/*char	*get_cmd(char *cmd, char **env)
{
	char	*env_path;
	char	**paths;
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		env_path = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
		if (env_path)
		{
			env_path = ft_substr(env[i], 0, ft_strlen(env[i]));
			break ;
		}
		i++;
	}
	paths = ft_split(env_path, ':');
	free(env_path);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	free(paths);
	return (cmd_path);
}*/

/*int	main(int ac, char **av, char **env)
{
	char	*cmd_path;
	char	*options[3] = {"ls", "-la", NULL};
	char	*cmd;

	cmd = "ls";
	(void)ac;
	(void)av;
	cmd_path = get_cmd(cmd, env);
	if (!cmd_path)
	{
		perror(cmd_path);
		return (-1);
	}
	execve("/usr/bin/ls", options, env);
	printf("Victory!\n");
	free(cmd_path);
	return (0);
}*/