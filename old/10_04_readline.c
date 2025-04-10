/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:41 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/10 11:48:33 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct history {
	char *s;
	struct history *next;
}	t_cmd_history;

void	save_to_history(t_cmd_history *his, char *s);

void	free_history(t_cmd_history *his);

int	g_signum;

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
int	ft_strcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		exit(-1);
	while(s1[i] && i < n)
	{
		if (s1[i] - s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	i--;
	return (s1[i] - s2[i]);
}

char	*ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	p = malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = 0;
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	t;
	char	*p;

	i = 0;
	t = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while(s2[t])
	{
		p[t + i] = s2[t];
		t++;
	}
	p[t + i] = 0;
	free(s1);
	return (p);
}

char	*ft_strldup(char *s, size_t	n)
{
	size_t	i;
	size_t	len;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (n <= len)
		p = malloc(n + 1);
	else
		p = malloc(len + 1);
	while (s[i] && i < n)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = 0;
	return (p);
}


char	*ft_remove_isspace(char *s)
{
	size_t	i;
	size_t	t;
	size_t	count;
	char	*p;

	i = 0;
	t = 0;
	count = 0;
	if (!s)
		return NULL;
	while ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
		t++;
	while (s[i + t])
	{
		if ((s[i + t] >= 9 && s[i + t] <= 13) || s[i + t] == ' ')
		{
			while ((s[i + t] >= 9 && s[i + t] <= 13) || s[i + t] == ' ')
				t++;
			if (s[i + t])
				count++;
		}
		i++;
	}
	p = malloc(i + count + 1);
	i = t = 0;
	while ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
		t++;
	while (s[t])
	{
	//	p[i] = s[t];
		if ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
		{
			while ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
				t++;
			if (s[t])
				p[i] = ' ';
		}
		else
		{
			p[i] = s[t];
			t++;
		}
		i++;
	}
	p[i] = 0;
	return (p);
}
void	signal_handler(int signum)
{
//	printf("%d\n", rl_end);
//	printf("%d\n", rl_point);
//	printf("%s\n", rl_line_buffer);
	g_signum = signum;
//	rl_delete_text(0, rl_end);
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
//	rl_reset_line_state();
//	rl_forced_update_display();
//	rl_point = 0;
	
//	int	end_prompt = rl_end();
//	return (0);
}
int	ft_echo(char *p1)
{
	char	*s;

	s = ft_strchr(p1, 'o');
		//	arg[0] = "echo";
		//	arg[1] = s + 2;
	if (!s[1])
	{
		printf("\n");
			//	execve("/usr/bin/echo", arg, NULL);
			//check for error of execve
	}
	else if (s[1] == ' ')
	{
		s = ft_remove_isspace(s + 2);
	//	execve("/usr/bin/echo", arg, NULL);
		//check for error of execve
		if (!(ft_strcmp("-n ", s, 3)))
			printf("%s", (s + 3));
		else
			printf("%s\n", (s));
		free(s);
		//	return (0);
//			exit(0);
	}
	else
	{
		printf("%s: command not found\n", p1);
//		exit(127);
//		return (127);
	}
	return (0);
}
int	ft_pwd(void)
{
	char	*p2;

	p2 = NULL;
	p2 = getcwd(p2, 4100);
	printf("%s\n", p2);
	free(p2);
	return (0);
}

int	ft_cd(char	*p1)
{
	char	*p = NULL;
	char	*p2 = NULL;
	
	p = getcwd(p, 4100);
	printf("prev: %s\n", p);
	free(p);
	p = NULL;
	if (chdir(ft_strchr(p1, ' ') + 1))
	{
		printf("error while changing dir\n");
		exit (-1);
	}
	p = getcwd(p, 4100);
	printf("curr: %s\n", p);
}

char	**ft_export(char *p1, char ***envp, int *status)
{
	char **temp;
	char	**p;
	char	*s;
	char	*new;
	char	*t;
	int	size;
	size_t	i;

	i = 0;
	size = 0;
	temp = *envp;
		//return (*envp);
	if (!ft_strchr(p1, '='))
		return (*envp);
//	s = ft_strchr(p1, ' ') + 1;
	s = p1;
	while (s[size] && s[size] != '=')
		size++;
	// if the exported variable exist in the environement file
	while (temp[i])
	{
		if (!ft_strcmp(temp[i], s, size))
		{
			s = ft_strchr(s, '=');
			if (ft_strchr(s, ' '))
				t = ft_strldup(s, ft_strchr(s, ' ') - s);
			else
				t = ft_strdup(s);
			new = ft_strldup(temp[i], ft_strchr(temp[i], '=') - temp[i]);
			new = ft_strjoin(new, t);
			free(t);
		//	free(temp[i]); the environement is not stored in the heap :)
		//	what if I allocated the environement in the heap ???
			temp[i] = new;
			*status = 0;
			return (temp);
		}
		i++;
	}
	// copying the old variables and making space for the new one;
	size = 0;
	while (temp[size])
		size++;
	p = malloc(sizeof(char *) * (size + 2));
	if (!p) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		*status = -1;
		return (NULL);
	}
	p[size + 1] = NULL;
	size = 0;
	while (temp[size])
	{
		p[size] = ft_strdup(temp[size]);
		size++;
	}
	if (ft_strchr(s, ' '))
		p[size] = ft_strldup(s, ft_strchr(s, ' ') - s);
	else
		p[size] = ft_strdup(s);
	*status = 0;
	return (p);
//	envp = &p;
}

char	**ft_unset(char *p1, char **envp, int *status)
{
	char	**temp = envp;
	char	**p;
	char	*s;
	char	*t;
	size_t	i = 0;
	size_t	size = 0;
	size_t	size_env = 0;
	int	found = 0;

//	s = ft_strchr(p1, ' ');
	if (!s)
		return (temp);
//	s++;
	s = p1;
	while (s[size] && s[size] != ' ')
		size++;
	while (temp[i])
	{
		if (ft_strcmp(temp[i], s, size))
			found++;
		i++;
	}
	if (found)
	{
		i = 0;
		while (temp[size_env])
			size_env++;
		p = malloc(sizeof(char *) * (size_env));
		if (!p)
			exit(-1);
		p[size_env] = NULL;
		size_env = 0;
		while (temp[i])
		{	
			if (ft_strcmp(temp[i], s, size))
			{
				p[size_env] = ft_strdup(temp[i]);
				size_env++;
			}
				free(temp[i]);
			i++;
		}
		free(temp);
		return (p);
	}
	return (temp);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction C_d;
	struct sigaction C_c;
	int	end_prompt;
	char	*p1;
	char	*p2 = NULL;
	char	*s;
	char	**arg;
	int	child_pid = 0;
	int	child_info;
	int	status;
	char	*re_run = NULL;
/*	arg = malloc(sizeof(char*) * 3);
	arg[0] = NULL;
	arg[1] = NULL;
	arg[2] = NULL;
	t_cmd_history his;
	his.next = NULL;
	his.s = NULL;
	t_cmd_history *temp;*/
	p1 = NULL;
	g_signum = 0;
	sigemptyset(&(C_d.sa_mask));
	sigemptyset(&(C_c.sa_mask));
	C_d.sa_flags = 0;
	C_c.sa_flags = 0;
	C_d.sa_handler = SIG_IGN;
	C_c.sa_handler = signal_handler;
	char *cwd = NULL;
	cwd = getcwd(cwd, 4100);
	printf("cwd: %s\n", cwd);
	cwd = ft_strjoin(cwd, ": ");
	printf("%s\n", getenv("SHELL"));
	int i = 0;
/*	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}*/
	while (1)
	{
		sigaction(SIGQUIT, &C_d, NULL);
		sigaction(SIGINT, &C_c, NULL);
	// check sigaction for error;
//	check for readline error;
	// try this:
//	char *first = readline("prompt: ");
//		add_history("friendly");
		p1 = readline(cwd);
		p1 = ft_remove_isspace(p1);
		if (p1 && p1[0] == 0)
		{
			free(p1);
			p1 = NULL;
		//	p1 = readline("re_propmt: ");
		}
	//	if (p1)
		else if (!p1)
		{
			printf("exit\n");
	//		free_history(&his);
			free(p1);
			exit(0);
		}
		// need to handle the case where there are spaces before the program name
		else if (!ft_strcmp("pwd", p1, 3)) //&& p1[3] == 0)
		{
			status = ft_pwd();
		}
		else if (!ft_strcmp("echo", p1, 4))
		{
			status = ft_echo(p1);
		}
		else if (!ft_strcmp("cd", p1, 2))
		{
			status = ft_cd(p1);
		}
		else if (!ft_strcmp("export", p1, 6))
		{
			if (*(ft_strchr(p1, 't') + 1) != ' ')
				printf("Command not found\n");
			else
			{
				re_run = ft_strchr(p1, ' ') + 1;
				envp = ft_export(re_run, &envp, &status);
				while (ft_strchr(re_run, ' '))
				{
					re_run = ft_strchr(re_run, ' ') + 1;
					envp = ft_export(re_run, &envp, &status);
					re_run++;
				}
				i = 0;
				while (envp[i] != NULL)
				{
					printf("%s\n", envp[i]);
					i++;
				}
			}
		}
		else if (!ft_strcmp ("unset", p1, 5))
		{
			if (*(ft_strchr(p1, 't') + 1) != ' ')
				printf("Command not found\n");
			else
			{
				re_run = ft_strchr(p1, ' ') + 1;
				envp = ft_unset(re_run, envp, &status);							  while (ft_strchr(re_run, ' '))
				{
					re_run = ft_strchr(re_run, ' ') + 1;
					envp = ft_unset(re_run, envp, &status);
					re_run++;
				}
				i = 0;
				while (envp[i] != NULL)
				{
					printf("%s\n", envp[i]);
					i++;
				}
			}
		}
		else
			printf("%s: command not found\n", p1);
			//set the variable '?' to 127
//		if (p1)
//			save_to_history(&his, p1);
		if (p1 && p1[0] != 0)
			add_history(p1);
		free(p1);
	}
	free(cwd);
}
void	free_history(t_cmd_history *his)
{
	t_cmd_history *head;

	free(his->s);
	if (!(his->next))
		return;
	head = his->next;
	while (head)
	{
		free(head->s);
		head = head->next;
	}
	free(head->s);
}
void	save_to_history(t_cmd_history *his, char *s)
{
	t_cmd_history	*head;
	t_cmd_history	*temp;
	t_cmd_history	*new;
	
	head = his;
	if (head->next == NULL)
	{
		head->s = ft_strdup(s);
		return;
	}
	while (head && head->next)
		head = head->next;
	new = malloc(sizeof(t_cmd_history));
	new->s = ft_strdup(s);
	new->next = NULL;
	head->next = new;
}
