/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:53:53 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 20:11:53 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	ft_msg_print(t_philo *philo, const char *message)
{
	long int	time_now;

	sem_wait(philo->data->resource);
	time_now = (ft_now() - philo->time_start);
	printf("(%ld)ms %d %s \n", time_now, philo->philo_id, message);
	if (message[10] == 'd')
		return ;
	sem_post(philo->data->resource);
}

long int	ft_now(void)
{
	struct timeval	t_now;

	gettimeofday(&t_now, NULL);
	return ((t_now.tv_sec * 1000) + (t_now.tv_usec / 1000));
}

void	ft_sleep(long int n_time, t_philo *philo)
{
	long int	curr_time;
	int			all;

	curr_time = ft_now();
	while ((ft_now() - curr_time) < n_time)
	{
		usleep(100);
		all = philo->data->n_philo - philo->philo_id;
		if (philo->data->max_meals == philo->min_meal && all == 1)
		{
			usleep(1000);
			printf("\n[Summary] : NO ONE DIE (%d)\n\n", philo->min_meal);
			exit(1);
		}
		if ((ft_now() - philo->time_meal) >= philo->data->time_2d)
		{
			ft_msg_print(philo, DEAD);
			exit(1);
		}
	}
}

static int	ft_overflow(int number)
{
	if (number < INT_MIN || number > INT_MAX)
	{
		printf("\033[0;31m[OVERFLOW DETECTED!]\033[0m\n");
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	number;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	if (ft_overflow(number))
		exit (0);
	return (number * sign);
}
