/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/27 21:28:49 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;

	if (argc != 1)
		return (printf("Wrong arguments\n"));

	//Вероятно тут будет бесконечный цикл, который будет завершаться exit'ом или ошибкой minishell
	while(1)
	{
		//printf("minishell>$ \n");
		readline("minishell>$ ");
		//Здесь нужен код, который будет слушать ввод, что-то там было про библиотеку readline

		//Здесь будет препарсер
		preparcer();
		//Здесь будет парсер
		parcer();	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла

		//Здесь будет экзекютер
		executer();	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла

		break ; //Убрать, когда будет написан код, слушающий ввод строки
	}
	//Вероятно, тут должна быть очистка памяти и закрытие потоков в случае exit'а или ошибки
	return (0);
}
