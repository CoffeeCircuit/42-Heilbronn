/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 23:49:56 by abalcu            #+#    #+#             */
/*   Updated: 2026/03/15 23:50:16 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <string>

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}

	std::string msgs = argv[1]; 
	
	for (int i = 2; i < argc; i++)
		msgs += argv[i];
	
	// std::transform(msgs.begin(), msgs.end(), msgs.begin(),
	// 	[](unsigned int c) { return (std::toupper(c)); });
	

	// alternative 
	for (char &c : msgs)
		c = std::toupper(static_cast<unsigned char>(c));
	

	std::cout << msgs << std::endl;
}
