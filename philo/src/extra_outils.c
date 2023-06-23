/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 23:20:05 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 20:35:05 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	ft_death(t_philo *philo, t_constd *data)
{
	long int	time;

	pthread_mutex_lock(philo->data->resource);
	if ((ft_now() - philo->time_meal) >= philo->data->time_2d)
	{
		data->is_end = 1;
		philo->data->end += 1;
		if (philo->data->finised != philo->data->n_philo)
		{
			time = (ft_now() - philo->time_start);
			printf("(%ld)ms %d %s\n", time, philo->philo_id, DEAD);
		}
		return (0);
	}
	pthread_mutex_unlock(philo->data->resource);
	return (1);
}

bool	ft_meals_and_dead(t_philo *philo, t_constd *data, int all)
{
	all = 0;
	if (!(ft_death(philo, data)))
		return (0);
	pthread_mutex_lock(philo->data->resource);
	if (philo->data->finised == philo->data->n_philo)
	{
		philo->data->is_end = 1;
		return (0);
	}
	pthread_mutex_unlock(philo->data->resource);
	return (1);
}

void	ft_check_philo(t_philo *philo, t_constd *data)
{
	int	i;

	while (wait_routine(philo))
		continue ;
	while (1)
	{
		i = 0;
		while (++i <= philo->data->n_philo)
		{
			if (!ft_meals_and_dead(philo, data, i))
				return ;
			philo = philo->next;
		}
	}
	return ;
}

int	break_philosophers(t_philo *philo, int key)
{
	pthread_mutex_lock(philo->data->resource);
	if (philo->data->is_end)
	{
		pthread_mutex_unlock(philo->data->resource);
		if (key == 1)
			pthread_mutex_unlock(philo->lock);
		if (key == 2)
		{
			pthread_mutex_unlock(philo->lock);
			pthread_mutex_unlock(philo->next->lock);
		}
		return (1);
	}
	pthread_mutex_unlock(philo->data->resource);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (break_philosophers(philo, 1))
		return ;
	ft_msg_print(philo, ON);
	pthread_mutex_lock(philo->next->lock);
	if (break_philosophers(philo, 2))
		return ;
	ft_msg_print(philo, ON);
	ft_msg_print(philo, EAT);
	ft_sleep(philo->data->time_2e);
	pthread_mutex_lock(philo->data->resource);
	philo->time_meal = ft_now();
	philo->min_meal++;
	pthread_mutex_unlock(philo->data->resource);
	pthread_mutex_unlock(philo->lock);
	pthread_mutex_unlock(philo->next->lock);
}
