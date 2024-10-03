/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:15:48 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/03 22:48:50 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <errno.h>
#include <sys/_types/_size_t.h>

static char	*find_val(char *var, char **env)
{
	t_var	my_var;

	my_var.i = 0;
	my_var.len = 0;
	while (*var == '$')
		var++;
	my_var.len = ft_strlen(var);
	while (env[my_var.i])
	{
		if (ft_strncmp(env[my_var.i], var, my_var.len) == 0
			&& env[my_var.i][my_var.len] == '=')
			return (&env[my_var.i][my_var.len + 1]);
		my_var.i++;
	}
	return (NULL);
}

static void	expnad_env_word(char *arg, t_var *var, char **env)
{
	int		k;

	k = 0;
	k = var->ex + 1;
	if (arg[var->ex + 1] == '\'')
		var->exp.final_arg = ft_strdup("$");
	while ((arg[k] == '_' || ft_isalnum(arg[k])) && arg[k] != '\'')
		k++;
	var->exp.var_name = ft_strndup(&arg[var->ex + 1], k - var->ex - 1);
	var->exp.var_val = find_val(var->exp.var_name, env);
	if (!var->exp.var_val)
		var->exp.var_val = ft_strdup("\x03");
	if (var->exp.var_val)
		var->exp.final_arg = ft_strjoin(var->exp.final_arg, var->exp.var_val);
	var->ex = k - 1;
}

static void	expnad_cmd_word(char *arg, int *j, char **final_arg)
{
	char	*temp;

	temp = ft_strndup(&arg[*j], 1);
	*final_arg = ft_strjoin(*final_arg, temp);
}

char	*handle_odd_even_env(char *arg, t_var *var)
{
	while (arg[var->i])
	{
		while (is_space(arg[var->i]))
			var->i++;
		if (arg[var->i] == '$')
			var->c++;
		else
			break ;
		var->i++;
	}
	if (var->c % 2 == 0)
		return (var->exp.final_arg = ft_strdup(&arg[var->c])
			, var->exp.final_arg);
	return (NULL);
}

char	*expand_dlr_args(char *arg, char **env)
{
	t_var	var;

	intial_data(&var);
	if (*arg == '$' && (*(arg + 1) >= '1'
			&& *(arg + 1) <= '9')
		&& *(arg + 2) != '\0')
		arg += 2;
	if (!ft_strncmp(arg, "$", 2))
		return (var.exp.final_arg = ft_strdup("$"), var.exp.final_arg);
	if (!ft_strcmp(arg, "$?"))
		return (var.exp.final_arg = ft_itoa(ft_exit_status(0, 0))
			, var.exp.final_arg);
	if (handle_odd_even_env(arg, &var))
		return (var.exp.final_arg);
	while (arg[++var.ex])
	{
		if (arg[var.ex] != '$' )
			expnad_cmd_word(arg, &var.ex, &var.exp.final_arg);
		if (arg[var.ex] == '$')
			expnad_env_word(arg, &var, env);
	}
	return (var.exp.final_arg);
}
