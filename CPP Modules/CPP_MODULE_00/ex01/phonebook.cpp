/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:00:07 by abalcu            #+#    #+#             */
/*   Updated: 2026/03/16 03:02:01 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"


std::string prompt(const std::string &msg)
{
	char buf[1024]{0};
	std::string input;

	std::cout << msg << ": ";
	std::cin.getline(buf, sizeof(buf));
	input = buf;
	while (!input.length())
	{
		std::cout << "Empty field not allowed\n";
		std::cout << msg << ": ";
		std::cin.getline(buf, sizeof(buf));
		input = buf;
	}
	return (input);
}

std::string truncate(const std::string &s)
{
	std::string out;

	if (s.length() > MAX_FIELD_LEN)
	{
		out.assign(s, 0, MAX_FIELD_LEN - 1);
		out.append(".");
	}
	else
		out.assign(s);

	return (out);
}


int PhoneBook::add()
{
	Contact c;
	bool loop = true;
	
	if (id < MAX_ENTRIES) {id++;}
	c.first_name = prompt("Enter first name");
	c.last_name = prompt("Enter last name");
	c.nickname = prompt("Enter nickname");
	do 
	{		
		try {
			c.phone_nbr = std::stoi(prompt("Enter phone number"));
			loop = false;
		} catch (const std::exception& e) {
			std::cerr << "Not a valid int" << std::endl;
		}
	} while (loop);
	c.darkest_secret = prompt("Enter darkest secret");
	entries[id] = c;
	return (0);
}

int PhoneBook::search()
{
	if (id >= 0)
	{
		std::cout << std::right
				  << std::setw(10) << "ID" << '|'
				  << std::setw(10) << "First Name" << '|'
				  << std::setw(10) << "Last Name" << '|'
				  << std::setw(10) << "Nickname" << '|'
				  << std::endl;
	}
	else
		return (1);

	for (int i = 0; i <= id; i++)
	{
		std::cout << std::setw(10) << i << '|'
				  << std::setw(10) << truncate(entries[i].first_name) << '|'
				  << std::setw(10) << truncate(entries[i].last_name) << '|'
				  << std::setw(10) << truncate(entries[i].nickname) << '|'
				  << std::endl;
	}
	return (0);
}

int str_to_upper(std::string &str)
{
	int count;

	count = 0;
	for (char &c : str)
	{
		c = std::toupper(c);
		count++;
	}
	return (count);
}

int main()
{
	std::string input;
	PhoneBook phonebook;

	while (true)
	{
		std::cout << "Phone Book > ";
		std::cin >> input;
		str_to_upper(input);
		if (std::cin.eof() || std::cin.fail())
		{
			std::cout << "\nExiting.\n";
        	break;
		}
		else if (input == "EXIT")
			break;
		else if (input == "ADD")
		{
			std::cin.ignore();
			phonebook.add();
		}
		else if (input == "SEARCH")
		{
			std::cin.ignore();
			if (phonebook.search() != 0)
				std::cout << "No entries" << std::endl;
		}		
		else
			std::cout << "Unknown command: " << input << std::endl;
	}

	return (EXIT_SUCCESS);
}
