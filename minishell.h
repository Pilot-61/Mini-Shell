/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:17:11 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/01 20:25:34 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

int	g_sig_v;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tokens
{
	int				flag;
	char			*data;
	char			*type;
	int				join_mode;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_gcol
{
	void				*var;
	struct s_gcol		*next;
}				t_gcol;

typedef struct s_redr
{
	char			*redr;
	char			*type;
	struct s_redr	*next;
}				t_redr;

typedef struct s_control
{
	int	old_stdin;
	int	old_stdout;
	int	exit_status;
}	t_control;

typedef struct s_cmd
{
	char				*cmd;
	char				**args;
	t_redr				*redirections;
	t_control			control;
	struct s_cmd		*next;
}				t_cmd;

typedef struct s_herdoc
{
	char				**_eofs;
	struct s_herdoc		*next;
}				t_herdoc;

typedef struct s_exp
{
	char	*var_name;
	char	*var_val;
	char	*final_arg;
}				t_exp;

typedef struct s_var
{
	int				i;
	int				j;
	int				k;
	t_env			*envp;
	char			*line;
	t_cmd			*cmd_list;
	struct termios	term;
	int				single_counter;
	int				double_counter;
	int				in_sngl_qts;
	int				in_dbl_qts;
	t_tokens		*new_head;
	t_tokens		*new_token;
	char			*temp;
	t_exp			exp;
	size_t			len;
	char			*to_exp;
	char			**dbl_char;
	char			*result;
	char			*joined_data;
	t_tokens		*spc;
	int				c;
	int				ex;
	// int			fd;
	// int			i;
	// char *file_name;
	int				was_sgl;
}				t_var;

typedef struct parser
{
	t_tokens	*curr;
	t_tokens	*prev;
	t_tokens	*new_head;
	t_tokens	*node_before;
	t_tokens	*node_after;
	t_redr		*node_redirection;
	char		*red;
	t_cmd		*node_cmd;
	t_cmd		*head;
	t_redr		*head_red;
	char		*miniline;
	char		**splited_miniline;
	int			j;
}				t_parser;

int			ft_exit_status(int exit, int type);
void		handle_sig_child(int a);
int			is_empty_line(char *line);
int			open_close_quote(char *line);
int			is_space(char c);
int			is_not_spic(char *str);
int			space_at_end(char *str);
void		free_dbl_char(char **split);
int			space_in_begin(char *str);
char		*ft_strndup(const char *s, size_t n);
int			syntaxe_error(t_tokens *tokens);
void		add_back(t_tokens **head, char *value, char *type, int flag);
char		*to_linkd_list(t_tokens **head, char *value,
				char *type, char *start);
void		intial_data(t_var *var);
t_tokens	*tokenize(char *input);
t_cmd		*parse_commands(t_tokens *tokens);
t_tokens	*parser_commands(t_tokens	*head, char **env);
t_tokens	*createnode(char *value, char *type, int flag);
t_tokens	*copy_node(t_tokens *node);
void		ft_tkn_add_back(t_tokens **lst, t_tokens *newa);
t_tokens	*ft_new_token(void *content);
char		*expand_dlr_args(char *arg, char **env);
int			handle_num(t_var *var, char *arg);
t_tokens	*parser(t_tokens *tokens);
t_cmd		*new_cmd_node(char **content, t_redr *head_red);
void		ft_her_add_back(t_herdoc **lst, t_herdoc *newa);
int			is_numeric(const char *str);
t_herdoc	*create_herdoc_node(char **_EOF);
void		handel_sig(void);
void		joined(t_var **var, t_tokens *curr, char **env);
int			handle_env(t_tokens *curr, t_tokens **new_head,
				t_tokens *prev, char **env);
void		h_jnd(char **joined_data, int *was_sgl,
				t_tokens **new_head, char **env);
void		copy_and_add_to_list(t_tokens *curr, t_tokens **new_head);
void		join_token(t_tokens **new_head, t_tokens **curr);
char		*ft_itoa(int n);
int			handle_herdoc_del(t_tokens **curr, char **env, int fd,
				char *file_name);
void		handle_qu_par(t_tokens *curr, t_var *var,
				t_tokens *prev, char **env);
int			handle_word_env(t_tokens *curr, t_var *var,
				char **env, t_tokens *prev);
void		create_linkd_list_red(t_parser *var);
void		create_mini_line(t_parser *var);
void		create_last_result(t_parser *var);
void		add_cmd_back(t_cmd **head_cmds, t_cmd *node);
int			is_not_dlr(char *str);
void		expand_her(char *l, char **env, int fd);
char		*qtkn(t_tokens **head, char *start,
				int *in_sngl_qts, int *in_dbl_qts);
t_cmd		*the_input(char *line, t_env *env);
void		create_add_likedlist(t_tokens **head,
				char *val, char *type, int flag);
t_redr		*create_red_node(char *red, char *type);
void	printList_tcmd(t_cmd *lst);
void		next_skip_spaces(t_tokens **curr);
int			handle_ambguis(t_tokens *prev, char *to_exp, int c);
int			ft_isalnum(int c);
void		print_tokens(t_tokens *head);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_env		*ft_lstnew(char *key, char *value);
int			ft_lstadd_back(t_env **lst, t_env *news);
char		**ft_split2(char *s, char c);
void		ft_free(char **ptr);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
int			ft_strcmp(char	*s1, char *s2);
t_env		*envinit(char **env);
void		get_cwd(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		printenv(t_env	*envp);
void		split_command(char *input, char **cmd, char **arg);
char		*trim_spaces(const char *str);
int			ft_isspace(int c);
int			is_buit_in(t_cmd *command, t_env **envp);
void		echo(char *arg);
void		export(t_env **env, char **arg);
void		ft_lstdelone(t_env *lst, void (*del)(void*));
void		unset(t_env **envp, char *arg);
void		change_dir(char *temp, t_env **envp);
void		update_env(t_env **envp, const char *key, const char *value);
void		export_notargs(t_env **envp);
void		export_sort_alpha(t_env **envp);
void		exit_shell(t_env *env, t_cmd *arg);
void		free_env(t_env **env);
void		execution(t_cmd *command, char **envp, t_env *env);
char		*find_command_in_path(const char *cmd, t_env *g_env);
void		ft_strcat(char *dst, const char *src);
void		ft_strcpy(char *dst, char *src);
void		exec(t_cmd *cmd_list, t_env **envp);
void		exec_cmd(t_cmd *combined, char **env, t_env *envp);
void		exec_pip(t_cmd *commands, int command_count, t_env *env);
char		*my_split(char *str, const char *delim);
int			command_count(t_cmd *cmd_list);
void		handle_redirections(t_redr *redirections);
char		**env_to_array(t_env *envp);
void		free_cmd_list(t_cmd *cmd_list);
t_tokens	*parse_heredock(t_tokens *line, char **env);
void		err_exit(char *msg);
void		safe_waitpid(pid_t pid, int options);
void		safe_close(int fd);
int			safe_open(char *file, int flags, int mode);
void		safe_dup2(int old_fd, int new_fd);
pid_t		safe_fork(void);
void		handle_redirections(t_redr *redirections);
void		append_redir(char *file);
void		write_redir(char *file);
void		read_redir(char *file);
int			builin_checker(t_cmd *current_cmd, t_env **envp,
				t_control control);
void		init_control(t_control *control);
void		child_helper(t_cmd *current_cmd, t_env *env);
void		my_dup2(int old_stdin, int old_stdout);
int			built_in_check(char *command);
void		*ft_malloc(size_t size, int type);
t_env		*lstnew_env(char *key, char *value);
void		lstaddb_env(t_env **lst, t_env *news);
char		*ft_strdup2(const char *s1);
char		*ft_strjoin2(char const *s1, char const *s2);
void		ex_var(t_env *existing, char *k, char *v, int apnd);
void		parse_arg(char *arg, char **k, char **v, int *apnd);
#endif