/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:24:43 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 20:13:02 by areifoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include <time.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define ERROR_MESSAGE "\033[0;31m[Example] ./philo [4] [410] [200] [200]\033[0m"
# define INVALID "\033[0;31m[Error] : Invalid Arguments !\033[0m"
# define ERROR_THREADS "[Error] : Threads Failed !"

# define ON "has taken a fork"
# define EAT "\033[0;32mis eating\033[0m"
# define DEAD "\033[0;31mdead\033[0m"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

typedef struct s_constd
{
	int			total;
	int			n_philo;
	int			max_meals;

	bool		is_end;
	bool		is_dead;
	bool		is_start;

	long int	time_2d;
	long int	time_2e;
	long int	time_2s;

	sem_t		*resource;
	sem_t		*semaphore;

}t_constd;

typedef struct s_philo
{
	int				philo_id;
	int				min_meal;

	long int		time_start;
	long int		time_meal;

	pid_t			child;
	t_constd		*data;

	struct s_philo	*next;

}t_philo;

long int	ft_now(void);
t_philo		*ft_lstlast(t_philo *head);
int			ft_check_arg(char **av);
t_philo		*ft_addnew(int counter);
int			ft_atoi(const char *str);
t_constd	*ft_init_data(char **av);
int			ft_check_data(t_constd *data, char **av);
void		ft_addback(t_philo *new, t_philo **head);
void		ft_sleep(long int n_time, t_philo *philo);
int			ft_link_philo(t_constd *data, t_philo **philo);
void		ft_msg_print(t_philo *philo, const char *message);
int			ft_init_semaphore(t_constd *data, t_philo **philo);
int			ft_notice(char *msg, int key, t_philo *p, t_constd *d);

#endif
