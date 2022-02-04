/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:19:34 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/02/04 17:06:54 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_name(char c)
{
	if (ms_isdigit(c) || ms_isalpha(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

static char	*get_val_name(char *token)
{
	char	*val_name;
	int		i;

	i = 1;
	while (token[i] != '\0' && is_name(token[i]))
		i++;
	val_name = ms_strndup(token, i);
	return (val_name);
}

void	expand(char **token)
{
	char	*val_name;
	char	*new_word;
	char	*ret;
	char	*tmp;
	int		start;
	int		i;
	t_quote	quote;

	quote = NONE;
	start = 0;
	i = 0;
	ret = ms_strdup("");
	while ((*token)[i] != '\0')
	{
		if (is_quote((*token)[i]))
			quote_set((*token)[i++], &quote);
		else if (quote == SINGLE || (*token)[i] != '$')
			i++;
		else
		{
			//＄より前をtmpにいれる。
			tmp = ms_substr(*token, start, i - start);
			//printf("tmp is %s\n", tmp);

			//上で作ったtmpを, retにくっつける。
			ret = ms_strappend(ret, tmp);
			//printf("ret is %s\n", ret);

			//tokenにある$後の変数名を取得
			val_name = get_val_name(&(*token)[i]);
			//printf("val_name is %s\n", val_name);

			//変数名から環境変数にある右辺を取得する
			new_word = search_environ(val_name);
			//printf("new_word is %s\n", new_word);

			//取得した右辺の値をretにくっつける（展開）
			ret = ms_strappend(ret, new_word);
			//printf("ret is %s\n", ret);

			//tokenのインデックスを変数名の大きさだけ進める
			i++;
			while ((*token)[i] != '\0' && is_name((*token)[i]))
				i++;
			start = i;
		}
	}

	tmp = ms_substr(*token, start, i);
	//printf("tmp is %s\n", tmp);

	ret = ms_strappend(ret, tmp);
	//printf("ret is %s\n", ret);

	free(*token);
	*token = ret;
}
