/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usf <usf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:51:08 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/15 12:55:12 by usf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "sys/time.h"
# include "pthread.h"

// # include "limits.h"
// # include "time.h"
// # include "strings.h"
// # include "string.h"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	pthread_mutex_t	*meals_eaten_lock;
	time_t			start_time;
	time_t			last_meal_time;
	pthread_mutex_t	*last_meal_lock;
	pthread_t		tid;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	time_t			lifespan;
	time_t			eating_duration;
	time_t			sleeping_duration;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				terminated;
	pthread_mutex_t	*terminated_lock;
	int				n_philos;
	int				n_meals;
}					t_data;

typedef struct s_gc_mutex
{
	pthread_mutex_t		*ptr;
	struct s_gc_mutex	*next;
}						t_gc_mutex;

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

int		ft_atoi(const char *nptr);
void	*gc_malloc(size_t size);
void	gc_free_all(void);
int		initialize_philos(t_data *data);
void	*cctv(void *args);
time_t	get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo, time_t time);
int		compare_meals_eaten(t_data *data);
int		get_state(t_data *data);
void	set_state(t_data *data, int val);
void	*habits(void *args);
void	precise_sleep(time_t time);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
time_t	get_current_time(void);
void	print_habit(t_philo *philo, char *msg);
int		gc_mutex_init(pthread_mutex_t **mutex);
void	gc_mutex_destroy_all(void);
int		gc_mutex_register(pthread_mutex_t *mutex);
int		increment_meals_eaten(t_philo *philo);

#endif
