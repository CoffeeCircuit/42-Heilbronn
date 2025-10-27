#include "ft_printf.h" // Make sure this header declares ft_printf
#include <stdio.h>

int	main(void)
{
	int ret_std, ret_ft;
	printf("=== %%c Tests ===\n");
	ret_std = printf("STD: [%5c]\n", 'A');
	ret_ft = ft_printf("FT : [%5c]\n", 'A');
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%-5c]\n", 'A');
	ret_ft = ft_printf("FT : [%-5c]\n", 'A');
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	printf("=== %%s Tests ===\n");
	ret_std = printf("STD: [%10s]\n", "Hello");
	ret_ft = ft_printf("FT : [%10s]\n", "Hello");
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%-10s]\n", "Hello");
	ret_ft = ft_printf("FT : [%-10s]\n", "Hello");
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%5s]\n", "");
	ret_ft = ft_printf("FT : [%5s]\n", "");
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	printf("=== %%d / %%i Tests ===\n");
	ret_std = printf("STD: [%5d]\n", 42);
	ret_ft = ft_printf("FT : [%5d]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%-5d]\n", 42);
	ret_ft = ft_printf("FT : [%-5d]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%05d]\n", 42);
	ret_ft = ft_printf("FT : [%05d]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%+5d]\n", 42);
	ret_ft = ft_printf("FT : [%+5d]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [% 5d]\n", 42);
	ret_ft = ft_printf("FT : [% 5d]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%+05d]\n", 42);
	ret_ft = ft_printf("FT : [%+05d]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%+5d]\n", -42);
	ret_ft = ft_printf("FT : [%+5d]\n", -42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%05i]\n", -42);
	ret_ft = ft_printf("FT : [%05i]\n", -42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	printf("=== %%u Tests ===\n");
	ret_std = printf("STD: [%5u]\n", 42);
	ret_ft = ft_printf("FT : [%5u]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%-5u]\n", 42);
	ret_ft = ft_printf("FT : [%-5u]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%05u]\n", 42);
	ret_ft = ft_printf("FT : [%05u]\n", 42);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%5u]\n", 0);
	ret_ft = ft_printf("FT : [%5u]\n", 0);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	ret_std = printf("STD: [%5u]\n", 4294967295u);
	ret_ft = ft_printf("FT : [%5u]\n", 4294967295u);
	printf("Return values → STD: %d, FT: %d\n\n", ret_std, ret_ft);
	return (0);
}
