/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:34:08 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 22:51:14 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// ** MAIN **

// main_loop.c
int		process_line(char *line, t_all *all);

// ** BUILTINS **

int		ft_echo(t_cmd *cmd);
int		ft_env(t_env *envp);
int		ft_cd(t_cmd *cmd, t_env **env);
void	ft_exit(t_cmd *cmd, t_all *all);
int		ft_unset(t_env **env, t_cmd *cmd);
int		ft_pwd(void);

// export
void	ft_env_export(t_env *envp);
int		ft_export(t_cmd *cmd, t_env **env);
void	add_env_node(t_env **env, t_env *new);

// utils_builtins
int		count_arg(char **arg);
int		is_valid_long_long(char *str);
void	set_env_var(t_env *node, char *new_value);
int		no_home(char *old_cwd, char *path);

// ** ENV **

// env_expansion.c
char	*expand_variables(char *str, t_env *env, int is_quoted, t_all *all);
char	*get_env_value(char *name, t_env *env);

// env_expansion_utils.c
char	*join_words(char **words);
char	*get_env_value(char *name, t_env *env);

// init_env.c
t_env	*envp_to_list(char **envp);

// env_array.c
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
char	**env_list_to_array(t_env *env);

// ** EXEC **

// exec_cmd.c
void	exec_cmd(t_cmd *cmd, t_all *all);
void	execute_child_process(t_cmd *cmd, t_all *all, t_pipe_data *data);

// cmd_utils.c
t_cmd	*new_cmd(void);
int		count_args(t_token *token);
void	dot_command(t_cmd *cmd, t_all *all);
int		is_directory(const char *path);

// heredoc.c
int		handle_heredoc(char	*delimiter, t_all *all);

// execve_utils.c
char	*get_path(char *cmd, t_env *env);
void	check_access_exec(char *cmd, char **args, char **envp, t_all *all);

// exec_cmd_utils.c
void	restore_fds(int saved_fds[2]);
void	exec_cmd_loop(t_cmd *cmd, t_all *all);
void	save_fds(int saved_fds[2]);

// exec_cmd_utils_children.c
void	wait_all_children(pid_t last_pid, t_all *all);
void	setup_child_pipes(t_cmd *cmd, int in_fd, int pipe_fd[2]);
void	child_exit_handler(t_cmd *cmd, char *path, char **envp_arr, t_all *all);

// redir_utils.c
int		handle_in(t_redirection *r);
int		handle_out(t_redirection *r);
int		handle_append(t_redirection *r);
int		handle_hd(t_redirection *r);

// redir.c
int		handle_redirections(t_cmd *cmd);

// exec_builtins.c
void	exec_builtin(t_cmd *cmd, t_all *all);
int		is_stateful_builtin(t_cmd *cmd);

// ** PARSER **

// heredoc_prepare.c
int		prepare_all_heredocs(t_cmd *head, t_all *all);

// parsing.c
t_cmd	*parser(t_token *tokens, t_all *all);
int		process_token(t_cmd *cmd, t_token **tokens, int *i);

// parsing_utils.c
int		count_fields_in_word(char *s);
int		compute_args_capacity(t_token *tokens);
void	strip_inplace(char *s, char ch);
int		add_fields_to_args(t_cmd *cmd, char **fields, int *i);

// parsing_cmd_utils.c
void	set_cmd_type(t_cmd *cmd);
int		parse_single_cmd(t_cmd *cmd, t_token **tokens);

// split_quote.c
char	**split_with_quote(char *line, t_all *all);
char	*extract_word(char *line, int *i, t_all *all, int skip_expand);

// split_quote_helper.c
char	*extract_quoted(char *line, int *i, int skip_expand, t_all *all);
int		count_tokens(char *line);

// split_utils.c
void	skip_spaces(char *line, int *i);
int		is_single_operator(char c);
int		is_double_operator(char *s, const char *op, int *i);
char	*extract_delimiter(char *line, int *i);
char	*handle_quotes(char *line, int *i, int skip_expand, t_all *all);

// tokens_redir.c
int		add_redir(t_cmd *cmd, t_redirection_type type, char *value);

// tokens.c
t_token	*create_struct_tokens(char **pre_token);

// SIG
void	siging_handler(int sig);
void	set_heredoc_interrupted(int sig);

// ** UTILS **

// check_error.c
int		check_syntax_errors(t_token *tokens);

// free_utils
void	free_array_str(char **str);
void	free_cmd(t_cmd *cmd);
void	free_token(t_token *token);
void	free_env(t_env *env);
void	free_export_add_env(t_env *new, char **arg);
void	free_all(t_all *all);
void	free_split(char **split_arg);

// close_heredoc.c
void	close_all_heredocs(t_cmd *head);

#endif