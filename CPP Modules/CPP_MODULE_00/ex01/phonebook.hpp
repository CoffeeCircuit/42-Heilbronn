/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 23:50:27 by abalcu            #+#    #+#             */
/*   Updated: 2026/03/16 03:01:24 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H
# define MAX_ENTRIES 8
# define MAX_FIELD_LEN 10
# include <string>
# include <iostream>
# include <iomanip>

struct Contact
{
	std::string	first_name;
	std::string	last_name;
	std::string	nickname;
	int			phone_nbr;
	std::string	darkest_secret;
};


class PhoneBook
{
private:
	Contact	entries[MAX_ENTRIES];
	int id = -1;
	
public:
	PhoneBook() = default;
	~PhoneBook() = default;
	int add();
	int search();
};


int str_to_upper(const std::string &str);

#endif
