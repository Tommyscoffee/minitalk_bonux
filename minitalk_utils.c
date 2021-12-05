#include "includes/minitalk.h"
#include <stdio.h>


void	ft_bzero(void *s, size_t n)//memsetでもできる。
{
	size_t	i;
	char	*s_chr_p;

	i = 0;
	s_chr_p = (char *)s;
	while (i < n)
	{
		*(s_chr_p + i) = 0;
		i++;
	}
}

void	success(int sig)
{
	(void)sig;
	write(1,"Data has been received.\n", 25);
}

