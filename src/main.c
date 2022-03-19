/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/19 23:23:47 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	switch_echoctl(char on)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	if (on)
		ts.c_lflag |= ECHOCTL;
	else
		ts.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
}

char	*ft_readline(void)
{
	char	*input;

	input = readline("minishell>$ ");
	if (!input)
	{
		printf(" exit\n");
		exit(-1);
	}
	else if (*input == '\0')
		free(input);
	else
		add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	//Нужно переменные занулять до выделения памяти, чтобы при очистке всех структур...
	//...в случае выхода по ошибке или стандартного, можно было очищать то, что выделено, и не очищать то, что не выделено
	t_exec	vars;
	// t_cmd	*tmp_cmds;
	// t_redir	*tmp_redir;
	// int		i;

	(void)argv;
	//инициализировать структуру или найти, где она инициализируется далее.
	//Возможно, инциализацию стоит сделать в начале бесконечного цикла ниже.
	if (argc != 1)
		return (printf("Wrong arguments\n"));
	vars.envp = ft_add_str_to_arr(envp, NULL); //почистить в конце
	vars.exit_status = 0;
	//начать с нуля
	//увеличить переменную SHLVL
	//возможно при повторном запуске минишел, передать ей в переменную текущее envp или SHLVL

	// i = -1;
	// while (vars.envp[++i])
	//  	printf("vars.envp[%d] = %s\n", i, vars.envp[i]);
	switch_echoctl(0);
	//vars.st = 1;
	//дописать заполнение указателей структуры нулями, а также в структурах, где аллоцируется память
	//а затем написать функцию очистки структур с проходом по указателям
	//либо сделать структуру с указателями памяти для очистки, fd'шниками дл закрытия, и функцию гарбэйдж-коллектора

	//Вероятно тут будет бесконечный цикл, который будет завершаться exit'ом или ошибкой minishell

	while(1)
	{
		//Здесь нужен код, который будет слушать ввод, что-то там было про библиотеку readline
		ft_signals();
		vars.str = ft_readline();
		if (!vars.str || !ft_strlen(vars.str))
			continue ;

		//Здесь будет парсер
		if (preparser(&vars))
			return (1);
		vars.st = 1;
		parser(&vars);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла

		free(vars.str);
		vars.str = NULL;
		//Здесь будет экзекютер
		if (executer(&vars) == -1)
			ft_errfrex(&vars, ERFR, vars.exit_status, NULL);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла
		else
			clean_base_struct(&vars, 0);
	}
	//Вероятно, тут должна быть очистка памяти и закрытие потоков в случае exit'а или ошибки
	//добавить изменине SHLVL
	//добавить изменение $_

	return (0);
}
