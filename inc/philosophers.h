/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:51:54 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/10 12:12:05 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "aesthetic.h"

typedef struct s_data
{
	int philos_num;
	pthread_mutex_t start;
	pthread_mutex_t print;
	pthread_mutex_t *fork;
	int time_to_eat;
	int time_to_die;
	int time_sleep;
	int must_eat;
	int someone_died;
	long long start_time;
} t_data;

typedef struct s_philo
{
	int num_philo;
	int fork_left;
	int fork_right;
	int n_times_has_eat;
	long long last_eat;
	t_data *data;
} t_philo;

// parsing.c//
int is_digit(char **argv);
int check_errors(char **argv);
// errors.c//
void print_error_exit(char *error);
int ft_error(int n);
// data.c//
int ft_atoi(char *str);
int init_mutex(t_data *data);
int giving_data(t_data *data, char **argv);
// time_control.c //
long long time_dif(long long current, long long past);
long long get_time(void);
void ft_sleep(long long time);
// free_and_destroy.c //
int free_and_destroy(t_data *data, t_philo *philo, int out);
// create.c //
t_philo *create_philo(t_data *data);
void *if_only_one_philo(void *argv);
int create_one_philo(t_data *data, t_philo *philo);
// printing //
void printing(int n, t_philo *philo);
void continue_printing(int n, t_philo *philo);

#endif
