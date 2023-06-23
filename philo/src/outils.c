/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:53:53 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 20:29:05 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	ft_msg_print(t_philo *philo, const char *message)
{
	long int	time;

	pthread_mutex_lock(philo->data->resource);
	time = (ft_now() - philo->time_start);
	printf("(%ld)ms %d %s \n", time, philo->philo_id, message);
	pthread_mutex_unlock(philo->data->resource);
}

long int	ft_now(void)
{
	struct timeval	t_now;

	gettimeofday(&t_now, NULL);
	return ((t_now.tv_sec * 1000) + (t_now.tv_usec / 1000));
}

void	ft_sleep(long int n_time)
{
	long int	curr_time;

	curr_time = ft_now();
	while ((ft_now() - curr_time) < n_time)
		usleep(150);
}

static int	ft_overflow(long int number)
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
		return (0);
	return (number * sign);
}
