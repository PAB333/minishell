/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:38:33 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 21:12:29 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_redir(t_cmd *cmd, t_redirection_type type, char *value)
{
	t_redirection	*new;
	t_redirection	*tmp;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (0);
	new->type = type;
	new->file = ft_strdup(value);
	new->heredoc_fd = -1;
	new->next = NULL;
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}
