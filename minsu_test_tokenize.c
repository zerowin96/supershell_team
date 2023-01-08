#include "test.h"

void env_expansion(t_list *list, char **envp);
char	*ft_strjoin2(const char *replace, const char *source, int start, int finish);
		//tokens i need to handle :
		// " ' < << > >> | commands options
		// quotes, redirections, pipe, commands and options
			// -1: 따옴표부터 묶어서 특수문자(< 등) 들어와도 그냥 글자로 인식하도록
				// shell이 quote 안의 metacharacters를 글자로만 인식해야 함
				// 쌍따옴표는 환경변수 확장이 이루어지도록 해야 함 -> 따옴표로 묶고 파싱 후 풀어버리면 안됨.
			// 0 : 재지정 표시
			// 1 : 커맨드 구분할 파이프
			// 2 : 커맨드랑 옵션으로 나누기! 그럼 끝인가
			// 3 : 
		// 열린 따옴표나 세미콜론, 백슬래시는 해석하지 않는다.

		//bonus :
		// && || * ()
		// env expansion will be done after tokenization;

// typedef struct s_parse_list
// {
// 	char				*content;
// 	struct s_parse_list	next;
// 	int					status; //(is_separator);
// };


// int is_order(char c)
// {
// 	if (c == '>' || c == '<' || c == '|')
// 		return (0);
// 	return (1);
// }

int	is_ifs(int c)
{
	return ((c == ' ' || c =='n' || c == '\t'));
}

static int is_separator(char *string)
{
	int	index = 0;
	// t_cnt *pipe;
	// char *tokens[] = {'\'', '\"', '<', '>', '|'};

	if (string[index] == '\'')
	{
		index++;
		while (string[index] != '\'' && string[index])
			index++;
		index++;
	}
	else if (string[index] == '\"')
	{
		index++;
		while (string[index] != '\"' && string[index])
			index++;
		index++;
	}
	else if (string[index] == '>')
	{
		index++;
		if (string[index] == '>')
			index++;

	}
	else if (string[index] == '<')
	{
		index++;
		if (string[index] == '<')
			index++;
	}
	else if (string[index] == '|')
	{
		// pipe->pipe_cnt++;
		return (1);
	}
	else
		return (0);
	return (index);
}


void	partial_string(t_list *list, char *string, int start, int finish)
{
	char *temp;

	printf("partial string : %d~%d", start, finish);
	temp = (char *)ft_calloc(finish - start + 2, sizeof(char));
	ft_memmove(temp, &string[start], finish - start + 1);
	printf("  ....%s....\n", temp);
	ft_lstadd_back(&list, ft_lstnew(temp));
}

void	tokenize(t_list *list, char *string)
{
	// char	*tokens[] = {"\"", "\'", "<", "<<", ">", ">>", "|", " "};
	int		start = 0;
	int		finish = 0;
	int		index = 0;
	// t_list	*list = 0;
	// int		count = 0;
	//useful function : isalpha, iswhite, isdigit, 
	//ft_lstadd_back(&list, ft_lstnew(string));

	// count = 0;
	// index = 0;
	//count how many quotes in it.

	index = 0;
	while (string[index])
	{
		while (string[index] >= 9 && string[index] <= 13)
			index++;
		if (is_separator(&string[index]))
		{
			start = index;
			index += (is_separator(&string[index]) - 1);
			finish = index;
			partial_string(list, string, start, finish);
		}
		else if (string[index] && string[index] != ' ' && string[index] == '$')
		{
			start = index;
			while (string[index] != ' ' && string[index] && \
			is_separator(&string[index]) == 0)
			{
				index++;
				if (string[index] == '$')
					break ;
			}
			finish = index - 1;
			partial_string(list, string, start, finish);
			index--;
		}
		else if (string[index] && string[index] != ' ')
		{
			start = index;
			while (string[index] != ' ' && string[index] && \
			is_separator(&string[index]) == 0 && string[index] != '$')
				index++;
			finish = index - 1;
			partial_string(list, string, start, finish);
			index--;
		}
		if (string[index] == 0)
			break ;
		index++;
	}
}

t_list *parsing(char *line, char **envp)
{
	//char *string = "	'cat -e'"|	 ls -al | while || <<< >> ls ls ls lslsls ><\" \"||$123|\'\'//..,,>>><<<\"\" ppplll>>>lllsss$USERpsdl$user | >>>$hello";
	// char *string = "ppplll\'>>>\'lllsss";
	t_list *list;
	t_list *now;

	list = ft_lstnew(0);
	tokenize(list, line);


	env_expansion(list, envp);


	now = list->next;
	while (now)
	{
		printf("%s\n", now->content);
		now = now->next;
	}
	printf("tokens are stored in linked list\n");
	return (list);
}

// int main(void)
// {
// 	char *string = "	$HElloWorld123 $* $& $?$           $";
// 	parsing(string);
// }

// static void	get_section(char *string, int *index, int *start, int *finish)
// {
// 	while (string[*index] == ' ')
// 		(*index)++;
// 	if (string[*index] == 0)
// 		return ;
// 	if (string[*index] == '\'')
// 	{
// 		*start = ++(*index);
// 		while (string[*index] != '\'' && string[*index])
// 			(*index)++;
// 		*finish = (*index)++;
// 	}
// 	else if (string[*index] && string[*index] != ' ')
// 	{
// 		*start = *index;
// 		while (string[*index] != ' ' && \
// 		string[*index] && string[*index] != '\'')
// 			(*index)++;
// 		*finish = *index;
// 	}
// }

// static char	**ft_linkedlist_to_split(t_list *list)
// {
// 	char	**help2;
// 	int		index;
// 	t_list	*temp;

// 	help2 = (char **)ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
// 	index = 0;
// 	temp = list;
// 	while (list)
// 	{
// 		temp = list->next;
// 		help2[index++] = (char *)(list->content);
// 		free(list);
// 		list = temp;
// 	}
// 	return (help2);
// }

// static char	**pipex_split_quote_parse(t_list *list, char *string)
// {
// 	int		index;
// 	int		start;
// 	int		finish;
// 	char	*help;

// 	index = 0;
// 	start = 0;
// 	finish = 0;
// 	help = 0;
// 	while (string[index])
// 	{
// 		get_section(string, &index, &start, &finish);
// 		help = (char *)ft_calloc(finish - start + 1, sizeof(char));
// 		ft_memmove(help, &string[start], finish - start);
// 		ft_lstadd_back(&list, ft_lstnew(help));
// 		if (string[index] == 0)
// 			break ;
// 	}
// 	return (ft_linkedlist_to_split(list));
// }

// char	**pipex_split_quote(char *command)
// {
// 	t_list	*list;
// 	int		index;
// 	int		count;
// 	char	**res;

// 	list = 0;
// 	index = 0;
// 	count = 0;
// 	// while (command[index])
// 	// 	if (command[index++] == '\'')
// 	// 		count++;
// 	// if (count % 2 != 0)
// 	// {
// 	// 	ft_putstr_fd("Invalid option (quote)\n", 2);
// 	// 	exit (1);
// 	// }
// 	// FIND UNCLOSED QUOTE
// 	res = pipex_split_quote_parse(list, command);
// 	return (res);
// }

// char *search_on_env()



void env_expansion(t_list *list, char **envp)
{
	char	*string;
	t_list	*cursor;
	int		index;
	int		start;
	int		finish;
	// char	*temp_string;
	// int		i;

	char 	*temp;	// 저장 : envp에서 검색해 올 메모리 저장
	char	*temp2; // 저장 : envp에서 검색된 key
	char	*temp3;
	// t_list *prev = list;
	cursor = list->next;

	// t_list	*now;
	
	while (cursor)
	{
		printf("CURSOR WHILE LOOP\n");
		//test

		//PRINT ALL THE LIST
		// now = list->next;
		// while (now)
		// {
		// 	printf("1                   ||%p\n", now);
		// 	printf("1                   ||%p\n", now->content);
		// 	printf("1                   ||%s\n", now->content);
		// 	now = now->next;
		// }
		//test done
		index = 0;
		string = cursor->content;
		if (string && *string && (*string != '\'' && *string != '>' && *string != '|' && *string != '<'))
		{
			// printf("IF STRING\n");
			while (string[index])
			{
				// printf("WHILE STRING[INDEX]\n");
				// printf("searching : %d\n", index);
				while (string[index] != '$' && string[index])
					index++;
				if (string[index] == '$')
				{
					start = ++index;
					// while (string[index] && string[index] != '$' && string[index] != '\'' && string[index] != '>' && string[index] != ' ' && string[index] != '<' && is_ifs(string[index]) == 0)
					// 	index++; 
					// is_alpha 와 is_digit으로 교체
					while (ft_isalpha(string[index]) || ft_isdigit(string[index]))
						index++;
					finish = index - 1;









					temp = (char *)ft_calloc(finish - start + 3, sizeof(char));	// USER : 4글자, index 3차이. : fin-stt + 1 + 1(=) + 1(NULL)
					ft_memmove(temp, &string[start], finish - start + 1);		// fin-stt + 1 글자만큼 검색할 문자열 temp에 넣기
					temp[finish - start + 1] = '=';
					// printf("finding : %s from %d to %d\n", temp, start, finish);
					printf("finding : %s\n", temp);

					temp2 = 0;
					int i = 0;
					while(envp[i])
					{
						if (ft_strncmp(envp[i], temp, ft_strlen(temp)) == 0)
						{
							temp2 = &(envp[i][ft_strlen(temp)]); // envp안에 temp와 같은 key가 있는 경우 value값의 주소를 가져옴
							break ;
						}
						i++;
					}
					free(temp);
					printf("its key : %s\n", temp2);
					// if (envp[i] == 0)
					// 	temp2 = 0;
					// if (envp[i] == 0)
					// 이 때는 그냥 공백도 아니고 그 부분 비워버려야 함
					
					// cursor -> content = ft_strjoin(ads, temp2, start, finish);

					// printf("2. cursor->content : %p\n", cursor->content);
					temp3 = ft_strjoin2(temp2, string, start, finish);
					// printf("3. cursor->content : %p\n", cursor->content);
					// cursor->content = string;
					// if (string)
					// 	free(string);
					free(string);
					string = temp3;
					cursor->content = temp3;
					temp2 = 0; //not allocated
					// printf("4. cursor->content : %p\n", cursor->content);
					// printf("replaced : ...%s...\n", temp3);

					index = (start - 1) + ft_strlen(temp2);
					// printf("next index : %d\n", index);
					// printf("string : %p\n", string);
					
					// string = 0;

					// printf("temp : %p\n", temp);
					
					// temp = 0;
					// free(temp2);
					// printf("temp : %p\n", temp);
					// free(string);
					// string = temp3;
					// cursor->content = temp3;


					// if (cursor->content == 0 || ((char *)cursor->content)[0] == 0)
					// {
					// 	prev->next = cursor->next;
					// 	if (cursor->content)
					// 		free(cursor->content);
					// 	free(cursor);
					// 	cursor = 0;
					// 	cursor = prev->next;
					// }
					// free(cursor->content);
					// free(temp);

					// printf("one env replaced : now string is ::%s\n", cursor->content);
					// 이제 ENVP에서 찾고 value값 주소 받아오기 (ENVP에서 key의 첫 '='값 다음부터 그 key의 value임)
					// 지금 들고 있는 위치는 : 1. token   2. expand[start]   3. expand[finish]   4. key의 value   5. 
					// 새로운 string에 붙여야 하는 부분 : 
						// (expand[start]은 $USER 의 $, expand[finish]는 $USER의 R부분을 가리킴)
						// token[0] ~ token[start - 1] (== expand[0]의 전부분)
						// value
						// token[finish + 1] == (expand[last]의 다음부분) ~ token[last]
					// 나머지 전부 free하고 cursor->content 를 새로운 token으로 교체
					// 이후 처음부터 다시 확장? 이거는 확인해보자
					// 확장된 다음 부분부터 확장 시작 : 다음 시작 부분은 token[start - 1]의 index + expand[last]의 index(value의 길이) 
					// == start + ft_strlen(value); 부터 시작하면 될 것
					//
					// index = 
				}
				// PRINT ALL THE LIST
				// now = list->next;
				// while (now)
				// {
				// 	printf("                    ||%p\n", now);
				// 	printf("                    ||%p\n", now->content);
				// 	printf("                    ||%s\n", now->content);
				// 	now = now->next;
				// }
				// else
				// 	index++;
			}
			// printf("while ended\n");
		}
		// printf("cursor moves\n");
		// cursor = prev->next->next;
		if (cursor)
			cursor = cursor->next;
		// else
		// 	break;
		// prev = prev->next;
		// printf("cursor moves done\n");
	}
	// printf("CURSOR WHILE DONE\n");
	// perror("");





	//content가 비어있거나 content[0] = NULL인 list의 node를 삭제하며 다시 연결하기
	cursor = list->next;
	t_list	*prev = list;
	while (cursor)
	{
		if (cursor->content == 0 || *((char *)(cursor->content)) == 0)
		{// prev = cursor->next;
			prev->next = cursor->next;
			if (cursor->content)
				free(cursor->content);
			free(cursor);
			cursor = prev->next;
		}
		cursor = cursor->next;
		prev = prev->next;
	}
}


char	*ft_strjoin2(const char *replace, const char *source, int start, int finish)
{

	char temp[1];

	temp[0] = 0;
	if (!replace)
		replace = temp;

	int		len;
	char	*ret_str;

	// printf("strjoin input : ||%s|| ||%s|| %d %d\n", replace, source, start, finish);
	
	len = (ft_strlen(source) - 1) + ( -finish + start - 1 ) + ft_strlen(replace) + 1;
	ret_str = (char *)ft_calloc(len, sizeof(char));
	// ret_str = (char *)malloc(len * sizeof(char));
	// ft_bzero(ret_str, len);

	// printf("replace : %p\n", replace);
	// printf("source  : %p\n", source);
	// printf("start   : %d\n", start);
	// printf("finish  : %d\n", finish);
	// printf("len     : %d\n", len);
	// printf("ret_str : %p\n", ret_str);
	// printf("string length = %d\n", len);

	ft_memmove(ret_str, source, start - 1);
	// printf("phase1 : %s || start - 1 : %d\n", ret_str, start - 1);


	if (replace)
		ft_memmove(&ret_str[start - 1], replace, ft_strlen(replace));
	// printf("phase2 : %s || strlen : %zu\n", ret_str, ft_strlen(replace));
	ft_memmove(&ret_str[ft_strlen(ret_str)], &source[finish + 1], ft_strlen(&source[finish + 1]));
	// printf("phase3 : %s || finish + 1 : %d || strlen : %lu\n", ret_str, finish + 1, ft_strlen(&source[finish + 1]));
	// printf("strjoin2 : %s\n", ret_str);
	// for (int i = 0; i < len; i++)
	// {
	// 	printf("%c", ret_str[i]);
	// 	if (ret_str[i] == 0)
	// 		printf(".");
	// }
	// printf("||\n");
	return (ret_str);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char *string = "\"  aa$USERauqe$USER$USER$USER\"$USER\' $USER\' $USERAU close$USER";
// 	parsing(string, envp);
// 	system("leaks a.out | grep leak");
// 	// perror("");
// 	argc = 0;
// 	argv = &argv[0];
// }