#include "minishell.h"

void	call_export(char *env_name, char *value, char ***my_env)
{
	char	**argv;
	char	*tmp;

	argv = malloc(sizeof(char *) * 3);
	tmp = ms_strjoin(env_name, "=");
	argv[0] = ms_strdup("export");
	argv[1] = ms_strjoin(tmp, value);
	argv[2] = NULL;
	builtin_export(2, argv, my_env);
	ms_split_free(argv);
	free(tmp);
}
