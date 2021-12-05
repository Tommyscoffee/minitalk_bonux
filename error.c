
#include "libft.h"

void	error(char *error_message)
{
	char	*tmp;

	tmp = error_message;
	while (*error_message)
	{
		error_message++;
	}
	write(2, tmp, error_message - tmp);
	exit(1);
}
