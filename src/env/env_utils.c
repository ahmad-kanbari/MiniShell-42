/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 06:47:59 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 22:29:21 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*env_new(char *key, char *value, int flag)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->value = value;
	env_node->key = key;
	env_node->next = NULL;
	env_node->tmp = 0;
	env_node->sign = flag;
	return (env_node);
}

static char	*creat_entry_value(char *equal_sign, char *key)
{
	char	*shllvl;
	int		num;
	char	*value;

	if (ft_ifstrequal(key, "SHLVL"))
	{
		shllvl = ft_strdup(equal_sign + 1);
		if (!shllvl)
			value = ft_itoa(2);
		else
		{
			num = ft_atoi(shllvl);
			num++;
			value = ft_itoa(num);
		}
		free(shllvl);
	}
	else
		value = ft_strdup(equal_sign + 1);
	return (value);
}

//check all the envp , and get all the key befoe the '=' 
//and the create a new node , and insert it to the env_list;
void	add_env_entry(t_minishell *minishell, char **envp, \
	int i, t_env **env_list)
{
	char		*key;
	char		*value;
	char		*equal_sign;
	t_env		*new_node;

	(void)minishell;
	equal_sign = ft_strchr(envp[i], '=');
	if (equal_sign)
	{
		key = ft_substr(envp[i], 0, equal_sign - envp[i]);
		value = creat_entry_value(equal_sign, key);
		new_node = env_new(key, value, 1);
	}
	else
		new_node = env_new(ft_strdup(envp[i]), NULL, 0);
	ft_env_lstadd_back(env_list, new_node);
}

void	init_env_list(t_minishell *minishell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_env_entry(minishell, envp, i, &minishell->env_list);
		i++;
	}
	if (getenv_value(minishell, "PATH", minishell->env_list))
		parse_bin(minishell);
}
