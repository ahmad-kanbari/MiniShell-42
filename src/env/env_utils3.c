/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:39:06 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:15:09 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

/*
    check for the already head, if you find the 
	same key that is in the same node but the value of the 
    new node is zero , free the new node. other 
	than that I want you free the value of the older node 
    and update with the value of new node and free the new node after that.
*/
int	env_update_entry(t_env **env_head, t_env *new_node)
{
	t_env	*tmp;

	tmp = *env_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, new_node->key) == 0)
		{
			if (new_node->value == NULL)
			{
				free_env_node(&new_node);
				return (1);
			}
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(new_node->value);
			free_env_node(&new_node);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
    this function will check for all environment linked lists and , 
	and gonna update the value of the
    new node if it found one, other than that , it is gonn set the 
	the new node as the first node
    if the env_list is empty. if the env_list is not empty it is 
	gonna compare the key of the list
    and the key of the new node, if the differece between the new
	 node key and the env_list key is 
    less than 0 , the new node will be set before the env_list, 
	otherwise it is gonna loog and it 
    has been set and the end of the list node and just before the 
	head node because it is gonna be less than it;
*/
void	insert_sorted_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*head;
	t_env	*tmp;

	head = *env_list;
	tmp = NULL;
	if (env_update_entry(env_list, new_node))
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	if (ft_strcmp(new_node->key, (*env_list)->key) < 0)
	{
		new_node->next = *env_list;
		*env_list = new_node;
		return ;
	}
	while (head && ft_strcmp(new_node->key, head->key) > 0)
	{
		tmp = head;
		head = head->next;
	}
	tmp->next = new_node;
	new_node->next = head;
}

void	free_env_node(t_env **node)
{
	if ((*node)->key)
		ft_strdel(&(*node)->key);
	if ((*node)->value)
		ft_strdel(&(*node)->value);
	if (*node)
		free(*node);
	*node = NULL;
}

void	free_env_var_list(t_env **env_list)
{
	t_env	*tmp;
	t_env	*current;

	current = *env_list;
	while (current)
	{
		tmp = current->next;
		free_env_node(&current);
		current = tmp;
	}
	*env_list = NULL;
}

char	*getenv_value(t_minishell *shell, char *key, t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	if (ft_ifstrequal(key, "?"))
	{
		if (shell->exit_str)
			ft_strdel(&shell->exit_str);
		shell->exit_str = ft_itoa(shell->exit);
		return (shell->exit_str);
	}
	return (NULL);
}
