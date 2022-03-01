
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

char	*set_input_path(int argc, char **argv)
{
	if (argc == 1 || argv[1][0] == '~')
	{
		if (getenv("HOME") == NULL)
		{
			ms_putendl_fd("minishell:HOME not set", STDERR);
			return (NULL);
		}
		else if (argc == 1 || ms_strlen(argv[1]) == 1)
			return (ms_strdup(getenv("HOME")));
		else
			return (ms_strjoin(getenv("HOME"), argv[1] + 1));
	}
	else
		return(argv[1]);
}

t_list	*split_lst(char *str, char c)
{
	t_list	*lst;
	char	**dir_pptr;
	int		i;

	dir_pptr = ms_split(str, c);
	if (dir_pptr[0] == NULL)
		return (NULL);
	lst = ms_lstnew(dir_pptr[0]);
	i = 1;
	while (dir_pptr[i] != NULL)
	{
		ms_lstadd_back(&lst, ms_lstnew(dir_pptr[i]));
		i++;
	}
	return (lst);
}

char	*lst_to_string(t_list *list)
{
	char	*str;

	str = NULL;
	while (list != NULL)
	{
		if (str == NULL)
			str = ms_strdup(ms_strjoin("/", (char *)list->content));
		else
			str = ms_strjoin(str, ms_strjoin("/", (char *)list->content));
		list = list->next;
	}
	return (str);
}

char	*rewrite_absolute_path(t_list *dir_lst, char *input_path)
{
	char	*new_path;
	t_list	*new_dir_lst;

	new_dir_lst = NULL;
	if (dir_lst == NULL)
		return (input_path);
	while (dir_lst != NULL)
	{
		if (ms_strcmp((char *)dir_lst->content, "..") == 0)
			del_last_elem(&new_dir_lst);
		else if (ms_strcmp((char *)dir_lst->content, ".") != 0)
		{
			if (ms_lstsize(new_dir_lst) == 0)
				new_dir_lst = ms_lstnew(dir_lst->content);
			else
				ms_lstadd_back(&new_dir_lst, ms_lstnew(dir_lst->content));
		}
		dir_lst = dir_lst->next;
	}
	new_path = lst_to_string(new_dir_lst);
	ms_lstclear(&new_dir_lst, free);
	return (new_path);
}

char	*rewrite_relative_path(t_list *dir_lst, char *pwd)
{
	char	*new_path;
	t_list	*new_pwd_lst;

	new_pwd_lst = split_lst(pwd, '/');
	while (dir_lst != NULL)
	{
		if (ms_strcmp(dir_lst->content, "..") == 0)
			del_last_elem(&new_pwd_lst);
		else if (ms_strcmp(dir_lst->content, ".") != 0)
			ms_lstadd_back(&new_pwd_lst, ms_lstnew(dir_lst->content));
		dir_lst = dir_lst->next;
	}
	new_path = lst_to_string(new_pwd_lst);
	ms_lstclear(&new_pwd_lst, free);
	return (new_path);
}

int	builtin_cd(int argc, char *argv[], t_dir *d_info)
{
	t_list		*dir_lst;
	char		*input_path;
	char		*new_pwd;

	input_path = set_input_path(argc, argv);
	dprintf(STDERR, "input_path=%s\n", input_path);
	if (input_path == NULL)
		return (EXIT_FAILURE);
	else
	{
		dir_lst = split_lst(input_path, '/');
		if (input_path[0] == '/')
			new_pwd = ms_strdup(rewrite_absolute_path(dir_lst, input_path));
		else
			new_pwd = ms_strdup(rewrite_relative_path(dir_lst, d_info->pwd));
		if (chdir(new_pwd) < 0)
			perror("minishell");
		else
		{
			if (d_info->old_pwd != NULL)
				free(d_info->old_pwd);
			d_info->old_pwd = ms_strdup(d_info->pwd);
			free(d_info->pwd);
			d_info->pwd = ms_strdup(new_pwd);
			call_export("PWD", d_info->pwd);
			call_export("OLDPWD", d_info->old_pwd);
		}
		free(new_pwd);
	}
	return (0);
}
