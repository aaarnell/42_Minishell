/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/19 22:51:14 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int redir_base(t_exec *vars)
{
	if (vars->tm_cmd != vars->cmds)
	{
		close(vars->tfd[1]);
		dup2(vars->tfd[0], 0);
		close(vars->tfd[0]);
	}
	if (vars->tm_cmd->next)
	{
		close(vars->pfd[0]);
		dup2(vars->pfd[1], 1);
		close(vars->pfd[1]);
	}
	return (0);
}

static void call_child(t_exec *vars)
{
	int res;

	redir_base(vars);
	if (redirection_fd(vars->tm_cmd->v_rdr) == -1)
		puterr_frexit(vars, ERFREX, 1, NULL);
	res = builtin_check_exec(vars);
	if (res == -1)
		puterr_frexit(vars, ERFREX, 1, NULL);
	if (!res)
	{
		vars->path = get_path(vars->envp, vars->tm_cmd->cmd[0]);
		if (!vars->path)
			puterr_frexit(vars, ERFREX, 1, NULL);
		if (execve(vars->path, vars->tm_cmd->cmd, vars->envp) == -1)
		{
			if (errno == 2)
				puterr_frexit(vars, ERFREX, 127, NULL);
			puterr_frexit(vars, ERFREX, 1, NULL);
		}
	}
	puterr_frexit(vars, FREX, 0, NULL);
}

static int call_parent(t_exec *vars)
{
	if (vars->tm_cmd != vars->cmds)
	{
		close(vars->tfd[0]);
		close(vars->tfd[1]);
	}
	vars->tfd[0] = vars->pfd[0];
	vars->tfd[1] = vars->pfd[1];
	if(waitpid(vars->pid, &vars->exit_status, WUNTRACED) == -1)
		return (-1);		//дописать норм выход с очисткой и выводом ошибки, как в баш
		//тут выхода не будет, программа уйдет на след. итерацию
	//сделать обработку сигналов от дочерних процессов
	// if (status == SIGINT || status == SIGQUIT)
	// 	signal_handler(status);
	// if (WIFEXITED(status))
	// 	g_status = WEXITSTATUS(status);
	return (0);
}

static int exec_cmd(t_exec *vars)
{
	if (vars->tm_cmd->next && pipe(vars->pfd) == -1)
		return (-1);
	vars->pid = fork();		//дописать проверку на ошибку
	if (vars->pid == -1)
		return (-1);
	if (!vars->pid)
		call_child(vars);	//обработка ошибок?
	return (call_parent(vars));
}

int executer(t_exec *vars)
{
	int res;

	res = 0;
	vars->ofd[0] = dup(0);
	vars->ofd[1] = dup(1);
	vars->tm_cmd = vars->cmds;
	while (vars->tm_cmd)
	{
		if (vars->st == 1)
		{
			res = builtin_check_exec(vars);
			if (res)
				break ;
		}
		res = exec_cmd(vars);
		if(res == -1)
			break ;
		vars->tm_cmd = vars->tm_cmd->next;
	}
	dup2(vars->ofd[0], 0);
	dup2(vars->ofd[1], 1);
	close(vars->ofd[0]);
	close(vars->ofd[1]);
	return (res);
}
