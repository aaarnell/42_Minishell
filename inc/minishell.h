/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:45:20 by cnorma            #+#    #+#             */
/*   Updated: 2022/04/04 01:06:21 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>					//для вывода кода ошибок из errno
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>					//для переменных внутри функции open()

# include "../readline/readline.h"
# include "../readline/history.h"
# include "../libft/libft.h"
# include <signal.h>
# include <termios.h>

pid_t		*g_pid;

typedef enum e_err{
	FR,
	ER,
	ERFR,
	ERFREX,
	FREX
}	t_err;

typedef enum e_rtp{
	OUT,
	INP,
	APN,
	HRD
}	t_rtp;

typedef struct s_redir{
	t_rtp			type;
	int				fd;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd{
	t_redir			*v_rdr;
	int				cmd_num;
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char	**envp;
	char	*str;
	t_cmd	*cmds;
	pid_t	pid;
	pid_t	*pids;
	int		ofd[2];
	int		pfd[2];
	int		tfd[2];
	t_cmd	*tm_cmd;
	int		st;
	char	*path;
	int		exit_status;
}	t_exec;


int		parser(t_exec *vars);
int		executer(t_exec *vars);
void	ft_quote(t_exec *vars, int *i);
void	ft_bslesh(t_exec *vars, int *i);
//void	ft_space(t_exec *vars, int *i);

void	ft_dollar_parse(t_exec *vars, int *i);
//void	ft_dollar(t_exec *vars, int *i);
//void	ft_dollar_question(t_exec *vars, int *i);

void	ft_backward_redir(t_exec *vars, int *i, int fd);
void	ft_forward_redir(t_exec *vars, int *i, int fd);
//t_redir	*ft_redir_new(t_cmd *tmp_cmds);
//t_redir	*ft_create_redir(void);
//char 	*ft_file_parser(t_exec *vars, int *i, t_rtp type);

void	ft_digit(t_exec *vars, int *i);
void	ft_split_pipe(t_exec *vars, int *i);
void	ft_create_cmdmas(t_exec *vars, char *new_str);
//char	**ft_str_newline(char **str_mas, char *new_str, int str_num);
t_cmd	*ft_create_cmds(void);

void	ft_create_cmdmas(t_exec *vars, char *new_str);
int		preparser(t_exec *vars);
char	*get_path(char **envp, char *cmd);
// int		redirection_fd(t_redir *v_rdr);
int		redirection_fd(t_redir *v_rdr, int fd);
int		redir_base(t_exec *vars);

char	*get_varname(char *var_str, int with_eq);
char	*get_varvalue(char *var_str);
int		srch_var_in_envp(char **envp, char *var_name);
int		add_var_in_envp(t_exec *vars, char *var);

int		builtin_check_exec(t_exec *vars);
int		builtin_export(t_exec *vars, char **cmd);
int		builtin_unset(t_exec *vars, char **cmd);
int		builtin_pwd(void);
int		builtin_echo(char **cmd);
void	chng_oldpwd(char **path, t_exec *vars);
char	*ft_cd_getpath(char	*dir, char **path);
int		builtin_cd(char	*dir, t_exec *vars);
int		builtin_env(t_exec *vars);
void	builtin_exit(t_exec *vars, char **code);

void	ft_signals(void);
// void	ft_signal_ctrl_d(t_exec *vars);


void	clean_base_struct(t_exec *vars, int ext);
int		ft_errfrex(t_exec *vars, t_err tp, int ex_st, char *err);
int		find_repl_val_var_in_envp(char **envp, char *var);

void	err_valid_id(t_exec *vars, char *str);
void	put_err(t_exec *vars, char *str1, char *str2);
void	err_search_var(char **path, t_exec *vars, char *str);

//void	ft_change_shlvl(t_exec *vars, int flag);

#endif
