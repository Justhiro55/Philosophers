/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:07:21 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/09/15 21:20:09 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philo *philo)
{
	if (get_time() - philo->last_meal_time > philo->info->time_to_die)
		return ;
	if (philo->info->finish_count == philo->info->philo_num)
		return ;
	if (philo->info->finish_count != philo->info->philo_num
		&& philo->info->dead != 1)
		print(philo, "is thinking");
}

void	sleep_philo(t_philo *philo)
{
	if (philo->info->dead == 1)
		return ;
	if (philo->info->finish_count != philo->info->philo_num
		&& philo->info->dead != 1)
		print(philo, "is sleeping");
	if (philo->info->finish_count == philo->info->philo_num)
		return ;
	usleep(philo->info->time_to_sleep * 1000);
	if (get_time() - philo->last_meal_time > philo->info->time_to_die)
		return ;
}

int	monitor_count(t_philo *philo)
{
	if (philo->eat_count == philo->info->must_eat && philo->finish_flag == 0)
	{
		philo->finish_flag++;
		philo->info->finish_count++;
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	if (philo->info->finish_count == philo->info->philo_num)
		return ;
	pthread_mutex_lock(&philo->info->forks[philo->id - 1]);
	if (philo->info->finish_count != philo->info->philo_num
		&& philo->info->dead != 1)
		print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->forks[(philo->id)
		% philo->info->philo_num]);
	if (philo->info->finish_count != philo->info->philo_num
		&& philo->info->dead != 1)
		print(philo, "has taken a fork");
	philo->last_meal_time = get_time();
	if (philo->info->finish_count != philo->info->philo_num
		&& philo->info->dead != 1)
		print(philo, "is eating");
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->info->forks[(philo->id)
		% philo->info->philo_num]);
	pthread_mutex_unlock(&philo->info->forks[philo->id - 1]);
	philo->eat_count++;
	monitor_count(philo);
}
