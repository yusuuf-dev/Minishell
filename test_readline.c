/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:41 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/09 09:29:20 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

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
int	main(void)
{
	struct sigaction C_d;
	struct sigaction C_c;
	int	end_prompt;
	char	*p1;
	char	*p2;
	char	*s;
	t_cmd_history his;
	his.next = NULL;
	his.s = NULL;
	t_cmd_history *temp;
	p1 = NULL;
	g_signum = 0;
	sigemptyset(&(C_d.sa_mask));
	sigemptyset(&(C_c.sa_mask));
	C_d.sa_flags = 0;
	C_c.sa_flags = 0;
	C_d.sa_handler = SIG_IGN;
	C_c.sa_handler = signal_handler;
	while (1)
	{
		//printf("%p\n", his.next);
		sigaction(SIGQUIT, &C_d, NULL);
		sigaction(SIGINT, &C_c, NULL);
	// check sigaction for error;
//	char *p = readline("prompt: ");
//	check for readline error;
	// try this:
//	char *first = readline("prompt: ");
//	sleep(3);
//		add_history("friendly");
	/*	if (his.s)
		{
			temp = &his;
			while (temp)
			{
				add_history(temp->s);
				temp = temp->next;
			}
		}*/
		p1 = readline("prompt: ");
		if (p1 && p1[0] == 0)
		{
			free(p1);
			p1 = NULL;
		//	p1 = readline("re_propmt: ");
		}
		else if (!p1)
		{
			printf("exit\n");
			free_history(&his);
			free(p1);
			exit(1);
		}
		else if (!ft_strcmp("echo", p1, 4))
		{
			s = ft_strchr(p1, 'o');
			if (!s[1])
				printf("\n");
			else if (s[1] == ' ')
				printf("%s\n", &s[2]);
			else
				printf("%s: command not found\n", p1);
		}
		else
			printf("%s: command not found\n", p1);
//		if (p1)
//			save_to_history(&his, p1);
		if (p1 && p1[0] != 0)
			add_history(p1);
		free(p1);
	}
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
