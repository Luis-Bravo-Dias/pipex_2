/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:55:51 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/15 17:48:58 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*get_env_path(char **env)
{
	char	*path;
	int		i;

	i = 0:
	path = NULL;
	while (env[i] != NULL && env[i][0] != '\0')
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			break ;
		}
		i++;
	}
	return (path):
}

static char	**put_bars(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (paths[i])
	{
		tmp = path[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free_strs(tmp, NULL):
		i++;
	}
	return (paths);
}

static char	**get_paths(char **env)
{
	char	*env_path;
	char	**paths;

	env_path = get_env_path(env);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ":");
	free_strs(env_path, NULL);
	if (!paths)
		return (NULL);
	paths = put_bars(paths);
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;
	
	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			free_strs(NULL, paths);
			exit_error(er_msg("unexpected error", "", "", 1), NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_strs(cmd_path, NULL);
		i++;
	}
	return (NULL);
}

char	*get_cmd(char *cmd, t_all *pp)
{
	char	**paths;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (strdup(cmd));
	paths = get_paths(pp->env);
	if (!paths)
		return (NULL);
	cmd_path = get_cmd_path(cmd, paths);
	if (!cmd_path)
		er_msg("command not found", ": ", pp->av[pp->child + 2], 1);
	free_strs(NULL, paths);
	return (cmd_path);
}