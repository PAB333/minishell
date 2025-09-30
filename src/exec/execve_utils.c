/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:42:53 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 22:52:27 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec_error(char *cmd, t_all *all)
{
	if (is_directory(cmd))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		all->last_status_exit = 126;
	}
	else if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		all->last_status_exit = 126;
	}
	else
		all->last_status_exit = 0;
}

void	check_access_exec(char *cmd, char **args, char **envp, t_all *all)
{
	if (access(cmd, F_OK) != 0)
	{
		if (ft_strchr(cmd, '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			all->last_status_exit = 127;
		}
		return ;
	}
	handle_exec_error(cmd, all);
	if (all->last_status_exit == 0)
	{
		execve(cmd, args, envp);
		perror("minishell");
		all->last_status_exit = 126;
	}
}

char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (paths && paths[i])
	{
		path = ft_strjoin_3(paths[i], "/", cmd);
		if (!path)
			break ;
		if (access(path, X_OK && !is_directory(path)) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

char	*handle_no_path(char *cmd)
{
	char	*path;

	path = ft_strjoin("./", cmd);
	if (path && access(path, F_OK) == 0)
		return (path);
	if (path)
		free(path);
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	t_env	*tmp;
	char	**paths;
	char	*path;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (ft_strcmp(cmd, "..") == 0)
		return (NULL);
	tmp = env;
	while (tmp && ft_strcmp(tmp->name, "PATH") != 0)
		tmp = tmp->next;
	if (!tmp || !tmp->value)
		return (handle_no_path(cmd));
	paths = ft_split(tmp->value, ':');
	if (!paths)
		return (NULL);
	path = search_in_paths(paths, cmd);
	free_split(paths);
	return (path);
}
