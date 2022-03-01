#include "minishell.h"

void	call_export(char *env_name, char *value)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = ms_strdup("export");
	argv[1] = ms_strjoin(ms_strjoin(env_name, "="), value);
	argv[2] = NULL;
	builtin_export(2, argv);
	ms_split_free(argv);
}
