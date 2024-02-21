/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_control_all.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:11:36 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/21 11:45:46 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_if_everyone_has_eaten(t_philo *philo)
{
	printing(6, philo);
	pthread_mutex_lock(&philo->data->print);
	philo->data->someone_died = 1;
	pthread_mutex_unlock(&philo->data->print);
}

int	check_if_someone_is_dead(t_philo *philo, int i)
{
	if (time_dif(get_time(), philo[i].last_eat) > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->start);
		pthread_mutex_lock(&philo->data->print);
		philo->data->someone_died = 1;
		printf(BRED "%lld Philo %d has died 💀\n" RESET, (get_time()
				- philo->data->start_time), (i + 1));
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->start);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->start);
	return (0);
}

void	*check_philo(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->someone_died == 0)
	// meter mutex cada vez que marco como que ha comido
	{
		i = 0;
		while (i < philo->data->philos_num)
		{
			if (check_if_someone_is_dead(philo, i) == 1)
				break ;
			i++;
		}
		while (--i >= 0 && (philo[i].n_times_has_eat == philo->data->must_eat)
			&& philo->data->someone_died == 0)
		{
			if (i == 0)
			{
				check_if_everyone_has_eaten(philo);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}

int	create_control(t_data *data, t_philo *philo)
{
	pthread_t	control;

	if (pthread_create(&control, NULL, &check_philo, philo) != 0)
	{
		printf("Can't control if someone died\n");
		return (free_and_destroy(data, philo, -1));
	}
	pthread_join(control, NULL);
	return (0);
}

void	*if_only_one_philo(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;                                  
		// TODO: que valor le d aqui
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
		// TODO: porque hace lock del fork dccho solamente
	printing(2, philo);                                       
		// TODO: de donde saca el int n = 2?
	ft_sleep(philo->data->time_to_die);                       
		// TODO: porque lo pone a dormir seguro
	printf(BRED "%lld Philo has died 💀\n" RESET,
			(get_time() // TODO: cuando printea esto?
			- philo->data->start_time));
	return (NULL);
}
