/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:26:13 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 20:12:37 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

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
	tmp->is_start = 0;
	tmp->total = 0;
	if (ft_check_data(tmp, av))
		return (0);
	return (tmp);
}

void	kill_pro(t_philo *philo)
{
	while (philo)
	{
		kill(philo->child, SIGKILL);
		philo = philo->next;
		if (philo->philo_id == 1)
			break ;
	}
	sem_close(philo->data->resource);
	sem_close(philo->data->semaphore);
	sem_unlink("/semaphore");
	sem_unlink("/resource");
}

int	main(int ac, char **av)
{
	t_constd	*data;
	t_philo		*philo;

	philo = NULL;
	if (ac > 6 || ac < 5 || ft_check_arg(av))
		return (ft_notice(ERROR_MESSAGE, 0, 0, 0));
	data = ft_init_data(av);
	if (!data || ft_init_semaphore(data, &philo))
		exit (0);
	waitpid(-1, NULL, 0);
	kill_pro(philo);
	return (ft_notice("\t-----------\n", 1, philo, data));
}
