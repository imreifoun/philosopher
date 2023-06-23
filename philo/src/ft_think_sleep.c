/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:16:46 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 03:40:05 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	ft_sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(philo->data->resource);
	if (philo->min_meal == philo->data->max_meals)
	{
		philo->data->finised++;
		pthread_mutex_unlock(philo->data->resource);
		return ;
	}
	pthread_mutex_unlock(philo->data->resource);
}
