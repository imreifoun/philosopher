/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:53:33 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 20:30:05 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

bool	ft_mutex_init(t_philo *philo, t_constd *data)
{
	int	i;

	data->fork = NULL;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->resource = NULL;
	data->resource = malloc(sizeof(pthread_mutex_t));
	if (!data->fork || !data->resource)
		return (1);
	if (pthread_mutex_init(data->resource, NULL) != 0)
		return (1);
	i = -1;
	while (++i < data->n_philo && philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (1);
		philo->data->resource = data->resource;
		philo = philo->next;
	}
	return (0);
}

int	ft_init_philo(t_constd *params, t_philo **head)
{
	int		i;
	t_philo	*node;

	i = 0;
	while (++i <= params->n_philo)
	{
		node = ft_addnew(i);
		if (!node)
			return (1);
		node->data = params;
		ft_addback(node, head);
	}
	ft_lstlast(*head)->next = *head;
	return (0);
}

int	ft_check_data(t_constd *data, char **av)
{
	if (av[5])
	{
		data->max_meals = ft_atoi(av[5]);
		if (data->max_meals <= 0)
			return (1);
	}
	else
		data->max_meals = -5;
	if (data->time_2d <= 0 || data->time_2e <= 0)
		return (1);
	else if (data->time_2s <= 0 || data->n_philo <= 0)
		return (1);
	return (0);
}

t_constd	*ft_init_data(char **av)
{
	t_constd	*tmp;

	tmp = malloc(sizeof(t_constd));
	if (!tmp)
		return (0);
	tmp->n_philo = ft_atoi(av[1]);
	tmp->time_2d = ft_atoi(av[2]);
	tmp->time_2e = ft_atoi(av[3]);
	tmp->time_2s = ft_atoi(av[4]);
	tmp->is_end = 0;
	tmp->dead = 0;
	tmp->end = 0;
	tmp->is_start = 0;
	if (ft_check_data(tmp, av))
		return (0);
	return (tmp);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_constd	*data;

	philo = NULL;
	if (ac > 6 || ac < 5 || ft_check_arg(av))
		return (ft_notice(ERROR_MESSAGE, 0, 0, 0));
	data = ft_init_data(av);
	if (!data || ft_init_philo(data, &philo))
		return (ft_notice(INVALID, 1, philo, data));
	if (ft_mutex_init(philo, data))
		return (ft_notice(ERROR_THREADS, 2, philo, data));
	if (ft_thread_creat(philo, data))
		return (ft_notice(ERROR_THREADS, 2, philo, data));
	ft_check_philo(philo, data);
	if ((data->is_end) && !(data->end))
		printf("%s \033[0;31m(%d)\033[0m times !\n", PHILO, philo->min_meal);
	return (ft_notice("\n\t[FINISH]\n", 2, philo, data));
}
