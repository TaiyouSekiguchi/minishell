#include "minishell.h"

static void	del_last_elem(t_list **pptr)
{
	int		len;
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *pptr;
	len = ms_lstsize(*pptr);
	if (len == 0)
		return ;
	else if (len == 1)
	{
		free((*pptr)->content);
		free(*pptr);
		return ;
	}
	else if (len == 2)
		tmp2 = tmp->next;
	else
	{
		while (tmp->next->next)
			tmp = tmp->next;
		tmp2 = tmp->next;
	}
	tmp->next = NULL;
	free(tmp2->content);
	free(tmp2);
}

static char	*lst_to_string(t_list *list, char *c)
{
	char	*str;

	if (list == NULL)
		return (NULL);
	str = ms_strappend(ms_strdup(c), ms_strdup((char *)list->content));
	list = list->next;
	while (list != NULL)
	{
		str = ms_strappend(str, ms_strdup(c));
		str = ms_strappend(str, ms_strdup((char *)list->content));
		list = list->next;
	}
	ms_lstclear(&list, free);
	return (str);
}

char	*rewrite_absolute_path(t_list *dir_lst, char *input_path)
{
	char	*tmp;
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
			tmp = ms_strdup(current->content);
			if (ms_lstsize(new_dir_lst) == 0)
				new_dir_lst = ms_lstnew(tmp);
			else
				ms_lstadd_back(&new_dir_lst, ms_lstnew(tmp));
		}
		current = current->next;
	}
	ms_lstclear(&dir_lst, free);
	return (lst_to_string(new_dir_lst, "/"));
}

char	*rewrite_relative_path(t_list *dir_lst, char *pwd)
{
	char	*tmp;
	t_list	*new_pwd_lst;
	t_list	*current;

	new_pwd_lst = split_lst(pwd, '/');
	current = dir_lst;
	while (current != NULL)
	{
		if (ms_strcmp(current->content, "..") == 0)
			del_last_elem(&new_pwd_lst);
		else if (ms_strcmp(current->content, ".") != 0)
		{
			tmp = ms_strdup(current->content);
			ms_lstadd_back(&new_pwd_lst, ms_lstnew(tmp));
		}
		current = current->next;
	}
	ms_lstclear(&dir_lst, free);
	return (lst_to_string(new_pwd_lst, "/"));
}
