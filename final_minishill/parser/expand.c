/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:26:52 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/24 20:54:33 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*build_result(char *input, char *varname, int var_len)
{
	char	*env;
	t_shell *ptr;
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*result;

	ptr = NULL;
	// if(strcmp("?",varname) == 0)
	// {
	// 	env = ft_itoa(ptr->last_exit_status);
		
	// 	printf("%d\n",ptr->last_exit_status);
	// 	return env;
	// }
	env = getenv(varname);
	prefix = ft_substr(input, 0, ft_strchr(input, '$') - input);
	suffix = ft_strdup(ft_strchr(input, '$') + var_len + 1);
	if (env)
		tmp = ft_strjoin(prefix, env);
	else
		tmp = ft_strjoin(prefix, "");
	result = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(tmp);
	return (result);
}

char	*expand_variables(char *input)
{
	int		i;
	char	*pos;
	char	*key;
	char	*varname;
	char	*result;

	if (!input || !ft_strchr(input, '$'))
		return (ft_strdup(input));
	pos = ft_strchr(input, '$');
	key = pos + 1;
	if (*key == '\0')
		return (ft_strdup(input));
	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	varname = ft_substr(key, 0, i);
	if(!varname[i])
	result = build_result(input, varname, i);
	return (result);
}

void	count_dollar(t_pars *pars)
{
	pars->numdollar = 0;
	pars->i = 0;
	while (pars->content[pars->i])
	{
		if (pars->content[pars->i] == '$')
			pars->numdollar++;
		pars->i++;
	}
	pars->i = 0;
}
