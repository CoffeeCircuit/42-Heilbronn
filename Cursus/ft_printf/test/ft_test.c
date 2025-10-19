/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:47:27 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/19 10:58:34 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../ft_printf.h"
// #include "ft_test.h"

#include <stdio.h>

int	main(void)
{
    // Integer tests
    printf("Integer default            : [%d]\n", 42);
    printf("Integer with +             : [%+d]\n", 42);
    printf("Integer with space         : [% d]\n", 42);
    printf("Integer with 0             : [%010d]\n", 42);
    printf("Integer with -             : [%-10d]\n", 42);
    printf("Integer with + and 0       : [%+010d]\n", 42);
    printf("Integer with - and +       : [%-+10d]\n", 42);

    // Hexadecimal tests
    printf("Hex default                : [%x]\n", 255);
    printf("Hex with #                 : [%#x]\n", 255);
    printf("Hex with 0                 : [%010x]\n", 255);
    printf("Hex with -                 : [%-10x]\n", 255);
    printf("Hex with # and 0           : [%#010x]\n", 255);

    // Character tests
    printf("Char default               : [%c]\n", 'A');
    printf("Char with width            : [%10c]\n", 'A');
    printf("Char with -                : [%-10c]\n", 'A');

    // String tests
    printf("String default             : [%s]\n", "Hi");
    printf("String with -              : [%-10s]\n", "Hi");



}
