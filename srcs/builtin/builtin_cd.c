
#include "minishell.h"

void	del_last_elem(t_list **pptr)
{
	int		len;
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *pptr;
	len = ms_lstsize(*pptr);
	if (len == 1)
	{
		free((*pptr)->content);
		free(*pptr);
	}
	else if (len == 2)
	{
		tmp2 = tmp->next;
		tmp->next = NULL;
		free(tmp2->content);
		free(tmp2);
	}
	else if (len > 2)
	{
		while (tmp->next->next)
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = NULL;
		free(tmp2->content);
		free(tmp2);
	}
}

static char	*set_input_path(int argc, char **argv, char **my_env)
{
	char	*value;

	if (argc == 1 || argv[1][0] == '~')
	{
		value = ms_getenv(my_env, "HOME");
		if (value == NULL)
		{
			ms_putendl_fd("minishell: cd: HOME not set", STDERR);
			return (NULL);
		}
		else if (argc == 1 || ms_strlen(argv[1]) == 1)
			return (value);
		else
			return (ms_strjoin(value, argv[1] + 1));
	}
	else
		return(argv[1]);
}

t_list	*split_lst(char *str, char c)
{
	t_list	*lst;
	char	**dir_pptr;
	int		i;
	char	*tmp;

	dir_pptr = ms_split(str, c);
	if (dir_pptr[0] == NULL)
		return (NULL);
	tmp = ms_strdup(dir_pptr[0]);
	lst = ms_lstnew(tmp);
	i = 1;
	while (dir_pptr[i] != NULL)
	{
		tmp = ms_strdup(dir_pptr[i]);
		ms_lstadd_back(&lst, ms_lstnew(tmp));
		i++;
	}
	ms_split_free(dir_pptr);
	return (lst);
}

char	*lst_to_string(t_list *list, char *c)
{
	char	*str;
	char	*tmp;

	if (list == NULL)
		return (NULL);
	//str = NULL;
	tmp = ms_strjoin(c, (char *)list->content);
	str = ms_strdup(tmp);
	free(tmp);
	list = list->next;
	while (list != NULL)
	{
		tmp = ms_strjoin(c, (char *)list->content);
		str = ms_strappend(str, tmp);

		/*if (str == NULL)
			str = ms_strdup(tmp);
		else
			str = ms_strjoin(str, tmp);*/

		list = list->next;
	}
	return (str);
}

static char	*rewrite_absolute_path(t_list *dir_lst, char *input_path)
{
	char	*new_path;
	t_list	*new_dir_lst;
	t_list	*current;

	new_dir_lst = NULL;
	if (dir_lst == NULL)
		return (input_path);

	current = dir_lst;
	while (current != NULL)
	{
		if (ms_strcmp((char *)current->content, "..") == 0)
			del_last_elem(&new_dir_lst);
		else if (ms_strcmp((char *)current->content, ".") != 0)
		{
			if (ms_lstsize(new_dir_lst) == 0)
				new_dir_lst = ms_lstnew(ms_strdup(current->content));
			else
				ms_lstadd_back(&new_dir_lst, ms_lstnew(ms_strdup(current->content)));
		}
		current = current->next;
	}
	new_path = lst_to_string(new_dir_lst, "/");
	ms_lstclear(&dir_lst, free);
	ms_lstclear(&new_dir_lst, free);
	return (new_path);
}

static char	*rewrite_relative_path(t_list *dir_lst, char *pwd)
{
	char	*new_path;
	t_list	*new_pwd_lst;
	t_list	*current;

	new_pwd_lst = split_lst(pwd, '/');
	current = dir_lst;
	while (current != NULL)
	{
		if (ms_strcmp(current->content, "..") == 0)
			del_last_elem(&new_pwd_lst);
		else if (ms_strcmp(current->content, ".") != 0)
			ms_lstadd_back(&new_pwd_lst, ms_lstnew(ms_strdup(current->content)));
		current = current->next;
	}
	new_path = lst_to_string(new_pwd_lst, "/");
	ms_lstclear(&dir_lst, free);
	ms_lstclear(&new_pwd_lst, free);
	return (new_path);
}

int	builtin_cd(int argc, char *argv[], t_dir *d_info)
{
	t_list		*dir_lst;
	char		*input_path;
	char		*new_pwd;

	input_path = set_input_path(argc, argv, d_info->my_env);
	if (input_path == NULL)
		return (EXIT_FAILURE);
	else
	{
		dir_lst = split_lst(input_path, '/');
		if (input_path[0] == '/')
			new_pwd = rewrite_absolute_path(dir_lst, input_path);
		else
			new_pwd = rewrite_relative_path(dir_lst, d_info->pwd);
		if (chdir(new_pwd) < 0)
		{
			perror("minishell: cd");
			free(new_pwd);
			return (EXIT_FAILURE);
		}
		else
		{
			if (d_info->old_pwd != NULL)
				free(d_info->old_pwd);
			d_info->old_pwd = ms_strdup(d_info->pwd);
			free(d_info->pwd);
			d_info->pwd = ms_strdup(new_pwd);
			call_export("PWD", d_info->pwd, &d_info->my_env);
			call_export("OLDPWD", d_info->old_pwd, &d_info->my_env);
		}
		free(new_pwd);
	}
	return (EXIT_SUCCESS);
}
