/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzayas-s <vzayas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:23:04 by vzayas-s          #+#    #+#             */
/*   Updated: 2023/05/31 11:56:20 by vzayas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_init(t_info *info)
{
	int	i;
	//reservar memoria para hilo
	info->th = malloc(sizeof(pthread_t) * info->nb);
	if (!info->th)
		return (1);
	//reservar memoria para fork
	info->fork = malloc(sizeof(pthread_t) * info->nb);
	if (!info->fork)
	{
		//se liberan los hilos en caso de error
		free(info->th);
		return (1);
	}
	//se inician los mutex
	i = 0;
	while (++i < info->nb)
		pthread_mutex_init(&info->fork[i], NULL);
	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_init(&info->status, NULL);
	info->died = 0;
	info->eaten = 0;
	return (0);
}

static int	ft_get_args(char **argv, t_info *info)
{
	info->nb = ft_atoi(argv[1]);
	if (info->nb <= 0)
		return (1);
	info->ttd = ft_atoi(argv[2]);
	if (info->ttd <= 0)
		return (1);
	info->tte = ft_atoi(argv[3]);
	if (info->tte <= 0)
		return (1);
	info->tts = ft_atoi(argv[4]);
	if (info->tts <= 0)
		return (1);
	if (!argv[5])
		info->must_eat = 0;
	else
	{
		info->must_eat = atoi(argv[5]);
		if (info->must_eat <= 0)
			return (1);
	}
	if (ft_init(info))
		return (1);
	return (0);
}

int	ft_check(int argc, char **argv, t_info *info)
{
	if (argc < 5)
	{
		return (1);
		printf("there are not enough arguments\n");
	}
	if (argc > 6)
	{
		return (1);
		printf("there are too many arguments\n");
	}
	if (ft_get_args(argv, info))
		return (1);
	return (0);
}
