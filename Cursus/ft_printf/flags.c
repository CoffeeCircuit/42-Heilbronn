
// #include "ft_printf.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

#define VALID_CS (1 << 14)
#define VALID_U (1 << 14) | (1 << 17)
#define VALID_P (1 << 14)
#define VALID_H (1 << 4) | (1 << 14) | (1 << 17)
#define VALID_DI (1 << 1) | (1 << 12) | (1 << 14) | (1 << 17)

typedef struct s_format
{
	char	flags[6];
	char	isvalid;
	char	spec;
}			t_format;

int	ft_flag(t_format *fmt, char *s)
{
	unsigned int	bitmask;
	int				len;

	len = 0;
	bitmask = (1 << 1) | (1 << 4) | (1 << 12) | (1 << 14) | (1 << 17);
	while (s[len] >= 32 && s[len] <= 48 && bitmask & (1 << (s[len] - 31)))
	{
		if (len > 5 || strchr(fmt->flags, s[len]))
			return (0);
		fmt->flags[len] = s[len];
		len++;
	}
	fmt->flags[len] = '\0';
	return (len);
}

void	ft_validate_flags(t_format *fmt)
{
	int	i;

	i = 0;
	fmt->isvalid = 1;
	while (fmt->flags[i])
	{
		if (fmt->spec == 'c' && !((VALID_CS) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		break ;
		i++;
	}
}

int	main(void)
{
	// t_format format = {.flags = "-", .spec = 'c'};
	// ft_validate_flags(&format);
	// printf("%d\n", format.isvalid);

	printf("|%d|\n", 42);     // |A|
	printf("|%-5d|\n", 42);   // |A    |
	printf("|%5d|\n", 42);    // |A    |
	printf("|%*d|\n", 5, 42); // |A    |
	printf("|%05d|\n", 42);   // |00042|
	// printf("|%-05d|\n", 42);   // error
	printf("|%+5d|\n", 42);   // error
	printf("|% 5d|\n", 42);   // error
	// printf("|%#5d|\n", 42);   // erorr
}



