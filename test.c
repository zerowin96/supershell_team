
#include "test.h"

static int	sep_kind(t_list *node)
{
	if (ft_strncmp(node->content, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(node->content, "<<", 3) == 0)
		return (2);
	else if (ft_strncmp(node->content, ">", 2) == 0)
		return (3);
	else if (ft_strncmp(node->content, ">>", 3) == 0)
		return (4);
	else if (ft_strncmp(node->content, "|", 2) == 0)
		return (5);
	return (0);
}

static int	builtin_check(char *line, t_list *node, t_copy *e)
{
	char *string = (char *)(node->content);

	if (ft_strncmp(string, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(string, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(string, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(string, "export", 7) == 0)
	{
		ft_export(line, node, e);
		return (4);
	}
	else if (ft_strncmp(string, "unset", 6) == 0)
	{
		ft_unset((char *)node->next->content, e);
		return (5);
	}
	else if (ft_strncmp(string, "env", 4) == 0)
	{
		ft_env(e);
		return (6);
	}
	else if (ft_strncmp(string, "exit", 5) == 0)
		return (7);
	return (0);
}

char *reading(void)
{
	char *line;
	line = 0;

	line = readline("./minishell >$");
	if (line && *line)
		add_history(line);
	return (line);
}

void exec(t_list *list, char *line, t_copy *e);


int main(int argc, char **argv, char **envp)
{

	char *line;
	t_list *list;
	t_copy env;

	line = 0;
	list = NULL;
	env.cp_envp = envp;

	while (1)
	{
		line = reading();
		list = parsing(line, envp);
		exec(list, line, &env);

	}
	argc = 0;
	argv = 0;
	envp = 0;
}

void	exec(t_list* list, char *line, t_copy *e)
{
	t_list *now;
	int flag;

	flag = 0;
	now = list->next;
	printf("exec\n");

	t_list *temp1;
	t_list *head;
	t_list *last;
	int temp_no;
	int	cmd_sign;

	last = 0;
	head = list->next;
	temp1 = head;
	while (temp1)
	{
		printf("%s ", (char *)(temp1->content));
		temp1 = temp1->next;
	}
	printf("\n");

	while (1)
	{
		temp_no = 0;
		cmd_sign = 0;
		temp1 = head;
		while (temp1)
		{
			if (temp1->content && ((char *)(temp1->content))[0] == '|')
			{
				temp_no = 1;
				last = temp1->next;
				break;
			}
			temp1 = temp1->next;
		}
		temp1 = head;
		while (temp1 && ((char *)(temp1->content))[0] != '|')
		{
			printf("%s ", temp1->content);
			temp1 = temp1->next;
		}
		printf("\n");
		temp1 = head;

		while (temp1 && ((char *)(temp1->content))[0] != '|')
		{
			if (sep_kind(temp1) && !(temp1->next))
			{
				printf("invalid syntax\n");
				break;
			}
			if (sep_kind(temp1) && sep_kind(temp1->next))
			{
				printf("syntax error near unexpected token '%s'\n", (char *)(temp1->next->content));
				break ;
			}
			if (sep_kind(temp1) == 1)
			{
				printf("infile : %s\n", (char *)(temp1->next->content));
			}
			else if (sep_kind(temp1) == 2)
			{
				printf("here_doc limiter : %s\n", (char *)(temp1->next->content));
			}
			else if (sep_kind(temp1) == 3)
			{
				printf("outfile : %s\n", (char *)(temp1->next->content));
			}
			else if (sep_kind(temp1) == 4)
			{
				printf("outfile_append : %s\n", (char *)(temp1->next->content));
			}
			else
			{
				// printf("command part : %s", (char *)(temp1->content))
				if (cmd_sign == 0)
				{
					if (flag == builtin_check(line, temp1, e))
					{
						printf("builtin : %s\n", (char *)(temp1->content));
					}
					else
						printf("command : %s\n", (char *)(temp1->content));
					cmd_sign = 1;
				}
				else
					printf("option : %s\n", (char *)(temp1->content));
				temp1 = temp1->next;
				continue;
			}
			temp1 = temp1->next->next;
		}
		printf("\n");

		if (temp1)
			head = last;
		else
			break;
	}


}
