/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 08:29:31 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/16 01:03:04 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/// @brief Checks if char c is a ASCII chararcher [A-Za-z]
/// @param c a character
/// @return Returns 1 if true and 0 if false
int					ft_isalpha(int c);

/// @brief Checks if the character c is in the range [0-9]
/// @param c a character
/// @return Returns 1 if true and 0 if false
int					ft_isdigit(int c);

/// @brief Checks if the character c is alphanumeric, ie [A-Za-z0-9]
/// @param c a character
/// @return Returns 1 if true and 0 if false
int					ft_isalnum(int c);

/// @brief Checks if the byte c is in ASCII range, i.e. [0-127]
/// @param c a character
/// @return Returns 1 if true and 0 if false
int					ft_isascii(int c);

/// @brief Checks if the character c is printable, i.e. range [32-126],
/// this includes space
/// @param c a character
/// @return Returns 1 if true and 0 if false
int					ft_isprint(int c);

/// @brief Calculates the length of the string pointed to by s,
/// excluding the terminating null byte ('\0')
/// @param s the string
/// @return String length or zero if s is NULL
size_t				ft_strlen(const char *s);

/// @brief Fills the first 'n' bytes of the memory area pointed to by 's'
/// with the constant byte 'c'.
/// @param s destination string
/// @param c fill character
/// @param n number of bites
/// @return Returns a pointer to the memory area s.
void				*ft_memset(void *s, int c, size_t n);

/// @brief Writes zeros ('\0') 'n' times at the starting location pointed to
/// by 's'
/// @param s start of memory location
/// @param n number of zero bytes ('\0') to write
void				ft_bzero(void *s, size_t n);

/// @brief Copies 'n' bytes from 'src' to 'dest'.
/// The memory areas must not overlap. In case of overlap use memmove
/// @param dest destination of bytes from 'src'
/// @param src source to be copied from
/// @param n number ot bytes to copy
/// @return Returns a pointer to 'dest'.
void				*ft_memcpy(void *dest, const void *src, size_t n);

/// @brief Copies 'n' bytes from 'src' to 'dest'. Memory overlaping is allowed
/// @param dest destination of bytes from 'src'
/// @param src source to be copied from
/// @param n number ot bytes to copy
/// @return Returns a pointer to 'dest'.
void				*ft_memmove(void *dest, const void *src, size_t n);

/// @brief Copies up to size - 1 characters from the NUL-terminated string
/// 'src' to dst, NUL-terminating the result
/// @param dst destination string
/// @param src source string
/// @param size the number of bytes to copy
/// @return The length of 'src'
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

/// @brief Cappends the NUL-terminated string 'src' to the end of 'dst'.
/// @param dst destination string
/// @param src source string
/// @param size the number of bytes to copy
/// @return The initial length of dst plus the length of src
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/// @brief Converts a character to uppercase
/// @param c the character
/// @return The uppercase of 'c' or 'c' if conversion fails
int					ft_toupper(int c);

/// @brief Converts a character to lowercase
/// @param c the character
/// @return The lowercase of 'c' or 'c' if conversion fails
int					ft_tolower(int c);

/// @brief Returns a pointer to the FIRST occurrence of the character 'c'
/// in the string 's'. For LAST use ft_strrchr()
/// @param s the search string
/// @param c the comparator
/// @return Position of FIRST occurence of 'c' in 's' or NULL if 'c' not found
char				*ft_strchr(const char *s, int c);

/// @brief Returns a pointer to the LAST occurrence of the character 'c'
/// in the string 's'.
/// @param s the search string
/// @param c the comparator
/// @return Position of LAST occurence of 'c' in 's' or NULL if 'c' not found
char				*ft_strrchr(const char *s, int c);

/// @brief Compares n-bytes between 's1' and 's2
/// @param s1 a string to be compared
/// @param s2 a string to compare to
/// @param n number of bytes to compare
/// @return Returns zero if the strings are identical or the difference between
/// 's1' and 's2' if the stirngs are different
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/// @brief Scans 'n' bytes of the memory pointed to by 's' for the
/// first instance of 'c'
/// @param s the string to be scaned
/// @param c comparator character (unsigned char)
/// @param n numer of bytes scaned in 's'
/// @return Return a pointer to the matching byte or NULL if the character
/// does not occur in the given memory area
void				*ft_memchr(const void *s, int c, size_t n);

/// @brief Compares the first 'n' bytes of the memory areas s1 and s2.
/// @param s1 memory area
/// @param s2 memory area
/// @param n number of bytes to compare
/// @return An int < 0 if s1 < s2 or 0 if s1 == s2 or > 0 if s1 > s2
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/// @brief Finds the first occurrence of 'little' string in the 'big' string
/// @param big the string to search in
/// @param little the searched string
/// @param len the number of characters to search
/// @return Returns 'big' if 'little' is empty or NULL if 'little' is not
/// found in 'big' or pointer to location where 'little' starts in 'big'
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

/// @brief Returns the int for a given string containing only numbers
/// @param nptr the string representing an int
/// @return An int specified in text
int					ft_atoi(const char *nptr);

/// @brief Allocates new memory on the heap, and fills the area with zero
/// @param nmemb number of elements
/// @param size size of each element
/// @return A newly allocated region of memory and fills the area with zeros
void				*ft_calloc(size_t nmemb, size_t size);

/// @brief Makes a duplicate of the given string
/// @param s the orginial string
/// @return A newly MALLOC'd string that can be freed with 'free()' or NULL if
/// allocation fails
char				*ft_strdup(const char *s);

/// @brief Returns a new string from 's' from a given starting position and
/// a given lenth
/// @param s the original string
/// @param start the starting position of 's' from which to make the substring
/// @param len the length of the substring
/// @return A newly MALLOC'd string that can be freed with 'free()' or NULL if
/// allocation fails
char				*ft_substr(char const *s, unsigned int start, size_t len);

/// @brief Concatenates two string, with 's2' appended to 's1'
/// @param s1 the prefix string
/// @param s2 the suffix string
/// @return A newly MALLOC'd string that can be freed with 'free()' or NULL if
/// allocation fails
char				*ft_strjoin(char const *s1, char const *s2);

/// @brief Returns a copy of ’s1’ with the characters from ’set’ removed
/// from the beginning and the end of 's1'
/// @param s1 string to be trimmed
/// @param set set of characters to trim front and back of 's1'
/// @return A newly MALLOC'd string that can be freed with 'free()' or NULL if
/// allocation fails
char				*ft_strtrim(char const *s1, char const *set);

/// @brief Creates an array of strings by splitting 's' by the character 'c'
/// @param s the string to be split
/// @param c the delimiter character
/// @return A newly MALLOC'd string that can be freed with 'free()' or NULL if
/// allocation fails
char				**ft_split(char const *s, char c);

/// @brief String representation of an int
/// @param n an integer
/// @return Returns a MALLOC-ed string representation of an int.
char				*ft_itoa(int n);

/// @brief Applies the function 'f()' to each character of the string 's',
/// @param s the source string
/// @param f function applied to each character of 's'
/// @return Returns a MALLOC-ed string with each character changed by 'f()'
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/// @brief Applies 'f()' to each character pf string 's'.
/// @param s the string to iterate over
/// @param f the function applied to each character. Where f(index, &s[index])
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/// @brief Outputs the character ’c’ to the specified file descriptor 'fd'.
/// @param c output character
/// @param fd The file descriptor on which to write.
void				ft_putchar_fd(char c, int fd);

/// @brief Outputs the string ’s’ to the specified file descriptor 'fd'.
/// @param s output string
/// @param fd The file descriptor on which to write.
void				ft_putstr_fd(char *s, int fd);

/// @brief Outputs the string ’s’ + '\n' to the specified file descriptor 'fd'.
/// @param s output string
/// @param fd The file descriptor on which to write.
void				ft_putendl_fd(char *s, int fd);

/// @brief Outputs the integer ’n’ to the specified file descriptor 'fd'.
/// @param n output integer
/// @param fd The file descriptor on which to write.
void				ft_putnbr_fd(int n, int fd);

/// @brief Allocates memory (MALLOC) for a new node.
/// @param content The content to store in the new node.
/// @return Returns a pointer to the new node.
t_list				*ft_lstnew(void *content);

/// @brief Adds the node ’new’ at the beginning of the list.
/// @param lst Adress of the first node of a list.
/// @param new Adress of the new node.
void				ft_lstadd_front(t_list **lst, t_list *new);

/// @brief Counts number of nodes in the list
/// @param lst The begining of the list
/// @return Size of the list
int					ft_lstsize(t_list *lst);

/// @brief Returns the last node of the list.
/// @param lst The begining of the list
/// @return Last node of the list
t_list				*ft_lstlast(t_list *lst);

/// @brief Adds the node ’new’ at the end of the list.
/// @param lst address of a pointer to the first node of a list.
/// @param new address of a pointer to the node to be added
void				ft_lstadd_back(t_list **lst, t_list *new);

/// @brief Deletes a node and it's content, but does not free the next node
/// @param lst the node to be freed
/// @param del the function used to free the content
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/// @brief Deletes and frees the given node and all its successors
/// @param lst a pointer to a node of the list
/// @param del the function used to free the content
void				ft_lstclear(t_list **lst, void (*del)(void *));

/// @brief Applies the function 'f' to the content of each node of the list
/// @param lst a pointer to a node of the list
/// @param f the function to be applied to the content of each node
void				ft_lstiter(t_list *lst, void (*f)(void *));

/// @brief Applies the function 'f' to the content of each node of the list
/// and returns a new list
/// @param lst the original list
/// @param f the function applied to the content
/// @param del the functions used to free the content in case allocation fails
/// @return A new MALLOC'd list. Points to the begining of the list
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
