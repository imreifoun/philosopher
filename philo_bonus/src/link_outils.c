/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:53:45 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 19:31:44 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static void	ft_list_deallocale(t_philo	**head)
{
	t_philo	*current;
	t_philo	*next_node;

	current = (*head);
	while (current->next != *head)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	*head = NULL;
	free(current);
}

int	ft_notice(char *msg, int key, t_philo *p, t_constd *d)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(STDERR_FILENO, &msg[i], 1);
		i++;
	}
	write(1, "\n", 1);
	if (key == 1)
	{
		free(d);
		ft_list_deallocale(&p);
	}
	return (0);
}

t_philo	*ft_addnew(int counter)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->philo_id = counter;
	new->time_start = 0;
	new->time_meal = 0;
	new->next = NULL;
	return (new);
}

void	ft_addback(t_philo *new, t_philo **head)
{
	t_philo	*current;

	current = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_philo	*ft_lstlast(t_philo *head)
{
	t_philo	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
