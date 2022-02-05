/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/05 22:46:02 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void init_cmd_struct(t_exec *vars, char **str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	vars->st = i;
	vars->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (i + 1));
	vars->cmds[i] = NULL;
	while (i)
	{
		vars->cmds[--i] = (t_cmd *)malloc(sizeof(t_cmd));
		vars->cmds[i]->cmd = str[i];
		vars->cmds[i]->v_rdr = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	char *str1;
	//представим, что подана строка "ls -al | wc -l"
	char *str[] = {"ls -al", "wc -l", NULL};
	t_exec vars;

	if (argc != 1)
		return (printf("Wrong arguments\n"));
	vars.envp = envp;
	init_cmd_struct(&vars, str);
	printf("%s\n", vars.cmds[0]->cmd);
	printf("%s\n", vars.cmds[1]->cmd);

	//Вероятно тут будет бесконечный цикл, который будет завершаться exit'ом или ошибкой minishell
	while(1)
	{
		//Здесь нужен код, который будет слушать ввод, что-то там было про библиотеку readline
		str1 = NULL;
		//str1 = readline("minishell>$ ");

		//Здесь будет парсер
		//parser(str1);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла
		//printf("%s\n", str1);
		//free(str1);

		//Здесь будет экзекютер
		executer(&vars);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла

		break ; //Убрать, когда будет написан код, слушающий ввод строки
	}
	//Вероятно, тут должна быть очистка памяти и закрытие потоков в случае exit'а или ошибки
	return (0);
}
