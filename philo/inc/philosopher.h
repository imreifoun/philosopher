/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:54:07 by areifoun          #+#    #+#             */
/*   Updated: 2023/06/22 03:15:51 by areifoun         ###   ########.fr       */
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
# include <limits.h>
# include <time.h>
# include <sys/time.h>

# define ERROR_MESSAGE "\033[0;31m[Example] ./philo [4] [410] [200] [200]\033[0m\n"
# define INVALID "\033[0;31m[Error] : Invalid Arguments !\033[0m"
# define ERROR_THREADS "[Error] : Threads Failed !"
# define PHILO "\033[0;31m\n[NO ONE DIED]\033[0m Philosophers have eaten"

# define ON "has taken a fork"
# define EAT "\033[0;32mis eating\033[0m"
# define DEAD "\033[0;31mdead\033[0m\n"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

typedef struct s_constd
{
	int				n_philo;
	int				max_meals;
	int				finised;
	int				end;

	bool			is_start;
	bool			is_end;
	bool			dead;

	long int		time_2d;
	long int		time_2e;
	long int		time_2s;

	pthread_mutex_t	*fork;
	pthread_mutex_t	*protect;
	pthread_mutex_t	*resource;
	pthread_mutex_t	*time_lock;

}t_constd;

typedef struct s_philo
{
	int				philo_id;
	int				min_meal;

	long int		time_start;
	long int		time_meal;

	t_constd		*data;

	pthread_t		philosophers;

	pthread_mutex_t	*lock;

	struct s_philo	*next;

}t_philo;

long int	ft_now(void);
void		*rotine(void *data);
void		ft_eat(t_philo *philo);
int			ft_check_arg(char **av);
t_philo		*ft_addnew(int counter);
int			ft_atoi(const char *str);
t_constd	*ft_init_data(char **av);
void		ft_sleep(long int n_time);
t_philo		*ft_lstlast(t_philo *head);
int			wait_routine(t_philo *philo);
void		ft_printlist(t_philo **philo);
int			ft_free(t_philo *p, t_constd *d);
void		ft_sleep_and_think(t_philo *philo);
int			ft_death(t_philo *philo, t_constd *data);
int			ft_check_data(t_constd *data, char **av);
void		ft_addback(t_philo *new, t_philo **head);
bool		ft_creat(t_philo *philo, t_constd *data);
int			break_philosophers(t_philo *philo, int key);
void		ft_get_time(t_philo *philo, t_constd *data);
bool		ft_mutex_init(t_philo *philo, t_constd *data);
void		ft_check_philo(t_philo *philo, t_constd *data);
int			ft_init_philo(t_constd *params, t_philo **head);
bool		ft_thread_creat(t_philo *philo, t_constd *data);
void		ft_destroy_mutex(t_philo *philo, t_constd *data);
void		ft_msg_print(t_philo *philo, const char *message);
int			ft_notice(char *msg, int key, t_philo *p, t_constd *d);
bool		ft_meals_and_dead(t_philo *philo, t_constd *data, int all);

#endif
