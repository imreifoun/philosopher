/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:16:46 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 03:39:31 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	wait_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->data->time_lock);
	if (philo->data->is_start)
	{
		pthread_mutex_unlock(philo->data->time_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->data->time_lock);
	return (1);
}

void	*rotine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (wait_routine(philo))
		continue ;
	if (!(philo->philo_id % 2))
		ft_sleep(100);
	while (!(break_philosophers(philo, 0)))
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
		if (!(break_philosophers(philo, 0)))
		{
			ft_msg_print(philo, SLEEPING);
			ft_sleep(philo->data->time_2s);
			if (!(break_philosophers(philo, 0)))
				ft_msg_print(philo, THINKING);
		}
	}
	return ((void *)0);
}

bool	ft_creat(t_philo *philo, t_constd *data)
{
	int			i;
	long int	curr_time;

	i = 0;
	printf("\n\033[0;31m[TOTAL OF PHILOSOPHERS %d]\033[0m\n\n", data->n_philo);
	curr_time = ft_now();
	while (philo && ++i <= data->n_philo)
	{
		philo->time_start = curr_time;
		philo->time_meal = curr_time;
		if (pthread_create(&philo->philosophers, NULL, &rotine, philo) == -1)
			return (1);
		pthread_detach(philo->philosophers);
		philo = philo->next;
	}
	pthread_mutex_lock(philo->data->time_lock);
	data->is_start = 1;
	pthread_mutex_unlock(philo->data->time_lock);
	return (0);
}

bool	ft_thread_creat(t_philo *philo, t_constd *data)
{
	int	i;

	i = -1;
	data->time_lock = NULL;
	data->time_lock = malloc(sizeof(pthread_mutex_t));
	data->protect = NULL;
	data->protect = malloc(sizeof(pthread_mutex_t));
	if (!data->protect || !data->time_lock)
		return (1);
	if (pthread_mutex_init(data->protect, NULL) != 0)
		return (1);
	if (pthread_mutex_init(data->time_lock, NULL) != 0)
		return (1);
	while (++i < philo->data->n_philo && philo)
	{
		philo->lock = &data->fork[i];
		philo = philo->next;
	}
	return (ft_creat(philo, data));
}

int	ft_check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][0]) || !(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
