// #include "main.h"

// int	main(int argc, char **argv, char **envp)
// {


// 	int	fd[2][2];
// 	t_list *list;
// 	list = 0;
// 	fd[0][0] = 0;
// 	fd[0][1] = 0;
// 	fd[1][0] = 0;
// 	fd[0][1] = 0;

// 	while (1)
// 	{
// 		char **command = 0;
// 		char	*string = 0;
// 		char *line = readline("in : ");
// 		if (line == 0 || *line == 0)
// 		{
// 			free(line);
// 			continue;
// 		}
// 		list = ft_lstnew(0);
// 		tokenize(list, line);
// 		list_print("after tokenizing", list);


// 		command_split(list->next, fd, &command, &string);
// 		vector_print("after spliting", command);
// 		free_list(list);
// 		list = vector_to_list(&command);
// 		// vector_free(command);
// 		ft_lstadd_front(&list, ft_lstnew(0));
// 		list_print("after spliting", list);


// 		qmark_expansion(list, 0);
// 		env_expansion(list, envp);
// 		// printf("after expansion\n");
// 		list_print("after expansion", list);



// 		list_whitespace_split(list);
// 		// printf();
// 		list_print("after whitespace split", list);


// 		// quote_trim(list);
// 		// printf("after trimming quote\n");



// 		quote_trim(list);
// 		list_print("after trimming quote", list);








// 		printf("string : %s$\n", string);
// 		free(string);
// 		// free(string);
// 		// // string = listjoin(list);
// 		// t_list *temp_listjoin;
// 		// temp_listjoin = list;
// 		// char	*temp_string = (char *)ft_calloc(1, sizeof(char));
// 		// char	*temp_string1;
// 		// while (temp_listjoin)
// 		// {
// 		// 	temp_string1 = string_connect(temp_string, temp_listjoin->content);
// 		// 	// free(temp_string);
// 		// 	temp_string = temp_string1;
// 		// 	temp_listjoin = temp_listjoin->next;
// 		// }
// 		// string = temp_string;
// 		// printf("listjoin : %s$\n", string);
// 		// free_list(list);
// 		// list = ft_lstnew(0);
// 		// tokenize(list, string);
// 		// list_print("retokenized", list);
// 		list_tie(list);
// 		list_print("tied", list);
// 		free_space(list);
// 		free_empty(list);
// 		list_print("space and empty has freed", list);
// 		// vector_print("after spliting", command);
// 		// vector_free(command);
// 		command = list_to_vector(list);
// 		vector_print("after all", command);


// 		free(line);
// 		free_list(list);
// 		vector_free(command);
// 		// free(string);
// 	}
// }

// gcc -g3 telib -I${HOME}/.brew/opt/readline/include parsing/*.c exec/*.c builtin/*.cst.c -lreadline etc/*.c libft/libft.a -L${HOME}/.brew/opt/readline/
// gcc -g3 -lreadline etc/*.c libft/libft.a -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include parsing/*.c exec/*.c builtin/*.c test_func.c test.c





// gcc -g3 -lreadline etc/*.c libft/libft.a -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include parsing/*.c exec/*.c builtin/*.c test_func.c main/*
// for MAIN TEST


    //   ' ec"ho" "123"$USER"$USER"'$USER'456 '