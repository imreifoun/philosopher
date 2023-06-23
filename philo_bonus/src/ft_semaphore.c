/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semaphore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:53:45 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 19:30:02 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static void	ft_eat(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->data->semaphore);
		ft_msg_print(philo, ON);
		if (philo->data->n_philo == 1)
			ft_sleep(philo->data->time_2d, philo);
		sem_wait(philo->data->semaphore);
		ft_msg_print(philo, ON);
		ft_msg_print(philo, EAT);
		ft_sleep(philo->data->time_2e, philo);
		philo->time_meal = ft_now();
		philo->min_meal++;
		sem_post(philo->data->semaphore);
		sem_post(philo->data->semaphore);
		ft_msg_print(philo, SLEEPING);
		ft_sleep(philo->data->time_2s, philo);
		ft_msg_print(philo, THINKING);
	}
}

static int	ft_philo_start(t_philo *philo)
{
	if (!(philo->philo_id % 2))
		ft_sleep(philo->data->time_2e, philo);
	ft_eat(philo);
	return (0);
}

static int	ft_start_proc(t_constd *data, t_philo *philo)
{
	int			i;
	long int	time;

	i = 0;
	time = ft_now();
	while (i++ < data->n_philo)
	{
		philo->time_start = time;
		philo->child = fork();
		if (philo->child == -1)
			return (1);
		if (philo->child == 0)
		{
			philo->time_meal = ft_now();
			ft_philo_start(philo);
		}
		philo = philo->next;
	}
	return (0);
}

int	ft_init_semaphore(t_constd *data, t_philo **philo)
{
	int		i;
	t_philo	*node;

	i = 0;
	sem_unlink("/semaphore");
	sem_unlink("/resource");
	data->semaphore = sem_open("/semaphore", O_CREAT, 0644, data->n_philo);
	data->resource = sem_open("/resource", O_CREAT, 0644, 1);
	if (data->semaphore == SEM_FAILED || data->semaphore == SEM_FAILED)
		return (1);
	while (++i <= data->n_philo)
	{
		node = ft_addnew(i);
		if (!node)
			return (1);
		node->data = data;
		ft_addback(node, philo);
	}
	ft_lstlast(*philo)->next = *philo;
	return (ft_start_proc(data, (*philo)));
}
