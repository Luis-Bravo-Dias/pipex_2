/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:20:10 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/13 13:07:57 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
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