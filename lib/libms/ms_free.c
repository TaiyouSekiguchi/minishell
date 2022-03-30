#include "libms.h"

void	ms_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
